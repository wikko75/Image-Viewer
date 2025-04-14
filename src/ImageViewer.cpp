#include "ImageViewer.h"
#include "Window.h"
#include "GuiManager.h"
#include <print>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <opencv2/opencv.hpp>

ImView::ImageViewer::ImageViewer()
    : m_Window     {nullptr}
    , m_GuiManager {nullptr}
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

    m_GuiManager = std::make_shared<GuiManager>(m_Window);
}

void ImView::ImageViewer::Run()
{
    // OPENCV TEST - not working yet, cause of the OpenGL state conflict
    // cv::Mat image = cv::imread("Dolphin_triangle_mesh.png", cv::IMREAD_COLOR);

    // if (image.empty()) {
    //     std::print("Can not load image");
    //     return;
    // }
    
    // cv::namedWindow("My image", cv::WINDOW_AUTOSIZE);
    // cv::imshow("My image", image);
    // cv::waitKey(0);

    while (m_Window->IsOpen()) {
        // rendering my stuff
        // ==========================
        glClearColor(0.494f, 0.078f, 0.91f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT);
        // ==========================
        m_GuiManager->OnUpdate();
        m_GuiManager->OnRender();
        glfwSwapBuffers(m_Window->Get());
        glfwPollEvents();
    }
}
