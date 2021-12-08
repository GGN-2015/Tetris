// ����ֻ��һ��ԭ�Ͱ汾������һ������������ʽ 

#include <iostream>  
#include <cstdlib>
#include <string>

#include "AboutMenu.h"
#include "Chessboard.h"
#include "Game.h"
#include "GameLostMenu.h"
#include "GameMenu.h"
#include "IMenu.h"
#include "LoadMenu.h"
#include "MainMenu.h"
#include "PauseMenu.h"
#include "Screen.h"
#include "Scroll.h"
#include "SettingsMenu.h"
#include "UnfinishedMenu.h"
#include "View.h"

Screen View::mScreen = Screen(0, 0, MAX_HEIGHT, MAX_WIDTH);

void View::showIMenu(const IMenu* imenu) {
    getScreen() -> drawMargin(CharPixel("��"));
    getScreen() -> newLine(2);
    
    getScreen() -> appendMarginNewLine(imenu -> getTitle().c_str(), 2, 2); // ������� 
    
    for(int id = 0; id < imenu -> getTermsCount(); id ++) {
        getScreen() -> jumpMargin(2);
        if(id == imenu -> getActiveTermId()) { // ��ǰ��ѡ�е��� 
            getScreen() -> appendString(" => ", ConsoleColor::RED);
            getScreen() -> appendString(imenu -> getTerms()[id].c_str());
        }else { // ��ǰû�б�ѡ�е��� 
            getScreen() -> appendString("    ", ConsoleColor::RED);
            getScreen() -> appendString(imenu -> getTerms()[id].c_str());
        }
        getScreen() -> newLine(2);
    }
}

void View::showMainMenu(const MainMenu* mainMenu) {
    showIMenu(mainMenu); // Ŀǰ��ʱ������ͬ�ķ�ʽ����������Ժ���ܻ���� 
    
    getScreen() -> appendMarginNewLine("Use Up/Down to select term", 2, 1, ConsoleColor::YELLOW);
    getScreen() -> appendMarginNewLine("use Enter to confirm.", 2, 1, ConsoleColor::YELLOW);

    getScreen() -> display();
}

void View::showSettngsMenu(const SettingsMenu* settingsMenu) {
    showIMenu(settingsMenu); // Ŀǰ��ʱ������ͬ�ķ�ʽ����������Ժ���ܻ���� 
    
    getScreen() -> appendMarginNewLine("Use Up/Down to select term", 2, 1, ConsoleColor::YELLOW);
    getScreen() -> appendMarginNewLine("Use Left/Right to change the value.", 2, 2, ConsoleColor::YELLOW);
    
    View::showScroll(
        "Volumn     ", 
        settingsMenu -> getVolumnScroll(), // ��ʾ ����ˮƽ����� 
        settingsMenu -> getActiveTermId() == SettingsMenu::Volumn
    );
    View::showScroll(
        "Resolution ", 
        settingsMenu -> getResolutionScroll(), // ��ʾ�ֱ���ˮƽ����� 
        settingsMenu -> getActiveTermId() == SettingsMenu::Resolution
    );
    
    getScreen() -> display();
}

void View::showScroll(const char* scrollName, const Scroll* scroll, bool highlight) {
    // Scroll [===================>] ���һ��ˮƽ����� 
    
    const int SCROLL_LENGTH = 20; // ˮƽ���������󳤶� 
    std::string message = "";
    message += "[";
    for(int i = 1; i <= SCROLL_LENGTH; i ++) {
        double rateNow = double(i)/SCROLL_LENGTH;
        double rateNxt = double(i+1)/SCROLL_LENGTH;
        if(i == 1 && scroll -> getRate() == 0) {
            message += ">";
        }else {
            if(rateNow > scroll -> getRate()) {
                message += " "; // �ո� 
            }else {
                if(rateNxt > scroll -> getRate()) { // ���һ��λ���� '>' 
                    message += ">";
                }else {
                    message += "=";
                }
            }
        }
    }
    message += "]";
    getScreen() -> appendMarginNewLine(
        "  * ", 2, 0, // 0 ��ʾ���½�һ������ 
        highlight ? ConsoleColor::RED : ConsoleColor::WHITE // �����Ƿ������ʾ 
    );
    getScreen() -> appendMarginNewLine(scrollName, 0, 0);
    getScreen() -> appendMarginNewLine(
        message.c_str(), 0, 2,
        highlight ? ConsoleColor::RED : ConsoleColor::WHITE // �����Ƿ������ʾ 
    );
}

