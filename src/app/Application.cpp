#ifndef APPLICATION_H
#define APPLICATION_H

#include "Window.h"
#include "render/camera.h"

class Application {
public:
    bool init();        
    void run();         
    void shutdown();    

private:
    void processInput(); 
    void update();       
    void render();      

    // thành phần lõi
    Window window;
    Camera camera;
    Framebuffer framebuffer;
    Renderer renderer;
    ImGuiLayer imgui;

    // dữ liệu compute (để chuyển cho CUDA)
    std::vector<float> simulationData;
};

#endif // APPLICATION_H