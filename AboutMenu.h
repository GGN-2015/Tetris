// AboutMenu ���������������������Ϣ 
// ʵ���ϻ�������������κ�ֻ�� OK ������Ϣ 

#ifndef ABOUTMENU_H
#define ABOUTMENU_H

#include <string>
#include <vector>

#include "IMenu.h"

class AboutMenu: public IMenu {
public:
    AboutMenu(std::string title, const std::vector<std::string>& messageList);
    
    enum Terms { // ��Ҫ�ֶ��� terms һ�� 
        OK = 0
    };
    
    std::string getTitle() const;
    const std::vector<std::string>& getTerms() const;
    
    void show() const;
    void process();
    
    const std::vector<std::string>& getMessageList() const; // �����Ϣ���� 

private:
    std::string mTitle;
    std::vector<std::string> mMessageList; // ��Ϣ���� 
};

#endif

