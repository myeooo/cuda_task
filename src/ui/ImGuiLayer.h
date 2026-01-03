#ifndef IMGUILAYER_H
#define IMGUILAYER_H

struct GLFWwindow;

class ImGuiLayer {
public:
    bool init(GLFWwindow* window);

    void begin();
    void render();   
    void end();

    void shutdown();
};

#endif // IMGUILAYER_H
