#ifndef GAME_H
#define GAME_H // 储存各种游戏运行时的数据 

#include "Chessboard.h"

const int TICK_LENGTH_MAX  = 600; 
const int TICK_LENGTH_STEP = 90;

class Game {
public:
    
    static Game& getInstance(); // 静态单例 
    int getScore() const;
    void runTick(); // 尝试让游戏进行一个 tick 
    
    void newGame(); // 新建一个游戏 
    
    const Chessboard* getChessboard() const; // 获取当前的棋盘信息 
    Chessboard* getChessboard();
    void inActive();                         // 计时失活 
    
    static void setSpeed(int degree);
    void saveGameMenu() const; // 储存当前游戏状态 
    void setScore(int score);  // 设置游戏分数 
    
    void outputToFile(const char* filename) const;
    void inputFromFile(const char* filename);
    
private:
    // 从文件中读取数据, 向文件中写入数据 
    
    static int tickLength; // 每一个 tick 的长度 
    
    int mLastTickTime;      // 上一个 tick 更新的时间 
    int mScore = 0;         // 新游戏，得分为零 
    Chessboard* mChessboard; // 棋盘 
    
    Game();
};

#endif

