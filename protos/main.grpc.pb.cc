// Generated by the gRPC C++ plugin.
// If you make any local change, they will be lost.
// source: main.proto

#include "main.pb.h"
#include "main.grpc.pb.h"

#include <functional>
#include <grpcpp/impl/codegen/async_stream.h>
#include <grpcpp/impl/codegen/async_unary_call.h>
#include <grpcpp/impl/codegen/channel_interface.h>
#include <grpcpp/impl/codegen/client_unary_call.h>
#include <grpcpp/impl/codegen/client_callback.h>
#include <grpcpp/impl/codegen/message_allocator.h>
#include <grpcpp/impl/codegen/method_handler.h>
#include <grpcpp/impl/codegen/rpc_service_method.h>
#include <grpcpp/impl/codegen/server_callback.h>
#include <grpcpp/impl/codegen/server_callback_handlers.h>
#include <grpcpp/impl/codegen/server_context.h>
#include <grpcpp/impl/codegen/service_type.h>
#include <grpcpp/impl/codegen/sync_stream.h>
namespace nnext {

static const char* NNext_method_names[] = {
  "/nnext.NNext/CreateIndex",
  "/nnext.NNext/ListIndices",
  "/nnext.NNext/DropIndex",
  "/nnext.NNext/GetIndex",
  "/nnext.NNext/VectorAdd",
  "/nnext.NNext/VectorGet",
  "/nnext.NNext/VectorSearch",
  "/nnext.NNext/VectorDelete",
  "/nnext.NNext/VectorClear",
};

std::unique_ptr< NNext::Stub> NNext::NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options) {
  (void)options;
  std::unique_ptr< NNext::Stub> stub(new NNext::Stub(channel, options));
  return stub;
}

NNext::Stub::Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options)
  : channel_(channel), rpcmethod_CreateIndex_(NNext_method_names[0], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_ListIndices_(NNext_method_names[1], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_DropIndex_(NNext_method_names[2], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_GetIndex_(NNext_method_names[3], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_VectorAdd_(NNext_method_names[4], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_VectorGet_(NNext_method_names[5], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_VectorSearch_(NNext_method_names[6], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_VectorDelete_(NNext_method_names[7], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_VectorClear_(NNext_method_names[8], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  {}

::grpc::Status NNext::Stub::CreateIndex(::grpc::ClientContext* context, const ::nnext::Index& request, ::nnext::Index* response) {
  return ::grpc::internal::BlockingUnaryCall< ::nnext::Index, ::nnext::Index, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_CreateIndex_, context, request, response);
}

void NNext::Stub::async::CreateIndex(::grpc::ClientContext* context, const ::nnext::Index* request, ::nnext::Index* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::nnext::Index, ::nnext::Index, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_CreateIndex_, context, request, response, std::move(f));
}

void NNext::Stub::async::CreateIndex(::grpc::ClientContext* context, const ::nnext::Index* request, ::nnext::Index* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_CreateIndex_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::nnext::Index>* NNext::Stub::PrepareAsyncCreateIndexRaw(::grpc::ClientContext* context, const ::nnext::Index& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::nnext::Index, ::nnext::Index, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_CreateIndex_, context, request);
}

::grpc::ClientAsyncResponseReader< ::nnext::Index>* NNext::Stub::AsyncCreateIndexRaw(::grpc::ClientContext* context, const ::nnext::Index& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncCreateIndexRaw(context, request, cq);
  result->StartCall();
  return result;
}

::grpc::Status NNext::Stub::ListIndices(::grpc::ClientContext* context, const ::nnext::ListIndicesRequest& request, ::nnext::ListIndicesResponse* response) {
  return ::grpc::internal::BlockingUnaryCall< ::nnext::ListIndicesRequest, ::nnext::ListIndicesResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_ListIndices_, context, request, response);
}

void NNext::Stub::async::ListIndices(::grpc::ClientContext* context, const ::nnext::ListIndicesRequest* request, ::nnext::ListIndicesResponse* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::nnext::ListIndicesRequest, ::nnext::ListIndicesResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_ListIndices_, context, request, response, std::move(f));
}

void NNext::Stub::async::ListIndices(::grpc::ClientContext* context, const ::nnext::ListIndicesRequest* request, ::nnext::ListIndicesResponse* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_ListIndices_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::nnext::ListIndicesResponse>* NNext::Stub::PrepareAsyncListIndicesRaw(::grpc::ClientContext* context, const ::nnext::ListIndicesRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::nnext::ListIndicesResponse, ::nnext::ListIndicesRequest, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_ListIndices_, context, request);
}

::grpc::ClientAsyncResponseReader< ::nnext::ListIndicesResponse>* NNext::Stub::AsyncListIndicesRaw(::grpc::ClientContext* context, const ::nnext::ListIndicesRequest& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncListIndicesRaw(context, request, cq);
  result->StartCall();
  return result;
}

::grpc::Status NNext::Stub::DropIndex(::grpc::ClientContext* context, const ::nnext::Index& request, ::nnext::Index* response) {
  return ::grpc::internal::BlockingUnaryCall< ::nnext::Index, ::nnext::Index, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_DropIndex_, context, request, response);
}

void NNext::Stub::async::DropIndex(::grpc::ClientContext* context, const ::nnext::Index* request, ::nnext::Index* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::nnext::Index, ::nnext::Index, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_DropIndex_, context, request, response, std::move(f));
}

void NNext::Stub::async::DropIndex(::grpc::ClientContext* context, const ::nnext::Index* request, ::nnext::Index* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_DropIndex_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::nnext::Index>* NNext::Stub::PrepareAsyncDropIndexRaw(::grpc::ClientContext* context, const ::nnext::Index& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::nnext::Index, ::nnext::Index, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_DropIndex_, context, request);
}

::grpc::ClientAsyncResponseReader< ::nnext::Index>* NNext::Stub::AsyncDropIndexRaw(::grpc::ClientContext* context, const ::nnext::Index& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncDropIndexRaw(context, request, cq);
  result->StartCall();
  return result;
}

::grpc::Status NNext::Stub::GetIndex(::grpc::ClientContext* context, const ::nnext::Index& request, ::nnext::Index* response) {
  return ::grpc::internal::BlockingUnaryCall< ::nnext::Index, ::nnext::Index, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_GetIndex_, context, request, response);
}

void NNext::Stub::async::GetIndex(::grpc::ClientContext* context, const ::nnext::Index* request, ::nnext::Index* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::nnext::Index, ::nnext::Index, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_GetIndex_, context, request, response, std::move(f));
}

void NNext::Stub::async::GetIndex(::grpc::ClientContext* context, const ::nnext::Index* request, ::nnext::Index* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_GetIndex_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::nnext::Index>* NNext::Stub::PrepareAsyncGetIndexRaw(::grpc::ClientContext* context, const ::nnext::Index& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::nnext::Index, ::nnext::Index, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_GetIndex_, context, request);
}

::grpc::ClientAsyncResponseReader< ::nnext::Index>* NNext::Stub::AsyncGetIndexRaw(::grpc::ClientContext* context, const ::nnext::Index& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncGetIndexRaw(context, request, cq);
  result->StartCall();
  return result;
}

::grpc::Status NNext::Stub::VectorAdd(::grpc::ClientContext* context, const ::nnext::VectorAddRequest& request, ::nnext::VectorAddResponse* response) {
  return ::grpc::internal::BlockingUnaryCall< ::nnext::VectorAddRequest, ::nnext::VectorAddResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_VectorAdd_, context, request, response);
}

