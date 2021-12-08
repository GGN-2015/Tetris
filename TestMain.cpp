#include "App.h"
#include "MainMenu.h"
#include "MenuMgr.h"

int main() { // 用于测试的主程序 
    App app;
    app.initialize();
    app.run();
    app.terminate();
    return 0;
}

