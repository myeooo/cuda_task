#include "Application.h"
#include <iostream>
#include "globalContext.h"
using namespace std;
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
    glfwSetFramebufferSizeCallback(
        m_Window.getNativeWindow(),
        [](GLFWwindow* win, int w, int h)
        {
            auto* window = static_cast<Window*>(glfwGetWindowUserPointer(win));
            if (window) window->onResize(w, h);
        }
    );

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
    if (!m_Renderer.init()) {
        std::cerr << "Failed to init Renderer\n";
        return false;
    }
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
    GlobalContext* context = GlobalContext::getGlobalContext();
    GLFWwindow* win = m_Window.getNativeWindow();
    if (glfwGetKey(m_Window.getNativeWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        context->focus3DView = false;
        
    }
    if(context->resetCamera) {
        m_Camera.resetCamera();
        context->resetCamera = false;
    }   
    if (!context->focus3DView)
        return;
    m_Camera.speed = context->moveRate;
    if (glfwGetKey(win, GLFW_KEY_W) == GLFW_PRESS)
        m_Camera.processKeyboard(GLFW_KEY_W);

    if (glfwGetKey(win, GLFW_KEY_S) == GLFW_PRESS)
        m_Camera.processKeyboard(GLFW_KEY_S);

    if (glfwGetKey(win, GLFW_KEY_A) == GLFW_PRESS)
        m_Camera.processKeyboard(GLFW_KEY_A);

    if (glfwGetKey(win, GLFW_KEY_D) == GLFW_PRESS)
        m_Camera.processKeyboard(GLFW_KEY_D);

    if (glfwGetKey(win, GLFW_KEY_SPACE) == GLFW_PRESS)
        m_Camera.position.y += m_Camera.speed;

    if (glfwGetKey(win, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
        m_Camera.position.y -= m_Camera.speed;
}

void Application::update()
{
    updateCursorMode();
}

void Application::updateCursorMode()
{
    GlobalContext* context = GlobalContext::getGlobalContext();

    if (context->focus3DView) {
        glfwSetInputMode(
            m_Window.getNativeWindow(),
            GLFW_CURSOR,
            GLFW_CURSOR_DISABLED
        );
    } else {
        glfwSetInputMode(
            m_Window.getNativeWindow(),
            GLFW_CURSOR,
            GLFW_CURSOR_NORMAL
        );
        
    }
}
void Application::render()
{

    // ===== PHASE 1: render scene vào FBO =====
    m_Renderer.renderScene(m_Camera, m_Window.width()*2/3, m_Window.height());

    // ===== PHASE 2: render ImGui =====
    m_ImGui.begin();
    m_ImGui.render(
        m_Renderer.getSceneFramebuffer()->getColorTexture()
    );
    m_ImGui.end();
}

void Application::onMouseMove(double xpos, double ypos) {
     auto context = GlobalContext::getGlobalContext(); 
    if (!context->focus3DView){
        s_LastX = xpos;
        s_LastY = ypos;
        return;
    }
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
