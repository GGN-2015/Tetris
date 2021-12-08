#ifndef CHESSBOARD_H
#define CHESSBOARD_H // ��¼һ������˹��������� 

const int CHESSBOARD_HEIGHT = 22;
const int CHESSBOARD_WIDTH  = 11; // ���̵Ĵ�С 

#include "TetrisBlock.h"

class Chessboard {
public:
    Chessboard(); // ���������� 
    ~Chessboard();
    
    int moveDown(bool& okToRun); // �� mTetris ��ͼ�����ƶ� 
    
    void show() const; // ��ʾһ������, ֱ��ί�и� View �� 
    bool reset();      // ���´Ӷ������� 
    void getPosXY(int&,int&) const; // ��ȡ�����λ�� 
    
    
    int getViewPosColor(int x, int y) const; // ���ؿ���������ɫ, ���ǵ���� 
    void setPosColor(int row, int col, int color);
    
    void tetrisLeft  ();
    void tetrisRight ();
    void tetrisTurn  ();  // ��ͼ�ƶ���ת����˹���� 
    bool tetrisDown  ();
    
    int getPosColor(int row, int col) const; // �õ�ĳһ��λ�õ���ɫ����Ե���� WHITE (�����ǵ����) 
    // �� �˺������� PutDownIsLand/���� ʹ�� 

private:
    int deleteTest();
    void putDownIsland(); // �������������㷨 
    
    bool checkFull(int row) const; // �����һ���Ƿ����� 
    void shiftDown(int row);       // ����ͼ���������ƣ������±�Ϊ row ���� 
    
    static int rand(int L, int R); // ���ɱ������ڵ������ 
    
    void setTetrisBlock(int x, int y, const TetrisBlock& tb);       // �� TetrisBlock ����ͼ�� 
    bool checkAvailable(int x, int y, const TetrisBlock& tb) const; // ���ĳ��λ���Ϸ���һ�� Block �Ƿ�Ϸ� 
    
    bool InChessboard(int row, int col) const; // ���ĳ��λ���Ƿ��������� 
    bool InTeris(int row, int col) const; // ���ĳ��λ���Ƿ��ڵ���鷶Χ�� 
    // int getPosColor(int row, int col) const; // �õ�ĳһ��λ�õ���ɫ����Ե���� WHITE (�����ǵ����) 
    
    void makeNextType(); 
    
    int mColors[CHESSBOARD_HEIGHT][CHESSBOARD_WIDTH] {}; // ��¼������ÿ��λ�õ���ɫ, 0 ��ʾ�޷��� 
    int mPosX, mPosY;
    TetrisBlock* mTetrisBlock; // ��¼��ǰ�� 
    
    TetrisBlock::TetrisType mNextType;    // ��һ�������ʽ 
    ConsoleColor::Colors    mNextColorId; // ��һ�������ɫ 
    
    Chessboard(const Chessboard&) = delete;
    Chessboard& operator= (const Chessboard&) = delete; // ��ֹ������ֵ 
};

#endif

