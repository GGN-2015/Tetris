#include "App.h"
#include "MainMenu.h"
#include "MenuMgr.h"

int main() { // ���ڲ��Ե������� 
    App app;
    app.initialize();
    app.run();
    app.terminate();
    return 0;
}

