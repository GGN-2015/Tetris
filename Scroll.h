#ifndef SCROLL_H
#define SCROLL_H // 数据卷滚条 

class Scroll {
public:
    Scroll(int posCount); // 总共有 PosCount 个挡位的水平卷滚条 
    
    void leftMove();          // 向左移动一个位置 
    void rightMove();         // 向右移动一个位置 
    void setPos(int newPos);  // 设置位置 
    int  getPos() const;      // 获取当前的挡位 
    int  getPosCount() const; // 获取挡位个数 
    
    double getRate() const;   // 获得比例 
    
private:
    int mPosCount, mPosNow; // PosCount 是挡位总数， PosNow 是当前挡位 
};

#endif

