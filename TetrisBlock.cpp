// �Ҿ��ðɣ������Ϸ�߼�ûʲô����չ�� 
// ��ֱ�� if - else�ˣ��о����ⲻ�� 
// Ҫ�Ƿ�Ҫ��չ�����ǲ��绻����Ϸ 

#include <iostream>

#include "TetrisBlock.h"
#include "ConsoleColor.h"

TetrisBlock::TetrisBlock(TetrisType type, ConsoleColor::Colors colorId) { // colorId
    mColorId = (int)colorId; // ע���������� 0, ������ 8 
    if(type == TYPE_Z) { // ���� type ���������˹��������� 
        mPos[0][0] = 1; // ����
        mPos[0][1] = 1; //   ����
        mPos[1][1] = 1;
        mPos[1][2] = 1;
    }else
    if(type == TYPE_RZ) { // ���� type ���������˹��������� 
        mPos[0][1] = 1; //   ����
        mPos[0][2] = 1; // ����
        mPos[1][0] = 1;
        mPos[1][1] = 1;
    }else
    if(type == TYPE_T) {
        mPos[0][0] = 1; // ������
        mPos[0][1] = 1; //   ��
        mPos[0][2] = 1; 
        mPos[1][1] = 1;
    }else
    if(type == TYPE_L) {
        mPos[0][0] = 1; // ��
        mPos[1][0] = 1; // ��
        mPos[2][0] = 1; // ����
        mPos[2][1] = 1; 
    }else
    if(type == TYPE_RL) { // ����� L 
        mPos[0][1] = 1; //   ��
        mPos[1][1] = 1; //   ��
        mPos[2][0] = 1; // ����
        mPos[2][1] = 1; 
    }else
    if(type == TYPE_I) {
        mPos[0][0] = 1; // ��
        mPos[1][0] = 1; // ��
        mPos[2][0] = 1; // ��
        mPos[3][0] = 1; // ��
    }else
    if(type == TYPE_O) {
        mPos[0][0] = 1; // ����
        mPos[0][1] = 1; // ����
        mPos[1][0] = 1;
        mPos[1][1] = 1;
    }else {
        system("cls");
        std::cout << "TetrisBlock::TetrisBlock(TetrisType type) type error! " << (int)type << std::endl;
    }
}

void TetrisBlock::debugShow() const { // ����ʱʹ�õ�������� 
    std::cout << std::endl;           // �Ժ��ò����� 
    for(int i = 0; i < 4; i ++) {
        for(int j = 0; j < 4; j ++) {
            if(mPos[i][j]) {
                std::cout << "��";
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
            int ni = j, nj = 3 - i; // ������˳ʱ����ת 90 �� 
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
    // ����һ����û��ֵ 
    for(int i = 0; i < 4; i ++) {
        if(mPos[i][0]) {
            return true;
        }
    }
    return false;
}

bool TetrisBlock::upMost() const {
    // ����һ����û��ֵ 
    for(int j = 0; j < 4; j ++) {
        if(mPos[0][j]) {
            return true;
        }
    }
    return false;
}

void TetrisBlock::moveLeft() {
    for(int j = 0; j < 3; j ++) {
        // ���п��� 
        for(int i = 0; i < 4; i ++) {
            mPos[i][j] = mPos[i][j+1];
        }
    }
    for(int i = 0; i < 4; i ++) {
        mPos[i][3] = 0; // ������һ�� 
    }
}

void TetrisBlock::moveUp() {
    for(int i = 0; i < 3; i ++) {
        // ���п��� 
        for(int j = 0; j < 4; j ++) {
            mPos[i][j] = mPos[i+1][j];
        }
    }
    for(int j = 0; j < 4; j ++) {
        mPos[3][j] = 0; // ������һ�� 
    }
}

int TetrisBlock::getPos(int row, int col) const {
    if(0 <= row && row <= 3 && 0 <= col && col <= 3) {
        return mPos[row][col]; 
    }else {
        return false; // ���е��Ƿ����� 
    }
}

int TetrisBlock::getColorId() const {
    return mColorId;
}

