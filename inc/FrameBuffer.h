#ifndef FRAME_BUFFER_H
#define FRAME_BUFFER_H

#include <cstdint>

namespace ImView {

struct Size
{
    uint32_t width = 800;
    uint32_t height = 600;
};

class FrameBuffer
{
public:
    explicit FrameBuffer();
    FrameBuffer(const FrameBuffer& other) = delete;
    FrameBuffer(FrameBuffer&& other) = delete;
    FrameBuffer& operator=(const FrameBuffer& other) = delete;
    FrameBuffer& operator=(FrameBuffer&& other) = delete;
    [[nodiscard]] uint32_t GetColorAttachment() const;
    void Bind() const;
    void Unbind() const;
    void Resize(const Size new_size) noexcept;
    [[nodiscard]] Size GetSize() const noexcept;
    ~FrameBuffer();

private:
    [[nodiscard]] uint32_t CreateColorAttachment(const Size size);
private:
    uint32_t m_id;
    uint32_t m_color_attachment;
    Size m_size;
};
} // namespace ImView
#endif

