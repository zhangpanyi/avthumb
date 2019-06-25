#ifndef __REPEATER_H__
#define __REPEATER_H__

#include <mutex>
#include <cstdint>
#include <unordered_set>
#include <unordered_map>

#include "worker.h"

namespace google
{
    namespace protobuf
    {
        class Message;
    }
}

struct Result;
class ThreadPool;

class Queue
{
public:
    explicit Queue(ThreadPool &pool);

public:
    /**
     * 获取完成集合
     */
    std::unordered_set<uint32_t> get_completed() const;

    /**
     * 获取任务结果
     */
    bool get_task_result(uint32_t task_id, Result *out_result);

    /**
     * 添加任务到队列
     */
    void add_task_to_queue(uint32_t task_id, std::shared_ptr<google::protobuf::Message> message);

private:
    Queue(const Queue&) = delete;
    Queue& operator= (const Queue&) = delete;

private:
    ThreadPool&                             pool_;
    mutable std::mutex                      mutex_;
    std::unordered_map<uint32_t, Result>    responses_;
};

#endif
