#ifndef LOADMENU_H
#define LOADMENU_H

#include <string>
#include <vector>

#include "IMenu.h"

const int MAX_LOAD_SIZE = 6; // ֻ��ʾ��������浵 

class LoadMenu: public IMenu {
public:
    virtual std::string getTitle() const;                     // ��ȡ�˵��ı��� 
    virtual const std::vector<std::string>& getTerms() const; // ��ȡ�˵���ÿһ������ 
    virtual void show() const;                                // ��ʾ����˵�, ί�и� View �� 
    virtual void process();
};

#endif

