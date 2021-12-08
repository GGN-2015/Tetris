#include <iostream>
#include <string>
#include <vector>

#include "Controller.h"
#include "IMenu.h"
#include "SettingsMenu.h"
#include "View.h"

SettingsMenu::SettingsMenu() { // do nothing
    
}

Scroll SettingsMenu::mVolumn(VOLUMN_MAX);        // 音量条 
Scroll SettingsMenu::mResolution(RESOLUTION_MAX); // 分辨率条 

std::string SettingsMenu::getTitle() const {
    return "SettingsMenu";
}

const std::vector<std::string>& SettingsMenu::getTerms() const{
    static std::vector<std::string> terms
    {
        "Volumn",
        "Resolution",
        "BackToMainMenu",
    };
    return terms;
}

void SettingsMenu::show() const {
    View::showSettngsMenu(this);
}

void SettingsMenu::process() {
    Controller::processSettingsMenu(this); // 把处理函数委托给 Controller 
}

void SettingsMenu::leftMoveActive() {
    if(getActiveTermId() == Volumn) {
        mVolumn.leftMove();
    }
    if(getActiveTermId() == Resolution) {
        mResolution.leftMove();
    }
}

void SettingsMenu::rightMoveActive() {
    if(getActiveTermId() == Volumn) {
        mVolumn.rightMove();
    }
    if(getActiveTermId() == Resolution) {
        mResolution.rightMove();
    }
}

const Scroll* SettingsMenu::getVolumnScroll() const {
    return &mVolumn;
}

const Scroll* SettingsMenu::getResolutionScroll() const {
    return &mResolution;
}

