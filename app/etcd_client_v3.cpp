#include "etcd_client_v3.h"
#include "logger.h"

EtcdClientV3::EtcdClientV3(std::shared_ptr<grpc::Channel> channel)
    : stub_(etcdserverpb::KV::NewStub(channel))
{
}

// 注册服务
bool EtcdClientV3::register_service(const std::string &name, const std::string &ip, uint16_t port)
{
    // 计算kv 
    std::string addr = ip + ":" + std::to_string(port);
    std::string key = name + "/" + addr;
    char val[256] = { 0 };
    snprintf(val, sizeof(val), "{\"Op\":0,\"Addr\":\"%s\",\"Metadata\":\"\"}", addr.c_str());

    // 发起注册请求
    grpc::ClientContext context;
    etcdserverpb::PutRequest request;
    etcdserverpb::PutResponse response;
    request.set_key(key);
    request.set_value(val);
    auto status = stub_->Put(&context, request, &response);
    if (!status.ok())
    {
        logger()->error("Failed to register service, {}", status.error_message().c_str());
        return false;
    }
    return true;
}

// 注销服务
bool EtcdClientV3::unregister_service(const std::string &name, const std::string &ip, uint16_t port)
{
    // 计算key
    std::string addr = ip + ":" + std::to_string(port);
    std::string key = name + "/" + addr;

    // 发起注销请求
    grpc::ClientContext context;
    etcdserverpb::DeleteRangeRequest request;
    etcdserverpb::DeleteRangeResponse response;
    request.set_key(key);
    auto status = stub_->DeleteRange(&context, request, &response);
    if (!status.ok())
    {
        logger()->error("Failed to unregister service, {}", status.error_message().c_str());
        return false;
    }
    return true;
}
