#include "service.h"
#include "logger.h"

template <typename Request, typename Reply>
class CallData : public CallDataBase
{
public:
    typedef std::function<
        void(grpc::ServerContext*,
            Request*,
            grpc::ServerAsyncResponseWriter<Reply>*,
            void*)> Reader;

public:
    CallData(int tag, Service *service, Reader reader)
        : tag_(tag)
        , reader_(reader)
        , service_(service)
        , request_(std::make_shared<Request>())
        , responder_(&ctx_)
    {
        proceed();
    }

public:
    /**
     * 逻辑处理
     */
    virtual void proceed() override
    {
        if (status_ == CallStatus::CREATE)
        {
            // 读取操作请求
            status_ = CallStatus::RECEVICE;
            reader_(&ctx_, request_.get(), &responder_, this);
        }
        else if (status_ == CallStatus::RECEVICE)
        {
            // 添加任务到队列
            logger()->debug("Received request, {}", Request::descriptor()->full_name());
            service_->make_request(tag_);
            task_id_ = service_->add_task_to_queue(request_);
            status_ = CallStatus::PROCESS;
        }
        else if (status_ == CallStatus::PROCESS)
        {
            // 获取任务处理结果
            Result result;
            if (service_->get_task_result(task_id_, &result))
            {
                Reply *reply = dynamic_cast<Reply*>(result.message.get());
                assert(reply != nullptr);
                if (reply != nullptr)
                {
                    responder_.Finish(*reply, grpc::Status::OK, this);
                    status_ = CallStatus::FINISH;
                }
                else
                {
                    logger()->error("Wrong return result, {}", Request::descriptor()->full_name());
                    std::exit(-1);
                }
            }
            else
            {
                assert(false);
                logger()->error("Failed to get task result, {}", Request::descriptor()->full_name());
            }
        }
        else
        {
            assert(status_ == CallStatus::FINISH);
            logger()->debug("Finshed request, {}", Request::descriptor()->full_name());
        }
    }

private:
    int                                     tag_;
    grpc::ServerContext                     ctx_;
    Reader                                  reader_;
    Service*                                service_;
    std::shared_ptr<Request>                request_;
    grpc::ServerAsyncResponseWriter<Reply>  responder_;
};

enum RequestTag
{
    ResizeRequestTag,
    ConstraintRequestTag,
    CompressRequestTag,
    VideoPreviewRequestTag,
    AudioPreviewRequestTag,
};

Service::Service(ThreadPool &pool)
    : qps_(0)
    , tps_(0)
    , repeater_(pool)
    , sequeue_(0)
    , last_time_(std::chrono::steady_clock::now())
{
    avthumb::ResizeRequest::default_instance();
    avthumb::ConstraintRequest::default_instance();
    avthumb::VideoPreviewRequest::default_instance();
    avthumb::AudioPreviewRequest::default_instance();
    avthumb::CompressImageRequest::default_instance();
}

Service::~Service()
{
    if (server_ != nullptr)
    {
        server_->Shutdown();
    }

    if (queue_ != nullptr)
    {
        queue_->Shutdown();
    }
}

// 运行服务
void Service::run(const std::string &addr, uint16_t port)
{
    grpc::ServerBuilder builder;
    std::string server_address = addr + ":" + std::to_string(port);
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    builder.RegisterService(&service_);

    queue_ = builder.AddCompletionQueue();
    server_ = builder.BuildAndStart();
    logger()->info("Server listening on {}", server_address);

    loop();
}

// 获取任务结果
bool Service::get_task_result(uint32_t task_id, Result *out_result)
{
    return repeater_.get_task_result(task_id, out_result);
}

// 添加任务到队列
uint32_t Service::add_task_to_queue(std::shared_ptr<google::protobuf::Message> message)
{
    if (sequeue_ == std::numeric_limits<uint32_t>::max())
    {
        sequeue_ = 0;
    }
    uint32_t id = ++sequeue_;
    repeater_.add_task_to_queue(id, message);
    return id;
}

// 生成请求
void Service::make_request(int tag)
{
    switch (tag)
    {
        case ResizeRequestTag:
            make_resize_request();
            break;
        case ConstraintRequestTag:
            make_constraint_request();
            break;
        case CompressRequestTag:
            make_compress_request();
            break;
        case VideoPreviewRequestTag:
            make_viewpreview_request();
            break;
        case AudioPreviewRequestTag:
            make_audiopreview_request();
            break;
    }
}

// 生成Resize请求
void Service::make_resize_request()
{
    typedef avthumb::ResizeReply ResType;
    typedef avthumb::ResizeRequest ReqType;
    auto handle_read = [&](grpc::ServerContext *ctx, ReqType *req, grpc::ServerAsyncResponseWriter<ResType> *reply, void *tag) {
        service_.RequestResize(ctx, req, reply, queue_.get(), queue_.get(), tag);
    };
    auto request = std::make_shared<CallData<ReqType, ResType>>(ResizeRequestTag, this, handle_read);
    requests_.push_back(request);
}

