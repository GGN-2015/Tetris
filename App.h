#ifndef APP_H
#define APP_H

#include <string>
#include <vector>

const std::string STORAGE_LIST_FILE = "./storage/storageList.txt"; // �ļ�������·�� 

class Game;

class App {
public:
    App();
    
    void initialize(); // ��ʼ�� 
    void run();        // ���� 
    void terminate();  // ��ֹ���� 
    
    bool checkResource(); // ���������е���Դ�ļ��Ƿ���ȱʧ 
    bool checkVersion();  // �����������ļ��İ汾�� exe �ļ��İ汾�Ƿ���� 
    void saveData();      // ������д���ļ� 
    
    static int getVersion(); // ��ȡ exe �İ汾����Ϣ 
    
    static void saveGameMenu(const Game*); // ����������Ϣ 
    static std::string getDateTime();    // ��ȡϵͳʱ�� 
    static void loadGame(std::string); // ������Ϸ���� 
    
    static const std::vector<std::string>& getAboutMessage(); // ��ù�����Ϣ 
    static void appendLineInFile(std::string fileName, std::string message); // �ļ�β׷����Ϣ 
    
    static std::vector<std::string> getStorageList(); // ��ô����ļ����� 
    
private:
    static const int mVersion; // ��¼��ǰ�汾 
    
    App(const App&) = delete;
    App& operator= (const App&) = delete; // ��ֹ�����͸�ֵ 
};

#endif

