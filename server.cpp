/*
* Copyright NNext Co. and/or licensed to NNext Co.
* @author [Peter. Njenga]
*
* This file and its contents are licensed under the NNext License.
* Please see the included NOTICE for copyright information and
* LICENSE for a copy of the license.
*/


//Standard Libraries
#include <iostream>
#include <memory>
#include <string>
#include <stdio.h>
#include <random>
#include <assert.h>
#include <unordered_map>
#include <tuple>

// External Libraries
#include <google/protobuf/map.h>
#include <fmt/core.h>
#include <spdlog/spdlog.h>
#include <grpcpp/grpcpp.h>
#include <faiss/IndexFlat.h>
#include <faiss/IndexHNSW.h>
#include <faiss/MetricType.h>
#include <faiss/IndexNNDescent.h>
#include <rocksdb/db.h>
#include <argparse/argparse.hpp>

// Internal Libraries
#include "server.h"
#include "util.h"
#include "protos/main.grpc.pb.h"

using nnext::NNext;
using namespace std;
/*
* TODO Move to utils.
*/

/*
***********************************************************************************************************************
*/

void NNextServiceImpl::_init() {
 /** Read the indices persisted to disk and return them.
  *
  * Use an open RockDB connection to read from Disk serialized index parameters.
  *
  * @param rocksdb: Connected RocksDB instance.
  */
 std::string value;
 rocksdb::Status db_status;

 if (p__index_list_pb == nullptr) {
   spdlog::warn("Null pointer passed. Initializing.");
   p__index_list_pb = std::make_shared<nnext::IndexList>();
 }

 // Read from rocks DB.
 db_status = _rocksdb->Get(rocksdb::ReadOptions(), "indices", &value);

 if (!db_status.ok())
   spdlog::error("RocksDB error: {}", db_status.ToString());

 p__index_list_pb->ParseFromString(value);
 spdlog::info("Loaded {} indices from disk.", p__index_list_pb->indices_size());

 std::string vector_list_key;

 for (int i = 0; i < p__index_list_pb->indices_size(); i++) {
   const nnext::Index &pb__index = p__index_list_pb->indices(i);
   const int dims = pb__index.dims();
   const std::string index_name = pb__index.name();

   spdlog::debug("Reconstructing index [name={}, dims={} schema={}]",
                 index_name,
                 dims,
                 pb__index.schema().DebugString());

   /*
    * read index vectors from disk.
    */
   vector_list_key = fmt::format("index__{}__vectors]", index_name);

   spdlog::debug("Reading index vectors from RocksDB disk [key={}]", vector_list_key);
   db_status = _rocksdb->Get(rocksdb::ReadOptions(), vector_list_key, &value);

   if (!db_status.ok())
     spdlog::error("RocksDB error {}", db_status.ToString());

   auto pb__vector_list = std::make_shared<nnext::VectorList>();
   pb__vector_list_map[index_name] = pb__vector_list;

   /*
    * Deserialize the vectors using gRPC protobufs. Serialization/deserialization is a tricky operation that has
    * lots of edge-case depending on the system (OS, architecture, mood of the gods e.t.c). Use gRPC it to handle
    * the nitty gritty.
    */
   pb__vector_list->ParseFromString(value);
   spdlog::debug("Loaded vectors from disk [index.name={} nvectors={}]",
                 index_name,
                 pb__vector_list->rptd__vector_size());

   /*
    * Create a new index to store the elements.
    * TODO These numbers are hardcoded. You can surely do better than this.
    */
   const int n = pb__vector_list->rptd__vector_size();
   const size_t nlist = 4; // Number of cluster centroids.
   int m_pq = 128;
   int M = 16; // Number of neighbors used in the graph. A larger M is more accurate but uses more memory
   std::vector<float> data_vec;

   /*
    * Create the approximated index and the storage (quantizer)
    */
   std::shared_ptr ptr__quantizer = std::make_shared<faiss::IndexFlat>(dims);
   std::shared_ptr curr_index = std::make_shared<faiss::IndexHNSW2Level>(ptr__quantizer.get(), nlist, m_pq, M);

   /*
    * Extract the vector data array
    */
   auto rptd__vector = pb__vector_list->mutable_rptd__vector();
   for (auto iter_rptd__vector = rptd__vector->begin(); iter_rptd__vector < rptd__vector->end(); iter_rptd__vector++) {
     auto rptd__element = iter_rptd__vector->rptd__element();
     data_vec.insert(data_vec.end(), rptd__element.begin(), rptd__element.end());
   }

   /*
    * Train the index 🎪🦭🐘🐅🤡 using 1/5th of the entire vector set as the training set.
    */
   const unsigned int n_train = (data_vec.size() / dims) * 0.20;

   if (n_train > 300) {
     spdlog::info("Training [n_train={} index_name={}]", n_train, index_name);

     curr_index->train(n_train, &data_vec[0]);

     spdlog::info("Done training is_trained={} n_train={} index_name={}", curr_index->is_trained, n_train, index_name);
   } else {
     spdlog::info("Skipped training. Not enough examples (<= 300)");
   }


   /*
    * Add the ANN index and quantizer into the map.
    */
   index_map.insert(std::make_pair(index_name, curr_index));
   storage_map.insert(std::make_pair(index_name, ptr__quantizer));

   /*
    * Add the elements to the index. Note we can directly access the underlying float array pointer from the std::vector
    * since vector elements are guaranteed to be contiguous.
    */

   if (data_vec.size() > 5000) {
     spdlog::debug("Adding vectors to index [name={}]", index_name);
     curr_index->add(n, &data_vec[0]);

     spdlog::info("Added data to index [name={} ntotal={} is_trained={}]",
                  index_name,
                  curr_index->ntotal,
                  curr_index->is_trained);
   } else {
     spdlog::info("Adding data to flat index [name={}]", index_name);
     ptr__quantizer->add(n, &data_vec[0]);
   }
 }
}

