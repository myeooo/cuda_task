#include <iostream>
#include "algorithm/vector_processing.h"
#include <vector>
#include <random>
#include <chrono>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include "app/globalContext.h"
#include "imgui/section/imgui3DSectionController.h"
#include "imgui/section/imgui3DSection.h"
#include "utils/draw_utils.h"
#include "3Dwindow/camera/camera.h"

using namespace std;
double lastX, lastY;
bool firstMouse = true;
Camera camera({0,0,10});
void mouseCallback(GLFWwindow* window, double xpos, double ypos) {
    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }
    
    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // đảo ngược vì hệ toạ độ màn hình
    lastX = xpos;
    lastY = ypos;

    camera.processMouseMovement(xoffset, yoffset);
}

bool open = true;
ImGuiWindowFlags windowFlag = ImGuiWindowFlags_NoResize  | ImGuiWindowFlags_NoDecoration| ImGuiWindowFlags_NoInputs| ImGuiWindowFlags_NoNav;
ImGuiChildFlags childFlag = ImGuiChildFlags_Borders;
int main() {
    auto context = GlobalContext::getGlobalContext();
    int numbTest = 1;
    glfwInit();
    GLFWwindow* window = glfwCreateWindow(context->width, context->height, "4D Viz Start", NULL, NULL);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);  
    glfwSetCursorPosCallback(window, mouseCallback);
    glfwMakeContextCurrent(window);
    glewInit();

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");
    // for (int i = 0 ; i < numbTest; i ++){
    //     VectorAlgorithm::scaleVectorWithConstants();
    // }
    glfwSetWindowSizeLimits(window, 1280, 720, GLFW_DONT_CARE,GLFW_DONT_CARE);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, {0,0});
    GLuint fbo, rbo;
    glGenFramebuffers(1, &fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);

    // texture sẽ chứa nội dung render 3D
    glGenTextures(1, &context->texColor);
    glBindTexture(GL_TEXTURE_2D, context->texColor);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, context->width*2/3, context->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, context->texColor, 0);

    // renderbuffer cho depth (bạn sẽ cần khi bắt đầu 3D)
    glGenRenderbuffers(1, &rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, rbo);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, context->width*2/3, context->height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);

    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        cout << "FBO Error!" << endl;
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    Imgui3DSectionController controller;
    Imgui3DSection threeDsection;
    while (!glfwWindowShouldClose(window)) {
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) camera.processKeyboard(GLFW_KEY_W);
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) camera.processKeyboard(GLFW_KEY_S);
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) camera.processKeyboard(GLFW_KEY_A);
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) camera.processKeyboard(GLFW_KEY_D);

        if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) camera.position.y += camera.speed;
        if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) camera.position.y -= camera.speed;
        
        glfwPollEvents();
        // === RENDER 3D INTO FBO ===
        glBindFramebuffer(GL_FRAMEBUFFER, fbo);
        glViewport(0, 0, context->width*2/3, context->height);

        // Clear nền xanh để test
        glClearColor(0.8f, 0.8f, 0.8f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // <--- SAU NÀY SẼ VẼ SCENE 3D, CAMERA, MESH TẠI ĐÂY
        
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();

        float aspect = (context->width * 2.0f/3) / (float)context->height;
        glm::mat4 proj = camera.getProjectionMatrix(aspect, 45.0f);
        glm::mat4 view = camera.getViewMatrix();

        // chuyển glm -> OpenGL matrix
        glLoadMatrixf(&proj[0][0]);
        glMatrixMode(GL_MODELVIEW);
        glLoadMatrixf(&view[0][0]);

        // ===== VẼ HAI HÌNH TRÒN =====
        glColor3f(1.0f, 1.0f, 1.0f); 
        DrawUtils::drawCircle(0.0f, 0.0f, 3.0f); // hình tròn đầu tiên

        glColor3f(1.0f, 0.0f, 0.0f);
        DrawUtils::drawCircle(4.0f, 0.0f, 3.0f); // hình thứ hai cách 4 đơn vị trên trục X

        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        glfwGetWindowSize(window, &context->width, &context->height);
        ImGui::SetNextWindowPos({0,0});
        ImGui::SetNextWindowSize({(float)context->width,(float)context->height});
        ImGui::Begin("Panel", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoDecoration| ImGuiWindowFlags_NoInputs| ImGuiWindowFlags_NoNav);
        ImGui::Text("OpenGL + ImGui running!");
        threeDsection.show();

        ImGui::SameLine();
        controller.show();
        ImGui::End();
        
        ImGui::Render();
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window);
    }
    ImGui::PopStyleVar();
    glfwDestroyWindow(window);

    return 0;
}
