#ifndef WINDOW_H_1
#define WINDOW_H_1

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <utility>
namespace ImView {

struct WindowData
{
    int width  {800};
    int height {600};
    bool is_resized{false};
    const char* title {"Window"};
};

class Window
{
public:
    explicit Window(const WindowData& data);
    ~Window();
    GLFWwindow* Get();
    bool Close() noexcept;
    [[nodiscard]] bool IsResized() const;
    [[nodiscard]] std::pair<int, int> GetSize() const noexcept;
    void Resized(bool flag) noexcept;
private:
    GLFWwindow* m_Window;
    WindowData m_Data;
    bool m_IsOpen;
};

}

#endif