Screen* View::getScreen() { // ��ȡ���� 
    return &mScreen;
}

void View::showUnfinishedMenu(const UnfinishedMenu* unfinishedMenu) { // ��ʾδ��ɵ�ҳ�� 
    showIMenu(unfinishedMenu);
    getScreen() -> appendMarginNewLine("use Enter to confirm.", 2, 2, ConsoleColor::YELLOW);
    getScreen() -> appendMarginNewLine("You see this page ", 2, 1, ConsoleColor::BLUE);
    getScreen() -> appendMarginNewLine("because this part is not finished.", 2, 1, ConsoleColor::BLUE);
    
    getScreen() -> display();
}

void View::showChessboard(const Chessboard* chessboard) {
    getScreen() -> drawMargin(CharPixel("��"));
    for(int i = 0; i < CHESSBOARD_HEIGHT + 2; i ++) {
        for(int j = 0; j < CHESSBOARD_WIDTH + 2; j ++) {
            int x = i - 1, y = j - 1; // ���������� 
            int colorId = chessboard -> getViewPosColor(x, y);
            if(colorId) {
                getScreen() -> setPixel(i, j, CharPixel("��", colorId));
            }else {
                getScreen() -> setPixel(i, j, CharPixel("  ", ConsoleColor::WHITE));
            }
        }
    }
    // �����ǿؼ������Բ�д getScreen() -> display();
    // ����һ�� chessboard ����Ļ 
}

void View::showGameMenu(const GameMenu* gameMenu) {
    View::showChessboard(Game::getInstance().getChessboard());
    
    char nowScore[15]; sprintf(nowScore, "%d", Game::getInstance().getScore()); // ��ȡ�ɼ��ַ��� 
    
    getScreen() -> newLine(2); // ��ʾ���� 
    getScreen() -> appendMarginNewLine("Now Score:", CHESSBOARD_WIDTH + 4, 1, ConsoleColor::WHITE);
    getScreen() -> appendMarginNewLine(nowScore, CHESSBOARD_WIDTH + 4, 2, ConsoleColor::YELLOW);
    getScreen() -> appendMarginNewLine("Esc to pause.", CHESSBOARD_WIDTH + 4, 1, ConsoleColor::YELLOW);
    getScreen() -> appendMarginNewLine("Space to set.", CHESSBOARD_WIDTH + 4, 1, ConsoleColor::YELLOW);
    
    getScreen() -> display();
}

void View::showPauseMenu(const PauseMenu* pauseMenu) {
    showIMenu(pauseMenu); // Ŀǰ��ʱ������ͬ�ķ�ʽ����������Ժ���ܻ���� 
    
    getScreen() -> appendMarginNewLine("Use Up/Down to select term", 2, 1, ConsoleColor::YELLOW);
    getScreen() -> appendMarginNewLine("Use Left/Right to change the value.", 2, 2, ConsoleColor::YELLOW);
    
    View::showScroll(
        "Speed      ", 
        pauseMenu -> getSpeedScroll(), // ��ʾ ����ˮƽ����� 
        pauseMenu -> getActiveTermId() == PauseMenu::Speed
    );
    
    getScreen() -> display();
}

void View::showGameLostMenu(const GameLostMenu* gameLostMenu) {
    showIMenu(gameLostMenu);
    
    getScreen() -> appendMarginNewLine("Final Score:", 2, 1, ConsoleColor::WHITE);
    
    char finalScore[15]; sprintf(finalScore, "%d", gameLostMenu -> getFinalScore());
    getScreen() -> appendMarginNewLine(finalScore, 2, 2, ConsoleColor::YELLOW);
    getScreen() -> appendMarginNewLine("Press Enter to continue.", 2, 1, ConsoleColor::YELLOW);
    
    getScreen() -> display(); // �ǵ� display����Ȼ����ʾ�� 
}

void View::showAboutMenu(const AboutMenu* aboutMenu) {
    showIMenu(aboutMenu);
    
    for(auto listItem: aboutMenu -> getMessageList()) {
        getScreen() -> appendMarginNewLine(listItem.c_str(), 2, 1, ConsoleColor::YELLOW);
    }
    
    getScreen() -> display(); // �ǵ� display����Ȼ����ʾ�� 
}

void View::showLoadMenu(const LoadMenu* loadMenu) { // ֱ���� IMenu ������� 
    showIMenu(loadMenu);
    getScreen() -> display(); // �ǵ� display����Ȼ����ʾ�� 
}

