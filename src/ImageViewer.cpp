#include "ImageViewer.h"
#include "Image.h"
#include "VertexBuffer.h"
#include "Window.h"
#include "GuiManager.h"
#include "FrameBuffer.h"
#include <filesystem>
#include <memory>
#include <print>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Shader.h"
#include "VertexArray.h"

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
    m_GuiManager = std::make_shared<GuiManager>(m_Window);
}

void ImView::ImageViewer::Run()
{
    std::array vertices = {
        //pos               tex. coors
	-0.5f, -0.5f, 0.0f,     0.0f, 0.0f,
	 0.5f, -0.5f, 0.0f,     1.0f, 0.0f,
	 0.5f,  0.5f, 0.0f,     1.0f, 1.0f,

	 0.5f,  0.5f, 0.0f,     1.0f, 1.0f,
	-0.5f,  0.5f, 0.0f,     0.0f, 1.0f,
	-0.5f, -0.5f, 0.0f,     0.0f, 0.0f
    };

    const auto base { std::filesystem::current_path() / "assets" / "shaders"};
    const std::string vertex_path { (base / "vertex.glsl").c_str() };
    const std::string fragment_path { (base / "fragment.glsl").c_str() };
    const std::string image_path { base.parent_path() / "images" / "Dolphin_triangle_mesh.png" };
    Shader shader { vertex_path, fragment_path };

    VertexArray vao {};
    vao.Bind();
    VertexBuffer vbo {vertices};
    Image image { image_path };

    shader.Bind();
    glUniform1i(glGetUniformLocation(shader.GetID(), "texture_sampler"), 0);

    while (m_Window->Close()) 
    {
        // rendering my stuff rendering to custom buffer
        // ==========================
        {
            m_Framebuffer->Bind();
            glClearColor(0.2f, 0.2f, 0.2f, 1.f);
            glClear(GL_COLOR_BUFFER_BIT);
            shader.Bind();
            vao.Bind();
            image.Show();
            glDrawArrays(GL_TRIANGLES, 0, 6);
            glBindFramebuffer(GL_FRAMEBUFFER, 0);
        }
        // ==========================
        m_GuiManager->OnUpdate(*m_Framebuffer);
        m_GuiManager->OnRender();
        glfwSwapBuffers(m_Window->Get());
        glfwPollEvents();
    }
}