void NNext::Stub::async::VectorAdd(::grpc::ClientContext* context, const ::nnext::VectorAddRequest* request, ::nnext::VectorAddResponse* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::nnext::VectorAddRequest, ::nnext::VectorAddResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_VectorAdd_, context, request, response, std::move(f));
}

void NNext::Stub::async::VectorAdd(::grpc::ClientContext* context, const ::nnext::VectorAddRequest* request, ::nnext::VectorAddResponse* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_VectorAdd_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::nnext::VectorAddResponse>* NNext::Stub::PrepareAsyncVectorAddRaw(::grpc::ClientContext* context, const ::nnext::VectorAddRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::nnext::VectorAddResponse, ::nnext::VectorAddRequest, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_VectorAdd_, context, request);
}

::grpc::ClientAsyncResponseReader< ::nnext::VectorAddResponse>* NNext::Stub::AsyncVectorAddRaw(::grpc::ClientContext* context, const ::nnext::VectorAddRequest& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncVectorAddRaw(context, request, cq);
  result->StartCall();
  return result;
}

::grpc::Status NNext::Stub::VectorGet(::grpc::ClientContext* context, const ::nnext::VectorGetRequest& request, ::nnext::VectorGetResponse* response) {
  return ::grpc::internal::BlockingUnaryCall< ::nnext::VectorGetRequest, ::nnext::VectorGetResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_VectorGet_, context, request, response);
}

void NNext::Stub::async::VectorGet(::grpc::ClientContext* context, const ::nnext::VectorGetRequest* request, ::nnext::VectorGetResponse* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::nnext::VectorGetRequest, ::nnext::VectorGetResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_VectorGet_, context, request, response, std::move(f));
}

