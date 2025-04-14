#ifndef IMAGE_VIEWER_H
#define IMAGE_VIEWER_H

#include <memory>

namespace ImView {

class Window;
class GuiManager;

class ImageViewer
{
public:
    explicit ImageViewer();
    void Run();
    ~ImageViewer() = default;
private:
    std::shared_ptr<Window>     m_Window;
    std::shared_ptr<GuiManager> m_GuiManager;
};

} // namespace ImView

#endif