// Screen::demonstration();   // ��ɫ���Ǻ� 

#ifndef SCREEN_H
#define SCREEN_H

#include "ConsoleColor.h"

struct CharPixel {
	char chr[2] {0, 0}; // chr = 0 ��ʾ��λ��û�о�������ʼ�� 
	int colorID; // ���ڼ�¼��Ļ��ĳ��λ�õ� �ַ� �� ��ɫ 
	
	CharPixel();       // ��ʼ�� chr = 0
	CharPixel(const char* str); // chr = c
	CharPixel(const char* str, int col);
	
	bool equalTo(const CharPixel&) const; // �Ƚ����������Ƿ���ȫһ�� 
	bool empty() const;                   // ����ǲ��ǿո�� 
};

class Screen {
public:
	Screen(int row, int col, int height, int width); // ����һ����Ļ���� 
	~Screen(); // ������ʱ��Ҫ�����Ļ���� 
	
	void display(); // ����ǰ�����е�����������������һ������ 
	void clearCache(int id, const CharPixel& cp = CharPixel("  ")); // ���ĳһ�黺�� 
	
	void setPixel(int row, int col, const CharPixel& charPixel);           // д�뵱ǰ���� 
	void writeString(int row, int col, const char* str, int colorId);      // �ַ���д�뻺�� 
	void appendString(const char* str, int colorId = ConsoleColor::WHITE); // �� mCurX, mCurY, д�ַ��� 
	
	static void demonstration(); // ������ʾ��С���� 
	
	void resetCurXY();     // ���������� 
	void newLine();        // �������л�����һ�� 
	void newLine(int cnt); // �������л�����  cnt �� 
	void jumpMargin(int);  // �����߿�����ɸ��ַ� 
	
	void drawMargin(const CharPixel& cp); // ��ĳ���ַ����߿� 
	
	void appendMarginNewLine(const char* str, int = 0, int = 0, int = ConsoleColor::WHITE); // ���һ������ 
	
	void clearAll();
	
	
private:
    // inRow, inCol ��ʾ�ڲ�������������� 
    bool needOutput(int inRow, int inCol) const; // ���ĳ��λ���Ƿ���Ҫ��� 
    void deleteNewline(char* str) const;         // ɾ��һ���ַ����е����л��з� 
    
	int mRow, mCol, mHeight, mWidth;
	
	int mCurrentId;	       // ��ǰ���� ID 
	CharPixel** mCache[2]; // ˫���棬Ҫ�����ַ����б������ż����ʼ 
	
	int mCurX, mCurY;      // ��ǰ���ָ�룬������ʱ������ 
};

#endif // SCREEN_H

