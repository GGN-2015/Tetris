// Screen::demonstration();   // 红色的星号 

#ifndef SCREEN_H
#define SCREEN_H

#include "ConsoleColor.h"

struct CharPixel {
	char chr[2] {0, 0}; // chr = 0 表示改位置没有经历过初始化 
	int colorID; // 用于记录屏幕上某个位置的 字符 和 颜色 
	
	CharPixel();       // 初始化 chr = 0
	CharPixel(const char* str); // chr = c
	CharPixel(const char* str, int col);
	
	bool equalTo(const CharPixel&) const; // 比较两个像素是否完全一致 
	bool empty() const;                   // 检测是不是空格对 
};

class Screen {
public:
	Screen(int row, int col, int height, int width); // 构建一个屏幕区域 
	~Screen(); // 析构的时候要清空屏幕缓存 
	
	void display(); // 将当前缓存中的数据输出，并清空下一个缓存 
	void clearCache(int id, const CharPixel& cp = CharPixel("  ")); // 清空某一块缓存 
	
	void setPixel(int row, int col, const CharPixel& charPixel);           // 写入当前缓存 
	void writeString(int row, int col, const char* str, int colorId);      // 字符串写入缓存 
	void appendString(const char* str, int colorId = ConsoleColor::WHITE); // 在 mCurX, mCurY, 写字符串 
	
	static void demonstration(); // 用于演示的小程序 
	
	void resetCurXY();     // 重置输出光标 
	void newLine();        // 输出光标切换到下一行 
	void newLine(int cnt); // 输出光标切换到下  cnt 行 
	void jumpMargin(int);  // 跳过边框的若干个字符 
	
	void drawMargin(const CharPixel& cp); // 用某种字符填充边框 
	
	void appendMarginNewLine(const char* str, int = 0, int = 0, int = ConsoleColor::WHITE); // 输出一行内容 
	
	void clearAll();
	
	
private:
    // inRow, inCol 表示内部的相对行列坐标 
    bool needOutput(int inRow, int inCol) const; // 检测某个位置是否需要输出 
    void deleteNewline(char* str) const;         // 删除一个字符串中的所有换行符 
    
	int mRow, mCol, mHeight, mWidth;
	
	int mCurrentId;	       // 当前缓存 ID 
	CharPixel** mCache[2]; // 双缓存，要求汉字字符的列标必须是偶数开始 
	
	int mCurX, mCurY;      // 当前输出指针，随机输出时不考虑 
};

#endif // SCREEN_H

