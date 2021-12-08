#ifndef MAINMENU_H
#define MAINMENU_H

#include "IMenu.h" // ���еĲ˵����� IMenu �������� 

class MainMenu: public IMenu {
public:
    enum Terms { // �˴������ֶ��� getTerms �е�����һ�� 
        NewGame = 0, SaveLoad = 1, Settings = 2, About = 3, Quit = 4
    };
    
    virtual std::string getTitle() const;
    virtual const std::vector<std::string>& getTerms() const;
    virtual void show() const;
    
    virtual void process();
    virtual std::string getMenuType() const;
};

#endif

