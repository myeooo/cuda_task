#include "camera.h"

glm::mat4 Camera::getViewMatrix()
{
    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    return glm::lookAt(position, position + glm::normalize(front), {0, 1, 0});
}
glm::mat4 Camera::getProjectionMatrix(float aspect, float fov)
{
    float nearPlane = 0.1f;
    float farPlane = 100.0f;
    return glm::perspective(glm::radians(fov), aspect, nearPlane, farPlane);
}
void Camera::processMouseMovement(float xoffset, float yoffset)
{
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch += yoffset;

    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;
}
void Camera::processKeyboard(int keydirection)
{
    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    front = glm::normalize(front);
    glm::vec3 right = glm::normalize(glm::cross(front, {0, 1, 0}));

    if (keydirection == GLFW_KEY_W)
        position += front * speed;
    if (keydirection == GLFW_KEY_S)
        position -= front * speed;
    if (keydirection == GLFW_KEY_A)
        position -= right * speed;
    if (keydirection == GLFW_KEY_D)
        position += right * speed;
}
