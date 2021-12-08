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

void Controller::processIMenu(IMenu* imenu) { // ���� imenu �������¼� 
    Event event;               // ��ȡ��ǰ�������¼� 
    event.operateIMenu(imenu); // ���ݵ�ǰ�¼��� imenu ���е��� 
    
    if(event.isConfirm()) { // isConfirm  :��ȷ���¼� 
        int id = imenu -> getActiveTermId();
        std::cout << "Term(" << id << ") is Choosen." << std::endl;
        system("pause");
    }
}

void Controller::processMainMenu(MainMenu* mainMenu) { // ���� imenu �������¼� 
    Event event;                  // ��ȡ��ǰ�������¼� 
    event.operateIMenu(mainMenu); // �����¼��� mainMenu ���е�������ʱʹ�� IMenu �ķ��� 
    
    if(event.isConfirm()) {
        int id = mainMenu -> getActiveTermId();
        switch(id) {
            case MainMenu::NewGame:
                Game::getInstance().newGame();
                MenuMgr::getInstance().pushMenuStack(new GameMenu);
                //std::cout << "Here!" << std::endl;
                //system("pause");
                break;
            case MainMenu::SaveLoad: // ��ȡ�浵 
                MenuMgr::getInstance().pushMenuStack(new LoadMenu);
                break;
            case MainMenu::Settings: // �������� 
                MenuMgr::getInstance().pushMenuStack(new SettingsMenu); // ����ҳ���ջ 
                break;
            case MainMenu::About:
                MenuMgr::getInstance().pushMenuStack(new AboutMenu("AboutMenu", App::getAboutMessage())); // ���ڽ��� 
                break;
            case MainMenu::Quit:     // �˳���Ϸ 
                MenuMgr::getInstance().popMenuStack();
                break; // ��Ҫʹ�� cstdlib �е� exit ����ֱ���˳�����, ���ܻ��ڴ�й© 
        }
    }
}

void Controller::processSettingsMenu(SettingsMenu* settingsMenu) {
    Event event;                      // ��ȡ��ǰ�������¼� 
    event.operateIMenu(settingsMenu); // �����¼��� mainMenu ���е�������ʱʹ�� IMenu �ķ��� 
    
    if(event.isLeft()) {
        settingsMenu -> leftMoveActive(); // ����/�ֱ��ʵ��� 
    }
    if(event.isRight()) {
        settingsMenu -> rightMoveActive(); // ����/�ֱ��ʵ��� 
    }
    if(event.isConfirm() && settingsMenu -> getActiveTermId() == SettingsMenu::Back) {
        MenuMgr::getInstance().popMenuStack(); // �ص����˵����ϼ��˵� 
    }
}

void Controller::processUnfinishedMenu(UnfinishedMenu* unfinishedMenu) {
    Event event;                        // ��ȡ��ǰ�������¼� 
    event.operateIMenu(unfinishedMenu); // �����¼��� unfinishedMenu ���е�������ʱʹ�� IMenu �ķ��� 
    
    if(event.isConfirm()) {
        MenuMgr::getInstance().popMenuStack(); // �˳���ǰҳ�� 
    }
}

void Controller::processGameMenu(GameMenu* gameMenu) {
    Game::getInstance().runTick();   // ��ͼ����һ�� tick 
    Event event;                     // ��ȡ��ǰ�������¼� 
    event.operateGameMenu(gameMenu); // �����¼��� gameMenu ���е�������ʱʹ�� IMenu �ķ��� 
    
    if(event.isEsc()) { // �� ESC ��ͣ 
        // TODO: �˴�Ӧ�ò�����ͣҳ�� 
        // MenuMgr::getInstance().pushMenuStack(new UnfinishedMenu);
        MenuMgr::getInstance().pushMenuStack(new PauseMenu);
    }
}

void Controller::processPauseMenu(PauseMenu* pauseMenu) {
    Event event;                   // ��ȡ��ǰ�������¼� 
    event.operateIMenu(pauseMenu); // �����¼��� mainMenu ���е�������ʱʹ�� IMenu �ķ��� 
    
    if(event.isLeft()) {
        pauseMenu -> leftMoveActive(); // �ٶȵ��� 
    }
    if(event.isRight()) {
        pauseMenu -> rightMoveActive(); // �ٶȵ��� 
    }
    if(event.isConfirm()) {
        if(pauseMenu -> getActiveTermId() == PauseMenu::Resume) {
            MenuMgr::getInstance().popMenuStack(); // �ص��ϼ��˵� 
        }else
        if(pauseMenu -> getActiveTermId() == PauseMenu::Quit) {
            MenuMgr::getInstance().popMenuStack(); // �ص����˵� 
            MenuMgr::getInstance().popMenuStack(); // ��ջ���� 
        }else
        if(pauseMenu -> getActiveTermId() == PauseMenu::Save) {
            // ���浱ǰ��Ϸ״̬ 
            IMenu* imenu = MenuMgr::getInstance().getSecondMenu(); // ���λ�ڴ��ϲ����Ϸ���� 
            
            GameMenu* gameMenu = dynamic_cast<GameMenu*>(imenu);      // �˴�һ������Ϸ���� 
            
            Game::getInstance().saveGameMenu(); // �洢��Ϸ״̬���ļ� 
            
            std::vector<std::string> files = App::getStorageList();
            std::string fileNow = files[files.size() - 1]; // ��ȡ���һ���ļ��� 
            
            MenuMgr::getInstance().pushMenuStack(new AboutMenu("SaveSuccessfully", {"Save To File:", fileNow}));
        }
    }
}

void Controller::lostGame(int finalScore) {// ��Ϸʧ�ܣ����ճɼ�δ final Score 
    MenuMgr::getInstance().pushMenuStack(new GameLostMenu(finalScore));
}

void Controller::processGameLostMenu(GameLostMenu* gameLostMenu) {
    Event event;                      // ��ȡ��ǰ�������¼� 
    event.operateIMenu(gameLostMenu); // �����¼��� IMenu ���е�������ʱʹ�� IMenu �ķ��� 
    
    if(event.isConfirm()) {
        MenuMgr::getInstance().popMenuStack();
        MenuMgr::getInstance().popMenuStack(); // ���������ص����˵� 
    }
}

void Controller::processAboutMenu(AboutMenu* aboutMenu) {
    Event event;                   // ��ȡ��ǰ�������¼� 
    event.operateIMenu(aboutMenu); // �����¼��� aboutMenu ���е�������ʱʹ�� IMenu �ķ��� 
    
    if(event.isConfirm()) {
        MenuMgr::getInstance().popMenuStack(); // �ص����˵� 
    }
}

void Controller::processLoadMenu(LoadMenu* loadMenu) {
    Event event;
    event.operateIMenu(loadMenu);
    
    if(event.isConfirm()) {
        if(loadMenu -> getActiveTermId() != (loadMenu -> getTerms().size() - 1)) {
            // Back ������� 
            Game::getInstance().inputFromFile(
                loadMenu -> getTerms()[loadMenu -> getActiveTermId()].c_str()
            ); 
            MenuMgr::getInstance().pushMenuStack(new GameMenu); // ���ļ�����һ����Ϸ 
            MenuMgr::getInstance().popSecondMenuStack(); // ���� Load ���� 
        }else {
            MenuMgr::getInstance().popMenuStack();
        }
    }
}

