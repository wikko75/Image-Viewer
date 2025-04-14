#ifndef GUI_MANAGER_H
#define GUI_MANAGER_H

#include <memory>

namespace ImView {

class Window;

class GuiManager
{
public:
    GuiManager(const std::shared_ptr<Window>& window);
    ~GuiManager();
    void OnUpdate();
    void OnRender();

private:
    std::shared_ptr<Window> m_Window;
};

} // namespace ImView
#endif

