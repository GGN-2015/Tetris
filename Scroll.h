#ifndef SCROLL_H
#define SCROLL_H // ���ݾ���� 

class Scroll {
public:
    Scroll(int posCount); // �ܹ��� PosCount ����λ��ˮƽ����� 
    
    void leftMove();          // �����ƶ�һ��λ�� 
    void rightMove();         // �����ƶ�һ��λ�� 
    void setPos(int newPos);  // ����λ�� 
    int  getPos() const;      // ��ȡ��ǰ�ĵ�λ 
    int  getPosCount() const; // ��ȡ��λ���� 
    
    double getRate() const;   // ��ñ��� 
    
private:
    int mPosCount, mPosNow; // PosCount �ǵ�λ������ PosNow �ǵ�ǰ��λ 
};

#endif

