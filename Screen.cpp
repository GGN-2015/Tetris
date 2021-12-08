#include "Console.h"
#include "ConsoleColor.h"
#include "Screen.h"

CharPixel::CharPixel(): colorID(ConsoleColor::defaultColor) {}
CharPixel::CharPixel(const char* str): colorID(ConsoleColor::defaultColor) {
    chr[0] = str[0];
    chr[1] = str[1]; // 每个位置要记录两个字符 
}

CharPixel::CharPixel(const char* str, int col) {
    chr[0] = str[0];
    chr[1] = str[1];
    colorID = col; // 设置颜色和字符内容 
}

bool CharPixel::equalTo(const CharPixel& cp) const {
    return 
        chr[0] == cp.chr[0] && 
        chr[1] == cp.chr[1] &&
        colorID == cp.colorID; // 颜色与字符内容对应相等 
}

bool CharPixel::empty() const {
    return 
        chr[0] == ' ' && // 检测是不是空格对 
        chr[1] == ' ';
}

Screen::Screen(int row, int col, int height, int width) {
    mRow = row;
    mCol = col;
    mHeight = height; // 从参数拷贝一些数据 
    mWidth = width;
    
    mCurrentId = 0; // 当前缓存 id = 0 
    
    for(int id = 0; id <= 1; id ++) {
        // 创建缓存 mCache[id] 
        mCache[id] = new CharPixel*[height];
        for(int i = 0; i < height; i ++) {
            mCache[id][i] = new CharPixel[width]; // 申请一行像素对应的缓存 
        }
    }
}

Screen::~Screen() {
    for(int id = 0; id <= 1; id ++) { // 释放缓存 mCache[id] 对应的储存空间 
        for(int i = 0; i < mHeight; i ++) {
            delete[] mCache[id][i];
        }
        delete[] mCache[id];
    }
}

bool Screen::needOutput(int inRow, int inCol) const {
    const int& id = mCurrentId; // 当前缓冲 id 
    if(mCache[id ^ 1][inRow][inCol].chr[0] == 0 || mCache[id ^ 1][inRow][inCol].chr[1] == 0) {
        return true;
    }else {
        return !mCache[id][inRow][inCol].equalTo(mCache[id ^ 1][inRow][inCol]);
    }
}

void Screen::display() {   // 将当前缓存中的内容输出 
    Console::initialize(); // 每次输出前都要求必须隐藏光标 
    int& id = mCurrentId;
    for(int i = 0; i < mHeight; i ++) {
        for(int j = 0; j < mWidth; j ++) {
            if(needOutput(i, j)) {
                char str[3] = {mCache[id][i][j].chr[0], mCache[id][i][j].chr[1], 0};
                Console::showStr(
                    str,
                    mCache[id][i][j].colorID, // 在对应位置输出字符(串) 
                    i + mRow,
                    j * 2 + mCol
                );
            }
        }
    }
    id ^= 1;
    clearCache(id); // 清空当前缓存 
    resetCurXY();   // 输出光标恢复到文件头 
}

void Screen::clearCache(int id, const CharPixel& cp) { // 清空一块缓存 
    for(int i = 0; i < mHeight; i ++) {
        for(int j = 0; j < mWidth; j ++) {
            mCache[id][i][j] = cp; // 一般是空白字符 
        }
    }
}

void Screen::setPixel(int row, int col, const CharPixel& charPixel) {
    int& id = mCurrentId;
    if(0 <= row && row < mHeight && 0 <= col && col < mWidth) { // 自动忽略出界信息 
        mCache[id][row][col] = charPixel; // 赋值进入当前缓存 
    }
}

void Screen::writeString(int row, int col, const char* str, int colorId) {
    for(int i = 0; str[i]; i += 2) {
        char tmp[3] = {str[i], str[i + 1], 0};
        if(str[i + 1] == 0) {
            tmp[1] = ' '; // 并不输出字符 '\0' 而是输出空格 
        }
        deleteNewline(tmp); // 将换行符 crlf 改为空格 
        setPixel(row, col + i/2, CharPixel(tmp, colorId));
        if(str[i + 1] == 0) {
            break;
        }
    }
}

void Screen::appendString(const char* str, int colorId) {
    writeString(mCurX, mCurY, str, colorId);
    int length = ((int)strlen(str) + 1) / 2; // 两个字符占据一个位置 
    mCurY += length;
}

void Screen::appendMarginNewLine(const char* str, int marginCnt, int newLineCnt, int colorId) {
    jumpMargin(marginCnt);
    appendString(str, colorId);
    newLine(newLineCnt);
}

void Screen::demonstration() { // 演示性程序 
    Screen screen(5, 10, 5, 5); 
	int i = 0, j = 0;
	while(true) {
	    char str[] = "□";
	    for(int x = 0; x < 5;  x ++) {
	        for(int y = 0; y < 5; y ++) {
	            screen.setPixel(x, y, CharPixel(str, ConsoleColor::WHITE));
	        }
	    }
        screen.setPixel(i, j, CharPixel(str, ConsoleColor::RED));
	    screen.display();
	    j ++;
	    if(j == 5) {
	        i ++;
	        j = 0;
	    }
	    if(i == 5) {
	        i = 0;
	    }
	    Sleep(200); // 每 200 ms 切换一下小红点位置 
    }  
}

void Screen::resetCurXY() { // 重置输出光标 
    mCurX = mCurY = 0;
}

void Screen::jumpMargin(int yCnt) { // 跳过边框的一段区域 
    mCurY += yCnt;
}

void Screen::drawMargin(const CharPixel& cp) {
    for(int i = 0; i < mHeight; i ++) {
        setPixel(i, 0, cp);
        setPixel(i, mWidth - 1, cp); // 绘制左右边框 
    }
    for(int j = 0; j < mWidth; j ++) {
        setPixel(0, j, cp);
        setPixel(mHeight - 1, j, cp); // 绘制上下边框 
    }
}

void Screen::deleteNewline(char* str) const {
    for(int i = 0; str[i]; i ++) {
        if(str[i] == '\n' || str[i] == '\r') {
            str[i] = ' '; // 用空格替换换行相关的数据 
        }
    }
}

void Screen::clearAll() {
    //system("cls"); // 这并不是一个很好的清空屏幕的方法 
    char tmp[3] = {0};
    clearCache(0, CharPixel(tmp, ConsoleColor::WHITE));
    clearCache(1, CharPixel(tmp, ConsoleColor::WHITE));
}

void Screen::newLine() { // 开启新的一行内容 
    mCurX ++;
    mCurY = 0;
}

void Screen::newLine(int cnt) { // 开启新的一行内容 
    if(cnt > 0) {
        mCurX += cnt; // cnt <= 0 表示不需要新建任何空行 
        mCurY = 0;
    }
}

