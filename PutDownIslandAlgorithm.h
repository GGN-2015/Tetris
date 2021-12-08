#ifndef PUTDOWNISLANDALGORITHM_H
#define PUTDOWNISLANDALGORITHM_H

#include <vector>
#include "Chessboard.h"

const int UNVISITED = -1;

class PutDownIslandAlgorithm {
public:
    PutDownIslandAlgorithm(const Chessboard&);
    int getSolved(int row, int col) const; // �õ��������������� 
    
private:
    int mColor[CHESSBOARD_HEIGHT][CHESSBOARD_WIDTH];
    
    int mVis[CHESSBOARD_HEIGHT][CHESSBOARD_WIDTH];
    std::vector<int> mBlockBottom; // ��¼ÿ����ͨ��������� 
    int mBlockCnt; 
    
    void dfsAll();         // ���� dfs Ⱦɫ 
    void downFloat();      // ���յ�����һ����λ 
    bool hasFloat() const; // �����û�и��� 
    
    void dfs(int row, int col, int blockId);
    void clearCache(); // ��� cache 
    
    bool inRange(int row, int col) const; // �����Ƿ��ڷ�Χ�� 
    
    PutDownIslandAlgorithm(const PutDownIslandAlgorithm&) = delete;
    PutDownIslandAlgorithm& operator= (const PutDownIslandAlgorithm&) = delete;
};

#endif

