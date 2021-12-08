#include "Controller.h"
#include "MainMenu.h"
#include "View.h"

std::string MainMenu::getTitle() const { // 主菜单标题 
    return "MainMenu";
}

const std::vector<std::string>& MainMenu::getTerms() const {
    static std::vector<std::string> terms
    {
        "NewGame",    // 新游戏 
        "Load",       // 读取存档 
        "Settings",   // 修改设置 
        "About",      // 关于游戏内容 
        "Quit",       // 退出游戏 
    };
    return terms;
}

void MainMenu::show() const {
    View::showMainMenu(this); // 输出 MainMenu 对象 
}

void MainMenu::process() {
    Controller::processMainMenu(this); // 处理 MainMenu 的事件响应 
}

std::string MainMenu::getMenuType() const {
    return "MainMenu";
}
