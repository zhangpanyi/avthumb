#ifndef __CALL_DATA_H__
#define __CALL_DATA_H__

#include <memory>
#include <typeinfo>
#include <grpc++/grpc++.h>
#include <avthumb.pb.h>
#include <avthumb.grpc.pb.h>

#include "logger.h"

class Service;

class CallDataBase : public std::enable_shared_from_this<CallDataBase>
{
public:
    enum class CallStatus
    {
        CREATE,
        RECEVICE,
        PROCESS,
        FINISH
    };

public:
    CallDataBase()
        : task_id_(0)
        , status_(CallStatus::CREATE)
    {
    }

public:
    /**
     * 获取任务id
     */
    uint32_t task_id() const
    {
        return task_id_;
    }

    /**
     * 获取状态
     */
    CallStatus status() const
    {
        return status_;
    }

public:
    /**
     * 逻辑处理
     */
    virtual void proceed() = 0;

private:
    CallDataBase(const CallDataBase&) = delete;
    CallDataBase& operator= (const CallDataBase&) = delete;

protected:
    uint32_t    task_id_;
    CallStatus  status_;
};

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
        , responder_(&ctx_)
        , request_(std::make_shared<Request>())
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
    std::shared_ptr<Request>                request_;
    Service*                                service_;
    grpc::ServerAsyncResponseWriter<Reply>  responder_;
};

#endif
