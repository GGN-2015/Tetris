#include <string>
#include <vector>

#include "Controller.h"
#include "GameLostMenu.h"
#include "View.h"

GameLostMenu::GameLostMenu(int finalScore) {
    mFinalScore = finalScore;
}

std::string GameLostMenu::getTitle() const {
    return "GameLostMenu";
}

const std::vector<std::string>& GameLostMenu::getTerms() const {
    static std::vector<std::string> terms
    {
        "BackToMainMenu"
    };
    return terms;
}

void GameLostMenu::show() const {
    View::showGameLostMenu(this);
}

void GameLostMenu::process() {
    Controller::processGameLostMenu(this);
}

int GameLostMenu::getFinalScore() const {
    return mFinalScore;
}
