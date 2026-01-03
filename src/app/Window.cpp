#include "Window.h"
#include <iostream>

bool Window::init()
{
    m_Window = glfwCreateWindow(
        m_Width,
        m_Height,
        m_Title.c_str(),
        nullptr,
        nullptr
    );

    if (!m_Window) {
        std::cerr << "Failed to create GLFW window\n";
        return false;
    }

    glfwMakeContextCurrent(m_Window);

    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to init GLEW\n";
        return false;
    }

    glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    glfwSetWindowSizeLimits(m_Window, 1280, 720, GLFW_DONT_CARE, GLFW_DONT_CARE);

    return true;
}

void Window::shutdown()
{
    if (m_Window) {
        glfwDestroyWindow(m_Window);
        m_Window = nullptr;
    }
}

Window::Window(int width, int height, const std::string &title)
    : m_Width(width), m_Height(height), m_Title(title)
{
}

Window::~Window()
{
    shutdown();
}

void Window::pollEvents()
{
    glfwPollEvents();
}

void Window::swapBuffers()
{
    glfwSwapBuffers(m_Window);
}

bool Window::shouldClose() const
{
    return glfwWindowShouldClose(m_Window);
}

GLFWwindow* Window::getNativeWindow() const
{
    return m_Window;
}