grpc::Status NNextServiceImpl::GetIndex(grpc::ServerContext *p_context,
                                       const nnext::Index *p_request,
                                       nnext::Index *p_response) {
 std::string index_name = p_request->name();
 std::string log_msg;

 /*
  * First check that the index is actually contained in the map.
  */
 if (!index_map.contains(index_name)) {
   log_msg = fmt::format("⚠️  Index does not exist [name={}]", index_name);
   spdlog::error(log_msg);
   return grpc::Status(grpc::StatusCode::NOT_FOUND, log_msg);
 }

 /*
  * Get the index and set the properties of the Index Proto
  */
 auto index = index_map[index_name];
 p_response->set_name(index_name);
 p_response->set_dims(index->d);
 p_response->set_ntotal(index->ntotal);
 p_response->set_is_trained(index->is_trained);

 /*
  * Format a nice message to print out and return to the user.
  */
 log_msg = fmt::format("🎣 Retrieved Index. [name={} d={}, metric_type={} ntotal={}]",
                       index_name,
                       index->d,
                       index->metric_type,
                       index->ntotal);
 spdlog::info(log_msg);

 return grpc::Status(grpc::StatusCode::OK, log_msg);
}

grpc::Status NNextServiceImpl::ListIndices(grpc::ServerContext *p_context,
                                          const nnext::ListIndicesRequest *p_request,
                                          nnext::ListIndicesResponse *p_response) {

 std::string log_msg;
 auto _indices_pb = p__index_list_pb->mutable_indices();

 /*
  * Copy over the index protobuf for return.
  * TODO (Peter) Implement result pagination.
  */
 for (auto iter = _indices_pb->begin(); iter < _indices_pb->end(); iter++) {
   nnext::Index *new_index = p_response->add_indices();
   new_index->set_name(iter->name());
   new_index->set_dims(iter->dims());
 }

 p_response->set_total(index_map.size());

 /*
  * Format a nice message and return to the user.
  */
 log_msg = fmt::format("Found {} indices", _indices_pb->size());
 spdlog::info(log_msg);

 return grpc::Status(grpc::StatusCode::OK, log_msg);
}

