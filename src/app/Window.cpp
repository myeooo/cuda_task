#include "Window.h"
#include <string>
bool Window::init()
{
    GLFWwindow* window = glfwCreateWindow(width, height, name.c_str(), NULL, NULL);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL); 
    glfwMakeContextCurrent(window);
    glewInit();
    glfwSetWindowSizeLimits(window, 1280, 720, GLFW_DONT_CARE,GLFW_DONT_CARE);

    glfwSetCursorPosCallback(window, mouseCallback);
    return false;
}


