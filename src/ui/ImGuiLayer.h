#ifndef IMGUILAYER_H
#define IMGUILAYER_H
#include "imgui3DSectionController.h"
#include "imgui3DSection.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

struct GLFWwindow;

class ImGuiLayer {
public:
    bool init(GLFWwindow* window);

    void begin();
    void render(GLuint texColor);   
    void end();

    void shutdown();
private:
    Imgui3DSection    section;
    Imgui3DSectionController controller;
};

#endif // IMGUILAYER_H
