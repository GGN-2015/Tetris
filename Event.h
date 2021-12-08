// ��ǰ�¼������㷨һ�ɼ�����̧���¼� 
// �����������߼���·�е��½��� 

#ifndef EVENT_H
#define EVENT_H

class GameMenu;
class IMenu;
class MainMenu;

struct KeyList {
    bool mKeyLeft = 0, mKeyRight = 0, mKeyUp = 0, mKeyDown = 0; // ����� 
    bool mKeyEnter = 0, mKeyEsc = 0, mKeySpace = 0;
    
    void getKeyList(); // ��ȡ��ǰ��״̬���� 
    void clearKeyList();
}; 

class Event {
public:
    Event(); // �ڹ����ͬʱ��ȡ��ǰ���¼���Ϣ 
    
    virtual bool isConfirm() const;  // ���س��Ƿ񱻰����� 
    virtual bool isEsc() const;      // ��� Esc �Ƿ񱻰��� 
    
    bool isLeft  () const;
    bool isRight () const;
    bool isUp    () const;
    bool isDown  () const; // ����Ƿ����������ҷ����ƶ��ļ������� 
    bool isSpace () const;
    
    void operateIMenu(IMenu*) const;       // ���� IMenu �ĵ� ActiveTerm ��ѡ�� 
    void operateGameMenu(GameMenu*) const; // ������Ϸҳ�� 
    
    static void inActivate(); // ����ʧ�� 
    
private:
    static const int inactiveLength = 400; // 400 ms ʧ�� 
    static int inactiveTime;
    
    static KeyList keyListNow;
    static KeyList keyListLast;
};

#endif

