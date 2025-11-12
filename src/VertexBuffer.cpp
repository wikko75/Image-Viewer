#include "VertexBuffer.h"
#include <span>
#include <GL/glew.h>

ImView::VertexBuffer::VertexBuffer(std::span<const float> data)
: m_id{}
{
    glGenBuffers(1, &m_id);
    glBindBuffer(GL_ARRAY_BUFFER, m_id);
    glBufferData(GL_ARRAY_BUFFER,  sizeof(float) * data.size(), data.data(), GL_STATIC_DRAW);

    // pos
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // tex. coors
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
}

void ImView::VertexBuffer::Bind() const noexcept
{
    glBindBuffer(GL_ARRAY_BUFFER, m_id);
}

ImView::VertexBuffer::~VertexBuffer()
{
    glDeleteBuffers(1, &m_id);
}
