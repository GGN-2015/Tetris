#ifndef MENUMGR_H
#define MENUMGR_H

#include <stack> // 菜单管理器的本质是页面栈 

class IMenu; // 抽象菜单类型 

class MenuMgr {
public:
    static MenuMgr& getInstance(); // 菜单管理器是单例 
    
    IMenu* getActiveMenu() const; // 获得当前页面栈栈顶的元素 
    void popMenuStack();          // 弹出页面栈的栈顶元素，露出下方元素 
    void pushMenuStack(IMenu*);   // 向栈顶压入一个新的页面，弹栈时负责释放 
    void popSecondMenuStack();    // 弹出栈顶第二个页面 
    
    // void popAndExit(); // 弹出所有栈中元素并退出程序 
    
    IMenu* getSecondMenu(); // 获得位于次上层的界面 

private:
    MenuMgr();
    ~MenuMgr(); 
    
    MenuMgr(const MenuMgr&) = delete;
    MenuMgr& operator= (const MenuMgr&) = delete; // 禁止构造拷贝赋值 
    
    std::stack<IMenu*> mMenuStack; // 页面栈，弹栈的时候记得析构 
};

#endif

