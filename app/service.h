#ifndef __SERVICE_H__
#define __SERVICE_H__

#include <chrono>
#include <vector>
#include <string>
#include <cstdint>
#include <unordered_map>
#include <grpc++/grpc++.h>
#include <avthumb.grpc.pb.h>
#include <google/protobuf/message.h>

#include "queue.h"
#include "call_data.h"

class Service
{
public:
    explicit Service(ThreadPool &pool);

    ~Service();

public:
    /**
     * 运行服务
     */
    void run(const std::string &addr, uint16_t port);

public:
    /**
     * 生成请求
     */
    void make_request(int tag);

    /**
     * 获取任务结果
     */
    bool get_task_result(uint32_t task_id, Result *out_result);

    /**
     * 添加任务到队列
     */
    uint32_t add_task_to_queue(std::shared_ptr<google::protobuf::Message> message);

private:
    /**
     * 生成Resize请求
     */
    void make_resize_request();

    /**
     * 生成Constraint请求
     */
    void make_constraint_request();

    /**
     * 生成Compress请求
     */
    void make_compress_request();

    /**
     * 生成VideoPreview请求
     */
    void make_viewpreview_request();

    /**
     * 生成AudioPreview请求
     */
    void make_audiopreview_request();

private:
    /**
     * 事件循环
     */
    void loop();

private:
    Service(const Service&) = delete;
    Service& operator= (const Service&) = delete;

private:
    uint32_t                                     qps_;
    uint32_t                                     tps_;
    Queue                                        queue_;
    uint32_t                                     sequeue_;
    avthumb::AVThumb::AsyncService               service_;
    std::unique_ptr<grpc::ServerCompletionQueue> co_queue_;
    std::unique_ptr<grpc::Server>                server_;
    std::vector<std::shared_ptr<CallDataBase>>   requests_;
    std::chrono::steady_clock::time_point        last_time_;
};

#endif // __SERVICE_H__