grpc::Status NNextServiceImpl::CreateIndex(grpc::ServerContext *p_context,
                                          const nnext::Index *p_request,
                                          nnext::Index *p_response) {

 std::string index_name = p_request->name();
 std::string log_msg;

 /*
  * First check that the index is actually contained in the map.
  */
 if (index_map.contains(index_name)) {
   log_msg = fmt::format("⚠️  Index already exists [name={}]", index_name);
   spdlog::error(log_msg);
   return grpc::Status(grpc::StatusCode::ALREADY_EXISTS, log_msg);
 }

 rocksdb::Status db_status;
 int dims = p_request->dims();

 /*
  * Create the FAISS index and add to the map of indices. Indices are keyed by their name.
  */
 faiss::IndexFlat quantizer(dims);
 const size_t nlist = 4; // Number of cluster centroids.
 int m_pq = 128;
 int M = 16; // Number of neighbors used in the graph. A larger M is more accurate but uses more memory
 std::vector<float> data_vec;

 std::shared_ptr curr_index = std::make_shared<faiss::IndexHNSW2Level>(&quantizer, nlist, m_pq, M);
 index_map[index_name] = curr_index;

 /*
  * Create the ProtoBuf index representation for later serialization.
  */
 nnext::Index *index_pb = p__index_list_pb->add_indices();
 index_pb->CopyFrom(*p_request);

 /*
  * Parse and validate the schema. Return an error if invalid.
  */
 try {
   auto parsed_schema = parse_index_schema(p_request->schema());
   index_pb->mutable_schema()->CopyFrom(parsed_schema);
 } catch (const std::invalid_argument &ia) {
   log_msg = fmt::format("Invalid argument: {}", ia.what());
   spdlog::error(log_msg);
   return grpc::Status(grpc::StatusCode::INTERNAL, log_msg);
 }

 /*
  * Serialize the IndexList Proto to string.
  */
 std::string index_list_pb_str;
 p__index_list_pb->SerializeToString(&index_list_pb_str);

 /*
  * Persist the PB to memory using RocksDB.
  */
 db_status = _rocksdb->Put(rocksdb::WriteOptions(), "indices", index_list_pb_str);
 if (!db_status.ok()) {
   log_msg = fmt::format("RocksDB error {}", db_status.ToString());
   spdlog::error("RocksDB error {}", db_status.ToString());
   return grpc::Status(grpc::StatusCode::INTERNAL, log_msg);
 }

 /*
  * Set the return Proto values for the newly created index.
  */
 p_response->CopyFrom(*index_pb);

 /*
  * Format a nice message to print out and return to the user.
  */
 log_msg = fmt::format("✨ Created Index. \n[index={}]", index_pb->DebugString());
 spdlog::info(log_msg);

 return grpc::Status(grpc::StatusCode::OK, log_msg);
}

