#include "Renderer.h"

#include "app/GlobalContext.h"
#include "utils/draw_utils.h"

bool Renderer::init()
{
    glDepthFunc(GL_LESS);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    m_SceneFBO.init(
        GlobalContext::getGlobalContext()->width * 2 / 3,
        GlobalContext::getGlobalContext()->height
    );
    m_Circle.init();
    return true;
}

void Renderer::renderScene(Camera& camera, int width, int height)
{
    beginFrame();  // bind FBO + viewport

    float aspect = (float)width / (float)height;

    glm::mat4 proj = camera.getProjectionMatrix(aspect, 45.0f);
    glm::mat4 view = camera.getViewMatrix();

    glm::mat4 model1 = glm::mat4(1.0f);
    model1 = glm::translate(model1, glm::vec3(0.0f, 0.0f, 0.0f));
    model1 = glm::scale(model1, glm::vec3(3.0f));

    glm::mat4 mvp1 = proj * view * model1;
    m_Circle.draw(mvp1, {1, 1, 1});

    glm::mat4 model2 = glm::mat4(1.0f);
    model2 = glm::translate(model2, glm::vec3(4.0f, 0.0f, 0.0f));
    model2 = glm::scale(model2, glm::vec3(3.0f));

    glm::mat4 mvp2 = proj * view * model2;
    m_Circle.draw(mvp2, {1, 0, 0});

    endFrame();
}


void Renderer::beginFrame()
{
    m_SceneFBO.bind();
    auto context = GlobalContext::getGlobalContext();
    glViewport(0, 0, context->width*2/3, context->height);
    glClearColor(0.2, 0.2, 0.2, 1);
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
