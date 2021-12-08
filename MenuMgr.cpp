#include <stack>

#include "Event.h"
#include "MainMenu.h"
#include "MenuMgr.h"
#include "Screen.h"
#include "View.h"

MenuMgr& MenuMgr::getInstance() { // �˵����������þ�̬���� 
    static MenuMgr menuMgr;
    return menuMgr;
}

IMenu* MenuMgr::getActiveMenu() const { // ��ȡ��ǰҳ��ջ����Ĳ˵� 
    if(mMenuStack.size() > 0) {
        return mMenuStack.top();
    }else {
        return nullptr; // ҳ��ջ���Ѿ�û��ҳ��˵�������ʱӦ���˳� 
    }
}

void MenuMgr::popMenuStack() {
    if(mMenuStack.size() > 0) {  // ���ǿ�����Ϊ == 0 �����һ��������� 
        delete mMenuStack.top(); // �ڵ�ջʱ��ն�Ӧ�Ĵ��浥Ԫ 
        mMenuStack.pop();        // ��Ϊ����Ҫ�� App ������ IMenu = nullptr ʱ�ͻ������˳� 
        View::getScreen() -> clearAll();
        // Event::inactivate();     // �ڲ�����˲�䣬���¼���Ӧ��ʧ�� 
    }
}

void MenuMgr::pushMenuStack(IMenu* imenu) { // ��ҳ��ջ��ѹ��һ��Ԫ��: push(new MenuType); 
    mMenuStack.push(imenu);
    View::getScreen() -> clearAll();
    // Event::inactivate();
}

MenuMgr::MenuMgr() {
    mMenuStack.push(new MainMenu); // ��ʼ��ʱ�����һ�����˵� 
}

MenuMgr::~MenuMgr() {
    while(!mMenuStack.empty()) { // ��ֹ�ڴ�й©��������ʱ��Ҫ����ҳ��ջ 
        popMenuStack();
    }
}

IMenu* MenuMgr::getSecondMenu() { // ��ȡ��ջ��Ԫ�� 
    IMenu* tmpTop = mMenuStack.top();
    mMenuStack.pop(); // ����ջ��Ԫ�� 
    
    IMenu* ansMenu = mMenuStack.top();
    mMenuStack.push(tmpTop); // ջ��Ԫ�ش�� 
    
    return ansMenu;
}

void MenuMgr::popSecondMenuStack() {
    IMenu* tmpTop = mMenuStack.top();
    mMenuStack.pop(); // ����ջ��Ԫ�� 
    
    popMenuStack(); // ������������ǰ��ջ��Ԫ�� 
    
    mMenuStack.push(tmpTop); // ջ��Ԫ�ش�� 
}
