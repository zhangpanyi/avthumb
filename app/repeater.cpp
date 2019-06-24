#include "repeater.h"

#include "worker.h"
#include "service.h"
#include "thread_pool.h"
#include <avthumb.pb.h>

Repeater::Repeater(ThreadPool &pool)
    : pool_(pool)
{
}

// 获取完成集合
std::unordered_set<uint32_t> Repeater::get_completed() const
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
bool Repeater::get_task_result(uint32_t task_id, Result *out_result)
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
void Repeater::add_task_to_queue(uint32_t task_id, std::shared_ptr<google::protobuf::Message> message)
{
    pool_.append([=]() {
        Worker worker(task_id, *this);
        auto result = worker(message);
        result.task_id = task_id;
        std::lock_guard<std::mutex> lock(mutex_);
        responses_.insert(std::make_pair(task_id, result));
    });
}