grpc::Status NNextServiceImpl::DropIndex(grpc::ServerContext *p_context,
                                        const nnext::Index *p_request,
                                        nnext::Index *p_response) {
 rocksdb::Status db_status;
 bool found_index = false;
 std::string log_msg;
 std::string index_name = p_request->name();
 auto _indices_pb = p__index_list_pb->mutable_indices();

 /*
  * First check that the index is actually contained in the map.
  */
 if (!index_map.contains(index_name)) {
   log_msg = fmt::format("⚠️  Could not find index [name={}]", index_name);
   spdlog::error(log_msg);
   return grpc::Status(grpc::StatusCode::NOT_FOUND, log_msg);
 }

 /*
  * Find the index to be deleted from the protobuf and remove it.
  */
 for (int i = 0; i < _indices_pb->size(); i++) {
   nnext::Index _index = _indices_pb->at(i);

   if (_index.name() == index_name) {
     // Protobuf does not allow arbitrarily deleting elements and subsequent compacting.
     // Swap the element to be removed with the last one then pop it from the end of the list.
     _indices_pb->SwapElements(i, _indices_pb->size() - 1);
     _indices_pb->RemoveLast();
     spdlog::debug("Removed index from Protobuf list. [name={}, idx={}, size={}]", index_name, i, _indices_pb->size());
     found_index = true;
     break;
   }
 }

 /*
  * Check that the index was actually found in the protobuf. Return early with a NOT_FOUND status if not.
  */
 if (!found_index) {
   log_msg = fmt::format("⚠️  Could not find index [name={}]", index_name);
   spdlog::error(log_msg);
   return grpc::Status(grpc::StatusCode::NOT_FOUND, log_msg);
 }

 /*
  * Persist the index list protobuf to storage using RocksDB.
  */
 std::string index_list_pb_str;
 p__index_list_pb->SerializeToString(&index_list_pb_str);

 db_status = _rocksdb->Put(rocksdb::WriteOptions(), "indices", index_list_pb_str);
 if (!db_status.ok())
   spdlog::error("RocksDB error {}", db_status.ToString());

 /*
  * Populate the return object.
  */
 auto index = index_map[index_name];
 p_response->set_name(index_name);
 p_response->set_dims(index->d);
 p_response->set_ntotal(index->ntotal);
 p_response->set_is_trained(index->is_trained);

 /*
  * Remove the index from the index map.
  */
 index_map.erase(index_name);

 /*
  * Format a nice error message to return to the user.
  */
 log_msg = fmt::format("🗑 Dropped index. [name={}]", index_name);
 spdlog::info(log_msg);

 return grpc::Status(grpc::StatusCode::OK, log_msg);
}

