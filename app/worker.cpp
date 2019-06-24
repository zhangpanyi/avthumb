#include "worker.h"

#include "logger.h"
#include "avthumb.h"
#include "repeater.h"

Worker::Worker(uint32_t task_id, Repeater &repeater)
    : task_id_(task_id)
    , repeater_(repeater)
{
}

// 重置图片大小
Result Worker::resize(avthumb::ResizeRequest *req)
{
    Result result;
    assert(req != nullptr);
    if (req == nullptr)
    {
        return result;
    }

    auto reply = std::make_shared<avthumb::ResizeReply>();
    if (req->data().empty())
    {
        logger()->error("Failed to resize, bad args");
        reply->set_status(avthumb::StatusCodeFail);
        result.message = reply;
        return result;
    }

    std::vector<unsigned char> buf;
    buf.resize(req->data().size());
    ::memcpy(&*buf.begin(), req->data().data(), buf.size());
    if (!AVThumb::Resize(buf, req->width(), req->height()))
    {
        logger()->error("Failed to resize, internal error");
        reply->set_status(avthumb::StatusCodeFail);
        result.message = reply;
        return result;
    }

    reply->set_status(avthumb::StatusCodeOK);
    req->mutable_data()->resize(buf.size());
    ::memcpy(&*req->mutable_data()->begin(), buf.data(), buf.size());
    reply->mutable_data()->swap(*req->mutable_data());
    result.message = reply;
    return result;
}

// 约束图片大小
Result Worker::constraint(avthumb::ConstraintRequest *req)
{
    Result result;
    assert(req != nullptr);
    if (req == nullptr)
    {
        return result;
    }

    auto reply = std::make_shared<avthumb::ConstraintReply>();
    if (req->data().empty() || req->max_size() == 0)
    {
        logger()->error("Failed to constraint, bad args");
        reply->set_status(avthumb::StatusCodeFail);
        result.message = reply;
        return result;
    }

    ConstraintSize out_result;
    std::vector<unsigned char> buf;
    buf.resize(req->data().size());
    ::memcpy(&*buf.begin(), req->data().data(), buf.size());
    if (!AVThumb::Constraint(buf, req->max_size(), req->output_webp(), &out_result))
    {
        logger()->error("Failed to constraint, internal error");
        reply->set_status(avthumb::StatusCodeFail);
        result.message = reply;
        return result;
    }

    reply->set_status(avthumb::StatusCodeOK);
    req->mutable_data()->resize(buf.size());
    ::memcpy(&*req->mutable_data()->begin(), buf.data(), buf.size());
    reply->mutable_data()->swap(*req->mutable_data());
    reply->set_width(out_result.width);
    reply->set_height(out_result.height);
    reply->set_origin_width(out_result.origin_width);
    reply->set_origin_height(out_result.origin_height);
    result.message = reply;
    return result;
}

// 压缩图片质量
Result Worker::compress(avthumb::CompressImageRequest *req)
{
    Result result;
    assert(req != nullptr);
    if (req == nullptr)
    {
        return result;
    }

    auto reply = std::make_shared<avthumb::CompressImageReply>();
    if (req->data().empty())
    {
        logger()->error("Failed to compress, bad args");
        reply->set_status(avthumb::StatusCodeFail);
        result.message = reply;
        return result;
    }

    std::vector<unsigned char> buf;
    std::vector<unsigned char> outbuf;
    buf.resize(req->data().size());
    ::memcpy(&*buf.begin(), req->data().data(), buf.size());
    if (!AVThumb::CompressImage(buf, req->quality(), &outbuf))
    {
        logger()->error("Failed to compress, internal error");
        reply->set_status(avthumb::StatusCodeFail);
        result.message = reply;
        return result;
    }

    reply->set_status(avthumb::StatusCodeOK);
    req->mutable_data()->resize(outbuf.size());
    ::memcpy(&*req->mutable_data()->begin(), outbuf.data(), outbuf.size());
    reply->mutable_data()->swap(*req->mutable_data());
    result.message = reply;
    return result;
}

