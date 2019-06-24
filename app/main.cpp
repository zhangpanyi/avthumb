#include <vector>
#include <csignal>
#include <fstream>
#include <iostream>

#include "config.h"
#include "logger.h"
#include "avthumb.h"
#include "service.h"
#include "thread_pool.h"
#include "etcd_client_v3.h"

Config                          config; // 服务配置
std::unique_ptr<EtcdClientV3>   client; // etcd客户端

// 注销服务
void unregiser_service(int signal)
{
    if (signal != 0)
    {
        logger()->error("Received signal, {}", signal);
    }

    auto cfg = config.ectd();
    if (cfg == nullptr)
    {
        return;
    }
    client->unregister_service(cfg->server_name, cfg->server_host, cfg->server_port);
    std::exit(EXIT_SUCCESS);
};

int main(int argc, char *argv[])
{
    // 解析配置
    auto ok = config.LoadFromFile("../config/server.yml");
    if (!ok) {
        return 0;
    }

    // 注册服务
    auto ectd = config.ectd();
    if (ectd.get() != nullptr) {
        std::string etcdaddr = ectd->host + ":" + std::to_string(ectd->port);
        client = std::make_unique<EtcdClientV3>(grpc::CreateChannel(etcdaddr, grpc::InsecureChannelCredentials()));
        if (!client->register_service(ectd->server_name, ectd->server_host, ectd->server_port))
        {
            return 0;
        }
    }

    // 监听信号
    std::vector<int> signals = { SIGTERM, SIGSEGV, SIGINT, SIGILL, SIGABRT, SIGFPE };
    for (size_t i = 0; i < signals.size(); ++i)
    {
        if (ectd.get() != nullptr)
        {
            std::signal(signals[i], unregiser_service);
        }
    }

    // 创建线程池
    auto hardware_threads = std::thread::hardware_concurrency();
    logger()->info("Hardware threads: {}", hardware_threads);
    ThreadPool pool(hardware_threads);

    // 运行gRPC服务
    Service service(pool);
    service.run(config.host(), config.port());

    // 终止所有任务
    pool.termminiate();
    pool.join();

    // 注销服务
    if (ectd.get() != nullptr)
    {
        unregiser_service(0);
    }

    return 0;
}
