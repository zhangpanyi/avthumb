#ifndef __CONFIG_H__
#define __CONFIG_H__

#include <memory>
#include <string>

class Config
{
public:
    struct ETCD {
        uint16_t    port;
        std::string host;
        std::string server_name;
        std::string server_host;
        uint16_t    server_port;
    };

public:
    Config();

public:
    /**
     * 加载配置
     */
    bool LoadFromFile(const std::string &path);

public:
    /**
     * 获取端口号
     */
    uint16_t port() const
    {
        return port_;
    }

    /**
     * 获取主机名
     */
    const std::string& host() const
    {
        return host_;
    }

    /**
     * 获取ETCD配置
     */
    std::unique_ptr<ETCD> ectd() const
    {
        if (etcd_ == nullptr) {
            return nullptr;
        }
        auto ret = std::make_unique<ETCD>();
        ret->host = etcd_->host;
        ret->port = etcd_->port;
        ret->server_name = etcd_->server_name;
        ret->server_host = etcd_->server_host;
        ret->server_port = etcd_->server_port;
        return ret;
    }

private:
    uint16_t                port_;
    std::string             host_;
    std::unique_ptr<ETCD>   etcd_;
};

#endif
