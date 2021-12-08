#ifndef CHESSBOARD_H
#define CHESSBOARD_H // 记录一个俄罗斯方块的棋盘 

const int CHESSBOARD_HEIGHT = 22;
const int CHESSBOARD_WIDTH  = 11; // 棋盘的大小 

#include "TetrisBlock.h"

class Chessboard {
public:
    Chessboard(); // 创建空棋盘 
    ~Chessboard();
    
    int moveDown(bool& okToRun); // 将 mTetris 试图向下移动 
    
    void show() const; // 显示一个棋盘, 直接委托给 View 做 
    bool reset();      // 重新从顶部掉落 
    void getPosXY(int&,int&) const; // 获取掉落块位置 
    
    
    int getViewPosColor(int x, int y) const; // 返回看起来的颜色, 考虑掉落块 
    void setPosColor(int row, int col, int color);
    
    void tetrisLeft  ();
    void tetrisRight ();
    void tetrisTurn  ();  // 试图移动或翻转俄罗斯方块 
    bool tetrisDown  ();
    
    int getPosColor(int row, int col) const; // 得到某一个位置的颜色，边缘返回 WHITE (不考虑掉落块) 
    // ↑ 此函数仅供 PutDownIsLand/保存 使用 

private:
    int deleteTest();
    void putDownIsland(); // 悬浮岛屿下移算法 
    
    bool checkFull(int row) const; // 最底下一行是否满了 
    void shiftDown(int row);       // 整个图形整体下移，覆盖下标为 row 的行 
    
    static int rand(int L, int R); // 生成闭区间内的随机数 
    
    void setTetrisBlock(int x, int y, const TetrisBlock& tb);       // 把 TetrisBlock 放在图上 
    bool checkAvailable(int x, int y, const TetrisBlock& tb) const; // 检测某个位置上放置一个 Block 是否合法 
    
    bool InChessboard(int row, int col) const; // 检测某个位置是否在棋盘中 
    bool InTeris(int row, int col) const; // 检测某个位置是否在掉落块范围内 
    // int getPosColor(int row, int col) const; // 得到某一个位置的颜色，边缘返回 WHITE (不考虑掉落块) 
    
    void makeNextType(); 
    
    int mColors[CHESSBOARD_HEIGHT][CHESSBOARD_WIDTH] {}; // 记录棋盘上每个位置的颜色, 0 表示无方块 
    int mPosX, mPosY;
    TetrisBlock* mTetrisBlock; // 记录当前块 
    
    TetrisBlock::TetrisType mNextType;    // 下一个块的样式 
    ConsoleColor::Colors    mNextColorId; // 下一个块的颜色 
    
    Chessboard(const Chessboard&) = delete;
    Chessboard& operator= (const Chessboard&) = delete; // 禁止拷贝赋值 
};

#endif

