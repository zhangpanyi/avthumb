#include "queue.h"

#include "worker.h"
#include "service.h"
#include "thread_pool.h"
#include <avthumb.pb.h>

Queue::Queue(ThreadPool &pool)
    : pool_(pool)
{
}

// 获取完成集合
std::unordered_set<uint32_t> Queue::get_completed() const
{
    std::lock_guard<std::mutex> lock(mutex_);
    std::unordered_set<uint32_t> completed_set;
    for (auto iter = responses_.begin(); iter != responses_.end(); ++iter)
    {
        completed_set.insert(iter->first);
    }
    return completed_set;
}

// 获取任务结果
bool Queue::get_task_result(uint32_t task_id, Result *out_result)
{
    assert(out_result != nullptr);
    if (out_result == nullptr)
    {
        return false;
    }

    std::lock_guard<std::mutex> lock(mutex_);
    auto iter = responses_.find(task_id);
    if (iter == responses_.end())
    {
        return false;
    }
    *out_result = iter->second;
    responses_.erase(iter);
    return true;
}

// 添加任务到队列
void Queue::add_task_to_queue(uint32_t task_id, std::shared_ptr<google::protobuf::Message> message)
{
    pool_.append([=]() {
        Worker worker(task_id);
        auto result = worker(message);
        result.task_id = task_id;
        std::lock_guard<std::mutex> lock(mutex_);
        responses_.insert(std::make_pair(task_id, result));
    });
}
