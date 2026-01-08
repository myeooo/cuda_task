#include "ImGuiLayer.h"
#include "app/GlobalContext.h"

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

bool ImGuiLayer::init(GLFWwindow* window)
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGui::StyleColorsDark();
    if (!ImGui_ImplGlfw_InitForOpenGL(window, true))
        return false;

    if (!ImGui_ImplOpenGL3_Init("#version 330"))
        return false;
    
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, {0,0});
    return true;
}
void ImGuiLayer::begin()
{
    GlobalContext* context = GlobalContext::getGlobalContext();
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    
    ImGui::SetNextWindowPos({0,0});
    ImGui::SetNextWindowSize({(float)context->width,(float)context->height});
    ImGui::Begin("Panel", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoDecoration| ImGuiWindowFlags_NoInputs| ImGuiWindowFlags_NoNav);
}

void ImGuiLayer::render(GLuint texColor)
{
    ImGui::Text("OpenGL + ImGui running!");
    section.show(texColor);
    ImGui::SameLine();
    controller.show(texColor);
}
void ImGuiLayer::end()
{
    ImGui::End();
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void ImGuiLayer::shutdown()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}
