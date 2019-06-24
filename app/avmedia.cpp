#include "avmedia.h"

#include <mutex>
#include <cstring>
#include <cassert>
#include <opencv2/opencv.hpp>

extern "C"
{
#include <libavutil/mem.h>
#include <libavutil/imgutils.h>
#include <libavcodec/avcodec.h>    
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
}

struct BufferData
{
    size_t   size;
    size_t   seek;
    uint8_t* data;
};

// 初始化
static void OnceInitFFMpeg()
{
    static std::once_flag flag;
    std::call_once(flag, []() {
        av_register_all();
        av_log_set_level(AV_LOG_ERROR);
    });
}

// 读取数据包
static int ReadPacket(void *opaque, uint8_t *buf, int buf_size)
{
    struct BufferData *bd = reinterpret_cast<struct BufferData *>(opaque);
    auto min_size = FFMIN(buf_size, bd->size);
    buf_size = static_cast<int>(min_size);
    memcpy(buf, bd->data + bd->seek, buf_size);
    bd->size -= buf_size;
    bd->seek += buf_size;
    return buf_size;
}

// 寻找数据包
static int64_t SeekPacket(void *opaque, int64_t offset, int whence)
{
    struct BufferData *bd = reinterpret_cast<struct BufferData *>(opaque);
    bd->seek += offset;
    return bd->seek;
}

// 转换视频帧为JPEG
bool ConvertFrameToJpeg(AVFrame *frame, AVPixelFormat format, ImageData *out_image)
{
    assert(frame != nullptr && out_image != nullptr);
    if (frame == nullptr || out_image == nullptr)
    {
        return false;
    }

    // 初始化
    bool ret = false;
    int width = frame->width;
    int height = frame->height;
    SwsContext *convert_ctx = nullptr;
    AVFrame *frame_rgb = av_frame_alloc();
    if (frame_rgb == nullptr)
    {
        return false;
    }

    // 分配图片内存
    int bytes = av_image_get_buffer_size(AV_PIX_FMT_BGR24, width, height, 1);
    unsigned char *buffer = reinterpret_cast<unsigned char *>(av_malloc(bytes * sizeof(unsigned char)));
    if (buffer == nullptr)
    {
        goto Free;
    }

    // 视频帧转换
    av_image_fill_arrays(frame_rgb->data, frame_rgb->linesize, buffer, AV_PIX_FMT_BGR24, width, height, 1);
    convert_ctx = sws_getContext(width, height, format,
        width, height, AV_PIX_FMT_BGR24, SWS_BILINEAR,
        nullptr, nullptr, nullptr);
    if (convert_ctx == nullptr)
    {
        goto Free;
    }
    sws_scale(convert_ctx, frame->data, frame->linesize, 0, height, frame_rgb->data, frame_rgb->linesize);

    // 转换为JPEG图片
    try
    {
        out_image->buf.clear();
        out_image->width = static_cast<unsigned short>(width);
        out_image->height = static_cast<unsigned short>(height);
        cv::Mat mat(height, width, CV_8UC3, frame_rgb->data[0], frame_rgb->linesize[0]);
        cv::imencode(".jpg", mat, out_image->buf);
        ret = true;
    }
    catch (...)
    {
        ret = false;
    }

Free:
    if (buffer != nullptr)
    {
        av_free(buffer);
    }

    if (frame_rgb != nullptr)
    {
        av_frame_free(&frame_rgb);
    }

    if (convert_ctx != nullptr)
    {
        sws_freeContext(convert_ctx);
    }

    return ret;
}

/************************************************************************/
/************************************************************************/

AVMedia::AVMedia()
    : packet_(nullptr)
    , avio_ctx_(nullptr)
    , format_ctx_(nullptr)
    , video_index_(-1)
    , audio_index_(-1)
    , avio_ctx_buffer_(nullptr)
    , video_codec_ctx_(nullptr)
    , audio_codec_ctx_(nullptr)
{
}

AVMedia::~AVMedia()
{
    free_format_context();
    free_video_codec_context();
    free_audio_codec_context();
    if (packet_ != nullptr)
    {
        av_packet_free(&packet_);
    }
}

