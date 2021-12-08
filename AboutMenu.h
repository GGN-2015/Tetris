// AboutMenu 不仅可以用来输出关于信息 
// 实际上还可以用来输出任何只有 OK 键的信息 

#ifndef ABOUTMENU_H
#define ABOUTMENU_H

#include <string>
#include <vector>

#include "IMenu.h"

class AboutMenu: public IMenu {
public:
    AboutMenu(std::string title, const std::vector<std::string>& messageList);
    
    enum Terms { // 需要手动与 terms 一致 
        OK = 0
    };
    
    std::string getTitle() const;
    const std::vector<std::string>& getTerms() const;
    
    void show() const;
    void process();
    
    const std::vector<std::string>& getMessageList() const; // 获得消息内容 

private:
    std::string mTitle;
    std::vector<std::string> mMessageList; // 消息序列 
};

#endif

