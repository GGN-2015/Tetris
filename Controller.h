#ifndef CONTROLLER_H
#define CONTROLLER_H

class AboutMenu;
class GameLostMenu;
class GameMenu;
class IMenu;
class LoadMenu;
class MainMenu;
class PauseMenu;
class SettingsMenu;
class UnfinishedMenu;

class Controller {
public:
    static void processIMenu(IMenu*);                   // 处理一个 IMenu 的输入事件 
    static void processMainMenu(MainMenu*);             // 处理一个 MainMenu 的输入事件 
    static void processSettingsMenu(SettingsMenu*);     // 处理一个 SettingsMenu 的输入事件 
    static void processUnfinishedMenu(UnfinishedMenu*); // 处理一个 UnfinishedMenu 的输入事件 
    static void processGameMenu(GameMenu*);             // 处理一个 GameMenu 的输入事件 
    static void processPauseMenu(PauseMenu*);           // 处理一个 PauseMenu 的输入事件 
    static void processGameLostMenu(GameLostMenu*);     // 处理一个 GameLostMenu 的输入事件 
    static void processAboutMenu(AboutMenu*);           // 处理一个 AboutMenu 的输入事件 
    static void processLoadMenu(LoadMenu*);             // 处理一个 LoadMenu 的输入事件 
    
    static void lostGame(int scoreNow);
    
private:
    Controller() = delete;
    Controller(const Controller&) = delete;
    Controller& operator= (const Controller&) = delete; // 禁止构造拷贝赋值 
};

#endif