void NNext::Stub::async::VectorGet(::grpc::ClientContext* context, const ::nnext::VectorGetRequest* request, ::nnext::VectorGetResponse* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_VectorGet_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::nnext::VectorGetResponse>* NNext::Stub::PrepareAsyncVectorGetRaw(::grpc::ClientContext* context, const ::nnext::VectorGetRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::nnext::VectorGetResponse, ::nnext::VectorGetRequest, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_VectorGet_, context, request);
}

::grpc::ClientAsyncResponseReader< ::nnext::VectorGetResponse>* NNext::Stub::AsyncVectorGetRaw(::grpc::ClientContext* context, const ::nnext::VectorGetRequest& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncVectorGetRaw(context, request, cq);
  result->StartCall();
  return result;
}

::grpc::Status NNext::Stub::VectorSearch(::grpc::ClientContext* context, const ::nnext::VectorSearchRequest& request, ::nnext::VectorSearchResponse* response) {
  return ::grpc::internal::BlockingUnaryCall< ::nnext::VectorSearchRequest, ::nnext::VectorSearchResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_VectorSearch_, context, request, response);
}

void NNext::Stub::async::VectorSearch(::grpc::ClientContext* context, const ::nnext::VectorSearchRequest* request, ::nnext::VectorSearchResponse* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::nnext::VectorSearchRequest, ::nnext::VectorSearchResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_VectorSearch_, context, request, response, std::move(f));
}

void NNext::Stub::async::VectorSearch(::grpc::ClientContext* context, const ::nnext::VectorSearchRequest* request, ::nnext::VectorSearchResponse* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_VectorSearch_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::nnext::VectorSearchResponse>* NNext::Stub::PrepareAsyncVectorSearchRaw(::grpc::ClientContext* context, const ::nnext::VectorSearchRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::nnext::VectorSearchResponse, ::nnext::VectorSearchRequest, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_VectorSearch_, context, request);
}

::grpc::ClientAsyncResponseReader< ::nnext::VectorSearchResponse>* NNext::Stub::AsyncVectorSearchRaw(::grpc::ClientContext* context, const ::nnext::VectorSearchRequest& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncVectorSearchRaw(context, request, cq);
  result->StartCall();
  return result;
}

::grpc::Status NNext::Stub::VectorDelete(::grpc::ClientContext* context, const ::nnext::VectorDeleteRequest& request, ::nnext::VectorDeleteResponse* response) {
  return ::grpc::internal::BlockingUnaryCall< ::nnext::VectorDeleteRequest, ::nnext::VectorDeleteResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_VectorDelete_, context, request, response);
}

void NNext::Stub::async::VectorDelete(::grpc::ClientContext* context, const ::nnext::VectorDeleteRequest* request, ::nnext::VectorDeleteResponse* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::nnext::VectorDeleteRequest, ::nnext::VectorDeleteResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_VectorDelete_, context, request, response, std::move(f));
}

void NNext::Stub::async::VectorDelete(::grpc::ClientContext* context, const ::nnext::VectorDeleteRequest* request, ::nnext::VectorDeleteResponse* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_VectorDelete_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::nnext::VectorDeleteResponse>* NNext::Stub::PrepareAsyncVectorDeleteRaw(::grpc::ClientContext* context, const ::nnext::VectorDeleteRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::nnext::VectorDeleteResponse, ::nnext::VectorDeleteRequest, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_VectorDelete_, context, request);
}

::grpc::ClientAsyncResponseReader< ::nnext::VectorDeleteResponse>* NNext::Stub::AsyncVectorDeleteRaw(::grpc::ClientContext* context, const ::nnext::VectorDeleteRequest& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncVectorDeleteRaw(context, request, cq);
  result->StartCall();
  return result;
}

::grpc::Status NNext::Stub::VectorClear(::grpc::ClientContext* context, const ::nnext::VectorClearRequest& request, ::nnext::VectorClearResponse* response) {
  return ::grpc::internal::BlockingUnaryCall< ::nnext::VectorClearRequest, ::nnext::VectorClearResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_VectorClear_, context, request, response);
}

void NNext::Stub::async::VectorClear(::grpc::ClientContext* context, const ::nnext::VectorClearRequest* request, ::nnext::VectorClearResponse* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::nnext::VectorClearRequest, ::nnext::VectorClearResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_VectorClear_, context, request, response, std::move(f));
}

void NNext::Stub::async::VectorClear(::grpc::ClientContext* context, const ::nnext::VectorClearRequest* request, ::nnext::VectorClearResponse* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_VectorClear_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::nnext::VectorClearResponse>* NNext::Stub::PrepareAsyncVectorClearRaw(::grpc::ClientContext* context, const ::nnext::VectorClearRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::nnext::VectorClearResponse, ::nnext::VectorClearRequest, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_VectorClear_, context, request);
}

