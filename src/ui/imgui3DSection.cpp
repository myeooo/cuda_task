#include "imgui3DSection.h"
#include "imgui.h"
// Khởi tạo biến static
#include "app/globalContext.h"


void Imgui3DSection::show(GLuint texColor) {
    GlobalContext* context = GlobalContext::getGlobalContext();
    ImGuiIO& io = ImGui::GetIO();
    ImGui::BeginChild("3D", {(float)context->width * 2/3, -1}, context->childFlag, context->windowFlag);
    ImGui::GetContentRegionAvail();
    ImGui::Image(
        (ImTextureID)(intptr_t)texColor,
        ImGui::GetContentRegionAvail(),
        ImVec2(0, 1), ImVec2(1, 0) // lật ảnh do OpenGL coord
    );
    ImGui::EndChild();
}
