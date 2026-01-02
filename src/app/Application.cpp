#include "Application.h"

bool Application::init()
{
    if(!glfwInit()) {
        return false;
    }
    auto context = GlobalContext::getGlobalContext();
    window.init();
    imgui.init();
    processInput();
    return true;
}

void Application::run()
{

}

void Application::shutdown()
{
    glfwDestroyWindow(window.window);
}

void Application::processInput()
{
    glfwSetCursorPosCallback(window.window, mouseCallback);

}

void Application::update()
{
}

void Application::render()
{
}

void Application::mouseCallback(GLFWwindow* window, double xpos, double ypos) {
    Application* app = static_cast<Application*>(glfwGetWindowUserPointer(window));
    if (app) {
        app->onMouseMove(xpos, ypos);
    }
}

void Application::onMouseMove(double xpos, double ypos) {
    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }
    
    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; 
    lastX = xpos;
    lastY = ypos;

    camera.processMouseMovement(xoffset, yoffset);
}
