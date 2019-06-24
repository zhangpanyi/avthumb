#ifndef __WORKER_H__
#define __WORKER_H__

#include <avthumb.pb.h>

class Repeater;

struct Result
{
    uint32_t                                    task_id;
    std::shared_ptr<google::protobuf::Message>  message;
};

class Worker
{
public:
    explicit Worker(uint32_t task_id, Repeater &repeater);

    /**
     * 重载函数对象
     */
    Result operator() (std::shared_ptr<google::protobuf::Message> message);

private:
    /**
     * 重置图片大小
     */
    Result resize(avthumb::ResizeRequest *req);

    /**
     * 约束图片大小
     */
    Result constraint(avthumb::ConstraintRequest *req);

    /**
     * 压缩图片质量
     */
    Result compress(avthumb::CompressImageRequest *req);

    /**
     * 获取视频预览图
     */
    Result get_video_preview(avthumb::VideoPreviewRequest *req);

    /**
     * 获取音频预览
     */
    Result get_audio_preview(avthumb::AudioPreviewRequest *req);

private:
    Worker(const Worker&) = delete;
    Worker& operator= (const Worker&) = delete;

private:
    uint32_t    task_id_;
    Repeater&   repeater_;
};

#endif
