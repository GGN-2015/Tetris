#ifndef GAMELOSTMENU_H
#define GAMELOSTMENU_H

#include "IMenu.h"

class GameLostMenu: public IMenu {
public:
    GameLostMenu(int finalScore); // ��Ϸʧ��Ҫ�����ܳɼ� 
    
    std::string getTitle() const;
    const std::vector<std::string>& getTerms() const;
    void show() const;
    void process();
    
    int getFinalScore() const;
    
private:
    int mFinalScore; // ��¼���ճɼ� 
    
    GameLostMenu(const GameLostMenu&) = delete;
    GameLostMenu& operator= (const GameLostMenu&) = delete;
};

#endif

