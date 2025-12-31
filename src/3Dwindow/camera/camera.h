#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera {
public:
    glm::vec3 position;
    float yaw, pitch;
    float speed = 0.05f;
    float sensitivity = 0.1f;

    Camera(glm::vec3 start = {0, 0, 3})
        : position(start), yaw(-90.0f), pitch(0.0f) {}

    glm::mat4 getViewMatrix() {
        glm::vec3 front;
        front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        front.y = sin(glm::radians(pitch));
        front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
        return glm::lookAt(position, position + glm::normalize(front), {0, 1, 0});
    }
    glm::mat4 getProjectionMatrix(float aspect, float fov = 45.0f) {
        float nearPlane = 0.1f;
        float farPlane  = 100.0f;
        return glm::perspective(glm::radians(fov), aspect, nearPlane, farPlane);
    }
    void processMouseMovement(float xoffset, float yoffset) {
        xoffset *= sensitivity;
        yoffset *= sensitivity;

        yaw   += xoffset;
        pitch += yoffset;

        if (pitch > 89.0f)
            pitch = 89.0f;
        if (pitch < -89.0f)
            pitch = -89.0f;
    }
    
    void processKeyboard(char direction) {
        glm::vec3 front;
        front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        front.y = sin(glm::radians(pitch));
        front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
        front = glm::normalize(front);
        glm::vec3 right = glm::normalize(glm::cross(front, {0, 1, 0}));

        if (direction == 'W')
            position += front * speed;
        if (direction == 'S')
            position -= front * speed;
        if (direction == 'A')
            position -= right * speed;
        if (direction == 'D')
            position += right * speed;
    }
};

#endif
