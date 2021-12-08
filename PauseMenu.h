#ifndef PAUSEMENU_H
#define PAUSEMENU_H

#include "IMenu.h"
#include "Scroll.h"

const int MAX_SPEED = 6; // 速度挡位数量 

class PauseMenu: public IMenu {
public:
    enum Terms {
        Resume = 0, Save = 1, Speed = 2, Quit = 3
    };
    
    PauseMenu();
    
    virtual std::string getTitle() const;
    virtual const std::vector<std::string>& getTerms() const;
    virtual void show() const;
    
    virtual void process();
    
    const Scroll* getSpeedScroll() const;
    Scroll* getSpeedScroll();
    
    void leftMoveActive();
    void rightMoveActive();
    
private:
    static int mSpeedState;
    Scroll mSpeed; // 速度卷滚条 
};

#endif

