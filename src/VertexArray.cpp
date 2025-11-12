#include "VertexArray.h"
#include <GL/glew.h>

ImView::VertexArray::VertexArray()
: m_id{}
{
    glGenVertexArrays(1, &m_id);
}

void ImView::VertexArray::Bind() const noexcept
{
    glBindVertexArray(m_id);
}

ImView::VertexArray::~VertexArray()
{
    glDeleteVertexArrays(1, &m_id);
}
