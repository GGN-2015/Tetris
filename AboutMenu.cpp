#include <string>
#include <vector>

#include "AboutMenu.h"
#include "Controller.h"
#include "View.h"

AboutMenu::AboutMenu(std::string title, const std::vector<std::string>& messageList) {
    mMessageList = messageList;
    mTitle = title;
}

std::string AboutMenu::getTitle() const {
    return mTitle;
}

const std::vector<std::string>& AboutMenu::getTerms() const {
    static std::vector<std::string> terms
    {
        "OK"
    };
    return terms;
}

const std::vector<std::string>& AboutMenu::getMessageList() const {
    return mMessageList;
}

void AboutMenu::show() const {
    View::showAboutMenu(this);
}

void AboutMenu::process() {
    Controller::processAboutMenu(this);
}

