#include "Controller.h"
#include "Game.h"
#include "GameMenu.h"
#include "PauseMenu.h"
#include "View.h"

PauseMenu::PauseMenu():mSpeed(MAX_SPEED) {
    // 暂停界面 
    mSpeed.setPos(mSpeedState);
}

int PauseMenu::mSpeedState = 0; // 当前速度 

std::string PauseMenu::getTitle() const {
    return "PauseMenu";
}

const std::vector<std::string>& PauseMenu::getTerms() const {
    static std::vector<std::string> terms
    {
        "Resume",
        "Save",
        "Speed",
        "Quit"
    };
    return terms;
}

void PauseMenu::show() const {
    View::showPauseMenu(this);
}

void PauseMenu::process() {
    Controller::processPauseMenu(this); 
}

const Scroll* PauseMenu::getSpeedScroll() const {
    return &mSpeed;
}

Scroll* PauseMenu::getSpeedScroll() {
    return &mSpeed;
}

void PauseMenu::leftMoveActive() {
    if(getActiveTermId() == Speed) {
        mSpeed.leftMove();
        mSpeedState = mSpeed.getPos();
        Game::getInstance().setSpeed(mSpeedState); // 修改游戏速度 
    }
}

void PauseMenu::rightMoveActive() {
    if(getActiveTermId() == Speed) {
        mSpeed.rightMove();
        mSpeedState = mSpeed.getPos();
        Game::getInstance().setSpeed(mSpeedState);
    }
}
