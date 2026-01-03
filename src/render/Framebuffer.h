#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H


class Framebuffer {
public:
    bool init(int width, int height);
    void bind();
    void unbind();

    unsigned int getColorTexture() const;
    void resize(int width, int height);
    void shutdown();
};
#endif // FRAMEBUFFER_H