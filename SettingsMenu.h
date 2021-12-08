#ifndef SETTINGSMENU_H
#define SETTINGSMENU_H

#include "IMenu.h"
#include "Scroll.h"

const int VOLUMN_MAX = 6;
const int RESOLUTION_MAX = 6;

class SettingsMenu: public IMenu { // ѡ��˵� 
public:
    SettingsMenu();
    
    enum Terms { // ��Ҫ�ֶ��� getTerms һ�� 
        Volumn = 0, Resolution = 1, Back = 2
    };
    
    virtual std::string getTitle() const;
    virtual const std::vector<std::string>& getTerms() const;
    virtual void show() const;
    
    virtual void process();
    
    void leftMoveActive();
    void rightMoveActive(); // ����/�����ƶ���ǰ��ľ���� 
    
    const Scroll* getVolumnScroll() const;
    const Scroll* getResolutionScroll() const; // ��ȡ�������Ϣ 

public:
    static Scroll mVolumn;    // ���������ȼ� 
    static Scroll mResolution; // �ֱ��� 
};

#endif

