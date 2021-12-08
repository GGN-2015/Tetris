// 我觉得吧，这个游戏逻辑没什么可拓展的 
// 就直接 if - else了，感觉问题不大 
// 要是非要拓展，倒是不如换个游戏 

#include <iostream>

#include "TetrisBlock.h"
#include "ConsoleColor.h"

TetrisBlock::TetrisBlock(TetrisType type, ConsoleColor::Colors colorId) { // colorId
    mColorId = (int)colorId; // 注，不允许是 0, 可以是 8 
    if(type == TYPE_Z) { // 根据 type 来定义俄罗斯方块的类型 
        mPos[0][0] = 1; // □□
        mPos[0][1] = 1; //   □□
        mPos[1][1] = 1;
        mPos[1][2] = 1;
    }else
    if(type == TYPE_RZ) { // 根据 type 来定义俄罗斯方块的类型 
        mPos[0][1] = 1; //   □□
        mPos[0][2] = 1; // □□
        mPos[1][0] = 1;
        mPos[1][1] = 1;
    }else
    if(type == TYPE_T) {
        mPos[0][0] = 1; // □□□
        mPos[0][1] = 1; //   □
        mPos[0][2] = 1; 
        mPos[1][1] = 1;
    }else
    if(type == TYPE_L) {
        mPos[0][0] = 1; // □
        mPos[1][0] = 1; // □
        mPos[2][0] = 1; // □□
        mPos[2][1] = 1; 
    }else
    if(type == TYPE_RL) { // 反向的 L 
        mPos[0][1] = 1; //   □
        mPos[1][1] = 1; //   □
        mPos[2][0] = 1; // □□
        mPos[2][1] = 1; 
    }else
    if(type == TYPE_I) {
        mPos[0][0] = 1; // □
        mPos[1][0] = 1; // □
        mPos[2][0] = 1; // □
        mPos[3][0] = 1; // □
    }else
    if(type == TYPE_O) {
        mPos[0][0] = 1; // □□
        mPos[0][1] = 1; // □□
        mPos[1][0] = 1;
        mPos[1][1] = 1;
    }else {
        system("cls");
        std::cout << "TetrisBlock::TetrisBlock(TetrisType type) type error! " << (int)type << std::endl;
    }
}

void TetrisBlock::debugShow() const { // 测试时使用的输出函数 
    std::cout << std::endl;           // 以后用不到了 
    for(int i = 0; i < 4; i ++) {
        for(int j = 0; j < 4; j ++) {
            if(mPos[i][j]) {
                std::cout << "□";
            }else {
                std::cout << "**";
            }
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

int TetrisBlock::maxDepth() const {
    int maxDep = 0;
    for(int i = 3; i >= 0; i --) {
        for(int j = 0; j < 4; j ++) {
            if(mPos[i][j]) {
                maxDep = i;
                break;
            }
        }
    }
    return maxDep;
}

void TetrisBlock::rotate() {
    rotateFull();
    while(!leftMost()) {
        moveLeft();
    }
    while(!upMost()) {
        moveUp();
    }
}

void TetrisBlock::rotateFull() {
    bool nPos[4][4] = {};
    for(int i = 0; i < 4; i ++) {
        for(int j = 0; j < 4; j ++) {
            int ni = j, nj = 3 - i; // 绕中心顺时针旋转 90 度 
            nPos[ni][nj] = mPos[i][j];
        }
    }
    for(int i = 0; i < 4; i ++) {
        for(int j = 0; j < 4; j ++) {
            mPos[i][j] = nPos[i][j];
        }
    }
}

bool TetrisBlock::leftMost() const {
    // 检测第一列有没有值 
    for(int i = 0; i < 4; i ++) {
        if(mPos[i][0]) {
            return true;
        }
    }
    return false;
}

bool TetrisBlock::upMost() const {
    // 检测第一行有没有值 
    for(int j = 0; j < 4; j ++) {
        if(mPos[0][j]) {
            return true;
        }
    }
    return false;
}

void TetrisBlock::moveLeft() {
    for(int j = 0; j < 3; j ++) {
        // 按列拷贝 
        for(int i = 0; i < 4; i ++) {
            mPos[i][j] = mPos[i][j+1];
        }
    }
    for(int i = 0; i < 4; i ++) {
        mPos[i][3] = 0; // 清空最后一列 
    }
}

void TetrisBlock::moveUp() {
    for(int i = 0; i < 3; i ++) {
        // 按行拷贝 
        for(int j = 0; j < 4; j ++) {
            mPos[i][j] = mPos[i+1][j];
        }
    }
    for(int j = 0; j < 4; j ++) {
        mPos[3][j] = 0; // 清空最后一行 
    }
}

int TetrisBlock::getPos(int row, int col) const {
    if(0 <= row && row <= 3 && 0 <= col && col <= 3) {
        return mPos[row][col]; 
    }else {
        return false; // 特判掉非法访问 
    }
}

int TetrisBlock::getColorId() const {
    return mColorId;
}

