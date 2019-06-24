#include "logger.h"
#include <spdlog/async.h>
#include <spdlog/async_logger.h>
#include <spdlog/sinks/stdout_sinks.h>
#include <spdlog/sinks/rotating_file_sink.h>

static std::once_flag g_once_flag;
static std::shared_ptr<spdlog::logger> g_logger;

// 创建记录器
void OnlyCreateLoggerOnce()
{
    spdlog::drop_all();
    std::vector<spdlog::sink_ptr> sinks;
    auto file_sink = std::make_shared<spdlog::sinks::rotating_file_sink_mt>(
        "logs.txt", 10485760, 1);
    auto console_sink = std::static_pointer_cast<spdlog::sinks::sink>(
        std::make_shared<spdlog::sinks::stdout_sink_mt>());
    sinks.push_back(file_sink);
    sinks.push_back(console_sink);
    spdlog::set_pattern("[%H:%M:%S %z] [%l] [thread %t] %v");

    spdlog::init_thread_pool(128, 1);
    g_logger = std::make_shared<spdlog::async_logger>(
        "logger", begin(sinks), end(sinks), spdlog::thread_pool());
}

// 获取记录器
const std::shared_ptr<spdlog::logger>& logger()
{
    std::call_once(g_once_flag, OnlyCreateLoggerOnce);
    return g_logger;
}
