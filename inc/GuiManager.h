#ifndef GUI_MANAGER_H
#define GUI_MANAGER_H

#include <memory>

namespace ImView {

class Window;
class FrameBuffer;

class GuiManager
{
public:
    explicit GuiManager(const std::shared_ptr<Window>& window, const std::shared_ptr<FrameBuffer>& image_framebuffer);
    ~GuiManager();
    void OnUpdate();
    void OnRender();

private:
    std::shared_ptr<Window> m_Window;
    std::shared_ptr<FrameBuffer> m_Image_framebuffer;
};

} // namespace ImView
#endif

