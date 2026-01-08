#include "Application.h"
#include <iostream>
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
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    float aspect = (m_Window.width() * 2.0f/3) / (float)m_Window.height();
    glm::mat4 proj = m_Camera.getProjectionMatrix(aspect, 45.0f);
    glm::mat4 view = m_Camera.getViewMatrix();

    // chuyển glm -> OpenGL matrix
    glLoadMatrixf(&proj[0][0]);
    glMatrixMode(GL_MODELVIEW);
    glLoadMatrixf(&view[0][0]);

    // ===== VẼ HAI HÌNH TRÒN =====
    glColor3f(1.0f, 1.0f, 1.0f); 
    DrawUtils::drawCircle(0.0f, 0.0f, 3.0f); 

    glColor3f(1.0f, 0.0f, 0.0f);
    DrawUtils::drawCircle(4.0f, 0.0f, 3.0f);
}

void Application::render()
{
    auto context = GlobalContext::getGlobalContext();
    m_Renderer.beginFrame();    
    glfwGetWindowSize(m_Window.getNativeWindow(), &context->width, &context->height);
    m_ImGui.begin();
    auto texColor = m_Renderer.getSceneFramebuffer()->getColorTexture();
    cout << "Rendering with texColor: " << texColor << endl;
    m_ImGui.render(texColor);
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
