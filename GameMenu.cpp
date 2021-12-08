#include <ctime>
#include <iostream>

#include "App.h"
#include "Controller.h"
#include "GameMenu.h"
#include "View.h"

GameMenu::GameMenu() {
    
}

void GameMenu::show() const {
    View::showGameMenu(this); // 委托给 View 
}

void GameMenu::process() {
    Controller::processGameMenu(this); // 委托给 Controller 
}


std::string GameMenu::getMenuType() const {
    return "GameMenu";
}

