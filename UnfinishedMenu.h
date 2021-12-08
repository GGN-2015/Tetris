#ifndef UNFINISHEDMENU_H
#define UNFINISHEDMENU_H

#include <string>

#include "IMenu.h"

class UnfinishedMenu: public IMenu { // Ϊ��û���깤��Ŀ¼����ռλ 
public:
    enum Terms { // �˴������ֶ��� getTerms �е�����һ�� 
        OK = 0
    };
    
    UnfinishedMenu();
    UnfinishedMenu(std::string partName);
    
    virtual std::string getTitle() const;
    virtual const std::vector<std::string>& getTerms() const;
    virtual void show() const;
    
    virtual void process();

private:
    std::string mPartName;
};

#endif
