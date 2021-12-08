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
    return "UnfinishedMenu <" + mPartName + ">" ; // 未做完的目录 
}

const std::vector<std::string>& UnfinishedMenu::getTerms() const {
    static std::vector<std::string> terms {"OK"}; // 除了 OK 你别无选择 
    return terms;
}

void UnfinishedMenu::show() const { // 老规矩, 托管给 View 
    View::showUnfinishedMenu(this);
}

void UnfinishedMenu::process() { // 老规矩, 托管给 Controller 
    Controller::processUnfinishedMenu(this);
}
