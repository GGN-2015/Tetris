#include <conio.h>
#include <cstdio>
#include <ctime>
#include <windows.h>

#include "Console.h"
#include "Event.h"
#include "Game.h"
#include "GameMenu.h"
#include "IMenu.h"

int Event::inactiveTime = - inactiveLength; // Ĭ��û��ʧ�� 

KeyList Event::keyListNow;
KeyList Event::keyListLast;

void KeyList::getKeyList() {
    mKeyLeft  = Console::keyDown(VK_LEFT);
    mKeyRight = Console::keyDown(VK_RIGHT);
    mKeyUp    = Console::keyDown(VK_UP);
    mKeyDown  = Console::keyDown(VK_DOWN);
    mKeyEnter = Console::keyDown(VK_RETURN); // ����Ƿ���ָ���İ����������� 
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

Event::Event() { // ��ʱʹ�� conio.h ���ṩ�ĺ����������� 
    keyListLast = keyListNow;
    keyListNow.getKeyList(); // ��ȡ�µİ������� 
}       
        
bool Event::isLeft() const { // ����Ƿ��������ƶ��Ĳ��� 
    return keyListLast.mKeyLeft && !keyListNow.mKeyLeft;
}

bool Event::isRight() const { // ����Ƿ��������ƶ��Ĳ��� 
    return keyListLast.mKeyRight && !keyListNow.mKeyRight;
}

bool Event::isUp() const { // ����Ƿ��������ƶ��Ĳ��� 
    return keyListLast.mKeyUp && !keyListNow.mKeyUp;
}

bool Event::isDown() const { // ����Ƿ��������ƶ��Ĳ��� 
    return keyListLast.mKeyDown && !keyListNow.mKeyDown;
}

bool Event::isConfirm() const { // ����Ƿ���ȷ�ϲ��� 
    // �˴��������ܻᱻ�޸� 
    if(clock() - inactiveTime >= inactiveLength) {
        return keyListLast.mKeyEnter && !keyListNow.mKeyEnter;
    }
}

bool Event::isEsc() const { // ��� Esc ���Ƿ񱻰����� 
    return keyListLast.mKeyEsc && !keyListNow.mKeyEsc;
}

bool Event::isSpace() const {
    return keyListLast.mKeySpace && !keyListNow.mKeySpace;
}

void Event::operateIMenu(IMenu* imenu) const { // ���� event ���� imenu 
    if(isUp()) {
        imenu -> prevTerm(); // �������һ����Ŀ 
    }
    if(isDown()) {
        imenu -> nextTerm(); // �������һ����Ŀ 
    }
}

void Event::inActivate() {
    keyListNow.clearKeyList(); // ���֮ǰ�İ�ѹ�¼� 
    inactiveTime = clock();    // �ӵ�ǰʱ�̿�ʼʧ�� 
}

void Event::operateGameMenu(GameMenu* gameMenu) const {
    if(isLeft()) { // ��ͼ�����ƶ� 
        Game::getInstance().getChessboard() -> tetrisLeft();
    }
    if(isRight()) { // ��ͼ�����ƶ� 
        Game::getInstance().getChessboard() -> tetrisRight();
    }
    if(isUp()) { // ��ͼ��ת����� 
        Game::getInstance().getChessboard() -> tetrisTurn();
    }
    if(isDown()) { // ��ͼ�� ��������� 
        Game::getInstance().getChessboard() -> tetrisDown();
    }
    if(isSpace()) { // ��ͼ�÷���һֱ���䵽�� 
        while(Game::getInstance().getChessboard() -> tetrisDown());
    }
}

