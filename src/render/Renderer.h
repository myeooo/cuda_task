#ifndef RENDERER_H
#define RENDERER_H
#include "Camera.h"
#include "Framebuffer.h"
#include "app/Window.h"
#include <GL/glew.h>
#include "circleRenderer/CircleRenderer.h"
#include <GLFW/glfw3.h>
class Renderer {
public:
    bool init();
    void renderScene(Camera& camera, int width, int height);
    void beginFrame();
    void endFrame();
    Framebuffer* getSceneFramebuffer() { return &m_SceneFBO; }
    void setClearColor(float r, float g, float b, float a);
private:
    Framebuffer m_SceneFBO;
    CircleRenderer m_Circle;
};

#endif // RENDERER_H
