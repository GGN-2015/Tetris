#ifndef UNFINISHEDMENU_H
#define UNFINISHEDMENU_H

#include <string>

#include "IMenu.h"

class UnfinishedMenu: public IMenu { // 为还没有完工的目录进行占位 
public:
    enum Terms { // 此处必须手动与 getTerms 中的内容一致 
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
