#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>

class Camera {
public:
    glm::vec3 position;
    float yaw, pitch;
    float speed = 0.05f;
    float sensitivity = 0.1f;

    Camera(glm::vec3 start = {0, 0, 10})
        : position(start), yaw(-90.0f), pitch(0.0f) {}

    glm::mat4 getViewMatrix();
    glm::mat4 getProjectionMatrix(float aspect, float fov = 45.0f);
    void processMouseMovement(float xoffset, float yoffset);

    void processKeyboard(int keydirection);
};

#endif
