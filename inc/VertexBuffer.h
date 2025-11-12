#ifndef IMVIEW_VERTEX_BUFFER
#define IMVIEW_VERTEX_BUFFER 

#include <cstdint>
#include <span>

namespace ImView {

class VertexBuffer
{
public:
    explicit VertexBuffer(std::span<const float> data);
    VertexBuffer(const VertexBuffer&) = delete;
    VertexBuffer(VertexBuffer&&) = delete;
    VertexBuffer& operator=(const VertexBuffer&) = delete;
    VertexBuffer& operator=(VertexBuffer&&) = delete;
    void Bind() const noexcept;
    ~VertexBuffer();
private:
    uint32_t m_id;
};
} //namespace ImView
#endif
