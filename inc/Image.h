#ifndef IMAGE_H
#define IMAGE_H

/**
 * Abstraction of an image in form of OpenGL texture
 * This class creates an OpenGL texture feed it with cv::Mat data
 */

#include <cstdint>
#include <string_view>
#include <opencv2/opencv.hpp>

namespace ImView {

class Image
{
public:
    explicit Image(std::string_view path);
    void Show() const noexcept;
    ~Image();
private:
    cv::Mat m_image_data;
    uint32_t m_texture;
};
} //namespace ImView

#endif
