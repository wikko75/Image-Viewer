#include "FrameBuffer.h"
#include <GL/glew.h>
#include <cstdint>
#include <print>

ImView::FrameBuffer::FrameBuffer()
    : m_id{}
    , m_color_attachment{}
    , m_size{}
{
    glGenFramebuffers(1, &m_id);
    glBindFramebuffer(GL_FRAMEBUFFER, m_id);

    glGenTextures(1, &m_color_attachment);
    glBindTexture(GL_TEXTURE_2D, m_color_attachment);
      
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_size.width, m_size.height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); 

    glBindTexture(GL_TEXTURE_2D, 0);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_color_attachment, 0);  

    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    {
        std::print("ERROR::FRAMEBUFFER:: Framebuffer is not complete!\n");
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);  
}

uint32_t ImView::FrameBuffer::GetColorAttachment() const
{
    return m_color_attachment;
}

void ImView::FrameBuffer::Bind() const
{
    glBindFramebuffer(GL_FRAMEBUFFER, m_id);  
}

void ImView::FrameBuffer::Unbind() const
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

uint32_t ImView::FrameBuffer::CreateColorAttachment(const Size size)
{
    std::print("New size: [{}, {}]\n", size.width, size.height);
    glGenTextures(1, &m_color_attachment);
    glBindTexture(GL_TEXTURE_2D, m_color_attachment);
      
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, size.width, size.height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); 

    return m_color_attachment;
}
void ImView::FrameBuffer::Resize(const Size new_size) noexcept
{
    //TODO recreate texture
    m_size = new_size;
}

ImView::Size ImView::FrameBuffer::GetSize() const noexcept
{
    return m_size;
}

ImView::FrameBuffer::~FrameBuffer()
{
    glDeleteTextures(1, &m_color_attachment);
    glDeleteFramebuffers(1, &m_id);
}
