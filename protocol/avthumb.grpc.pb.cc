// Generated by the gRPC C++ plugin.
// If you make any local change, they will be lost.
// source: avthumb.proto

#include "avthumb.pb.h"
#include "avthumb.grpc.pb.h"

#include <grpc++/impl/codegen/async_stream.h>
#include <grpc++/impl/codegen/async_unary_call.h>
#include <grpc++/impl/codegen/channel_interface.h>
#include <grpc++/impl/codegen/client_unary_call.h>
#include <grpc++/impl/codegen/method_handler_impl.h>
#include <grpc++/impl/codegen/rpc_service_method.h>
#include <grpc++/impl/codegen/service_type.h>
#include <grpc++/impl/codegen/sync_stream.h>
namespace avthumb {

static const char* AVThumb_method_names[] = {
  "/avthumb.AVThumb/Resize",
  "/avthumb.AVThumb/Constraint",
  "/avthumb.AVThumb/CompressImage",
  "/avthumb.AVThumb/GetVideoPreview",
  "/avthumb.AVThumb/GetAudioPreview",
};

std::unique_ptr< AVThumb::Stub> AVThumb::NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options) {
  std::unique_ptr< AVThumb::Stub> stub(new AVThumb::Stub(channel));
  return stub;
}

AVThumb::Stub::Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel)
  : channel_(channel), rpcmethod_Resize_(AVThumb_method_names[0], ::grpc::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_Constraint_(AVThumb_method_names[1], ::grpc::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_CompressImage_(AVThumb_method_names[2], ::grpc::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_GetVideoPreview_(AVThumb_method_names[3], ::grpc::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_GetAudioPreview_(AVThumb_method_names[4], ::grpc::RpcMethod::NORMAL_RPC, channel)
  {}

::grpc::Status AVThumb::Stub::Resize(::grpc::ClientContext* context, const ::avthumb::ResizeRequest& request, ::avthumb::ResizeReply* response) {
  return ::grpc::BlockingUnaryCall(channel_.get(), rpcmethod_Resize_, context, request, response);
}

::grpc::ClientAsyncResponseReader< ::avthumb::ResizeReply>* AVThumb::Stub::AsyncResizeRaw(::grpc::ClientContext* context, const ::avthumb::ResizeRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::ClientAsyncResponseReader< ::avthumb::ResizeReply>::Create(channel_.get(), cq, rpcmethod_Resize_, context, request);
}

::grpc::Status AVThumb::Stub::Constraint(::grpc::ClientContext* context, const ::avthumb::ConstraintRequest& request, ::avthumb::ConstraintReply* response) {
  return ::grpc::BlockingUnaryCall(channel_.get(), rpcmethod_Constraint_, context, request, response);
}

::grpc::ClientAsyncResponseReader< ::avthumb::ConstraintReply>* AVThumb::Stub::AsyncConstraintRaw(::grpc::ClientContext* context, const ::avthumb::ConstraintRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::ClientAsyncResponseReader< ::avthumb::ConstraintReply>::Create(channel_.get(), cq, rpcmethod_Constraint_, context, request);
}

::grpc::Status AVThumb::Stub::CompressImage(::grpc::ClientContext* context, const ::avthumb::CompressImageRequest& request, ::avthumb::CompressImageReply* response) {
  return ::grpc::BlockingUnaryCall(channel_.get(), rpcmethod_CompressImage_, context, request, response);
}

::grpc::ClientAsyncResponseReader< ::avthumb::CompressImageReply>* AVThumb::Stub::AsyncCompressImageRaw(::grpc::ClientContext* context, const ::avthumb::CompressImageRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::ClientAsyncResponseReader< ::avthumb::CompressImageReply>::Create(channel_.get(), cq, rpcmethod_CompressImage_, context, request);
}

::grpc::Status AVThumb::Stub::GetVideoPreview(::grpc::ClientContext* context, const ::avthumb::VideoPreviewRequest& request, ::avthumb::VideoPreviewReply* response) {
  return ::grpc::BlockingUnaryCall(channel_.get(), rpcmethod_GetVideoPreview_, context, request, response);
}

::grpc::ClientAsyncResponseReader< ::avthumb::VideoPreviewReply>* AVThumb::Stub::AsyncGetVideoPreviewRaw(::grpc::ClientContext* context, const ::avthumb::VideoPreviewRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::ClientAsyncResponseReader< ::avthumb::VideoPreviewReply>::Create(channel_.get(), cq, rpcmethod_GetVideoPreview_, context, request);
}

::grpc::Status AVThumb::Stub::GetAudioPreview(::grpc::ClientContext* context, const ::avthumb::AudioPreviewRequest& request, ::avthumb::AudioPreviewReply* response) {
  return ::grpc::BlockingUnaryCall(channel_.get(), rpcmethod_GetAudioPreview_, context, request, response);
}

::grpc::ClientAsyncResponseReader< ::avthumb::AudioPreviewReply>* AVThumb::Stub::AsyncGetAudioPreviewRaw(::grpc::ClientContext* context, const ::avthumb::AudioPreviewRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::ClientAsyncResponseReader< ::avthumb::AudioPreviewReply>::Create(channel_.get(), cq, rpcmethod_GetAudioPreview_, context, request);
}

AVThumb::Service::Service() {
  AddMethod(new ::grpc::RpcServiceMethod(
      AVThumb_method_names[0],
      ::grpc::RpcMethod::NORMAL_RPC,
      new ::grpc::RpcMethodHandler< AVThumb::Service, ::avthumb::ResizeRequest, ::avthumb::ResizeReply>(
          std::mem_fn(&AVThumb::Service::Resize), this)));
  AddMethod(new ::grpc::RpcServiceMethod(
      AVThumb_method_names[1],
      ::grpc::RpcMethod::NORMAL_RPC,
      new ::grpc::RpcMethodHandler< AVThumb::Service, ::avthumb::ConstraintRequest, ::avthumb::ConstraintReply>(
          std::mem_fn(&AVThumb::Service::Constraint), this)));
  AddMethod(new ::grpc::RpcServiceMethod(
      AVThumb_method_names[2],
      ::grpc::RpcMethod::NORMAL_RPC,
      new ::grpc::RpcMethodHandler< AVThumb::Service, ::avthumb::CompressImageRequest, ::avthumb::CompressImageReply>(
          std::mem_fn(&AVThumb::Service::CompressImage), this)));
  AddMethod(new ::grpc::RpcServiceMethod(
      AVThumb_method_names[3],
      ::grpc::RpcMethod::NORMAL_RPC,
      new ::grpc::RpcMethodHandler< AVThumb::Service, ::avthumb::VideoPreviewRequest, ::avthumb::VideoPreviewReply>(
          std::mem_fn(&AVThumb::Service::GetVideoPreview), this)));
  AddMethod(new ::grpc::RpcServiceMethod(
      AVThumb_method_names[4],
      ::grpc::RpcMethod::NORMAL_RPC,
      new ::grpc::RpcMethodHandler< AVThumb::Service, ::avthumb::AudioPreviewRequest, ::avthumb::AudioPreviewReply>(
          std::mem_fn(&AVThumb::Service::GetAudioPreview), this)));
}

AVThumb::Service::~Service() {
}

::grpc::Status AVThumb::Service::Resize(::grpc::ServerContext* context, const ::avthumb::ResizeRequest* request, ::avthumb::ResizeReply* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status AVThumb::Service::Constraint(::grpc::ServerContext* context, const ::avthumb::ConstraintRequest* request, ::avthumb::ConstraintReply* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status AVThumb::Service::CompressImage(::grpc::ServerContext* context, const ::avthumb::CompressImageRequest* request, ::avthumb::CompressImageReply* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status AVThumb::Service::GetVideoPreview(::grpc::ServerContext* context, const ::avthumb::VideoPreviewRequest* request, ::avthumb::VideoPreviewReply* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status AVThumb::Service::GetAudioPreview(::grpc::ServerContext* context, const ::avthumb::AudioPreviewRequest* request, ::avthumb::AudioPreviewReply* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}


}  // namespace avthumb

