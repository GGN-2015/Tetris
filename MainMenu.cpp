#include "Controller.h"
#include "MainMenu.h"
#include "View.h"

std::string MainMenu::getTitle() const { // ���˵����� 
    return "MainMenu";
}

const std::vector<std::string>& MainMenu::getTerms() const {
    static std::vector<std::string> terms
    {
        "NewGame",    // ����Ϸ 
        "Load",       // ��ȡ�浵 
        "Settings",   // �޸����� 
        "About",      // ������Ϸ���� 
        "Quit",       // �˳���Ϸ 
    };
    return terms;
}

void MainMenu::show() const {
    View::showMainMenu(this); // ��� MainMenu ���� 
}

void MainMenu::process() {
    Controller::processMainMenu(this); // ���� MainMenu ���¼���Ӧ 
}

std::string MainMenu::getMenuType() const {
    return "MainMenu";
}
