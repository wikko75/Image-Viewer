#include "Window.h"
#include <GLFW/glfw3.h>
#include <print>

ImView::Window::Window(const WindowData &data)
    : m_Window {}
    , m_Data   {data}
    , m_IsOpen {false}
{
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_Window = glfwCreateWindow(data.width, data.height, data.title, nullptr, nullptr);
    if (m_Window == nullptr) {
        glfwTerminate();
        std::print("Failed to create GLFW window");
        return;
    }

    glfwSetWindowUserPointer(m_Window, &m_Data);

    glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* w, int width, int height) {
        glViewport(0, 0, width, height);
        WindowData* window_data { static_cast<WindowData*>(glfwGetWindowUserPointer(w)) };
        window_data->height = height;
        window_data->width = width;
        window_data->is_resized = true;
    });

    glfwMakeContextCurrent(m_Window);
    m_IsOpen = true;
}

ImView::Window::~Window()
{
    glfwTerminate();
}

GLFWwindow* ImView::Window::Get()
{
    return m_Window;
}

bool ImView::Window::Close() noexcept
{
    return !glfwWindowShouldClose(m_Window);
}

bool ImView::Window::IsResized() const
{
    return m_Data.is_resized;
}

std::pair<int, int> ImView::Window::GetSize() const noexcept
{
    return { m_Data.width, m_Data.height };
}

void ImView::Window::Resized(bool flag) noexcept
{
    m_Data.is_resized = flag;
}

