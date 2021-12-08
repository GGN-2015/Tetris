#ifndef GAMELOSTMENU_H
#define GAMELOSTMENU_H

#include "IMenu.h"

class GameLostMenu: public IMenu {
public:
    GameLostMenu(int finalScore); // 游戏失败要给出总成绩 
    
    std::string getTitle() const;
    const std::vector<std::string>& getTerms() const;
    void show() const;
    void process();
    
    int getFinalScore() const;
    
private:
    int mFinalScore; // 记录最终成绩 
    
    GameLostMenu(const GameLostMenu&) = delete;
    GameLostMenu& operator= (const GameLostMenu&) = delete;
};

#endif

