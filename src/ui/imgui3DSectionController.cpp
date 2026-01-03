#include "imgui3DSectionController.h"
#include "imgui.h"
// Khởi tạo biến static
#include "app/globalContext.h"


void Imgui3DSectionController::show() {
    GlobalContext* context = GlobalContext::getGlobalContext();
    ImGuiIO& io = ImGui::GetIO();
    ImGui::BeginChild("ControlBar", {-1, -1}, context->childFlag, context->windowFlag);

    float fps = 1.0f / io.DeltaTime; 
    ImGui::Text("Frame rate: %.1f", fps);
    ImGui::EndChild();
}
