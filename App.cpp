#include <iostream>
#include <cstdlib>
#include <ctime>

#include "AboutMenu.h"
#include "App.h" // App 负责所有和文件相关的操作以及程序运行的框架 
#include "Event.h"
#include "Game.h"
// #include "GameMenu.h"
#include "IMenu.h"
#include "MenuMgr.h"
#include "UnfinishedMenu.h"

const int App::mVersion = 20211208; // 当前的版本号 

App::App() {
    // 程序内部的 App 数据组织部分，暂时还没有什么需要做的 
    srand(time(NULL));
}

void App::initialize() {
    system("title Tetris");
    system("cls");
    std::cout << " * App::initialize() ... " << std::endl;
    bool resource = checkResource();
    bool version  = checkVersion ();
    if(!resource) { // 数据文件不全 
        std::cout << "App::initialize(): resource damaged!" << std::endl;
    }
    if(!version) { // 版本和 
        std::cout << "App::initialize(): version not match with resource!" << std::endl;
    }
    system("pause");
    system("cls");
    Event::inActivate(); // 刚进入 App 时动作失活 
}

void App::run() { // 运行整个 App 
    while(true) {
        IMenu* imenu = MenuMgr::getInstance().getActiveMenu();
        if(imenu == nullptr) break;
        else {
            imenu -> show();    // 显示页面信息 
            imenu -> process(); // 处理页面事件 
        }
    }
}

void App::terminate() {
    system("cls");
    saveData(); // 将数据写回文件 
    // system("pause");
}

bool App::checkResource() { // 检测数据文件是否完整 
    std::cout << " * checking resource ... \t";
    std::cout << "[OK]" << std::endl;
    return true;
}

bool App::checkVersion() { // 检测版本信息是否匹配 
    std::cout << " * checking version ... \t";
    std::cout << "[OK]" << std::endl;
    return true;
}
void App::saveData() { // 写回数据文件 
    std::cout << " * saving Data ... \t";
    std::cout << "[OK]" << std::endl;
}

std::string App::getDateTime(){
    char stime[256] = {0};
    
    time_t now_time;
    time(&now_time);
    
    strftime(stime, sizeof(stime), "%Y-%m-%d %H-%M-%S", localtime(&now_time));
    return stime;
}

int App::getVersion() {
    return mVersion;
}

void App::appendLineInFile(std::string fileName, std::string message) {
    FILE* fpout = fopen(fileName.c_str(), "a"); // 输入文件名序列 
    if(fpout == nullptr) {
        // TODO: 这里应该有一个错误处理的机制 
        // FatalMenu
        MenuMgr::getInstance().pushMenuStack(new UnfinishedMenu("storageListError"));
        return;
    }
    fprintf(fpout, "%s\n", message.c_str()); // message 本身不应该末尾有换行符 
    fclose(fpout);
}

std::vector<std::string> App::getStorageList() { // 获得文件序列 
    FILE* fpin = fopen(STORAGE_LIST_FILE.c_str(), "r");
    std::vector<std::string> storageList = {};
    if(fpin == nullptr) {
        // TODO: 这里应该有一个错误处理的机制 
        // FatalMenu
        MenuMgr::getInstance().pushMenuStack(new UnfinishedMenu("storageListError"));
        return storageList;
    }
    while(!feof(fpin)) { // 文件非空 
        char fileNameTmp[258] = {};
        fgets(fileNameTmp, sizeof(fileNameTmp), fpin); // 输入一行内容 
        for(int i = 0; fileNameTmp[i]; i ++) {
            if(fileNameTmp[i] == '\n' || fileNameTmp[i] == '\r') {
                fileNameTmp[i] = 0;
            }
            // 删除换行符和回车 
        }
        std::string strTmp = fileNameTmp;
        if(strTmp != "") { // 去掉空字符串 
            storageList.push_back(strTmp);
        }
    }
    fclose(fpin);
    return storageList;
}

void App::saveGameMenu(const Game* gameMenu) {
    std::string fileName = "./storage/" + getDateTime() + ".dat";  // getDateTime 获取日期和时间 
    
    appendLineInFile(STORAGE_LIST_FILE, fileName); // 在文件尾新增一行内容 
    
    FILE* fp = fopen(fileName.c_str(), "wb");       // 将游戏数据写入文件 
    
    fwrite(&mVersion, sizeof(int), 1, fp);          // 输出游戏的版本号 
    fwrite(&CHESSBOARD_HEIGHT, sizeof(int), 1, fp);
    fwrite(&CHESSBOARD_WIDTH , sizeof(int), 1, fp); // 输出游戏棋盘的长和宽 
    
    for(int i = 0; i < CHESSBOARD_HEIGHT; i ++) {
        for(int j = 0; j < CHESSBOARD_WIDTH; j ++) {
            // 输出棋盘中的每一个位置的二进制值 
            int val = gameMenu -> getChessboard() -> getPosColor(i, j); // 记录已经固化的游戏棋盘 
            fwrite(&val, sizeof(int), 1, fp);          // 输出一个二进制整数 
        }
    }
    
    int scoreNow = gameMenu -> getScore(); // 输出当前的得分 
    fwrite(&scoreNow, sizeof(int), 1, fp);
    fclose(fp);
}

void App::loadGame(std::string fileName) { // 从文件加载游戏 
    FILE* fpin = fopen(fileName.c_str(), "rb");
    
    if(fpin == nullptr) {
        MenuMgr::getInstance().pushMenuStack(new UnfinishedMenu("LoadFileError"));
        return; // TODO: 这里应该显示一个文件加载失败的页面 
    }
    
    int sVersion; fread(&sVersion, sizeof(int), 1, fpin); // 输入版本号 
    
    if(sVersion > getVersion()) { // 储存版本比当前版本高 
        MenuMgr::getInstance().pushMenuStack(new UnfinishedMenu("LoadVersionError"));
        return; // TODO: 这里应该显示一个文件加载失败的页面 
    }
    
    int chessboard_height; fread(&chessboard_height, sizeof(int), 1, fpin);
    int chessboard_width;  fread(&chessboard_width , sizeof(int), 1, fpin);
    
    if(
        chessboard_height != CHESSBOARD_HEIGHT || // 检测高度和宽度是否和我们当前的游戏界面匹配 
        chessboard_width  != CHESSBOARD_WIDTH
    ) {
        MenuMgr::getInstance().pushMenuStack(new AboutMenu("LoadFile", {"Chessboard Size Error!"}));
        return; // TODO: 这里应该显示一个文件加载失败的页面 
    }
    
    for(int i = 0; i < CHESSBOARD_HEIGHT; i ++) {
        for(int j = 0; j < CHESSBOARD_WIDTH; j ++) {
            int color;
            fread(&color, sizeof(int), 1, fpin); // 输入一个位置的颜色 
            Game::getInstance().getChessboard() -> setPosColor(i, j, color);
        }
    }
    
    int scoreNow; 
    fread(&scoreNow, sizeof(int), 1, fpin); // 输入一个当前成绩 
    Game::getInstance().setScore(scoreNow);
    
    fclose(fpin);
    // 载入成功，就别显示什么页面了 
}

const std::vector<std::string>& App::getAboutMessage() {
    char sVersion[15]; sprintf(sVersion, "%d", mVersion); // 获取版本号 
    
    static std::vector<std::string> terms
    {
        "Presented by GGN_2015",
        "", // 中间空一行 
        "Version:" + std::string(sVersion)
    };
    return terms;
}

