#ifndef __CALL_DATA_H__
#define __CALL_DATA_H__

#include <memory>
#include <typeinfo>
#include <grpc++/grpc++.h>
#include <avthumb.pb.h>
#include <avthumb.grpc.pb.h>

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

#endif
