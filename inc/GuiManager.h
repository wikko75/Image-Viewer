#ifndef GUI_MANAGER_H
#define GUI_MANAGER_H

#include <memory>

namespace ImView {

class Window;
class FrameBuffer;

class GuiManager
{
public:
    explicit GuiManager(const std::shared_ptr<Window>& window);
    ~GuiManager();
    void OnUpdate(FrameBuffer& image_framebuffer);
    void OnRender();
};

} // namespace ImView

#endif

