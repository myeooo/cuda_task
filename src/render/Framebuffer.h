#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Framebuffer {
public:
    GLuint fbo;
    GLuint rbo;
    GLuint texColor;
    bool init(int width, int height);
    void bind();
    void unbind();

    unsigned int getColorTexture() const;
    void resize(int width, int height);
    void shutdown();
};
#endif // FRAMEBUFFER_H