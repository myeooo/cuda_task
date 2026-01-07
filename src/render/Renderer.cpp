#include "Renderer.h"
#include <GL/glew.h>
#include "app/GlobalContext.h"

bool Renderer::init()
{
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    m_SceneFBO.init(
        GlobalContext::getGlobalContext()->width * 2 / 3,
        GlobalContext::getGlobalContext()->height
    );
    return true;
}

void Renderer::beginFrame()
{
    m_SceneFBO.bind();
    auto context = GlobalContext::getGlobalContext();
    glViewport(0, 0, context->width*2/3, context->height);
    glClearColor(0.8f, 0.8f, 0.8f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::endFrame()
{
    m_SceneFBO.unbind();
}

void Renderer::setClearColor(float r, float g, float b, float a)
{
    glClearColor(r, g, b, a);
}
