#include <iostream>
#include "app/globalContext.h"
#include "app/Application.h"

// #include "imgui/section/imgui3DSectionController.h"
// #include "imgui/section/imgui3DSection.h"
// #include "3Dwindow/camera/camera.h"

using namespace std;

int main() {
    auto context = GlobalContext::getGlobalContext();
    Application app;
    if (!app.init()) {
        std::cerr << "Failed to initialize application\n";
        return -1;
    }

    app.run();

    return 0;
}