// 生成Constraint请求
void Service::make_constraint_request()
{
    typedef avthumb::ConstraintReply ResType;
    typedef avthumb::ConstraintRequest ReqType;
    auto handle_read = [&](grpc::ServerContext *ctx, ReqType *req, grpc::ServerAsyncResponseWriter<ResType> *reply, void *tag) {
        service_.RequestConstraint(ctx, req, reply, queue_.get(), queue_.get(), tag);
    };
    auto request = std::make_shared<CallData<ReqType, ResType>>(ConstraintRequestTag, this, handle_read);
    requests_.push_back(request);
}

// 生成Compress请求
void Service::make_compress_request()
{
    typedef avthumb::CompressImageReply ResType;
    typedef avthumb::CompressImageRequest ReqType;
    auto handle_read = [&](grpc::ServerContext *ctx, ReqType *req, grpc::ServerAsyncResponseWriter<ResType> *reply, void *tag) {
        service_.RequestCompressImage(ctx, req, reply, queue_.get(), queue_.get(), tag);
    };
    auto request = std::make_shared<CallData<ReqType, ResType>>(CompressRequestTag, this, handle_read);
    requests_.push_back(request);
}

// 生成VideoPreview请求
void Service::make_viewpreview_request()
{
    typedef avthumb::VideoPreviewReply ResType;
    typedef avthumb::VideoPreviewRequest ReqType;
    auto handle_read = [&](grpc::ServerContext *ctx, ReqType *req, grpc::ServerAsyncResponseWriter<ResType> *reply, void *tag) {
        service_.RequestGetVideoPreview(ctx, req, reply, queue_.get(), queue_.get(), tag);
    };
    auto request = std::make_shared<CallData<ReqType, ResType>>(VideoPreviewRequestTag, this, handle_read);
    requests_.push_back(request);
}

// 生成audioPreview请求
void Service::make_audiopreview_request()
{
    typedef avthumb::AudioPreviewReply ResType;
    typedef avthumb::AudioPreviewRequest ReqType;
    auto handle_read = [&](grpc::ServerContext *ctx, ReqType *req, grpc::ServerAsyncResponseWriter<ResType> *reply, void *tag) {
        service_.RequestGetAudioPreview(ctx, req, reply, queue_.get(), queue_.get(), tag);
    };
    auto request = std::make_shared<CallData<ReqType, ResType>>(AudioPreviewRequestTag, this, handle_read);
    requests_.push_back(request);
}

// 事件循环
void Service::loop()
{
    // 接收消息事件
    make_resize_request();
    make_constraint_request();
    make_compress_request();
    make_viewpreview_request();
    make_audiopreview_request();

    // 进入事件循环
    while (true)
    {
        // 当前时间
        bool idle = true;
        auto start_time = std::chrono::steady_clock::now();

        // 获取事件
        bool ok = false;
        void *tag = nullptr;
        gpr_timespec deadline{ 0, 0, GPR_TIMESPAN };
        auto next_status = queue_->AsyncNext(&tag, &ok, deadline);
        assert(next_status != grpc::CompletionQueue::SHUTDOWN);

        // 事件循环
        auto completed_set = repeater_.get_completed();
        for (size_t i = 0; i < requests_.size();)
        {
            if (next_status == grpc::CompletionQueue::GOT_EVENT && tag == requests_[i].get())
            {
                requests_[i]->proceed();
                if (requests_[i]->status() != CallDataBase::CallStatus::FINISH)
                {
                    ++qps_;
                    ++i;
                }
                else
                {
                    ++tps_;
                    idle = false;
                    std::swap(requests_[i], requests_.back());
                    requests_.pop_back();
                }
            }
            else
            {
                if (requests_[i]->status() == CallDataBase::CallStatus::PROCESS)
                {
                    auto iter = completed_set.find(requests_[i]->task_id());
                    if (iter != completed_set.end())
                    {
                        idle = false;
                        completed_set.erase(iter);
                        requests_[i]->proceed();
                    }
                }
                ++i;
            }
        }

        // 清理数据
        Result result;
        for (auto iter = completed_set.begin(); iter != completed_set.end(); ++iter)
        {
            get_task_result(*iter, &result);
        }

        // 数据统计
        auto duration = std::chrono::steady_clock::now() - last_time_;
        if (std::chrono::duration_cast<std::chrono::seconds>(duration).count() >= 1)
        {
            if (tps_ > 0 || qps_ > 0)
            {
                logger()->info("Total, qps: {}, tps: {}", qps_, tps_);
                qps_ = 0;
                tps_ = 0;
                last_time_ = std::chrono::steady_clock::now();
            }
        }

        // 耗时统计
        duration = std::chrono::steady_clock::now() - start_time;
        auto count = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
        if (count >= 10)
        {
            logger()->warn("Loop dalay time: {} milliseconds", count);
        }

        // 空间休息
        if (idle)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }   
    }
}
