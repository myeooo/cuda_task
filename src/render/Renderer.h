#include "Framebuffer.h"
#include "app/Window.h"
#ifndef RENDERER_H
#define RENDERER_H

class Renderer {
public:
    bool init();

    void beginFrame();
    void endFrame();
    Framebuffer* getSceneFramebuffer() { return &m_SceneFBO; }
    void setClearColor(float r, float g, float b, float a);
private:
    Framebuffer m_SceneFBO;
};

#endif // RENDERER_H
