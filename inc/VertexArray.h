#ifndef IMVIEW_VERTEX_ARRAY_H
#define IMVIEW_VERTEX_ARRAY_H

#include <cstdint>

namespace ImView {

class VertexArray
{
public:
    VertexArray();
    VertexArray(const VertexArray&) = delete;
    VertexArray(VertexArray&&) = delete;
    VertexArray& operator=(const VertexArray&) = delete;
    VertexArray& operator=(VertexArray&&) = delete;
    void Bind() const noexcept;
    ~VertexArray();
private:
    uint32_t m_id;
};
} //namespace ImView
#endif
