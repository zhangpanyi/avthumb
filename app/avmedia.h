#ifndef __AVMEDIA_H__
#define __AVMEDIA_H__

#include <map>
#include <chrono>
#include <vector>
#include <string>

struct AVFrame;
struct AVPacket;
struct AVIOContext;
struct AVCodecContext;
struct AVFormatContext;

extern "C"
{
#include <libavutil/common.h>
}

class AVMedia final
{
public:
    AVMedia();

    ~AVMedia();


public:
    /**
     * 打开媒体
     */
    bool open(unsigned char *data, size_t size);

    /**
     * 是否已打开
     */
    bool is_open() const
    {
        return format_ctx_ != nullptr;
    };

    /**
     * 是否包含视频
     */
    bool has_video() const
    {
        return is_open() && video_index_ != -1;
    }

    /**
     * 是否包含音频
     */
    bool has_audio() const
    {
        return is_open() && audio_index_ != -1;
    }

    /**
     * 是否已打开视频解码器
     */
    bool is_open_video_codec() const
    {
        return video_codec_ctx_ != nullptr;
    }

    /**
     * 是否已打开音频解码器
     */
    bool is_open_audio_codec() const
    {
        return audio_codec_ctx_ != nullptr;
    }

public:
    /**
     * 获取视频下一帧
     */
    bool get_video_next_frame(AVFrame *frame);

    /**
     * 获取视频像素格式
     */
    bool get_video_pixel_format(AVPixelFormat *out_format);

    /**
     * 获取视频播放时长
     */
    bool get_video_duration(std::chrono::milliseconds *duration);

    /**
     * 获取音频播放时长
     */
    bool get_audio_duration(std::chrono::milliseconds *duration);

    /**
     * 获取音频元数据信息
     */
    bool get_audio_metadata(std::map<std::string, std::string> *out_map);

private:
    /**
     * 打开视频解码器
     */
    bool open_video_codec();

    /**
     * 打开音频解码器
     */
    bool open_audio_codec();

private:
    /**
     * 释放AVIOContext
     */
    void free_avio_context();

    /**
     * 释放AVFormatContext
     */
    void free_format_context();

    /**
     * 释放AVCodecContext
     */
    void free_video_codec_context();
    void free_audio_codec_context();

private:
    AVPacket*           packet_;            // 数据包
    AVIOContext*        avio_ctx_;          // IO上下文
    AVFormatContext*    format_ctx_;        // 格式上下文
    int                 video_index_;       // 视频流索引
    int                 audio_index_;       // 音频流索引
    unsigned char*      avio_ctx_buffer_;   // 数据缓冲区
    AVCodecContext*     video_codec_ctx_;   // 视频编码器
    AVCodecContext*     audio_codec_ctx_;   // 音频编码器
};

struct ImageData
{
    unsigned short width = 0;
    unsigned short height = 0;
    std::vector<unsigned char> buf;
};

// 转换视频帧为JPEG
bool ConvertFrameToJpeg(AVFrame *frame, AVPixelFormat format, ImageData *out_image);

#endif // !AVMEDIA_H__
