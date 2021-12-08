#include "Console.h"
#include "ConsoleColor.h"
#include "Screen.h"

CharPixel::CharPixel(): colorID(ConsoleColor::defaultColor) {}
CharPixel::CharPixel(const char* str): colorID(ConsoleColor::defaultColor) {
    chr[0] = str[0];
    chr[1] = str[1]; // ÿ��λ��Ҫ��¼�����ַ� 
}

CharPixel::CharPixel(const char* str, int col) {
    chr[0] = str[0];
    chr[1] = str[1];
    colorID = col; // ������ɫ���ַ����� 
}

bool CharPixel::equalTo(const CharPixel& cp) const {
    return 
        chr[0] == cp.chr[0] && 
        chr[1] == cp.chr[1] &&
        colorID == cp.colorID; // ��ɫ���ַ����ݶ�Ӧ��� 
}

bool CharPixel::empty() const {
    return 
        chr[0] == ' ' && // ����ǲ��ǿո�� 
        chr[1] == ' ';
}

Screen::Screen(int row, int col, int height, int width) {
    mRow = row;
    mCol = col;
    mHeight = height; // �Ӳ�������һЩ���� 
    mWidth = width;
    
    mCurrentId = 0; // ��ǰ���� id = 0 
    
    for(int id = 0; id <= 1; id ++) {
        // �������� mCache[id] 
        mCache[id] = new CharPixel*[height];
        for(int i = 0; i < height; i ++) {
            mCache[id][i] = new CharPixel[width]; // ����һ�����ض�Ӧ�Ļ��� 
        }
    }
}

Screen::~Screen() {
    for(int id = 0; id <= 1; id ++) { // �ͷŻ��� mCache[id] ��Ӧ�Ĵ���ռ� 
        for(int i = 0; i < mHeight; i ++) {
            delete[] mCache[id][i];
        }
        delete[] mCache[id];
    }
}

bool Screen::needOutput(int inRow, int inCol) const {
    const int& id = mCurrentId; // ��ǰ���� id 
    if(mCache[id ^ 1][inRow][inCol].chr[0] == 0 || mCache[id ^ 1][inRow][inCol].chr[1] == 0) {
        return true;
    }else {
        return !mCache[id][inRow][inCol].equalTo(mCache[id ^ 1][inRow][inCol]);
    }
}

void Screen::display() {   // ����ǰ�����е�������� 
    Console::initialize(); // ÿ�����ǰ��Ҫ��������ع�� 
    int& id = mCurrentId;
    for(int i = 0; i < mHeight; i ++) {
        for(int j = 0; j < mWidth; j ++) {
            if(needOutput(i, j)) {
                char str[3] = {mCache[id][i][j].chr[0], mCache[id][i][j].chr[1], 0};
                Console::showStr(
                    str,
                    mCache[id][i][j].colorID, // �ڶ�Ӧλ������ַ�(��) 
                    i + mRow,
                    j * 2 + mCol
                );
            }
        }
    }
    id ^= 1;
    clearCache(id); // ��յ�ǰ���� 
    resetCurXY();   // ������ָ����ļ�ͷ 
}

void Screen::clearCache(int id, const CharPixel& cp) { // ���һ�黺�� 
    for(int i = 0; i < mHeight; i ++) {
        for(int j = 0; j < mWidth; j ++) {
            mCache[id][i][j] = cp; // һ���ǿհ��ַ� 
        }
    }
}

void Screen::setPixel(int row, int col, const CharPixel& charPixel) {
    int& id = mCurrentId;
    if(0 <= row && row < mHeight && 0 <= col && col < mWidth) { // �Զ����Գ�����Ϣ 
        mCache[id][row][col] = charPixel; // ��ֵ���뵱ǰ���� 
    }
}

void Screen::writeString(int row, int col, const char* str, int colorId) {
    for(int i = 0; str[i]; i += 2) {
        char tmp[3] = {str[i], str[i + 1], 0};
        if(str[i + 1] == 0) {
            tmp[1] = ' '; // ��������ַ� '\0' ��������ո� 
        }
        deleteNewline(tmp); // �����з� crlf ��Ϊ�ո� 
        setPixel(row, col + i/2, CharPixel(tmp, colorId));
        if(str[i + 1] == 0) {
            break;
        }
    }
}

void Screen::appendString(const char* str, int colorId) {
    writeString(mCurX, mCurY, str, colorId);
    int length = ((int)strlen(str) + 1) / 2; // �����ַ�ռ��һ��λ�� 
    mCurY += length;
}

void Screen::appendMarginNewLine(const char* str, int marginCnt, int newLineCnt, int colorId) {
    jumpMargin(marginCnt);
    appendString(str, colorId);
    newLine(newLineCnt);
}

void Screen::demonstration() { // ��ʾ�Գ��� 
    Screen screen(5, 10, 5, 5); 
	int i = 0, j = 0;
	while(true) {
	    char str[] = "��";
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
	    Sleep(200); // ÿ 200 ms �л�һ��С���λ�� 
    }  
}

void Screen::resetCurXY() { // ���������� 
    mCurX = mCurY = 0;
}

void Screen::jumpMargin(int yCnt) { // �����߿��һ������ 
    mCurY += yCnt;
}

void Screen::drawMargin(const CharPixel& cp) {
    for(int i = 0; i < mHeight; i ++) {
        setPixel(i, 0, cp);
        setPixel(i, mWidth - 1, cp); // �������ұ߿� 
    }
    for(int j = 0; j < mWidth; j ++) {
        setPixel(0, j, cp);
        setPixel(mHeight - 1, j, cp); // �������±߿� 
    }
}

void Screen::deleteNewline(char* str) const {
    for(int i = 0; str[i]; i ++) {
        if(str[i] == '\n' || str[i] == '\r') {
            str[i] = ' '; // �ÿո��滻������ص����� 
        }
    }
}

void Screen::clearAll() {
    //system("cls"); // �Ⲣ����һ���ܺõ������Ļ�ķ��� 
    char tmp[3] = {0};
    clearCache(0, CharPixel(tmp, ConsoleColor::WHITE));
    clearCache(1, CharPixel(tmp, ConsoleColor::WHITE));
}

void Screen::newLine() { // �����µ�һ������ 
    mCurX ++;
    mCurY = 0;
}

void Screen::newLine(int cnt) { // �����µ�һ������ 
    if(cnt > 0) {
        mCurX += cnt; // cnt <= 0 ��ʾ����Ҫ�½��κο��� 
        mCurY = 0;
    }
}

