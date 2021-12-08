#ifndef SETTINGSMENU_H
#define SETTINGSMENU_H

#include "IMenu.h"
#include "Scroll.h"

const int VOLUMN_MAX = 6;
const int RESOLUTION_MAX = 6;

class SettingsMenu: public IMenu { // 选项菜单 
public:
    SettingsMenu();
    
    enum Terms { // 需要手动与 getTerms 一致 
        Volumn = 0, Resolution = 1, Back = 2
    };
    
    virtual std::string getTitle() const;
    virtual const std::vector<std::string>& getTerms() const;
    virtual void show() const;
    
    virtual void process();
    
    void leftMoveActive();
    void rightMoveActive(); // 向左/向右移动当前活动的卷滚条 
    
    const Scroll* getVolumnScroll() const;
    const Scroll* getResolutionScroll() const; // 获取卷滚条信息 

public:
    static Scroll mVolumn;    // 储存音量等级 
    static Scroll mResolution; // 分辨率 
};

#endif

