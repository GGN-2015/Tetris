// 现在只是一个原型版本，将来一定会更改输出方式 

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
    getScreen() -> drawMargin(CharPixel("□"));
    getScreen() -> newLine(2);
    
    getScreen() -> appendMarginNewLine(imenu -> getTitle().c_str(), 2, 2); // 输出标题 
    
    for(int id = 0; id < imenu -> getTermsCount(); id ++) {
        getScreen() -> jumpMargin(2);
        if(id == imenu -> getActiveTermId()) { // 当前被选中的项 
            getScreen() -> appendString(" => ", ConsoleColor::RED);
            getScreen() -> appendString(imenu -> getTerms()[id].c_str());
        }else { // 当前没有被选中的项 
            getScreen() -> appendString("    ", ConsoleColor::RED);
            getScreen() -> appendString(imenu -> getTerms()[id].c_str());
        }
        getScreen() -> newLine(2);
    }
}

void View::showMainMenu(const MainMenu* mainMenu) {
    showIMenu(mainMenu); // 目前暂时采用相同的方式进行输出，以后可能会更改 
    
    getScreen() -> appendMarginNewLine("Use Up/Down to select term", 2, 1, ConsoleColor::YELLOW);
    getScreen() -> appendMarginNewLine("use Enter to confirm.", 2, 1, ConsoleColor::YELLOW);

    getScreen() -> display();
}

void View::showSettngsMenu(const SettingsMenu* settingsMenu) {
    showIMenu(settingsMenu); // 目前暂时采用相同的方式进行输出，以后可能会更改 
    
    getScreen() -> appendMarginNewLine("Use Up/Down to select term", 2, 1, ConsoleColor::YELLOW);
    getScreen() -> appendMarginNewLine("Use Left/Right to change the value.", 2, 2, ConsoleColor::YELLOW);
    
    View::showScroll(
        "Volumn     ", 
        settingsMenu -> getVolumnScroll(), // 显示 音量水平卷滚条 
        settingsMenu -> getActiveTermId() == SettingsMenu::Volumn
    );
    View::showScroll(
        "Resolution ", 
        settingsMenu -> getResolutionScroll(), // 显示分辨率水平卷滚条 
        settingsMenu -> getActiveTermId() == SettingsMenu::Resolution
    );
    
    getScreen() -> display();
}

void View::showScroll(const char* scrollName, const Scroll* scroll, bool highlight) {
    // Scroll [===================>] 输出一个水平卷滚条 
    
    const int SCROLL_LENGTH = 20; // 水平卷滚条的最大长度 
    std::string message = "";
    message += "[";
    for(int i = 1; i <= SCROLL_LENGTH; i ++) {
        double rateNow = double(i)/SCROLL_LENGTH;
        double rateNxt = double(i+1)/SCROLL_LENGTH;
        if(i == 1 && scroll -> getRate() == 0) {
            message += ">";
        }else {
            if(rateNow > scroll -> getRate()) {
                message += " "; // 空格 
            }else {
                if(rateNxt > scroll -> getRate()) { // 最后一个位置用 '>' 
                    message += ">";
                }else {
                    message += "=";
                }
            }
        }
    }
    message += "]";
    getScreen() -> appendMarginNewLine(
        "  * ", 2, 0, // 0 表示不新建一行内容 
        highlight ? ConsoleColor::RED : ConsoleColor::WHITE // 决定是否高亮显示 
    );
    getScreen() -> appendMarginNewLine(scrollName, 0, 0);
    getScreen() -> appendMarginNewLine(
        message.c_str(), 0, 2,
        highlight ? ConsoleColor::RED : ConsoleColor::WHITE // 决定是否高亮显示 
    );
}

Screen* View::getScreen() { // 获取画布 
    return &mScreen;
}

void View::showUnfinishedMenu(const UnfinishedMenu* unfinishedMenu) { // 显示未完成的页面 
    showIMenu(unfinishedMenu);
    getScreen() -> appendMarginNewLine("use Enter to confirm.", 2, 2, ConsoleColor::YELLOW);
    getScreen() -> appendMarginNewLine("You see this page ", 2, 1, ConsoleColor::BLUE);
    getScreen() -> appendMarginNewLine("because this part is not finished.", 2, 1, ConsoleColor::BLUE);
    
    getScreen() -> display();
}

void View::showChessboard(const Chessboard* chessboard) {
    getScreen() -> drawMargin(CharPixel("□"));
    for(int i = 0; i < CHESSBOARD_HEIGHT + 2; i ++) {
        for(int j = 0; j < CHESSBOARD_WIDTH + 2; j ++) {
            int x = i - 1, y = j - 1; // 棋盘内坐标 
            int colorId = chessboard -> getViewPosColor(x, y);
            if(colorId) {
                getScreen() -> setPixel(i, j, CharPixel("□", colorId));
            }else {
                getScreen() -> setPixel(i, j, CharPixel("  ", ConsoleColor::WHITE));
            }
        }
    }
    // 由于是控件，所以不写 getScreen() -> display();
    // 绘制一个 chessboard 到屏幕 
}

void View::showGameMenu(const GameMenu* gameMenu) {
    View::showChessboard(Game::getInstance().getChessboard());
    
    char nowScore[15]; sprintf(nowScore, "%d", Game::getInstance().getScore()); // 获取成绩字符串 
    
    getScreen() -> newLine(2); // 显示分数 
    getScreen() -> appendMarginNewLine("Now Score:", CHESSBOARD_WIDTH + 4, 1, ConsoleColor::WHITE);
    getScreen() -> appendMarginNewLine(nowScore, CHESSBOARD_WIDTH + 4, 2, ConsoleColor::YELLOW);
    getScreen() -> appendMarginNewLine("Esc to pause.", CHESSBOARD_WIDTH + 4, 1, ConsoleColor::YELLOW);
    getScreen() -> appendMarginNewLine("Space to set.", CHESSBOARD_WIDTH + 4, 1, ConsoleColor::YELLOW);
    
    getScreen() -> display();
}

void View::showPauseMenu(const PauseMenu* pauseMenu) {
    showIMenu(pauseMenu); // 目前暂时采用相同的方式进行输出，以后可能会更改 
    
    getScreen() -> appendMarginNewLine("Use Up/Down to select term", 2, 1, ConsoleColor::YELLOW);
    getScreen() -> appendMarginNewLine("Use Left/Right to change the value.", 2, 2, ConsoleColor::YELLOW);
    
    View::showScroll(
        "Speed      ", 
        pauseMenu -> getSpeedScroll(), // 显示 音量水平卷滚条 
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
    
    getScreen() -> display(); // 记得 display，不然不显示了 
}

void View::showAboutMenu(const AboutMenu* aboutMenu) {
    showIMenu(aboutMenu);
    
    for(auto listItem: aboutMenu -> getMessageList()) {
        getScreen() -> appendMarginNewLine(listItem.c_str(), 2, 1, ConsoleColor::YELLOW);
    }
    
    getScreen() -> display(); // 记得 display，不然不显示了 
}

void View::showLoadMenu(const LoadMenu* loadMenu) { // 直接用 IMenu 输出即可 
    showIMenu(loadMenu);
    getScreen() -> display(); // 记得 display，不然不显示了 
}

