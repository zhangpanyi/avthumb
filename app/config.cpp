#include "config.h"
#include "logger.h"

#include <fstream>
#include <yaml-cpp/yaml.h>

Config::Config()
    : port_(17912)
    , host_("0.0.0.0")
    , etcd_(nullptr)
{
}

// 加载配置
bool Config::LoadFromFile(const std::string &path)
{
    YAML::Node config;
    try
    {
        config = YAML::LoadFile(path);
    }
    catch(const std::exception& e)
    {
        logger()->error("Failed to parse server config, file not found");
        return false;
    }

    try
    {
        port_ = config["port"].as<uint16_t>();
    }
    catch(const std::exception& e) {}

    try
    {
        host_ = config["host"].as<std::string>();
    }
    catch(const std::exception& e) {}

    auto etcd = config["etcd"];
    if (etcd.IsDefined())
    {
        try
        {
            auto ptr = std::make_unique<ETCD>();
            ptr->port = etcd["port"].as<uint16_t>();
            ptr->host = etcd["host"].as<std::string>();
            ptr->server_port = etcd["server_port"].as<uint16_t>();
            ptr->server_name = etcd["server_name"].as<std::string>();
            ptr->server_host = etcd["server_host"].as<std::string>();
            etcd_.swap(ptr);
        }
        catch(const std::exception& e) {}   
    }

    return true;
}