#include "Application.h"
#include <iostream>

namespace {
    bool s_FirstMouse = true;
    double s_LastX = 0.0;
    double s_LastY = 0.0;
}


bool Application::init()
{
    if (!glfwInit()) {
        std::cerr << "Failed to init GLFW\n";
        return false;
    }
    
    auto context = GlobalContext::getGlobalContext();
    if (!m_Window.init()) {
        std::cerr << "Failed to init Window\n";
        return false;
    }
    glfwSetWindowUserPointer(m_Window.getNativeWindow(), this);

    glfwSetCursorPosCallback(
        m_Window.getNativeWindow(),
        [](GLFWwindow* window, double xpos, double ypos)
        {
            auto* app = static_cast<Application*>(
                glfwGetWindowUserPointer(window)
            );
            if (app) {
                app->onMouseMove(xpos, ypos);
            }
        }
    );
    m_ImGui.init(m_Window.getNativeWindow());
    processInput();
    return true;
}

void Application::run()
{
    while (m_Running && !m_Window.shouldClose()) {
        m_Window.pollEvents();

        processInput();
        update();
        render();

        m_Window.swapBuffers();
    }

    shutdown();
}

void Application::shutdown()
{
    glfwDestroyWindow(m_Window.getNativeWindow());
    m_ImGui.shutdown();
    m_Window.shutdown();
    glfwTerminate();
}

Application::~Application()
{
}

void Application::processInput()
{
    if (glfwGetKey(m_Window.getNativeWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        m_Running = false;
    }
}

void Application::update()
{
}

void Application::render()
{
    m_Renderer.beginFrame();

    m_ImGui.begin();
    m_ImGui.render();
    m_ImGui.end();

    m_Renderer.endFrame();
}


void Application::onMouseMove(double xpos, double ypos) {
    if (s_FirstMouse) {
        s_LastX = xpos;
        s_LastY = ypos;
        s_FirstMouse = false;
    }

    float xoffset = xpos - s_LastX;
    float yoffset = s_LastY - ypos; 
    s_LastX = xpos;
    s_LastY = ypos;

    m_Camera.processMouseMovement(xoffset, yoffset);
}
