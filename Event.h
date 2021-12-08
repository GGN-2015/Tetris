// 当前事件处理算法一律检测的是抬起事件 
// 类似于数字逻辑电路中的下降沿 

#ifndef EVENT_H
#define EVENT_H

class GameMenu;
class IMenu;
class MainMenu;

struct KeyList {
    bool mKeyLeft = 0, mKeyRight = 0, mKeyUp = 0, mKeyDown = 0; // 方向键 
    bool mKeyEnter = 0, mKeyEsc = 0, mKeySpace = 0;
    
    void getKeyList(); // 获取当前的状态集合 
    void clearKeyList();
}; 

class Event {
public:
    Event(); // 在构造的同时读取当前的事件信息 
    
    virtual bool isConfirm() const;  // 检测回车是否被按下了 
    virtual bool isEsc() const;      // 检测 Esc 是否被按下 
    
    bool isLeft  () const;
    bool isRight () const;
    bool isUp    () const;
    bool isDown  () const; // 检测是否是上下左右方向移动的键被按下 
    bool isSpace () const;
    
    void operateIMenu(IMenu*) const;       // 操作 IMenu 的的 ActiveTerm 的选中 
    void operateGameMenu(GameMenu*) const; // 操作游戏页面 
    
    static void inActivate(); // 动作失活 
    
private:
    static const int inactiveLength = 400; // 400 ms 失活 
    static int inactiveTime;
    
    static KeyList keyListNow;
    static KeyList keyListLast;
};

#endif