// 释放AVIOContext
void AVMedia::free_avio_context()
{
    if (avio_ctx_ != nullptr)
    {
        av_freep(&avio_ctx_->buffer);
        av_freep(&avio_ctx_);
    }
    else
    {
        av_free(avio_ctx_buffer_);
        avio_ctx_buffer_ = nullptr;
    }
}

// 释放AVFormatContext
void AVMedia::free_format_context()
{
    if (format_ctx_ != nullptr)
    {
        free_avio_context();
        avformat_close_input(&format_ctx_);
    }
}

// 释放AVCodecContext
void AVMedia::free_video_codec_context()
{
    if (video_codec_ctx_ != nullptr)
    {
        avcodec_free_context(&video_codec_ctx_);
    }
}

void AVMedia::free_audio_codec_context()
{
    if (audio_codec_ctx_ != nullptr)
    {
        avcodec_free_context(&audio_codec_ctx_);
    }
}

// 打开媒体
bool AVMedia::open(unsigned char *data, size_t size)
{
    // 是否已打开
    if (is_open())
    {
        return false;
    }

    // 初始化
    BufferData bd;
    bd.seek = 0;
    bd.data = data;
    bd.size = size;
    avio_ctx_buffer_ = reinterpret_cast<unsigned char*>(av_malloc(size));

    // 打开文件流
    OnceInitFFMpeg();
    format_ctx_ = avformat_alloc_context();
    if (format_ctx_ == nullptr)
    {
        goto Failed;
    }

    // 读取媒体数据
    avio_ctx_ = avio_alloc_context(avio_ctx_buffer_, static_cast<int>(size), 0, &bd, ReadPacket, nullptr, SeekPacket);
    if (avio_ctx_ == nullptr)
    {
        goto Failed;
    }
    format_ctx_->pb = avio_ctx_;

    if (avformat_open_input(&format_ctx_, nullptr, nullptr, nullptr) < 0)
    {
        goto Failed;
    }

    if (avformat_find_stream_info(format_ctx_, nullptr) < 0)
    {
        goto Failed;
    }

    // 查找视频流位置
    for (size_t i = 0; i < format_ctx_->nb_streams; ++i)
    {
        if (format_ctx_->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_VIDEO)
        {
            video_index_ = static_cast<int>(i);
        }

        if (format_ctx_->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_AUDIO)
        {
            audio_index_ = static_cast<int>(i);
        }
    }
    return true;

Failed:
    free_format_context();
    return false;
}

// 打开视频解码器
bool AVMedia::open_video_codec()
{
    if (!has_video())
    {
        return false;
    }

    if (is_open_video_codec())
    {
        return true;
    }

    // 获取解码器
    AVCodecParameters *codecpar = format_ctx_->streams[video_index_]->codecpar;
    AVCodec *codec = avcodec_find_decoder(codecpar->codec_id);
    video_codec_ctx_ = avcodec_alloc_context3(codec);
    if (codec == nullptr || video_codec_ctx_ == nullptr)
    {
        goto Failed;
    }

    if (avcodec_parameters_to_context(video_codec_ctx_, format_ctx_->streams[video_index_]->codecpar) < 0)
    {
        goto Failed;
    }

    // 打开解码器
    if (avcodec_open2(video_codec_ctx_, codec, nullptr) < 0)
    {
        goto Failed;
    }

    return true;

Failed:
    free_video_codec_context();
    return false;
}

// 打开音频解码器
bool AVMedia::open_audio_codec()
{
    if (!has_video())
    {
        return false;
    }

    if (is_open_audio_codec())
    {
        return true;
    }

    // 获取解码器
    AVCodecParameters *codecpar = format_ctx_->streams[audio_index_]->codecpar;
    AVCodec *codec = avcodec_find_decoder(codecpar->codec_id);
    audio_codec_ctx_ = avcodec_alloc_context3(codec);
    if (codec == nullptr || audio_codec_ctx_ == nullptr)
    {
        goto Failed;
    }

    if (avcodec_parameters_to_context(audio_codec_ctx_, format_ctx_->streams[audio_index_]->codecpar) < 0)
    {
        goto Failed;
    }

    // 打开解码器
    if (avcodec_open2(audio_codec_ctx_, codec, nullptr) < 0)
    {
        goto Failed;
    }

    return true;

Failed:
    free_audio_codec_context();
    return false;
}

