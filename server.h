//
// Created by Wakahiu Njenga on 4/7/22.
//

#ifndef NNEXT__SERVER_H_
#define NNEXT__SERVER_H_

/*
 * Copyright NNext Co. and/or licensed to NNext Co.
 * @author [Peter. Njenga]
 *
 * This file and its contents are licensed under the NNext License.
 * Please see the included NOTICE for copyright information and
 * LICENSE for a copy of the license.
 */

#pragma once

#include <google/protobuf/map.h>
#include <rocksdb/db.h>
#include <faiss/IndexHNSW.h>
#include <faiss/MetricType.h>
#include <faiss/IndexNNDescent.h>

#include "protos/main.grpc.pb.h"

using nnext::NNext;
using namespace std;

class IdMap {
public:
  std::unordered_map<long, std::string> id_map;
  std::unordered_map<std::string, long> inv_map;

  long get(std::string id) {
    return inv_map[id];
  }

  std::string get(long id) {
    return id_map[id];
  }
};

enum pk_type {
  _int, _string,
};

class PK {
public:
  int idx_int;
  unsigned int idx_uint;
  std::string idx_str;
  pk_type _pk_type;

  PK() {
  }

  PK(int id) {
    idx_int = id;
    _pk_type = pk_type::_int;
  }

  PK(std::string id) {
    idx_str = id;
    _pk_type = pk_type::_string;
  }

  bool operator==(const PK &other) const {
    bool pk_type_eq = _pk_type == other._pk_type;

    if (!pk_type_eq) return false;

    switch (_pk_type) {
    case _int: return idx_int == other.idx_int;
    case _string: return idx_str == other.idx_str;
    default: return false;
    }
  }

  std::size_t operator()(const PK &pk) const {

    std::size_t h;
    switch (pk._pk_type) {
    case _int:h = std::hash<int>()(pk.idx_int);
    case _string:h = std::hash<std::string>()(pk.idx_str);
    default:spdlog::error("Error in PK hash func");
    }

    return h;
  }
};



class Datum {
public:
  PK pk;
  string pk_name;
  nnext::Datum pb_data;

  Datum(nnext::Datum _datum, pk_type _pk_type, string _pk_name) {
    pb_data = _datum;
    pk_name = _pk_name;

    switch (_pk_type) {
    case _int:
      //        int val = _datum.HasField(_pk_name)._int32;
      //        pk = new PK(val);
      break;
    case _string:
      //        string val = _datum(_pk_name)._string;
      //        pk = new PK(val);
      break;
    default:spdlog::error("Error in PK hash func");
    }
  }

  string to_string() {
    string str_data;
    pb_data.SerializeToString(&str_data);
    return str_data;
  }

  bool operator==(const Datum &d) const {
    return pk == d.pk;
    /*
     * TODO
     * 1. Use xtensor to compare the vector arrays. https://xtensor.readthedocs.io/en/latest/numpy.html
     * 2. Compare the rest of the values
     */
  }
};

class PKHashFN {
  std::size_t operator()(const PK &pk) const {

    std::size_t h;
    switch (pk._pk_type) {
    case _int:h = std::hash<int>()(pk.idx_int);
    case _string:h = std::hash<std::string>()(pk.idx_str);
    default:spdlog::error("Error in PK hash func");
    }

    return h;
  }
};

class NNextServiceImpl final : public NNext::Service {

public:
  rocksdb::DB *_rocksdb;
  std::unordered_map<std::string, std::shared_ptr<faiss::IndexHNSW2Level>> index_map;
  std::unordered_map<std::string, std::shared_ptr<faiss::IndexFlat>> storage_map;
  std::unordered_map<std::string, IdMap> id_map;
  unordered_map<PK, Datum, PKHashFN> data_map;
  std::unordered_map<std::string, std::shared_ptr<nnext::VectorList>> pb__vector_list_map;
  std::shared_ptr<nnext::IndexList> p__index_list_pb;
  std::shared_ptr<nnext::IndexMap> pb_index_map;

  void _init();

  grpc::Status ListIndices(grpc::ServerContext *p_context,
                           const nnext::ListIndicesRequest *p_request,
                           nnext::ListIndicesResponse *p_response) override;

  grpc::Status CreateIndex(grpc::ServerContext *p_context,
                           const nnext::Index *p_request,
                           nnext::Index *p_response) override;

  grpc::Status DropIndex(grpc::ServerContext *p_context,
                         const nnext::Index *p_request,
                         nnext::Index *p_response) override;

  grpc::Status GetIndex(grpc::ServerContext *p_context,
                        const nnext::Index *p_request,
                        nnext::Index *p_response) override;

  grpc::Status VectorAdd(grpc::ServerContext *p_context,
                         const nnext::VectorAddRequest *p_request,
                         nnext::VectorAddResponse *p_response) override;

  grpc::Status VectorGet(grpc::ServerContext *p_context,
                         const nnext::VectorGetRequest *p_request,
                         nnext::VectorGetResponse *p_response) override;

  grpc::Status VectorSearch(grpc::ServerContext *p_context,
                            const nnext::VectorSearchRequest *p_request,
                            nnext::VectorSearchResponse *p_response);
};

#endif // NNEXT__SERVER_H_
