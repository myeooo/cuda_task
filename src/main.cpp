#include <iostream>
#include "app/globalContext.h"
#include "app/Application.h"

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
