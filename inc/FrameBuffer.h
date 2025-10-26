#ifndef FRAME_BUFFER_H
#define FRAME_BUFFER_H

#include <cstdint>

namespace ImView {

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
    ~FrameBuffer();

private:
    uint32_t m_id;
    uint32_t m_color_attachment;
};
} // namespace ImView
#endif

