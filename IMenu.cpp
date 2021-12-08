#include <string>
#include <vector>

#include "Controller.h" // Controller �ฺ��������ܵĿ����Լ����� 
#include "IMenu.h"
#include "View.h" // View �ฺ��������ܵ�������� 

std::string IMenu::getTitle() const {
    return "IMenu.getTitle()"; // IMenu �ı������ݣ�����һ���ַ��� 
}

const std::vector<std::string>& IMenu::getTerms() const {
    static std::vector<std::string> terms
    { // IMenu ��ÿһ��ѡ���ֵ������һ�� vector<string> 
        "IMenu.getTerms(0): NewGame", 
        "IMenu.getTerms(1): Save/Load", 
        "IMenu.getTerms(2): Quit"
    };
    return terms;
}

void IMenu::show() const {
    View::showIMenu(this); // IMenu �����һ��Ҫί�и� View �� 
    // δ�� IMenu ������������Ҳһ��Ҫ�����ί�и� View �� 
}

void IMenu::process() {
    Controller::processIMenu(this); // IMenu �� process һ��Ҫί�и� Controller 
    
    // ����һ�������Ĳ˵���˵���ܹ��������¼� 
    // һ���� select  �¼� : �����޸� ActiveTermId 
    // һ���� confirm �¼� : ����ִ�� ActiveTerm ��Ӧ�Ĳ��� 
}

int IMenu::getActiveTermId() const {
    return mActiveTermId; // ���㵱ǰ���ڱ�ѡ�е�ѡ�� ID 
}

void IMenu::setActiveTermId(int newId) {
    mActiveTermId = newId; // ���ܻ��г��������±귶Χ������ 
    int termCnt = getTermsCount();
    
    mActiveTermId %= termCnt;
    if(mActiveTermId < 0) mActiveTermId += termCnt;
}

int IMenu::getTermsCount() const { // ���� getTerms ������ 
    return getTerms().size();
}

void IMenu::nextTerm() { // �� ActiveTerm ��������һ��Ŀ 
    mActiveTermId ++;
    mActiveTermId %= getTermsCount();
}

void IMenu::prevTerm() { // �� ActiveTerm ��������һ��Ŀ 
    mActiveTermId --;
    if(mActiveTermId < 0) mActiveTermId += getTermsCount();
}

std::string IMenu::getMenuType() const {
    return "IMenu";
}

