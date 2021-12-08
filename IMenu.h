#ifndef IMENU_H
#define IMENU_H

#include <string>
#include <vector>

class IMenu { // IMenu �ǳ���Ĳ˵��� 
public:
    virtual std::string getTitle() const;                     // ��ȡ�˵��ı��� 
    virtual const std::vector<std::string>& getTerms() const; // ��ȡ�˵���ÿһ������ 
    virtual void show() const;                                // ��ʾ����˵�, ί�и� View �� 
    
    virtual void process();                  // �����û��¼�, ί�и� Controller 
    virtual std::string getMenuType() const; // �õ� Menu ���� 
    
    int  getActiveTermId() const;    // ����õ���ǰ��ѡ�е�ѡ��� ID (�±�) 
    void setActiveTermId(int newId); // �޸ĵ�ǰ��ѡ�е�ѡ�� ID 
    int  getTermsCount() const;      // �õ���Ŀ������ 
    
    void nextTerm();
    void prevTerm(); // ������ƶ�����һ�������һ������֮�� 
    
protected:
    int mActiveTermId = 0; // ��¼��ǰ��ѡ�е���Ŀ�� ID 
};

#endif

