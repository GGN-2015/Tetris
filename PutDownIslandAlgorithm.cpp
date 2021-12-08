#include <algorithm>
#include <cstring>

#include "Chessboard.h"
#include "PutDownIslandAlgorithm.h"

PutDownIslandAlgorithm::PutDownIslandAlgorithm(const Chessboard& chessboard) {
    for(int i = 0; i < CHESSBOARD_HEIGHT; i ++) {
        for(int j = 0; j < CHESSBOARD_WIDTH; j ++) {
            mColor[i][j] = chessboard.getPosColor(i, j);
        }
    }
    dfsAll();
    while(hasFloat()) {
        downFloat(); // TODO: 实现 downFloat 
        dfsAll();
    }
}

void PutDownIslandAlgorithm::dfsAll() {
    clearCache();
    for(int i = 0; i < CHESSBOARD_HEIGHT; i ++) {
        for(int j = 0; j < CHESSBOARD_WIDTH; j ++) {
            if(!mVis[i][j]) {
                mBlockBottom.push_back(0);
                dfs(i, j, mBlockCnt);
                mBlockCnt ++;
            }
        }
    }
}

void PutDownIslandAlgorithm::downFloat() {
    // TODO: 我不在乎了，我不处理浮空岛了 
    // 有空再补上 
}

bool PutDownIslandAlgorithm::hasFloat() const {
    // 检测是否有悬浮岛 
    for(auto row: mBlockBottom) {
        if(row != CHESSBOARD_HEIGHT - 1) {
            return true;
            // 找到了浮空岛 
        }
    }
    return false; // 没找到浮空岛 
}

void PutDownIslandAlgorithm::clearCache() {
    memset(mVis, sizeof(mVis), UNVISITED); // 全清空成 -1 
    mBlockBottom.clear();
    mBlockCnt = 0;
}

bool PutDownIslandAlgorithm::inRange(int row, int col) const {
    return
        0 <= row && row < CHESSBOARD_HEIGHT &&
        0 <= col && col < CHESSBOARD_WIDTH;
}

void PutDownIslandAlgorithm::dfs(int row, int col, int blockId) {
    static const int dx[] = {0, 0, 1,-1};
    static const int dy[] = {1,-1, 0, 0}; // 四联通区域 
    
    if(!inRange(row, col) || mVis[row][col] != UNVISITED || mColor[row][col] == 0) {
        return;
    }
    mVis[row][col] = blockId; // 访问当前点 
    mBlockBottom[blockId] = std::max(row, mBlockBottom[blockId]);
    
    for(int d = 0; d < 4; d ++) {
        int nx = row + dx[d];
        int ny = col + dy[d];
        dfs(nx, ny, blockId);
    }
}

