#ifndef WINDOW_H
#define WINDOW_H

#include "render/camera.h"
#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
using namespace std;
class Window {
public:
    GLFWwindow* window;
    bool init();        
    int width = 1280;
    int height = 720;
    string name = "4D Viz Start";
};

#endif // WINDOW_H