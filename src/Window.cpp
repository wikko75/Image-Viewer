#include "Window.h"
#include <print>

ImView::Window::Window(const WindowData &data)
    : m_Window {nullptr}
    , m_Data   {data}
    , m_IsOpen {false}
{
    m_Window = glfwCreateWindow(data.width, data.height, data.title, NULL, NULL);
    
    if (!m_Window) {
        glfwTerminate();
        std::print("Failed to create GLFW window");
        return;
    }
    m_IsOpen = true;
    glfwMakeContextCurrent(m_Window);
}

ImView::Window::~Window()
{
    glfwTerminate();
}

GLFWwindow* ImView::Window::Get()
{
    return m_Window;
}

void ImView::Window::Close() noexcept
{
    m_IsOpen = false;
}

bool ImView::Window::IsOpen() const noexcept
{
    return m_IsOpen;
}