/*
* Vector Methods
*/
grpc::Status NNextServiceImpl::VectorAdd(grpc::ServerContext *p_context,
                                        const nnext::VectorAddRequest *p_request,
                                        nnext::VectorAddResponse *p_response) {

 std::string index_name = p_request->index_name();
 std::string log_msg;

 /*
  * Check that the index exists and exit early if not.
  */
 if (index_map.count(index_name) < 1) {
   log_msg = fmt::format("⚠️  Could not find index [name={}]", index_name);
   spdlog::error(log_msg);
   return grpc::Status(grpc::StatusCode::NOT_FOUND, log_msg);
 }
 /*
  * TODO:
  * 1. Write vectors to disk.
  * 2. Load vectors from disk on restart.
  * 3. Bifurcate the vector storage engine. For n < 10,000 and d < 1024 use IndexFlat.
  */

 auto curr_index = index_map[index_name];
 const auto req_data = p_request->data();
 const int n = req_data.size();
 std::vector<float> data_vec;
 rocksdb::Status db_status;
// pk_type _pk_type;
// string _pk_name = "xxx";

 /*
  * Create and reserve the Vector List PB for later serialization in column-order to disk.
  */
 if (pb__vector_list_map.count(index_name) < 1) {
   pb__vector_list_map[index_name] = std::make_shared<nnext::VectorList>();
 }
 auto pb__vector_list = pb__vector_list_map[index_name];

 /*
  * Extract the vector data array
  */
 for (auto pb_data : req_data) {
//   auto _datum = Datum(pb_data, _pk_type, _pk_name);
   auto vector = pb_data.rptd__vector();
   data_vec.insert(data_vec.end(), vector.begin(), vector.end());

   //    std::string rocks_key = fmt::format("{}::{}", index_name, _datum.pk());
   //
   //    data_map[_datum.pk] = _datum;
   //
   //    std::cout << _datum.pk << std::endl;
   //
   //    db_status = _rocksdb->Put(rocksdb::WriteOptions(), rocks_key, datum.to_string());

   if (!db_status.ok()) {
     log_msg = fmt::format("RocksDB error {}", db_status.ToString());
     spdlog::error("RocksDB error {}", db_status.ToString());
     return grpc::Status(grpc::StatusCode::INTERNAL, log_msg);
   }

   /*
    * Construct the elements of the serializable Vector List.
    */
   nnext::Vector *pb__vector = pb__vector_list->add_rptd__vector();
   pb__vector->mutable_rptd__element()->Add(vector.begin(), vector.end());
 }

 /*
  * Serialize the IndexList Proto to string.
  */
 std::string str__vector_list;
 pb__vector_list->SerializeToString(&str__vector_list);

 /*
  * Persist the Vector List PB to memory using RocksDB.
  */
 std::string vector_list_key = fmt::format("index__{}__vectors]", index_name);

 spdlog::debug("Serializing vectors and persisting to disk [key={} size<bytes>={}]",
               vector_list_key,
               str__vector_list.size());
 db_status = _rocksdb->Put(rocksdb::WriteOptions(), vector_list_key, str__vector_list);

 if (!db_status.ok()) {
   log_msg = fmt::format("RocksDB error {}", db_status.ToString());
   spdlog::error("RocksDB error {}", db_status.ToString());
   return grpc::Status(grpc::StatusCode::INTERNAL, log_msg);
 }

 log_msg = fmt::format("Added data to index [name={} ntotal={} is_trained={}]",
                       index_name,
                       curr_index->ntotal,
                       curr_index->is_trained);
 spdlog::info(log_msg);

 /*
  * Train the index (if untrained). Useful for the first time that vectors are added to the index.
  */
 if (!curr_index->is_trained) {
   spdlog::debug("Training index {}", data_vec.size());
   curr_index->train(300, &data_vec[0]);
 }

 /*
  * Add the elements to the index. Note we can directly access the underlying float array pointer from the std::vector
  * since vector elements are guaranteed to be contiguous.
  */
 spdlog::debug("Adding to index [data_vec.size()={}]", data_vec.size());
 curr_index->add(n, &data_vec[0]);

 /*
  * Format a nice response message to return to the user.
  */
 log_msg = fmt::format("Added data to index [name={} ntotal={} is_trained={}]",
                       index_name,
                       curr_index->ntotal,
                       curr_index->is_trained);

 spdlog::info(log_msg);

 return grpc::Status(grpc::StatusCode::OK, log_msg);
}

grpc::Status NNextServiceImpl::VectorGet(grpc::ServerContext *p_context,
                                        const nnext::VectorGetRequest *p_request,
                                        nnext::VectorGetResponse *p_response) {

 std::string index_name = p_request->index_name();
 std::string log_msg;

 /*
  * Check that the index exists and exit early if not.
  */
 if (index_map.count(index_name) < 1) {
   log_msg = fmt::format("⚠️  Could not find index [name={}]", index_name);
   spdlog::error(log_msg);
   return grpc::Status(grpc::StatusCode::NOT_FOUND, log_msg);
 }
 //
 //  auto index = index_map->at(index_name);
 //  int n = data.size();
 //  const int dims = 768;
 //  auto x = p_request->data();
 //  float x_data[n * dims];
 //
 //
 //  float _data[dims * n];
 //
 //  for (int i = 0; i < n; i++) {
 //    const nnext::Vector q_vector = p_request->q_vectors(i);
 //    for (int j = 0; j < dims; j++) {
 //      query_data[dims * i + j] = q_vector.data(j);
 //    }
 //  }
 //
 //
 //  for (auto iter = data.begin(); iter < data.end(); iter++) {
 //    auto vector = iter->vector();
 //    index.add(vector.size(), vector.mutable_data());
 //  }
 //
 //  index.add(dims, _data);

 //  spdlog::debug("🔆🔆 {} {} {}", index.ntotal, index.is_trained, index_map->size());

 /*
  * Format a nice error message to return to the user.
  */
 //  log_msg = fmt::format("Added {} vectors to index. [name={}]", n, index_name);
 //  spdlog::info(log_msg);

 return grpc::Status(grpc::StatusCode::OK, log_msg);
}

