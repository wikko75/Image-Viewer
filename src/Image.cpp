#include "Image.h"
#include <cstdint>
#include <GL/glew.h>
#include <opencv2/core/hal/interface.h>
#include <opencv2/imgcodecs.hpp>
#include <print>

ImView::Image::Image(std::string_view path)
: m_texture{}
{
    std::print("Image path: {}\n", path);
    cv::Mat image = cv::imread(path.data(), cv::IMREAD_COLOR_RGB);
    if (image.empty()) {
        std::print("Can not load image!");
        return;
    }

    glGenTextures(1, &m_texture);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_texture);
    
    //float borderColor[] = { 1.0f, 1.0f, 0.0f, 1.0f };
    //glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor); 

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
   
    std::print("Image info\ncols: {}\nrows: {}\nchannels: {}\nsize: {}\nIs continues? {}\n", image.cols, image.rows, image.channels(), image.size.dims(), image.isContinuous());
    std::print("step: {}\n", static_cast<int>(image.step));
    std::print("size: {}\n", image.cols * image.elemSize());
    std::print("elem count: {}\n", image.elemSize());
    std::print("elem size: {} bytes\n", image.elemSize1());

    uchar* data { image.data };
    int32_t width {image.cols};
    int32_t height {image.rows};
    
    // disable default aligment (4) since data is packed
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    
    std::print("OpenGL V: {}\n", reinterpret_cast<const char*>(glGetString(GL_VERSION)));
    if (data != nullptr)
    {
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
      glGenerateMipmap(GL_TEXTURE_2D);
    }
}

void ImView::Image::Show() const noexcept
{
    glBindTexture(GL_TEXTURE_2D, m_texture);
}

ImView::Image::~Image()
{
    glDeleteTextures(1, &m_texture);
}
