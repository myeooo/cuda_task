#include "CircleRenderer.h"
#include "render/shader/shader.h"
#include <iostream>
using namespace std;
void CircleRenderer::init()
{
    float quad[] = {
        -1.f, -1.f,
         1.f, -1.f,
         1.f,  1.f,
        -1.f, -1.f,
         1.f,  1.f,
        -1.f,  1.f
    };

    glGenVertexArrays(1, &m_VAO);
    glGenBuffers(1, &m_VBO);

    glBindVertexArray(m_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quad), quad, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);

    glBindVertexArray(0);

    m_Shader = LoadShader("glsl/vertex_shader.glsl", "glsl/fragment_shader.glsl");
    cout << "[CircleRenderer] Shader ID: " << m_Shader << endl;
}

void CircleRenderer::draw(const glm::mat4& mvp, const glm::vec3& color)
{
    glUseProgram(m_Shader);

    glUniformMatrix4fv(
        glGetUniformLocation(m_Shader, "u_MVP"),
        1, GL_FALSE, &mvp[0][0]
    );

    glUniform3fv(
        glGetUniformLocation(m_Shader, "u_Color"),
        1, &color[0]
    );

    glBindVertexArray(m_VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}

void CircleRenderer::shutdown()
{
    glDeleteVertexArrays(1, &m_VAO);
    glDeleteBuffers(1, &m_VBO);
    glDeleteProgram(m_Shader);
}