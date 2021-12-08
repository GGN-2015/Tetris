#include <string>

#include "Controller.h"
#include "UnfinishedMenu.h"
#include "View.h"

UnfinishedMenu::UnfinishedMenu() {
    mPartName = "Unknown Part";
}

UnfinishedMenu::UnfinishedMenu(std::string partName) {
    mPartName = partName;
}

std::string UnfinishedMenu::getTitle() const {
    return "UnfinishedMenu <" + mPartName + ">" ; // δ�����Ŀ¼ 
}

const std::vector<std::string>& UnfinishedMenu::getTerms() const {
    static std::vector<std::string> terms {"OK"}; // ���� OK �����ѡ�� 
    return terms;
}

void UnfinishedMenu::show() const { // �Ϲ��, �йܸ� View 
    View::showUnfinishedMenu(this);
}

void UnfinishedMenu::process() { // �Ϲ��, �йܸ� Controller 
    Controller::processUnfinishedMenu(this);
}
