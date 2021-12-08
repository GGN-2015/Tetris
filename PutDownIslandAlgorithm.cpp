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
        downFloat(); // TODO: ʵ�� downFloat 
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
    // TODO: �Ҳ��ں��ˣ��Ҳ������յ��� 
    // �п��ٲ��� 
}

bool PutDownIslandAlgorithm::hasFloat() const {
    // ����Ƿ��������� 
    for(auto row: mBlockBottom) {
        if(row != CHESSBOARD_HEIGHT - 1) {
            return true;
            // �ҵ��˸��յ� 
        }
    }
    return false; // û�ҵ����յ� 
}

void PutDownIslandAlgorithm::clearCache() {
    memset(mVis, sizeof(mVis), UNVISITED); // ȫ��ճ� -1 
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
    static const int dy[] = {1,-1, 0, 0}; // ����ͨ���� 
    
    if(!inRange(row, col) || mVis[row][col] != UNVISITED || mColor[row][col] == 0) {
        return;
    }
    mVis[row][col] = blockId; // ���ʵ�ǰ�� 
    mBlockBottom[blockId] = std::max(row, mBlockBottom[blockId]);
    
    for(int d = 0; d < 4; d ++) {
        int nx = row + dx[d];
        int ny = col + dy[d];
        dfs(nx, ny, blockId);
    }
}