grpc::Status NNextServiceImpl::VectorSearch(grpc::ServerContext *p_context,
                                           const nnext::VectorSearchRequest *p_request,
                                           nnext::VectorSearchResponse *p_response) {

 std::string index_name = p_request->index_name();
 std::string log_msg;

 /*
  * Check that the index exists and exit early it not.
  */
 if (index_map.count(index_name) < 1) {
   log_msg = fmt::format("⚠️  Could not find index [name={}]", index_name);
   spdlog::error(log_msg);
   return grpc::Status(grpc::StatusCode::NOT_FOUND, log_msg);
 }

 auto curr_index = index_map[index_name];
 const auto query_vectors = p_request->rptd_query_vector();
 const int n = query_vectors.size();
 const faiss::Index::idx_t k = p_request->k();
 std::vector<float> data_vec;
 std::vector<faiss::Index::idx_t> labels(k * n);
 rocksdb::Status db_status;

 /*
  * Extract the query vector data array
  */
 for (auto iter_qv = query_vectors.begin(); iter_qv < query_vectors.end(); iter_qv++) {
   auto vector = iter_qv->rptd__element();

   /*
    * Check that the dimensions match. Return error if not.
    */
   if (curr_index->d != vector.size()) {
     log_msg = fmt::format("❗️ Query vector size does not match index dims. [index.dims={} query.dims={}]",
                           curr_index->d,
                           vector.size());
     spdlog::error(log_msg);
     return grpc::Status(grpc::StatusCode::INVALID_ARGUMENT, log_msg);
   }
   data_vec.insert(data_vec.end(), vector.begin(), vector.end());
 }

 /*
  * Assign the labels of the k vectors closest to the query x.
  */
 log_msg = fmt::format("Querying nearest neighbor vectors. [k={} n={} omit_vector={} omit_metadata={}]",
                       k,
                       n,
                       p_request->omit_vector(),
                       p_request->omit_metadata());
 spdlog::info(log_msg);

 try {
   curr_index->assign(n, &data_vec[0], &labels[0], k);
 } catch (faiss::FaissException &ex) {
   spdlog::critical("FaissException: {}", ex.what());
 } catch (std::exception &ex) {
   spdlog::critical("std::exception: {}", ex.what());
 } catch (...) {
   std::exception_ptr p = std::current_exception();
   std::clog << (p ? p.__cxa_exception_type()->name() : "null") << std::endl;
 }

 for (int l : labels) {
   auto datum = p_response->add_rptd__datum();

   std::string _id = fmt::format("{}", l);
   datum->set_id(_id);
   std::cout << _id << std::endl;
 }

 for (int i = 0; i < n; i++) {
   for (int j = 0; j < k; j++) {
     std::cout << labels[i * k + j] << ",";
   }
   std::cout << std::endl;
 }

 p_response->set_ntotal(n);

 if (!p_request->omit_vector()) {
   log_msg = fmt::format("Extracting nearest vectors.");

   spdlog::info(log_msg);
 }

 if (!p_request->omit_metadata()) {
   log_msg = fmt::format("Retrieving metadata for nearest vectors.");

   spdlog::info(log_msg);
 }

 /*
* Format a nice response message to return to the user.
  */
 log_msg = fmt::format("Retrieved nearest neighbor vectors. [k={} n={} omit_vector={} omit_metadata={}]",
                       k,
                       n,
                       p_request->omit_vector(),
                       p_request->omit_metadata());

 spdlog::info(log_msg);

 return grpc::Status(grpc::StatusCode::OK, log_msg);
}