::grpc::ClientAsyncResponseReader< ::nnext::VectorClearResponse>* NNext::Stub::AsyncVectorClearRaw(::grpc::ClientContext* context, const ::nnext::VectorClearRequest& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncVectorClearRaw(context, request, cq);
  result->StartCall();
  return result;
}

NNext::Service::Service() {
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      NNext_method_names[0],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< NNext::Service, ::nnext::Index, ::nnext::Index, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](NNext::Service* service,
             ::grpc::ServerContext* ctx,
             const ::nnext::Index* req,
             ::nnext::Index* resp) {
               return service->CreateIndex(ctx, req, resp);
             }, this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      NNext_method_names[1],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< NNext::Service, ::nnext::ListIndicesRequest, ::nnext::ListIndicesResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](NNext::Service* service,
             ::grpc::ServerContext* ctx,
             const ::nnext::ListIndicesRequest* req,
             ::nnext::ListIndicesResponse* resp) {
               return service->ListIndices(ctx, req, resp);
             }, this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      NNext_method_names[2],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< NNext::Service, ::nnext::Index, ::nnext::Index, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](NNext::Service* service,
             ::grpc::ServerContext* ctx,
             const ::nnext::Index* req,
             ::nnext::Index* resp) {
               return service->DropIndex(ctx, req, resp);
             }, this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      NNext_method_names[3],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< NNext::Service, ::nnext::Index, ::nnext::Index, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](NNext::Service* service,
             ::grpc::ServerContext* ctx,
             const ::nnext::Index* req,
             ::nnext::Index* resp) {
               return service->GetIndex(ctx, req, resp);
             }, this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      NNext_method_names[4],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< NNext::Service, ::nnext::VectorAddRequest, ::nnext::VectorAddResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](NNext::Service* service,
             ::grpc::ServerContext* ctx,
             const ::nnext::VectorAddRequest* req,
             ::nnext::VectorAddResponse* resp) {
               return service->VectorAdd(ctx, req, resp);
             }, this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      NNext_method_names[5],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< NNext::Service, ::nnext::VectorGetRequest, ::nnext::VectorGetResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](NNext::Service* service,
             ::grpc::ServerContext* ctx,
             const ::nnext::VectorGetRequest* req,
             ::nnext::VectorGetResponse* resp) {
               return service->VectorGet(ctx, req, resp);
             }, this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      NNext_method_names[6],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< NNext::Service, ::nnext::VectorSearchRequest, ::nnext::VectorSearchResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](NNext::Service* service,
             ::grpc::ServerContext* ctx,
             const ::nnext::VectorSearchRequest* req,
             ::nnext::VectorSearchResponse* resp) {
               return service->VectorSearch(ctx, req, resp);
             }, this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      NNext_method_names[7],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< NNext::Service, ::nnext::VectorDeleteRequest, ::nnext::VectorDeleteResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](NNext::Service* service,
             ::grpc::ServerContext* ctx,
             const ::nnext::VectorDeleteRequest* req,
             ::nnext::VectorDeleteResponse* resp) {
               return service->VectorDelete(ctx, req, resp);
             }, this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      NNext_method_names[8],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< NNext::Service, ::nnext::VectorClearRequest, ::nnext::VectorClearResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](NNext::Service* service,
             ::grpc::ServerContext* ctx,
             const ::nnext::VectorClearRequest* req,
             ::nnext::VectorClearResponse* resp) {
               return service->VectorClear(ctx, req, resp);
             }, this)));
}

NNext::Service::~Service() {
}

::grpc::Status NNext::Service::CreateIndex(::grpc::ServerContext* context, const ::nnext::Index* request, ::nnext::Index* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status NNext::Service::ListIndices(::grpc::ServerContext* context, const ::nnext::ListIndicesRequest* request, ::nnext::ListIndicesResponse* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status NNext::Service::DropIndex(::grpc::ServerContext* context, const ::nnext::Index* request, ::nnext::Index* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status NNext::Service::GetIndex(::grpc::ServerContext* context, const ::nnext::Index* request, ::nnext::Index* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status NNext::Service::VectorAdd(::grpc::ServerContext* context, const ::nnext::VectorAddRequest* request, ::nnext::VectorAddResponse* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status NNext::Service::VectorGet(::grpc::ServerContext* context, const ::nnext::VectorGetRequest* request, ::nnext::VectorGetResponse* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status NNext::Service::VectorSearch(::grpc::ServerContext* context, const ::nnext::VectorSearchRequest* request, ::nnext::VectorSearchResponse* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status NNext::Service::VectorDelete(::grpc::ServerContext* context, const ::nnext::VectorDeleteRequest* request, ::nnext::VectorDeleteResponse* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status NNext::Service::VectorClear(::grpc::ServerContext* context, const ::nnext::VectorClearRequest* request, ::nnext::VectorClearResponse* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}


}  // namespace nnext