// 获取视频下一帧
bool AVMedia::get_video_next_frame(AVFrame *frame)
{
    assert(frame != nullptr);
    if (frame == nullptr)
    {
        return false;
    }

    if (!has_video())
    {
        return false;
    }

    if (!is_open_video_codec())
    {
        if (!open_video_codec())
        {
            return false;
        }
    }

    if (packet_ == nullptr)
    {
        packet_ = av_packet_alloc();
    }

    // 解码帧数据
    while (av_read_frame(format_ctx_, packet_) >= 0)
    {
        if (packet_->stream_index == video_index_)
        {
            if (avcodec_send_packet(video_codec_ctx_, packet_) < 0)
            {
                av_packet_unref(packet_);
                continue;
            }

            if (avcodec_receive_frame(video_codec_ctx_, frame) < 0)
            {
                av_packet_unref(packet_);
                continue;
            }

            av_packet_unref(packet_);
            return true;
        }
    }

    av_packet_unref(packet_);
    return false;
}

// 获取视频像素格式
bool AVMedia::get_video_pixel_format(AVPixelFormat *out_format)
{
    assert(out_format != nullptr);
    if (out_format == nullptr)
    {
        return false;
    }

    if (!has_video())
    {
        return false;
    }

    if (!is_open_video_codec())
    {
        if (!open_video_codec())
        {
            return false;
        }
    }

    *out_format = video_codec_ctx_->pix_fmt;
    return true;
}

// 获取视频播放时长
bool AVMedia::get_video_duration(std::chrono::milliseconds *duration)
{
    if (!has_video())
    {
        return false;
    }

    AVCodecParameters *codec_param = format_ctx_->streams[video_index_]->codecpar;
    if (format_ctx_->duration != AV_NOPTS_VALUE) // 计算视频播放时长
    {
        uint64_t val = format_ctx_->duration + 5000;
        uint64_t secs = val / AV_TIME_BASE;
        uint64_t us = val % AV_TIME_BASE;
        *duration = std::chrono::milliseconds((size_t)(secs * 1000 + ((1000 * us) / AV_TIME_BASE)));
    }
    else if (codec_param->codec_id == AV_CODEC_ID_GIF) // 计算gif动画播放时长
    {
        AVStream *st = format_ctx_->streams[video_index_];
        if (st->avg_frame_rate.den && st->avg_frame_rate.num == 0)
        {
            return false;
        }

        int count = st->codec_info_nb_frames;
        *duration = std::chrono::milliseconds((size_t)(1.0 / av_q2d(st->avg_frame_rate) * 1000 * count));
    }
    else
    {
        return false;
    }

    return true;
}

// 获取音频播放时长
bool AVMedia::get_audio_duration(std::chrono::milliseconds *duration)
{
    if (!has_audio())
    {
        return false;
    }

    if (format_ctx_->duration != AV_NOPTS_VALUE)
    {
        uint64_t val = format_ctx_->duration + 5000;
        uint64_t secs = val / AV_TIME_BASE;
        uint64_t us = val % AV_TIME_BASE;
        *duration = std::chrono::milliseconds((size_t)(secs * 1000 + ((1000 * us) / AV_TIME_BASE)));
        return true;
    }
    else
    {
        return false;
    }
}

// 获取音频元数据信息
bool AVMedia::get_audio_metadata(std::map<std::string, std::string> *out_map)
{
    assert(out_map != nullptr);
    if (out_map == nullptr)
    {
        return false;
    }

    if (!has_audio())
    {
        return false;
    }

    // 查询音频元信息
    if (format_ctx_->metadata != nullptr)
    {
        AVDictionaryEntry *tag = nullptr;
        while ((tag = av_dict_get(format_ctx_->metadata, "", tag, AV_DICT_IGNORE_SUFFIX)))
        {
            out_map->insert(std::make_pair(tag->key, tag->value));
        }
    }

    return true;
}
