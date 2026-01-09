#include "imgui3DSectionController.h"
#include "imgui.h"
// Khởi tạo biến static
#include "app/globalContext.h"


void Imgui3DSectionController::show(GLuint texColor) {
    static int test = 1;
    GlobalContext* context = GlobalContext::getGlobalContext();
    ImGuiIO& io = ImGui::GetIO();
    // if (context->focus3DView ){
    //     return;
    // }
    ImGui::BeginChild("ControlBar", {-1, -1}, context->childFlag, context->windowFlag);

    float fps = 1.0f / io.DeltaTime; 
    ImGui::Text("Frame rate: %.1f", fps);
    ImGui::Text("texColor: %d", texColor);
    if(ImGui::Button("focus 3D view")) {
        context->focus3DView = true;
    }
    if(ImGui::Button("reset Camera Position")) {
        context->resetCamera = true;
    }
    ImGui::DragFloat("keyboard move rate " , &context->moveRate, 0.005f, 0.0001f, 20.0f, "%0.4f");
    ImGui::EndChild();
}
