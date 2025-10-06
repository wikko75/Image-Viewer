#ifndef WINDOW_H_1
#define WINDOW_H_1

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace ImView {

struct WindowData
{
    int width  {800};
    int height {600};
    const char* title {"Window"};
};

class Window
{
public:
    explicit Window(const WindowData& data);
    ~Window();
    GLFWwindow* Get();
    bool Close() noexcept;
private:
    GLFWwindow* m_Window;
    WindowData m_Data;
    bool m_IsOpen;
};

}

#endif
