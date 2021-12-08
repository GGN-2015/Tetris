#include <cstdlib>
#include <iostream>

#include "Chessboard.h"
#include "ConsoleColor.h"
#include "TetrisBlock.h"
#include "View.h"

int Chessboard::rand(int L, int R) {
    return std::rand() % (R - L + 1) + L; // ��������� 
}

Chessboard::Chessboard() {
    mTetrisBlock = nullptr; // ��֤ delete �� RE 
    makeNextType();
    reset(); // �÷������´Ӷ������� 
}

int Chessboard::moveDown(bool& okToRun) { // �����ƶ�����˹���� 
    int scoreAdd = 0;
    okToRun = true;
    if(mTetrisBlock != nullptr) {
        int nPosX = mPosX + 1, nPosY = mPosY;
        if(!checkAvailable(nPosX, nPosY, *mTetrisBlock)) {
            // ������������ƶ� 
            // ˵����ʱӦ���Ѿ����� 
            setTetrisBlock(mPosX, mPosY, *mTetrisBlock); // �̻� 
            scoreAdd = deleteTest(); // ��ͼ���һЩ�·����� 
            putDownIsland();         // ������������ 
            okToRun = reset();       // ��¼��Ϸ�Ƿ�ʧ�� 
        }else {
            // ����������ƶ����������ƶ� 
            mPosX ++;
        }
    }
    return scoreAdd;
}

bool Chessboard::tetrisDown() {
    int nPosX = mPosX + 1, nPosY = mPosY;
    if(checkAvailable(nPosX, nPosY, *mTetrisBlock)) {
        mPosX ++;
        return true; // ��ͼ�����ƶ� 
    }
    return false;
}

void Chessboard::putDownIsland() {
    // TODO: ���������³��㷨��û��д 
    
}

Chessboard::~Chessboard() {
    delete mTetrisBlock; // �ͷŷ����ڴ� 
}

bool Chessboard::InChessboard(int row, int col) const {
    return 
        0 <= row && row < CHESSBOARD_HEIGHT &&
        0 <= col && col < CHESSBOARD_WIDTH;
}

bool Chessboard::InTeris(int row, int col) const {
    return // �ڵ�����Ͻ��Χ�� 
        mPosX <= row && row < mPosX + 4 &&
        mPosY <= col && col < mPosY + 4;
}

int Chessboard::getPosColor(int row, int col) const {
    if(InChessboard(row, col)) {
        return mColors[row][col]; // �ڲ� 
    }else {
        return ConsoleColor::WHITE; // �����ⲿ 
    }
}

bool Chessboard::checkAvailable(int x, int y, const TetrisBlock& tb) const {
    // ����� x, y λ�� tb �ܹ����� 
    for(int i = 0; i < 4; i ++) {
        for(int j = 0; j < 4; j ++) {
            if(
                tb.getPos(i, j) != 0 &&
                getPosColor(x + i, y + j) != 0
            ) {
                // �˴����ֳ�ͻ 
                return false;
            }
        }
    }
    return true;
}

void Chessboard::setTetrisBlock(int x, int y, const TetrisBlock& tb) {
    for(int i = 0; i < 4; i ++) {
        for(int j = 0; j < 4; j ++) {
            // ö������λ�� 
            if(tb.getPos(i, j) != 0) {
                mColors[x + i][y + j] = tb.getColorId();
                // ���÷��� 
            }
        }
    }
}

void Chessboard::show() const {
    View::showChessboard(this);
}

bool Chessboard::reset() {
    mPosX = 0;
    mPosY = CHESSBOARD_WIDTH / 2 - 2;
    
    delete mTetrisBlock; // ɾ���ϵĿ� 
    
    mTetrisBlock = new TetrisBlock(mNextType, mNextColorId);
    int cnt = rand(0, 3);
    while(cnt --) {
        mTetrisBlock -> rotate(); // ��ʼ�����ת���ɴ� 
    }
    
    makeNextType(); // ���� mNextType 
    
    if(!checkAvailable(mPosX, mPosY, *mTetrisBlock)) {
        // �˴�Ӧ��ת��ʧ��ҳ�� 
        return false; // ������ 
    }
    
    return true; // ���Լ�����Ϸ 
}

int Chessboard::deleteTest() {
    const int lineScore = 100;
    int lineCount = 0; // ͳ����ȥ�˼��� 
    for(int i = CHESSBOARD_HEIGHT - 1; i >= 0; i --) {
        while(checkFull(i)) {
            lineCount += 1;
            shiftDown(i);
        }
    }
    if(lineCount == 0) return 10;
    else {
        return (1 << lineCount - 1) * lineScore + 10;
    }
}

bool Chessboard::checkFull(int row) const {
    // ��������һ���Ƿ����� 
    for(int j = 0; j < CHESSBOARD_WIDTH; j ++) {
        if(mColors[row][j] == 0) {
            return false;
            // �ҵ���һ����λ 
        }
    }
    return true; // û���ҵ���λ 
}

void Chessboard::shiftDown(int row) {
    for(int i = row; i >= 0; i --) {
        // ��� i �п����� i - 1 �� 
        for(int j = 0; j < CHESSBOARD_WIDTH; j ++) {
            mColors[i][j] = mColors[i - 1][j];
        }
    }
    // ��յ�һ�� 
    for(int j = 0; j < CHESSBOARD_WIDTH; j ++) {
        mColors[0][j] = 0;
    }
}

int Chessboard::getViewPosColor(int x, int y) const {
    if(!InChessboard(x, y)) {
        return (int)ConsoleColor::WHITE;
    }
    if(InTeris(x, y)) {
        if(mTetrisBlock -> getPos(x - mPosX, y - mPosY)) {
            // �ڵ�����Ͻ��Χ�� 
            // ���ҵ�����ڴ˴���͸�� 
            return mTetrisBlock -> getColorId();
        }
    }
    return getPosColor(x, y); // �����ϵ�λ�� 
}

void Chessboard::tetrisLeft() {
    int nPosX = mPosX, nPosY = mPosY - 1;
    if(checkAvailable(nPosX, nPosY, *mTetrisBlock)) {
        mPosY --; // ���������ƶ� 
    }
}

void Chessboard::tetrisRight() {
    int nPosX = mPosX, nPosY = mPosY + 1;
    if(checkAvailable(nPosX, nPosY, *mTetrisBlock)) {
        mPosY ++; // ���������ƶ� 
    }
}

void Chessboard::tetrisTurn() {
    TetrisBlock nTetrisBlock = *mTetrisBlock;
    nTetrisBlock.rotate();
    if(checkAvailable(mPosX, mPosY, nTetrisBlock)) {
        delete mTetrisBlock;
        mTetrisBlock = new TetrisBlock(nTetrisBlock);
        // ����һ���µĿռ� 
    }
}

void Chessboard::makeNextType() {
    const int ColorCount = 6;
    mNextType = (TetrisBlock::TetrisType) rand(0, TetrisTypeCount - 1); // �������һ����״ 
    mNextColorId = (ConsoleColor::Colors) rand(1 + 8, ColorCount + 8);
}

void Chessboard::setPosColor(int row, int col, int color) {
    mColors[row][col] = color;
}

