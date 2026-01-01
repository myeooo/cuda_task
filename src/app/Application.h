#ifndef APPLICATION_H
#define APPLICATION_H

#include "Window.h"
#include "render/camera.h"
#include "ui/ImGuiLayer.h"
#include "render/Framebuffer.h"
#include "render/Renderer.h"

class Application {
public:
    bool init();        
    void run();         
    void shutdown();    

private:
    bool firstMouse = true;
    double lastX, lastY;
    void processInput(); 
    void update();       
    void render();   
    void onMouseMove(double xpos, double ypos);   
    static void mouseCallback(GLFWwindow* window, double xpos, double ypos);
    Window window;
    Camera camera;
    Framebuffer framebuffer;
    Renderer renderer;
    ImGuiLayer imgui;

};

#endif // APPLICATION_H