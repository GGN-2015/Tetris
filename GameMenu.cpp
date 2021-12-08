#include <ctime>
#include <iostream>

#include "App.h"
#include "Controller.h"
#include "GameMenu.h"
#include "View.h"

GameMenu::GameMenu() {
    
}

void GameMenu::show() const {
    View::showGameMenu(this); // ί�и� View 
}

void GameMenu::process() {
    Controller::processGameMenu(this); // ί�и� Controller 
}


std::string GameMenu::getMenuType() const {
    return "GameMenu";
}

