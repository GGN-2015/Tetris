#include <cstdlib>
#include <iostream>

#include "App.h"
#include "AboutMenu.h"
#include "Controller.h"
#include "Event.h"
#include "Game.h"
#include "GameLostMenu.h"
#include "GameMenu.h"
#include "IMenu.h"
#include "LoadMenu.h"
#include "MainMenu.h"
#include "MenuMgr.h"
#include "PauseMenu.h"
#include "SettingsMenu.h"
#include "UnfinishedMenu.h"

void Controller::processIMenu(IMenu* imenu) { // 处理 imenu 的输入事件 
    Event event;               // 获取当前的所有事件 
    event.operateIMenu(imenu); // 根据当前事件对 imenu 进行调整 
    
    if(event.isConfirm()) { // isConfirm  :是确认事件 
        int id = imenu -> getActiveTermId();
        std::cout << "Term(" << id << ") is Choosen." << std::endl;
        system("pause");
    }
}

void Controller::processMainMenu(MainMenu* mainMenu) { // 处理 imenu 的输入事件 
    Event event;                  // 获取当前的所有事件 
    event.operateIMenu(mainMenu); // 根据事件对 mainMenu 进行调整，暂时使用 IMenu 的方法 
    
    if(event.isConfirm()) {
        int id = mainMenu -> getActiveTermId();
        switch(id) {
            case MainMenu::NewGame:
                Game::getInstance().newGame();
                MenuMgr::getInstance().pushMenuStack(new GameMenu);
                //std::cout << "Here!" << std::endl;
                //system("pause");
                break;
            case MainMenu::SaveLoad: // 读取存档 
                MenuMgr::getInstance().pushMenuStack(new LoadMenu);
                break;
            case MainMenu::Settings: // 进行设置 
                MenuMgr::getInstance().pushMenuStack(new SettingsMenu); // 设置页面进栈 
                break;
            case MainMenu::About:
                MenuMgr::getInstance().pushMenuStack(new AboutMenu("AboutMenu", App::getAboutMessage())); // 关于界面 
                break;
            case MainMenu::Quit:     // 退出游戏 
                MenuMgr::getInstance().popMenuStack();
                break; // 不要使用 cstdlib 中的 exit 函数直接退出程序, 可能会内存泄漏 
        }
    }
}

void Controller::processSettingsMenu(SettingsMenu* settingsMenu) {
    Event event;                      // 获取当前的所有事件 
    event.operateIMenu(settingsMenu); // 根据事件对 mainMenu 进行调整，暂时使用 IMenu 的方法 
    
    if(event.isLeft()) {
        settingsMenu -> leftMoveActive(); // 音量/分辨率调低 
    }
    if(event.isRight()) {
        settingsMenu -> rightMoveActive(); // 音量/分辨率调高 
    }
    if(event.isConfirm() && settingsMenu -> getActiveTermId() == SettingsMenu::Back) {
        MenuMgr::getInstance().popMenuStack(); // 回到主菜单或上级菜单 
    }
}

void Controller::processUnfinishedMenu(UnfinishedMenu* unfinishedMenu) {
    Event event;                        // 获取当前的所有事件 
    event.operateIMenu(unfinishedMenu); // 根据事件对 unfinishedMenu 进行调整，暂时使用 IMenu 的方法 
    
    if(event.isConfirm()) {
        MenuMgr::getInstance().popMenuStack(); // 退出当前页面 
    }
}

void Controller::processGameMenu(GameMenu* gameMenu) {
    Game::getInstance().runTick();   // 试图运行一个 tick 
    Event event;                     // 获取当前的所有事件 
    event.operateGameMenu(gameMenu); // 根据事件对 gameMenu 进行调整，暂时使用 IMenu 的方法 
    
    if(event.isEsc()) { // 按 ESC 暂停 
        // TODO: 此处应该插入暂停页面 
        // MenuMgr::getInstance().pushMenuStack(new UnfinishedMenu);
        MenuMgr::getInstance().pushMenuStack(new PauseMenu);
    }
}

void Controller::processPauseMenu(PauseMenu* pauseMenu) {
    Event event;                   // 获取当前的所有事件 
    event.operateIMenu(pauseMenu); // 根据事件对 mainMenu 进行调整，暂时使用 IMenu 的方法 
    
    if(event.isLeft()) {
        pauseMenu -> leftMoveActive(); // 速度调低 
    }
    if(event.isRight()) {
        pauseMenu -> rightMoveActive(); // 速度调高 
    }
    if(event.isConfirm()) {
        if(pauseMenu -> getActiveTermId() == PauseMenu::Resume) {
            MenuMgr::getInstance().popMenuStack(); // 回到上级菜单 
        }else
        if(pauseMenu -> getActiveTermId() == PauseMenu::Quit) {
            MenuMgr::getInstance().popMenuStack(); // 回到主菜单 
            MenuMgr::getInstance().popMenuStack(); // 弹栈两次 
        }else
        if(pauseMenu -> getActiveTermId() == PauseMenu::Save) {
            // 保存当前游戏状态 
            IMenu* imenu = MenuMgr::getInstance().getSecondMenu(); // 获得位于次上层的游戏界面 
            
            GameMenu* gameMenu = dynamic_cast<GameMenu*>(imenu);      // 此处一定是游戏界面 
            
            Game::getInstance().saveGameMenu(); // 存储游戏状态到文件 
            
            std::vector<std::string> files = App::getStorageList();
            std::string fileNow = files[files.size() - 1]; // 获取最后一个文件名 
            
            MenuMgr::getInstance().pushMenuStack(new AboutMenu("SaveSuccessfully", {"Save To File:", fileNow}));
        }
    }
}

void Controller::lostGame(int finalScore) {// 游戏失败，最终成绩未 final Score 
    MenuMgr::getInstance().pushMenuStack(new GameLostMenu(finalScore));
}

void Controller::processGameLostMenu(GameLostMenu* gameLostMenu) {
    Event event;                      // 获取当前的所有事件 
    event.operateIMenu(gameLostMenu); // 根据事件对 IMenu 进行调整，暂时使用 IMenu 的方法 
    
    if(event.isConfirm()) {
        MenuMgr::getInstance().popMenuStack();
        MenuMgr::getInstance().popMenuStack(); // 两跳两级回到主菜单 
    }
}

void Controller::processAboutMenu(AboutMenu* aboutMenu) {
    Event event;                   // 获取当前的所有事件 
    event.operateIMenu(aboutMenu); // 根据事件对 aboutMenu 进行调整，暂时使用 IMenu 的方法 
    
    if(event.isConfirm()) {
        MenuMgr::getInstance().popMenuStack(); // 回到主菜单 
    }
}

void Controller::processLoadMenu(LoadMenu* loadMenu) {
    Event event;
    event.operateIMenu(loadMenu);
    
    if(event.isConfirm()) {
        if(loadMenu -> getActiveTermId() != (loadMenu -> getTerms().size() - 1)) {
            // Back 键在最后 
            Game::getInstance().inputFromFile(
                loadMenu -> getTerms()[loadMenu -> getActiveTermId()].c_str()
            ); 
            MenuMgr::getInstance().pushMenuStack(new GameMenu); // 从文件加载一个游戏 
            MenuMgr::getInstance().popSecondMenuStack(); // 弹出 Load 界面 
        }else {
            MenuMgr::getInstance().popMenuStack();
        }
    }
}

