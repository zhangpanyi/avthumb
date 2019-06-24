// Generated by the gRPC C++ plugin.
// If you make any local change, they will be lost.
// source: avthumb.proto
#ifndef GRPC_avthumb_2eproto__INCLUDED
#define GRPC_avthumb_2eproto__INCLUDED

#include "avthumb.pb.h"

#include <grpc++/impl/codegen/async_stream.h>
#include <grpc++/impl/codegen/async_unary_call.h>
#include <grpc++/impl/codegen/method_handler_impl.h>
#include <grpc++/impl/codegen/proto_utils.h>
#include <grpc++/impl/codegen/rpc_method.h>
#include <grpc++/impl/codegen/service_type.h>
#include <grpc++/impl/codegen/status.h>
#include <grpc++/impl/codegen/stub_options.h>
#include <grpc++/impl/codegen/sync_stream.h>

namespace grpc {
class CompletionQueue;
class Channel;
class RpcService;
class ServerCompletionQueue;
class ServerContext;
}  // namespace grpc

namespace avthumb {

// 定义媒体处理服务
class AVThumb final {
 public:
  static constexpr char const* service_full_name() {
    return "avthumb.AVThumb";
  }
  class StubInterface {
   public:
    virtual ~StubInterface() {}
    // Resize 重设图片大小
    virtual ::grpc::Status Resize(::grpc::ClientContext* context, const ::avthumb::ResizeRequest& request, ::avthumb::ResizeReply* response) = 0;
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::avthumb::ResizeReply>> AsyncResize(::grpc::ClientContext* context, const ::avthumb::ResizeRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::avthumb::ResizeReply>>(AsyncResizeRaw(context, request, cq));
    }
    // Constraint 约束图片尺寸
    virtual ::grpc::Status Constraint(::grpc::ClientContext* context, const ::avthumb::ConstraintRequest& request, ::avthumb::ConstraintReply* response) = 0;
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::avthumb::ConstraintReply>> AsyncConstraint(::grpc::ClientContext* context, const ::avthumb::ConstraintRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::avthumb::ConstraintReply>>(AsyncConstraintRaw(context, request, cq));
    }
    // CompressImage 压缩图片质量
    virtual ::grpc::Status CompressImage(::grpc::ClientContext* context, const ::avthumb::CompressImageRequest& request, ::avthumb::CompressImageReply* response) = 0;
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::avthumb::CompressImageReply>> AsyncCompressImage(::grpc::ClientContext* context, const ::avthumb::CompressImageRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::avthumb::CompressImageReply>>(AsyncCompressImageRaw(context, request, cq));
    }
    // GetVideoPreview 获取视频预览
    virtual ::grpc::Status GetVideoPreview(::grpc::ClientContext* context, const ::avthumb::VideoPreviewRequest& request, ::avthumb::VideoPreviewReply* response) = 0;
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::avthumb::VideoPreviewReply>> AsyncGetVideoPreview(::grpc::ClientContext* context, const ::avthumb::VideoPreviewRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::avthumb::VideoPreviewReply>>(AsyncGetVideoPreviewRaw(context, request, cq));
    }
    // GetAudioPreview 获取音频预览
    virtual ::grpc::Status GetAudioPreview(::grpc::ClientContext* context, const ::avthumb::AudioPreviewRequest& request, ::avthumb::AudioPreviewReply* response) = 0;
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::avthumb::AudioPreviewReply>> AsyncGetAudioPreview(::grpc::ClientContext* context, const ::avthumb::AudioPreviewRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::avthumb::AudioPreviewReply>>(AsyncGetAudioPreviewRaw(context, request, cq));
    }
  private:
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::avthumb::ResizeReply>* AsyncResizeRaw(::grpc::ClientContext* context, const ::avthumb::ResizeRequest& request, ::grpc::CompletionQueue* cq) = 0;
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::avthumb::ConstraintReply>* AsyncConstraintRaw(::grpc::ClientContext* context, const ::avthumb::ConstraintRequest& request, ::grpc::CompletionQueue* cq) = 0;
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::avthumb::CompressImageReply>* AsyncCompressImageRaw(::grpc::ClientContext* context, const ::avthumb::CompressImageRequest& request, ::grpc::CompletionQueue* cq) = 0;
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::avthumb::VideoPreviewReply>* AsyncGetVideoPreviewRaw(::grpc::ClientContext* context, const ::avthumb::VideoPreviewRequest& request, ::grpc::CompletionQueue* cq) = 0;
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::avthumb::AudioPreviewReply>* AsyncGetAudioPreviewRaw(::grpc::ClientContext* context, const ::avthumb::AudioPreviewRequest& request, ::grpc::CompletionQueue* cq) = 0;
  };
  class Stub final : public StubInterface {
   public:
    Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel);
    ::grpc::Status Resize(::grpc::ClientContext* context, const ::avthumb::ResizeRequest& request, ::avthumb::ResizeReply* response) override;
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::avthumb::ResizeReply>> AsyncResize(::grpc::ClientContext* context, const ::avthumb::ResizeRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::avthumb::ResizeReply>>(AsyncResizeRaw(context, request, cq));
    }
    ::grpc::Status Constraint(::grpc::ClientContext* context, const ::avthumb::ConstraintRequest& request, ::avthumb::ConstraintReply* response) override;
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::avthumb::ConstraintReply>> AsyncConstraint(::grpc::ClientContext* context, const ::avthumb::ConstraintRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::avthumb::ConstraintReply>>(AsyncConstraintRaw(context, request, cq));
    }
    ::grpc::Status CompressImage(::grpc::ClientContext* context, const ::avthumb::CompressImageRequest& request, ::avthumb::CompressImageReply* response) override;
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::avthumb::CompressImageReply>> AsyncCompressImage(::grpc::ClientContext* context, const ::avthumb::CompressImageRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::avthumb::CompressImageReply>>(AsyncCompressImageRaw(context, request, cq));
    }
    ::grpc::Status GetVideoPreview(::grpc::ClientContext* context, const ::avthumb::VideoPreviewRequest& request, ::avthumb::VideoPreviewReply* response) override;
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::avthumb::VideoPreviewReply>> AsyncGetVideoPreview(::grpc::ClientContext* context, const ::avthumb::VideoPreviewRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::avthumb::VideoPreviewReply>>(AsyncGetVideoPreviewRaw(context, request, cq));
    }
    ::grpc::Status GetAudioPreview(::grpc::ClientContext* context, const ::avthumb::AudioPreviewRequest& request, ::avthumb::AudioPreviewReply* response) override;
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::avthumb::AudioPreviewReply>> AsyncGetAudioPreview(::grpc::ClientContext* context, const ::avthumb::AudioPreviewRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::avthumb::AudioPreviewReply>>(AsyncGetAudioPreviewRaw(context, request, cq));
    }

