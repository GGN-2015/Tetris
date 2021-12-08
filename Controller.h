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
    static void processIMenu(IMenu*);                   // ����һ�� IMenu �������¼� 
    static void processMainMenu(MainMenu*);             // ����һ�� MainMenu �������¼� 
    static void processSettingsMenu(SettingsMenu*);     // ����һ�� SettingsMenu �������¼� 
    static void processUnfinishedMenu(UnfinishedMenu*); // ����һ�� UnfinishedMenu �������¼� 
    static void processGameMenu(GameMenu*);             // ����һ�� GameMenu �������¼� 
    static void processPauseMenu(PauseMenu*);           // ����һ�� PauseMenu �������¼� 
    static void processGameLostMenu(GameLostMenu*);     // ����һ�� GameLostMenu �������¼� 
    static void processAboutMenu(AboutMenu*);           // ����һ�� AboutMenu �������¼� 
    static void processLoadMenu(LoadMenu*);             // ����һ�� LoadMenu �������¼� 
    
    static void lostGame(int scoreNow);
    
private:
    Controller() = delete;
    Controller(const Controller&) = delete;
    Controller& operator= (const Controller&) = delete; // ��ֹ���쿽����ֵ 
};

#endif

