#ifndef APPLICATION_H
#define APPLICATION_H

#include "Window.h"
#include "render/camera.h"
#include "ui/ImGuiLayer.h"
#include "render/Framebuffer.h"
#include "render/Renderer.h"
#include "globalContext.h"
class Application
{
public:
    bool init();
    void run();
    void shutdown();
    ~Application();

private:

    void processInput();
    void update();
    void render();
    void onMouseMove(double xpos, double ypos);
    Window m_Window;
    Camera m_Camera;
    Renderer m_Renderer;
    ImGuiLayer m_ImGui;
    bool m_Running = true;

};

#endif // APPLICATION_H