// 获取视频预览图
Result Worker::get_video_preview(avthumb::VideoPreviewRequest *req)
{
    Result result;
    assert(req != nullptr);
    if (req == nullptr)
    {
        return result;
    }

    auto reply = std::make_shared<avthumb::VideoPreviewReply>();
    if (req->max_size() <= 0 || req->data().empty())
    {
        logger()->error("Failed to get video preview, bad args");
        reply->set_status(avthumb::StatusCodeFail);
        result.message = reply;
        return result;
    }

    VideoPreview preview;
    std::vector<unsigned char> buf;
    buf.resize(req->data().size());
    ::memcpy(&*buf.begin(), req->data().data(), buf.size());
    if (!AVThumb::GetVideoPreview(buf, &preview))
    {
        logger()->error("Failed to get video preview, internal error");
        reply->set_status(avthumb::StatusCodeFail);
        result.message = reply;
        return result;
    }

    if (req->max_size() > (std::max)(preview.width, preview.height))
    {
        reply->set_width(preview.width);
        reply->set_height(preview.height);
    }
    else
    {
        float scale = float(req->max_size()) / (std::max)(preview.width, preview.height);
        reply->set_width(preview.width * scale);
        reply->set_height(preview.height * scale);
        if (!AVThumb::Resize(preview.preview, reply->width(), reply->height()))
        {
            logger()->error("Failed to get video preview, resize error");
            reply->set_status(avthumb::StatusCodeFail);
            result.message = reply;
            return result;
        }
    }

    reply->set_status(avthumb::StatusCodeOK);
    reply->set_duration(preview.duration);
    req->mutable_data()->resize(preview.preview.size());
    ::memcpy(&*req->mutable_data()->begin(), preview.preview.data(), preview.preview.size());
    reply->mutable_preview()->swap(*req->mutable_data());
    result.message = reply;
    return result;
}

// 获取音频预览
Result Worker::get_audio_preview(avthumb::AudioPreviewRequest *req)
{
    Result result;
    assert(req != nullptr);
    if (req == nullptr)
    {
        return result;
    }

    auto reply = std::make_shared<avthumb::AudioPreviewReply>();
    if (req->data().empty())
    {
        logger()->error("Failed to get audio preview, bad args");
        reply->set_status(avthumb::StatusCodeFail);
        result.message = reply;
        return result;
    }

    AudioPreview preview;
    std::vector<unsigned char> buf;
    buf.resize(req->data().size());
    ::memcpy(&*buf.begin(), req->data().data(), buf.size());
    if (!AVThumb::GetAudioPreview(buf, &preview))
    {
        logger()->error("Failed to get audio preview, internal error");
        reply->set_status(avthumb::StatusCodeFail);
        result.message = reply;
        return result;
    }

    if (!preview.cover.empty())
    {
        if (req->max_size() > (std::max)(preview.width, preview.height))
        {
            reply->set_width(preview.width);
            reply->set_height(preview.height);
        }
        else
        {
            float scale = float(req->max_size()) / (std::max)(preview.width, preview.height);
            reply->set_width(preview.width * scale);
            reply->set_height(preview.height * scale);
            if (!AVThumb::Resize(preview.cover, reply->width(), reply->height()))
            {
                logger()->error("Failed to get audio preview, resize error");
                reply->set_status(avthumb::StatusCodeFail);
                result.message = reply;
                return result;
            }
        }
    }

    reply->set_status(avthumb::StatusCodeOK);
    reply->set_duration(preview.duration);
    reply->set_title(preview.title);
    reply->set_artist(preview.artist);
    if (!preview.cover.empty())
    {
        req->mutable_data()->resize(preview.cover.size());
        ::memcpy(&*req->mutable_data()->begin(), preview.cover.data(), preview.cover.size());
        reply->mutable_cover()->swap(*req->mutable_data());
    }
    result.message = reply;
    return result;
}

// 重载函数对象
Result Worker::operator() (std::shared_ptr<google::protobuf::Message> message)
{
    assert(message != nullptr); 

    Result result;
    if (message->GetDescriptor() == avthumb::ResizeRequest::descriptor())
    {
        result = resize(static_cast<avthumb::ResizeRequest*>(message.get()));
    }
    else if (message->GetDescriptor() == avthumb::ConstraintRequest::descriptor())
    {
        result = constraint(static_cast<avthumb::ConstraintRequest*>(message.get()));
    }
    else if (message->GetDescriptor() == avthumb::CompressImageRequest::descriptor())
    {
        result = compress(static_cast<avthumb::CompressImageRequest*>(message.get()));
    }
    else if (message->GetDescriptor() == avthumb::VideoPreviewRequest::descriptor())
    {
        result = get_video_preview(static_cast<avthumb::VideoPreviewRequest*>(message.get()));
    }
    else if (message->GetDescriptor() == avthumb::AudioPreviewRequest::descriptor())
    {
        result = get_audio_preview(static_cast<avthumb::AudioPreviewRequest*>(message.get()));
    }
    else
    {
        logger()->error("Invalid request, {}", message->GetDescriptor()->full_name());
        assert(false);
    }

    return result;
}
