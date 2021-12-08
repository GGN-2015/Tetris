#include <conio.h>
#include <cstdio>
#include <ctime>
#include <windows.h>

#include "Console.h"
#include "Event.h"
#include "Game.h"
#include "GameMenu.h"
#include "IMenu.h"

int Event::inactiveTime = - inactiveLength; // 默认没有失活 

KeyList Event::keyListNow;
KeyList Event::keyListLast;

void KeyList::getKeyList() {
    mKeyLeft  = Console::keyDown(VK_LEFT);
    mKeyRight = Console::keyDown(VK_RIGHT);
    mKeyUp    = Console::keyDown(VK_UP);
    mKeyDown  = Console::keyDown(VK_DOWN);
    mKeyEnter = Console::keyDown(VK_RETURN); // 检测是否是指定的按键被按下了 
    mKeyEsc   = Console::keyDown(VK_ESCAPE);
    mKeySpace = Console::keyDown(VK_SPACE);
}

void KeyList::clearKeyList() {
    mKeyLeft  = 0;
    mKeyRight = 0;
    mKeyUp    = 0;
    mKeyDown  = 0;
    mKeyEnter = 0;
    mKeyEsc   = 0;
    mKeySpace = 0;
}

Event::Event() { // 暂时使用 conio.h 中提供的函数进行输入 
    keyListLast = keyListNow;
    keyListNow.getKeyList(); // 获取新的按键向量 
}       
        
bool Event::isLeft() const { // 检测是否是向左移动的操作 
    return keyListLast.mKeyLeft && !keyListNow.mKeyLeft;
}

bool Event::isRight() const { // 检测是否是向右移动的操作 
    return keyListLast.mKeyRight && !keyListNow.mKeyRight;
}

bool Event::isUp() const { // 检测是否是向上移动的操作 
    return keyListLast.mKeyUp && !keyListNow.mKeyUp;
}

bool Event::isDown() const { // 检测是否是向下移动的操作 
    return keyListLast.mKeyDown && !keyListNow.mKeyDown;
}

bool Event::isConfirm() const { // 检测是否是确认操作 
    // 此处将来可能会被修改 
    if(clock() - inactiveTime >= inactiveLength) {
        return keyListLast.mKeyEnter && !keyListNow.mKeyEnter;
    }
}

bool Event::isEsc() const { // 检测 Esc 键是否被按下了 
    return keyListLast.mKeyEsc && !keyListNow.mKeyEsc;
}

bool Event::isSpace() const {
    return keyListLast.mKeySpace && !keyListNow.mKeySpace;
}

void Event::operateIMenu(IMenu* imenu) const { // 根据 event 操作 imenu 
    if(isUp()) {
        imenu -> prevTerm(); // 光标上移一个条目 
    }
    if(isDown()) {
        imenu -> nextTerm(); // 光标下移一个条目 
    }
}

void Event::inActivate() {
    keyListNow.clearKeyList(); // 清空之前的按压事件 
    inactiveTime = clock();    // 从当前时刻开始失活 
}

void Event::operateGameMenu(GameMenu* gameMenu) const {
    if(isLeft()) { // 试图向左移动 
        Game::getInstance().getChessboard() -> tetrisLeft();
    }
    if(isRight()) { // 试图向右移动 
        Game::getInstance().getChessboard() -> tetrisRight();
    }
    if(isUp()) { // 试图翻转掉落块 
        Game::getInstance().getChessboard() -> tetrisTurn();
    }
    if(isDown()) { // 试图让 掉落块下落 
        Game::getInstance().getChessboard() -> tetrisDown();
    }
    if(isSpace()) { // 试图让方块一直掉落到底 
        while(Game::getInstance().getChessboard() -> tetrisDown());
    }
}

