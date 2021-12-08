#ifndef GAME_H
#define GAME_H // ���������Ϸ����ʱ������ 

#include "Chessboard.h"

const int TICK_LENGTH_MAX  = 600; 
const int TICK_LENGTH_STEP = 90;

class Game {
public:
    
    static Game& getInstance(); // ��̬���� 
    int getScore() const;
    void runTick(); // ��������Ϸ����һ�� tick 
    
    void newGame(); // �½�һ����Ϸ 
    
    const Chessboard* getChessboard() const; // ��ȡ��ǰ��������Ϣ 
    Chessboard* getChessboard();
    void inActive();                         // ��ʱʧ�� 
    
    static void setSpeed(int degree);
    void saveGameMenu() const; // ���浱ǰ��Ϸ״̬ 
    void setScore(int score);  // ������Ϸ���� 
    
    void outputToFile(const char* filename) const;
    void inputFromFile(const char* filename);
    
private:
    // ���ļ��ж�ȡ����, ���ļ���д������ 
    
    static int tickLength; // ÿһ�� tick �ĳ��� 
    
    int mLastTickTime;      // ��һ�� tick ���µ�ʱ�� 
    int mScore = 0;         // ����Ϸ���÷�Ϊ�� 
    Chessboard* mChessboard; // ���� 
    
    Game();
};

#endif

