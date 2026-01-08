#ifndef CIRCLE_RENDERER_H
#define CIRCLE_RENDERER_H
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
class CircleRenderer {
public:
    void init();
    void draw(const glm::mat4& mvp, const glm::vec3& color);
    void shutdown();

private:
    unsigned int m_VAO = 0;
    unsigned int m_VBO = 0;
    unsigned int m_Shader = 0;
};

#endif // CIRCLE_RENDERER_H