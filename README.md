# avthumb
基于gRPC+OpenCV+FFMPEG开发的多媒体处理服务


## 搭建环境

### 获取代码
```
git clone git@192.168.212.220:gitlab.potato.im/avthumb.git
cd avthumb
git submodule update --init --recursive
```

### CentOS 7
```
yum install docker -y
systemctl start docker.service
chkconfig docker on
```

## 生成协议
```
cd proto
protoc -I=. --cpp_out=. avthumb.proto
protoc -I=. --grpc_out=. --plugin=protoc-gen-grpc=/usr/bin/grpc_cpp_plugin avthumb.proto
```

## 启动服务

### 构建Docker镜像
```
sudo docker build -t="zpy/avthumb:0.1" -f docker/Dockerfile .
```

### 运行Docker容器
```
sudo docker run -it -p 17912:17912 --cpuset-cpus 0-15 --cpu-shares 16384 --cpu-period 100000 --cpu-quota 1600000 zpy/avthumb:0.1 /bin/bash
```

### 启动AVThumb服务
```
cd ~/avthumb/bin && ./avthumb <服务ip> <服务端口> <etcdip> <etcd端口> <服务名称>
```

