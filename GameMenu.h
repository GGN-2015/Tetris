#ifndef GAMEMENU_H
#define GAMEMENU_H

#include "IMenu.h" // 所有的菜单都由 IMenu 派生而来 

class GameMenu: public IMenu {
public:
    GameMenu(); // 设置 mLastTickTime 
    virtual std::string getMenuType() const; // 计算目录类型 
    
    // 并不是很关心 Title 和 Terms，因为并不输出 
    // 从 IMenu 派生只是为了服用 show 和 process 接口 
    virtual void show() const;
    virtual void process();
};

#endif

