#include "ImGuiLayer.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
bool ImGuiLayer::init()
{
    GLFWwindow* window = glfwGetCurrentContext();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
}

void ImGuiLayer::render()
{
}

void ImGuiLayer::shutdown()
{
}
