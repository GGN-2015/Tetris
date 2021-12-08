#include <string>
#include <vector>

#include "Controller.h" // Controller 类负责整个框架的控制以及输入 
#include "IMenu.h"
#include "View.h" // View 类负责整个框架的所有输出 

std::string IMenu::getTitle() const {
    return "IMenu.getTitle()"; // IMenu 的标题内容，返回一个字符串 
}

const std::vector<std::string>& IMenu::getTerms() const {
    static std::vector<std::string> terms
    { // IMenu 的每一个选项卡的值，返回一个 vector<string> 
        "IMenu.getTerms(0): NewGame", 
        "IMenu.getTerms(1): Save/Load", 
        "IMenu.getTerms(2): Quit"
    };
    return terms;
}

void IMenu::show() const {
    View::showIMenu(this); // IMenu 的输出一定要委托给 View 类 
    // 未来 IMenu 的所有派生类也一定要将输出委托给 View 类 
}

void IMenu::process() {
    Controller::processIMenu(this); // IMenu 的 process 一定要委托给 Controller 
    
    // 对于一个基本的菜单来说，总共有两种事件 
    // 一个是 select  事件 : 用于修改 ActiveTermId 
    // 一个是 confirm 事件 : 用于执行 ActiveTerm 对应的操作 
}

int IMenu::getActiveTermId() const {
    return mActiveTermId; // 计算当前正在被选中的选项 ID 
}

void IMenu::setActiveTermId(int newId) {
    mActiveTermId = newId; // 可能会有超过数组下标范围的问题 
    int termCnt = getTermsCount();
    
    mActiveTermId %= termCnt;
    if(mActiveTermId < 0) mActiveTermId += termCnt;
}

int IMenu::getTermsCount() const { // 调用 getTerms 计算结果 
    return getTerms().size();
}

void IMenu::nextTerm() { // 将 ActiveTerm 更换到下一条目 
    mActiveTermId ++;
    mActiveTermId %= getTermsCount();
}

void IMenu::prevTerm() { // 将 ActiveTerm 更换到上一条目 
    mActiveTermId --;
    if(mActiveTermId < 0) mActiveTermId += getTermsCount();
}

std::string IMenu::getMenuType() const {
    return "IMenu";
}

