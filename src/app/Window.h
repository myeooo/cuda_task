#ifndef WINDOW_H
#define WINDOW_H

#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Window {
public:
    Window() = default;
    Window(int width, int height, const std::string& title);
    ~Window();

    bool init();
    void shutdown();

    void pollEvents();
    void swapBuffers();

    bool shouldClose() const;

    GLFWwindow* getNativeWindow() const;

private:
    GLFWwindow* m_Window = nullptr;

    int m_Width = 1280;
    int m_Height = 720;
    std::string m_Title = "4D Viz Start";
};

#endif // WINDOW_H
