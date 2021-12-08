#include <cstdlib>
#include <iostream>

#include "Chessboard.h"
#include "ConsoleColor.h"
#include "TetrisBlock.h"
#include "View.h"

int Chessboard::rand(int L, int R) {
    return std::rand() % (R - L + 1) + L; // 生成随机数 
}

Chessboard::Chessboard() {
    mTetrisBlock = nullptr; // 保证 delete 不 RE 
    makeNextType();
    reset(); // 让方块重新从顶部掉落 
}

int Chessboard::moveDown(bool& okToRun) { // 向下移动俄罗斯方块 
    int scoreAdd = 0;
    okToRun = true;
    if(mTetrisBlock != nullptr) {
        int nPosX = mPosX + 1, nPosY = mPosY;
        if(!checkAvailable(nPosX, nPosY, *mTetrisBlock)) {
            // 如果不能向下移动 
            // 说明此时应该已经到底 
            setTetrisBlock(mPosX, mPosY, *mTetrisBlock); // 固化 
            scoreAdd = deleteTest(); // 试图清除一些下方的行 
            putDownIsland();         // 悬浮岛屿下移 
            okToRun = reset();       // 记录游戏是否失败 
        }else {
            // 如果能向下移动，则向下移动 
            mPosX ++;
        }
    }
    return scoreAdd;
}

bool Chessboard::tetrisDown() {
    int nPosX = mPosX + 1, nPosY = mPosY;
    if(checkAvailable(nPosX, nPosY, *mTetrisBlock)) {
        mPosX ++;
        return true; // 试图向下移动 
    }
    return false;
}

void Chessboard::putDownIsland() {
    // TODO: 悬浮岛屿下沉算法还没有写 
    
}

Chessboard::~Chessboard() {
    delete mTetrisBlock; // 释放方块内存 
}

bool Chessboard::InChessboard(int row, int col) const {
    return 
        0 <= row && row < CHESSBOARD_HEIGHT &&
        0 <= col && col < CHESSBOARD_WIDTH;
}

bool Chessboard::InTeris(int row, int col) const {
    return // 在掉落块管辖范围内 
        mPosX <= row && row < mPosX + 4 &&
        mPosY <= col && col < mPosY + 4;
}

int Chessboard::getPosColor(int row, int col) const {
    if(InChessboard(row, col)) {
        return mColors[row][col]; // 内部 
    }else {
        return ConsoleColor::WHITE; // 棋盘外部 
    }
}

bool Chessboard::checkAvailable(int x, int y, const TetrisBlock& tb) const {
    // 检测在 x, y 位置 tb 能够容纳 
    for(int i = 0; i < 4; i ++) {
        for(int j = 0; j < 4; j ++) {
            if(
                tb.getPos(i, j) != 0 &&
                getPosColor(x + i, y + j) != 0
            ) {
                // 此处出现冲突 
                return false;
            }
        }
    }
    return true;
}

void Chessboard::setTetrisBlock(int x, int y, const TetrisBlock& tb) {
    for(int i = 0; i < 4; i ++) {
        for(int j = 0; j < 4; j ++) {
            // 枚举所有位置 
            if(tb.getPos(i, j) != 0) {
                mColors[x + i][y + j] = tb.getColorId();
                // 放置方块 
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
    
    delete mTetrisBlock; // 删除老的块 
    
    mTetrisBlock = new TetrisBlock(mNextType, mNextColorId);
    int cnt = rand(0, 3);
    while(cnt --) {
        mTetrisBlock -> rotate(); // 初始随机旋转若干次 
    }
    
    makeNextType(); // 设置 mNextType 
    
    if(!checkAvailable(mPosX, mPosY, *mTetrisBlock)) {
        // 此处应该转到失败页面 
        return false; // 你输了 
    }
    
    return true; // 可以继续游戏 
}

int Chessboard::deleteTest() {
    const int lineScore = 100;
    int lineCount = 0; // 统计消去了几行 
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
    // 检查最底下一行是否满了 
    for(int j = 0; j < CHESSBOARD_WIDTH; j ++) {
        if(mColors[row][j] == 0) {
            return false;
            // 找到了一个空位 
        }
    }
    return true; // 没有找到空位 
}

void Chessboard::shiftDown(int row) {
    for(int i = row; i >= 0; i --) {
        // 令第 i 行拷贝第 i - 1 行 
        for(int j = 0; j < CHESSBOARD_WIDTH; j ++) {
            mColors[i][j] = mColors[i - 1][j];
        }
    }
    // 清空第一行 
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
            // 在掉落块管辖范围内 
            // 并且掉落块在此处不透明 
            return mTetrisBlock -> getColorId();
        }
    }
    return getPosColor(x, y); // 棋盘上的位置 
}

void Chessboard::tetrisLeft() {
    int nPosX = mPosX, nPosY = mPosY - 1;
    if(checkAvailable(nPosX, nPosY, *mTetrisBlock)) {
        mPosY --; // 可以向左移动 
    }
}

void Chessboard::tetrisRight() {
    int nPosX = mPosX, nPosY = mPosY + 1;
    if(checkAvailable(nPosX, nPosY, *mTetrisBlock)) {
        mPosY ++; // 可以向左移动 
    }
}

void Chessboard::tetrisTurn() {
    TetrisBlock nTetrisBlock = *mTetrisBlock;
    nTetrisBlock.rotate();
    if(checkAvailable(mPosX, mPosY, nTetrisBlock)) {
        delete mTetrisBlock;
        mTetrisBlock = new TetrisBlock(nTetrisBlock);
        // 申请一块新的空间 
    }
}

void Chessboard::makeNextType() {
    const int ColorCount = 6;
    mNextType = (TetrisBlock::TetrisType) rand(0, TetrisTypeCount - 1); // 随机生成一个形状 
    mNextColorId = (ConsoleColor::Colors) rand(1 + 8, ColorCount + 8);
}

void Chessboard::setPosColor(int row, int col, int color) {
    mColors[row][col] = color;
}

