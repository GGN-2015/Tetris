#ifndef PUTDOWNISLANDALGORITHM_H
#define PUTDOWNISLANDALGORITHM_H

#include <vector>
#include "Chessboard.h"

const int UNVISITED = -1;

class PutDownIslandAlgorithm {
public:
    PutDownIslandAlgorithm(const Chessboard&);
    int getSolved(int row, int col) const; // 得到计算结束后的棋盘 
    
private:
    int mColor[CHESSBOARD_HEIGHT][CHESSBOARD_WIDTH];
    
    int mVis[CHESSBOARD_HEIGHT][CHESSBOARD_WIDTH];
    std::vector<int> mBlockBottom; // 记录每个连通块的最大深度 
    int mBlockCnt; 
    
    void dfsAll();         // 进行 dfs 染色 
    void downFloat();      // 浮空岛下移一个单位 
    bool hasFloat() const; // 检测有没有浮岛 
    
    void dfs(int row, int col, int blockId);
    void clearCache(); // 清空 cache 
    
    bool inRange(int row, int col) const; // 分析是否在范围内 
    
    PutDownIslandAlgorithm(const PutDownIslandAlgorithm&) = delete;
    PutDownIslandAlgorithm& operator= (const PutDownIslandAlgorithm&) = delete;
};

#endif

