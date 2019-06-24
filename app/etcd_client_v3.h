#ifndef __ETCD_CLIENT_V3_H__
#define __ETCD_CLIENT_V3_H__

#include <grpc++/grpc++.h>
#include <rpc.grpc.pb.h>

class EtcdClientV3
{
public:
    explicit EtcdClientV3(std::shared_ptr<grpc::Channel> channel);

public:
    /**
     * 注册服务
     */
    bool register_service(const std::string &name, const std::string &ip, uint16_t port);

    /**
     * 注销服务
     */
    bool unregister_service(const std::string &name, const std::string &ip, uint16_t port);

private:
    EtcdClientV3(const EtcdClientV3&) = delete;
    EtcdClientV3& operator= (const EtcdClientV3&) = delete;

private:
    std::unique_ptr<etcdserverpb::KV::Stub> stub_;
};

#endif // __ETCD_CLIENT_V3_H__
