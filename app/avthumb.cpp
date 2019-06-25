#include "avthumb.h"
#include "avmedia.h"
#include <opencv2/opencv.hpp>

extern "C"
{
#include <libavformat/avformat.h>
}

// 写入音乐信息
void WriteMusicInfo(const std::map<std::string, std::string> &meta, AudioPreview *out_preview)
{
    assert(out_preview != nullptr);
    if (out_preview == nullptr)
    {
        return;
    }

    auto iter = meta.find("title");
    if (iter != meta.end())
    {
        out_preview->title = iter->second;
    }

    iter = meta.find("artist");
    if (iter != meta.end())
    {
        out_preview->artist = iter->second;
    }
}

// 重置图片大小
bool AVThumb::Resize(std::vector<unsigned char> &in_out_buffer, uint32_t width, uint32_t height)
{
    try
    {
        cv::Mat dst;
        cv::Mat mat = cv::imdecode(cv::Mat(in_out_buffer, false), cv::IMREAD_UNCHANGED);
        cv::resize(mat, dst, cv::Size(width, height));
        in_out_buffer.clear();
        return cv::imencode(".jpg", dst, in_out_buffer);
    }
    catch (...)
    {
        return false;
    }
}

// 约束图片大小
bool AVThumb::Constraint(std::vector<unsigned char> &in_out_buffer, uint32_t max_size, bool output_webp, ConstraintSize *out_result)
{
    if (out_result == nullptr)
    {
        return false;
    }

    try
    {
        cv::Mat dst;
        cv::Mat mat = cv::imdecode(cv::Mat(in_out_buffer, false), cv::IMREAD_UNCHANGED);
        uint32_t width = mat.size().width;
        uint32_t height = mat.size().height;
        out_result->origin_width = width;
        out_result->origin_height = height;
        if (max_size > (std::max)(width, height))
        {
            out_result->width = width;
            out_result->height = height;
            return true;
        }
        
        float scale = static_cast<float>(max_size / (std::max)(width, height));
        width = width * scale;
        height = height * scale;
        cv::resize(mat, dst, cv::Size(width, height));

        in_out_buffer.clear();
        out_result->width = width;
        out_result->height = height;
        if (output_webp)
        {
            return cv::imencode(".webp", dst, in_out_buffer); 
        }
        return cv::imencode(".jpg", dst, in_out_buffer);
    }
    catch (...)
    {
        return false;
    }
}

// 压缩图片质量
bool AVThumb::CompressImage(std::vector<unsigned char> &in_buffer, uint16_t quality, std::vector<unsigned char> *out_buffer)
{
    if (out_buffer == nullptr)
    {
        return false;
    }

    try
    {
        out_buffer->clear();
        std::vector<int> params;
        params.push_back(cv::IMWRITE_JPEG_QUALITY);
        params.push_back(quality);
        cv::Mat mat = cv::imdecode(cv::Mat(in_buffer, false), cv::IMREAD_UNCHANGED);
        return cv::imencode(".jpg", mat, *out_buffer, params);
    }
    catch (...)
    {
        return false;
    } 
}

// 获取视频预览
bool AVThumb::GetVideoPreview(std::vector<unsigned char> &in_buffer, VideoPreview *out_preview)
{
    if (out_preview == nullptr)
    {
        return false;
    }

    try
    {
        AVMedia media;
        if (!media.open(in_buffer.data(), in_buffer.size()))
        {
            return false;
        }
    
        // 获取播放时长
        std::chrono::milliseconds duration;
        if (!media.get_video_duration(&duration))
        {
            return false;
        }
        out_preview->duration = static_cast<uint32_t>(duration.count());
    
        // 读取视频第一帧
        AVFrame *frame = av_frame_alloc();
        if (frame == nullptr)
        {
            return false;
        }
    
        if (!media.get_video_next_frame(frame))
        {
            av_frame_free(&frame);
            return false;
        }
    
        AVPixelFormat format;
        if (!media.get_video_pixel_format(&format))
        {
            av_frame_free(&frame);
            return false;
        }
    
        ImageData image;
        if (!ConvertFrameToJpeg(frame, format, &image))
        {
            av_frame_free(&frame);
            return false;
        }
        av_frame_free(&frame);
    
        // 获取首帧图片
        out_preview->width = image.width;
        out_preview->height = image.height;
        out_preview->preview = std::move(image.buf);
        return true;
    }
    catch (...)
    {
        return false;
    } 
}

// 获取音乐预览
bool AVThumb::GetAudioPreview(std::vector<unsigned char> &in_buffer, AudioPreview *out_preview)
{
    if (out_preview == nullptr)
    {
        return false;
    }

    try
    {
        AVMedia media;
        if (!media.open(in_buffer.data(), in_buffer.size()))
        {
            return false;
        }
    
        // 获取播放时长
        std::chrono::milliseconds duration;
        if (!media.get_audio_duration(&duration))
        {
            return false;
        }
        out_preview->duration = static_cast<uint32_t>(duration.count());
    
        // 获取音频元数据
        std::map<std::string, std::string> meta;
        if (media.get_audio_metadata(&meta))
        {
            WriteMusicInfo(meta, out_preview);
        }
        
        // 读取封面第一帧
        AVFrame *frame = av_frame_alloc();
        if (frame == nullptr)
        {
            return true;
        }
    
        if (!media.get_video_next_frame(frame))
        {
            av_frame_free(&frame);
            return true;
        }
    
        AVPixelFormat format;
        if (!media.get_video_pixel_format(&format))
        {
            av_frame_free(&frame);
            return true;
        }
    
        ImageData image;
        if (!ConvertFrameToJpeg(frame, format, &image))
        {
            av_frame_free(&frame);
            return true;
        }
        av_frame_free(&frame);
    
        // 获取封面首帧图片
        out_preview->cover = std::move(image.buf);
        out_preview->width = image.width;
        out_preview->height = image.height;
    
        return true;
    }
    catch (...)
    {
        return false;
    } 
}
