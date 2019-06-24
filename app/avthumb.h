#ifndef __AVTHUMB_H__
#define __AVTHUMB_H__

#include <string>
#include <vector>
#include <cstdint>

// 尺寸约束
struct ConstraintSize
{
    uint32_t    width;
    uint32_t    height;
    uint32_t    origin_width;
    uint32_t    origin_height;
};

// 视频预览信息
struct VideoPreview
{
    uint32_t                    width;
    uint32_t                    height;
    uint32_t                    duration;
    std::vector<unsigned char>  preview;
};

// 音频预览信息
struct AudioPreview
{
    uint32_t                    width;
    uint32_t                    height;
    uint32_t                    duration;
    std::string                 title;
    std::string                 artist;
    std::vector<unsigned char>  cover;
};

struct AVThumb
{
    /**
     * 重置图片大小
     */
    static bool Resize(std::vector<unsigned char> &in_out_buffer, uint32_t width, uint32_t height);

    /**
     * 约束图片大小
     */
    static bool Constraint(std::vector<unsigned char> &in_out_buffer, uint32_t max_size, bool output_webp, ConstraintSize *out_result);

    /**
     * 压缩图片质量
     */
    static bool CompressImage(std::vector<unsigned char> &in_buffer, uint16_t quality, std::vector<unsigned char> *out_buffer);

    /**
     * 获取视频预览
     */
     static bool GetVideoPreview(std::vector<unsigned char> &in_buffer, VideoPreview *out_preview);

    /**
     * 获取音乐预览
     */
    static bool GetAudioPreview(std::vector<unsigned char> &in_buffer, AudioPreview *out_preview);
};

#endif // __AVTHUMB_H__