   private:
    std::shared_ptr< ::grpc::ChannelInterface> channel_;
    ::grpc::ClientAsyncResponseReader< ::avthumb::ResizeReply>* AsyncResizeRaw(::grpc::ClientContext* context, const ::avthumb::ResizeRequest& request, ::grpc::CompletionQueue* cq) override;
    ::grpc::ClientAsyncResponseReader< ::avthumb::ConstraintReply>* AsyncConstraintRaw(::grpc::ClientContext* context, const ::avthumb::ConstraintRequest& request, ::grpc::CompletionQueue* cq) override;
    ::grpc::ClientAsyncResponseReader< ::avthumb::CompressImageReply>* AsyncCompressImageRaw(::grpc::ClientContext* context, const ::avthumb::CompressImageRequest& request, ::grpc::CompletionQueue* cq) override;
    ::grpc::ClientAsyncResponseReader< ::avthumb::VideoPreviewReply>* AsyncGetVideoPreviewRaw(::grpc::ClientContext* context, const ::avthumb::VideoPreviewRequest& request, ::grpc::CompletionQueue* cq) override;
    ::grpc::ClientAsyncResponseReader< ::avthumb::AudioPreviewReply>* AsyncGetAudioPreviewRaw(::grpc::ClientContext* context, const ::avthumb::AudioPreviewRequest& request, ::grpc::CompletionQueue* cq) override;
    const ::grpc::RpcMethod rpcmethod_Resize_;
    const ::grpc::RpcMethod rpcmethod_Constraint_;
    const ::grpc::RpcMethod rpcmethod_CompressImage_;
    const ::grpc::RpcMethod rpcmethod_GetVideoPreview_;
    const ::grpc::RpcMethod rpcmethod_GetAudioPreview_;
  };
  static std::unique_ptr<Stub> NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options = ::grpc::StubOptions());

  class Service : public ::grpc::Service {
   public:
    Service();
    virtual ~Service();
    // Resize 重设图片大小
    virtual ::grpc::Status Resize(::grpc::ServerContext* context, const ::avthumb::ResizeRequest* request, ::avthumb::ResizeReply* response);
    // Constraint 约束图片尺寸
    virtual ::grpc::Status Constraint(::grpc::ServerContext* context, const ::avthumb::ConstraintRequest* request, ::avthumb::ConstraintReply* response);
    // CompressImage 压缩图片质量
    virtual ::grpc::Status CompressImage(::grpc::ServerContext* context, const ::avthumb::CompressImageRequest* request, ::avthumb::CompressImageReply* response);
    // GetVideoPreview 获取视频预览
    virtual ::grpc::Status GetVideoPreview(::grpc::ServerContext* context, const ::avthumb::VideoPreviewRequest* request, ::avthumb::VideoPreviewReply* response);
    // GetAudioPreview 获取音频预览
    virtual ::grpc::Status GetAudioPreview(::grpc::ServerContext* context, const ::avthumb::AudioPreviewRequest* request, ::avthumb::AudioPreviewReply* response);
  };
  template <class BaseClass>
  class WithAsyncMethod_Resize : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service *service) {}
   public:
    WithAsyncMethod_Resize() {
      ::grpc::Service::MarkMethodAsync(0);
    }
    ~WithAsyncMethod_Resize() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status Resize(::grpc::ServerContext* context, const ::avthumb::ResizeRequest* request, ::avthumb::ResizeReply* response) final override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void RequestResize(::grpc::ServerContext* context, ::avthumb::ResizeRequest* request, ::grpc::ServerAsyncResponseWriter< ::avthumb::ResizeReply>* response, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncUnary(0, context, request, response, new_call_cq, notification_cq, tag);
    }
  };
  template <class BaseClass>
  class WithAsyncMethod_Constraint : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service *service) {}
   public:
    WithAsyncMethod_Constraint() {
      ::grpc::Service::MarkMethodAsync(1);
    }
    ~WithAsyncMethod_Constraint() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status Constraint(::grpc::ServerContext* context, const ::avthumb::ConstraintRequest* request, ::avthumb::ConstraintReply* response) final override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void RequestConstraint(::grpc::ServerContext* context, ::avthumb::ConstraintRequest* request, ::grpc::ServerAsyncResponseWriter< ::avthumb::ConstraintReply>* response, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncUnary(1, context, request, response, new_call_cq, notification_cq, tag);
    }
  };
  template <class BaseClass>
  class WithAsyncMethod_CompressImage : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service *service) {}
   public:
    WithAsyncMethod_CompressImage() {
      ::grpc::Service::MarkMethodAsync(2);
    }
    ~WithAsyncMethod_CompressImage() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status CompressImage(::grpc::ServerContext* context, const ::avthumb::CompressImageRequest* request, ::avthumb::CompressImageReply* response) final override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void RequestCompressImage(::grpc::ServerContext* context, ::avthumb::CompressImageRequest* request, ::grpc::ServerAsyncResponseWriter< ::avthumb::CompressImageReply>* response, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncUnary(2, context, request, response, new_call_cq, notification_cq, tag);
    }
  };
  template <class BaseClass>
  class WithAsyncMethod_GetVideoPreview : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service *service) {}
   public:
    WithAsyncMethod_GetVideoPreview() {
      ::grpc::Service::MarkMethodAsync(3);
    }
    ~WithAsyncMethod_GetVideoPreview() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status GetVideoPreview(::grpc::ServerContext* context, const ::avthumb::VideoPreviewRequest* request, ::avthumb::VideoPreviewReply* response) final override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void RequestGetVideoPreview(::grpc::ServerContext* context, ::avthumb::VideoPreviewRequest* request, ::grpc::ServerAsyncResponseWriter< ::avthumb::VideoPreviewReply>* response, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncUnary(3, context, request, response, new_call_cq, notification_cq, tag);
    }
  };
  template <class BaseClass>
  class WithAsyncMethod_GetAudioPreview : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service *service) {}
   public:
    WithAsyncMethod_GetAudioPreview() {
      ::grpc::Service::MarkMethodAsync(4);
    }
    ~WithAsyncMethod_GetAudioPreview() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status GetAudioPreview(::grpc::ServerContext* context, const ::avthumb::AudioPreviewRequest* request, ::avthumb::AudioPreviewReply* response) final override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void RequestGetAudioPreview(::grpc::ServerContext* context, ::avthumb::AudioPreviewRequest* request, ::grpc::ServerAsyncResponseWriter< ::avthumb::AudioPreviewReply>* response, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncUnary(4, context, request, response, new_call_cq, notification_cq, tag);
    }
  };
  typedef WithAsyncMethod_Resize<WithAsyncMethod_Constraint<WithAsyncMethod_CompressImage<WithAsyncMethod_GetVideoPreview<WithAsyncMethod_GetAudioPreview<Service > > > > > AsyncService;
  template <class BaseClass>
  class WithGenericMethod_Resize : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service *service) {}
   public:
    WithGenericMethod_Resize() {
      ::grpc::Service::MarkMethodGeneric(0);
    }
    ~WithGenericMethod_Resize() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status Resize(::grpc::ServerContext* context, const ::avthumb::ResizeRequest* request, ::avthumb::ResizeReply* response) final override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
  };
  template <class BaseClass>
  class WithGenericMethod_Constraint : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service *service) {}
   public:
    WithGenericMethod_Constraint() {
      ::grpc::Service::MarkMethodGeneric(1);
    }
    ~WithGenericMethod_Constraint() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status Constraint(::grpc::ServerContext* context, const ::avthumb::ConstraintRequest* request, ::avthumb::ConstraintReply* response) final override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
  };
  template <class BaseClass>
  class WithGenericMethod_CompressImage : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service *service) {}
   public:
    WithGenericMethod_CompressImage() {
      ::grpc::Service::MarkMethodGeneric(2);
    }
    ~WithGenericMethod_CompressImage() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status CompressImage(::grpc::ServerContext* context, const ::avthumb::CompressImageRequest* request, ::avthumb::CompressImageReply* response) final override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
  };
  template <class BaseClass>
  class WithGenericMethod_GetVideoPreview : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service *service) {}
   public:
    WithGenericMethod_GetVideoPreview() {
      ::grpc::Service::MarkMethodGeneric(3);
    }
    ~WithGenericMethod_GetVideoPreview() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status GetVideoPreview(::grpc::ServerContext* context, const ::avthumb::VideoPreviewRequest* request, ::avthumb::VideoPreviewReply* response) final override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
  };
  template <class BaseClass>
  class WithGenericMethod_GetAudioPreview : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service *service) {}
   public:
    WithGenericMethod_GetAudioPreview() {
      ::grpc::Service::MarkMethodGeneric(4);
    }
    ~WithGenericMethod_GetAudioPreview() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status GetAudioPreview(::grpc::ServerContext* context, const ::avthumb::AudioPreviewRequest* request, ::avthumb::AudioPreviewReply* response) final override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
  };
  template <class BaseClass>
  class WithStreamedUnaryMethod_Resize : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service *service) {}
   public:
    WithStreamedUnaryMethod_Resize() {
      ::grpc::Service::MarkMethodStreamed(0,
        new ::grpc::StreamedUnaryHandler< ::avthumb::ResizeRequest, ::avthumb::ResizeReply>(std::bind(&WithStreamedUnaryMethod_Resize<BaseClass>::StreamedResize, this, std::placeholders::_1, std::placeholders::_2)));
    }
    ~WithStreamedUnaryMethod_Resize() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable regular version of this method
    ::grpc::Status Resize(::grpc::ServerContext* context, const ::avthumb::ResizeRequest* request, ::avthumb::ResizeReply* response) final override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    // replace default version of method with streamed unary
    virtual ::grpc::Status StreamedResize(::grpc::ServerContext* context, ::grpc::ServerUnaryStreamer< ::avthumb::ResizeRequest,::avthumb::ResizeReply>* server_unary_streamer) = 0;
  };
  template <class BaseClass>
  class WithStreamedUnaryMethod_Constraint : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service *service) {}
   public:
    WithStreamedUnaryMethod_Constraint() {
      ::grpc::Service::MarkMethodStreamed(1,
        new ::grpc::StreamedUnaryHandler< ::avthumb::ConstraintRequest, ::avthumb::ConstraintReply>(std::bind(&WithStreamedUnaryMethod_Constraint<BaseClass>::StreamedConstraint, this, std::placeholders::_1, std::placeholders::_2)));
    }
    ~WithStreamedUnaryMethod_Constraint() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable regular version of this method
    ::grpc::Status Constraint(::grpc::ServerContext* context, const ::avthumb::ConstraintRequest* request, ::avthumb::ConstraintReply* response) final override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    // replace default version of method with streamed unary
    virtual ::grpc::Status StreamedConstraint(::grpc::ServerContext* context, ::grpc::ServerUnaryStreamer< ::avthumb::ConstraintRequest,::avthumb::ConstraintReply>* server_unary_streamer) = 0;
  };
  template <class BaseClass>
  class WithStreamedUnaryMethod_CompressImage : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service *service) {}
   public:
    WithStreamedUnaryMethod_CompressImage() {
      ::grpc::Service::MarkMethodStreamed(2,
        new ::grpc::StreamedUnaryHandler< ::avthumb::CompressImageRequest, ::avthumb::CompressImageReply>(std::bind(&WithStreamedUnaryMethod_CompressImage<BaseClass>::StreamedCompressImage, this, std::placeholders::_1, std::placeholders::_2)));
    }
    ~WithStreamedUnaryMethod_CompressImage() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable regular version of this method
    ::grpc::Status CompressImage(::grpc::ServerContext* context, const ::avthumb::CompressImageRequest* request, ::avthumb::CompressImageReply* response) final override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    // replace default version of method with streamed unary
    virtual ::grpc::Status StreamedCompressImage(::grpc::ServerContext* context, ::grpc::ServerUnaryStreamer< ::avthumb::CompressImageRequest,::avthumb::CompressImageReply>* server_unary_streamer) = 0;
  };
  template <class BaseClass>
  class WithStreamedUnaryMethod_GetVideoPreview : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service *service) {}
   public:
    WithStreamedUnaryMethod_GetVideoPreview() {
      ::grpc::Service::MarkMethodStreamed(3,
        new ::grpc::StreamedUnaryHandler< ::avthumb::VideoPreviewRequest, ::avthumb::VideoPreviewReply>(std::bind(&WithStreamedUnaryMethod_GetVideoPreview<BaseClass>::StreamedGetVideoPreview, this, std::placeholders::_1, std::placeholders::_2)));
    }
    ~WithStreamedUnaryMethod_GetVideoPreview() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable regular version of this method
    ::grpc::Status GetVideoPreview(::grpc::ServerContext* context, const ::avthumb::VideoPreviewRequest* request, ::avthumb::VideoPreviewReply* response) final override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    // replace default version of method with streamed unary
    virtual ::grpc::Status StreamedGetVideoPreview(::grpc::ServerContext* context, ::grpc::ServerUnaryStreamer< ::avthumb::VideoPreviewRequest,::avthumb::VideoPreviewReply>* server_unary_streamer) = 0;
  };
  template <class BaseClass>
  class WithStreamedUnaryMethod_GetAudioPreview : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service *service) {}
   public:
    WithStreamedUnaryMethod_GetAudioPreview() {
      ::grpc::Service::MarkMethodStreamed(4,
        new ::grpc::StreamedUnaryHandler< ::avthumb::AudioPreviewRequest, ::avthumb::AudioPreviewReply>(std::bind(&WithStreamedUnaryMethod_GetAudioPreview<BaseClass>::StreamedGetAudioPreview, this, std::placeholders::_1, std::placeholders::_2)));
    }
    ~WithStreamedUnaryMethod_GetAudioPreview() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable regular version of this method
    ::grpc::Status GetAudioPreview(::grpc::ServerContext* context, const ::avthumb::AudioPreviewRequest* request, ::avthumb::AudioPreviewReply* response) final override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    // replace default version of method with streamed unary
    virtual ::grpc::Status StreamedGetAudioPreview(::grpc::ServerContext* context, ::grpc::ServerUnaryStreamer< ::avthumb::AudioPreviewRequest,::avthumb::AudioPreviewReply>* server_unary_streamer) = 0;
  };
  typedef WithStreamedUnaryMethod_Resize<WithStreamedUnaryMethod_Constraint<WithStreamedUnaryMethod_CompressImage<WithStreamedUnaryMethod_GetVideoPreview<WithStreamedUnaryMethod_GetAudioPreview<Service > > > > > StreamedUnaryService;
  typedef Service SplitStreamedService;
  typedef WithStreamedUnaryMethod_Resize<WithStreamedUnaryMethod_Constraint<WithStreamedUnaryMethod_CompressImage<WithStreamedUnaryMethod_GetVideoPreview<WithStreamedUnaryMethod_GetAudioPreview<Service > > > > > StreamedService;
};

}  // namespace avthumb


#endif  // GRPC_avthumb_2eproto__INCLUDED