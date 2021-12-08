#ifndef MAINMENU_H
#define MAINMENU_H

#include "IMenu.h" // 所有的菜单都由 IMenu 派生而来 

class MainMenu: public IMenu {
public:
    enum Terms { // 此处必须手动与 getTerms 中的内容一致 
        NewGame = 0, SaveLoad = 1, Settings = 2, About = 3, Quit = 4
    };
    
    virtual std::string getTitle() const;
    virtual const std::vector<std::string>& getTerms() const;
    virtual void show() const;
    
    virtual void process();
    virtual std::string getMenuType() const;
};

#endif

