#ifndef GAMEMENU_H
#define GAMEMENU_H

#include "IMenu.h" // ���еĲ˵����� IMenu �������� 

class GameMenu: public IMenu {
public:
    GameMenu(); // ���� mLastTickTime 
    virtual std::string getMenuType() const; // ����Ŀ¼���� 
    
    // �����Ǻܹ��� Title �� Terms����Ϊ������� 
    // �� IMenu ����ֻ��Ϊ�˷��� show �� process �ӿ� 
    virtual void show() const;
    virtual void process();
};

#endif

