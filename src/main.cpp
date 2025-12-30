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
using namespace std;

int width = 1280;
int height = 720;
bool open = true;
ImGuiWindowFlags windowFlag = ImGuiWindowFlags_NoResize  | ImGuiWindowFlags_NoDecoration| ImGuiWindowFlags_NoInputs| ImGuiWindowFlags_NoNav;
ImGuiChildFlags childFlag = ImGuiChildFlags_Borders;
int main() {
    int numbTest = 1;
    glfwInit();
    GLFWwindow* window = glfwCreateWindow(width, height, "4D Viz Start", NULL, NULL);
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
    GLuint fbo, texColor, rbo;
    glGenFramebuffers(1, &fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);

    // texture sẽ chứa nội dung render 3D
    glGenTextures(1, &texColor);
    glBindTexture(GL_TEXTURE_2D, texColor);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width*2/3, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texColor, 0);

    // renderbuffer cho depth (bạn sẽ cần khi bắt đầu 3D)
    glGenRenderbuffers(1, &rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, rbo);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width*2/3, height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);

    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        cout << "FBO Error!" << endl;
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        // === RENDER 3D INTO FBO ===
        glBindFramebuffer(GL_FRAMEBUFFER, fbo);
        glViewport(0, 0, width*2/3, height);

        // Clear nền xanh để test
        glClearColor(0.0f, 0.2f, 0.4f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // <--- SAU NÀY SẼ VẼ SCENE 3D, CAMERA, MESH TẠI ĐÂY
        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        glfwGetWindowSize(window, &width, &height);
        ImGui::SetNextWindowPos({0,0});
        ImGui::SetNextWindowSize({(float)width,(float)height});
        ImGui::Begin("Panel", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoDecoration| ImGuiWindowFlags_NoInputs| ImGuiWindowFlags_NoNav);
        ImGui::Text("OpenGL + ImGui running!");
        ImGui::BeginChild("3D", {(float)width * 2/3, -1}, childFlag, windowFlag);
        ImGui::Image(
            (ImTextureID)(intptr_t)texColor,
            ImVec2(width * 2/3, height),
            ImVec2(0, 1), ImVec2(1, 0) // lật ảnh do OpenGL coord
        );
        ImGui::EndChild();

        ImGui::SameLine();
        ImGuiIO& io = ImGui::GetIO();
        ImGui::BeginChild("ControlBar", {-1, -1}, childFlag, windowFlag);

        float fps = 1.0f / io.DeltaTime; 
        ImGui::Text("Frame rate: %.1f", fps);
        ImGui::EndChild();
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
