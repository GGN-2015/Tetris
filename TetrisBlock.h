#ifndef TETRISBLOCK_H
#define TETRISBLOCK_H

#include "ConsoleColor.h"

const int TETRIS_TYPE_COUNT = 7; // ���Ϊ 0 ~ 4 

class TetrisBlock { // ������������˹�����е�һ���� 
public:
    enum TetrisType {
        TYPE_Z, TYPE_RZ, TYPE_T, TYPE_L, TYPE_RL, TYPE_I, TYPE_O // ����˹�����������״���� 
    };
    
    TetrisBlock(TetrisType type, ConsoleColor::Colors colorId); // ����һ������˹����Ļ�����״ 
    
    void debugShow() const; // �ڵ���ģʽ�£����������������˹�������״ 
    int maxDepth() const;   // ���㵱ǰ mPos ���з���λ�õ�����к� 
    
    void rotate();          // �Զ���˹�������˳ʱ����ת 
    int getPos(int, int) const; // ����ĳ��λ���Ƿ��з��� 
    
    int getColorId() const; // �õ�����˹�������ɫ 
    
private:
    void rotateFull();     // ������ 4 * 4 �������������ת 
    
    bool leftMost() const; // �ж�ͼ���Ƿ���������߽��� 
    bool upMost() const;   // �ж�ͼ���Ƿ��������ϱ߽��� 
    
    void moveLeft(); // ��ͼ�������ƶ�һ����λ 
    void moveUp();   // ��ͼ�������ƶ�һ����λ 
    
    bool mPos[4][4] {}; // ���ڼ�¼����˹�������״ 
    int mColorId;       // ��¼����˹�������ɫ 
};

#endif

