#ifndef IMENU_H
#define IMENU_H

#include <string>
#include <vector>

class IMenu { // IMenu 是抽象的菜单类 
public:
    virtual std::string getTitle() const;                     // 获取菜单的标题 
    virtual const std::vector<std::string>& getTerms() const; // 获取菜单中每一项内容 
    virtual void show() const;                                // 显示这个菜单, 委托给 View 做 
    
    virtual void process();                  // 处理用户事件, 委托给 Controller 
    virtual std::string getMenuType() const; // 得到 Menu 类型 
    
    int  getActiveTermId() const;    // 计算得到当前被选中的选项的 ID (下标) 
    void setActiveTermId(int newId); // 修改当前被选中的选项 ID 
    int  getTermsCount() const;      // 得到条目的总数 
    
    void nextTerm();
    void prevTerm(); // 将光标移动到上一项或者下一项内容之上 
    
protected:
    int mActiveTermId = 0; // 记录当前被选中的项目的 ID 
};

#endif

