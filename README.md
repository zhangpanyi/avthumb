# avthumb
基于gRPC+OpenCV+FFMPEG开发的多媒体处理服务。支持重设图片尺寸、约束图片尺寸、压缩图片质量、获取视频预览以及获取音频预览功能，使用gRPC对外提供接口服务。

## 搭建环境
本项目运行环境将生成一个Docker镜像，开发和上线服务程序均在容器内运行，保证了环境统一。

### 获取代码
```
git clone https://github.com/zhangpanyi/avthumb.git
cd avthumb && python init_config.py
git submodule update --init --recursive
```

### Docker
```
docker-compose build
docker-compose up -d
```
