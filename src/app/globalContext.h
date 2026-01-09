#ifndef GLOBAL_CONTEXT_H
#define GLOBAL_CONTEXT_H
#include "imgui.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
class GlobalContext {
public:
    int width = 1280;
    int height = 720;
   
    ImGuiWindowFlags windowFlag = ImGuiWindowFlags_NoResize  | ImGuiWindowFlags_NoDecoration| ImGuiWindowFlags_NoNav;
    ImGuiChildFlags childFlag = ImGuiChildFlags_Borders;
    GLuint texColor;
    static GlobalContext* context;
    static GlobalContext* getGlobalContext();
    bool focus3DView = false;
    float moveRate = 0.1;
    bool resetCamera = false;

};

#endif // GLOBAL_CONTEXT_H
