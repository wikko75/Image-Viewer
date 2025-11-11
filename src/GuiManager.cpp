#include "GuiManager.h"
#include "FrameBuffer.h"
#include "Window.h"
#include <imgui.h>
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <print>

ImView::GuiManager::GuiManager(const std::shared_ptr<Window>& window)
{
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // IF using Docking Branch

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window->Get(), true);    // Second param install_callback=true will install GLFW callbacks and chain to existing ones.
    ImGui_ImplOpenGL3_Init();

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
}

ImView::GuiManager::~GuiManager()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void ImView::GuiManager::OnUpdate(ImView::FrameBuffer& framebuffer)
{
    // Start the Dear ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();


    ImGui::DockSpaceOverViewport(0, ImGui::GetMainViewport());
    if (ImGui::BeginMainMenuBar()) {
        if (ImGui::BeginMenu("File")) {
            if (ImGui::MenuItem("Open", "Ctrl+O")) {
                std::print("Open file");
                std::fflush(stdout);
            };
            if (ImGui::MenuItem("Save", "Ctrl+S")) {;
                std::print("Save file");
                std::fflush(stdout);
            };
            
            ImGui::EndMenu();
        }
        
        ImGui::EndMainMenuBar();
    }
    if (ImGui::Begin("ViewPort"))
    {
        auto [current_width, current_height] {ImGui::GetContentRegionAvail()};
        auto [prev_width, prev_height]       {framebuffer.GetSize()};
        if (prev_width != static_cast<uint32_t>(current_width) || prev_height != static_cast<uint32_t>(current_height))
        {
            //TODO only changing struct, need to recreate framebuffer texture!
            framebuffer.Resize({ .width = static_cast<uint32_t>(current_width), .height = static_cast<uint32_t>(current_height)});
        }
        ImGui::Image(framebuffer.GetColorAttachment(), {current_width, current_height});
    }
    ImGui::End();
    ImGui::ShowDemoWindow(); // Show demo window! :)
}

void ImView::GuiManager::OnRender()
{
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
