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

