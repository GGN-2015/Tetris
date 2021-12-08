#include <string>
#include <vector>

#include "App.h"
#include "Controller.h"
#include "LoadMenu.h"
#include "View.h"

std::string LoadMenu::getTitle() const {
    return "LoadMenu";
}

const std::vector<std::string>& LoadMenu::getTerms() const {
    static std::vector<std::string> terms;
    terms.clear();
    terms = App::getStorageList(); // ��ȡ�浵�ļ����� 
    while(terms.size() >= MAX_LOAD_SIZE) {
        terms.erase(terms.begin()); // ֻ����ʾ�� MAX_LOAD_SIZE ���浵 
    }
    terms.push_back("Back");       // �ص����˵� 
    return terms;
}

void LoadMenu::show() const {
    View::showLoadMenu(this);
}

void LoadMenu::process() {
    Controller::processLoadMenu(this); 
}

