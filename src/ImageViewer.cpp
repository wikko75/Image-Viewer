#include "ImageViewer.h"
#include "Window.h"
#include "GuiManager.h"
#include "FrameBuffer.h"
#include <memory>
#include <print>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <opencv2/opencv.hpp>

ImView::ImageViewer::ImageViewer()
    : m_Window     {nullptr}
    , m_GuiManager {nullptr}
    , m_Framebuffer{nullptr}
{
    if (!glfwInit()) {
        std::print("Failed to initialize GLFW");
        return;
    }

    m_Window = std::make_shared<Window>(WindowData{800, 600, "Image Viewer"});

    if (glewInit() != GLEW_OK) {
        std::print("Failed to initialize GLEW");
        return;
    }

    m_Framebuffer = std::make_shared<FrameBuffer>();
    m_GuiManager = std::make_shared<GuiManager>(m_Window, m_Framebuffer);
}

void ImView::ImageViewer::Run()
{

    while (m_Window->Close()) {
        // rendering my stuff
        // ==========================
	//INFO rendering to custom buffer
	m_Framebuffer->Bind();
        glClearColor(0.494f, 0.078f, 0.91f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
        // ==========================
        m_GuiManager->OnUpdate();
        m_GuiManager->OnRender();
        glfwSwapBuffers(m_Window->Get());
        glfwPollEvents();
    }
}
