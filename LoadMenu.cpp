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
    terms = App::getStorageList(); // 获取存档文件序列 
    while(terms.size() >= MAX_LOAD_SIZE) {
        terms.erase(terms.begin()); // 只能显示后 MAX_LOAD_SIZE 个存档 
    }
    terms.push_back("Back");       // 回到主菜单 
    return terms;
}

void LoadMenu::show() const {
    View::showLoadMenu(this);
}

void LoadMenu::process() {
    Controller::processLoadMenu(this); 
}

