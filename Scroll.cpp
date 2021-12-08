#include <algorithm>
#include "Scroll.h"

Scroll::Scroll(int posCount) {
    mPosCount = posCount;
    mPosNow = 0; // ���㿪ʼ���� posCount - 1 
}

void Scroll::leftMove() {
    if(mPosNow > 0) {
        mPosNow --;
    }
}

void Scroll::rightMove() {
    if(mPosNow < mPosCount - 1) {
        mPosNow ++;
    }
}

void Scroll::setPos(int newPos) {
    mPosNow = newPos;
    mPosNow = std::max(0, mPosNow);
    mPosNow = std::min(mPosCount - 1, mPosNow);
}

int Scroll::getPos() const {
    return mPosNow;
}

int Scroll::getPosCount() const { // ��ȡ�ܵ�λ���� 
    return mPosCount;
}

double Scroll::getRate() const {
    return double(mPosNow)/(mPosCount - 1); // mPosNow: 0 ~ mPosCount - 1
}

