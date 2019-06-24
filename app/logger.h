#ifndef __LOGGER_H__
#define __LOGGER_H__

#include <spdlog/spdlog.h>

/**
 * 获取记录器
 */
const std::shared_ptr<spdlog::logger>& logger();

#endif
