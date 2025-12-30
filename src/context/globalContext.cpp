#include "globalContext.h"

// Khởi tạo biến static
GlobalContext* GlobalContext::context = nullptr;

GlobalContext* GlobalContext::getGlobalContext() {
    if (!context) {
        context = new GlobalContext();
    }
    return context;
}
