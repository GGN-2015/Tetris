#include <ctime>

#include "App.h"
#include "Game.h"
#include "ChessBoard.h"
#include "Controller.h" 

int Game::tickLength = TICK_LENGTH_MAX; // 600 ms

Game::Game() {
    mLastTickTime = clock(); // ��һ�� tick ���µ�ʱ�� 
    mChessboard = new Chessboard;
}

void Game::newGame() {
    mLastTickTime = clock(); // ��һ�� tick ���µ�ʱ�� 
    delete mChessboard;
    mChessboard = new Chessboard;
}

Game& Game::getInstance() {
    static Game game; // ����дָ���ˣ�ֱ�Ӿ�̬���� 
    return game; 
}

int Game::getScore() const {
    return mScore;
}

void Game::runTick() { // ��ͼ����һ�� tick 
    if(mLastTickTime < 0) {
        mLastTickTime = clock();
    }else {
        if(clock() - mLastTickTime >= tickLength) {
            bool okToRun = true;
            mScore += mChessboard -> moveDown(okToRun); // ����Ϸ����һ�� tick 
            mLastTickTime = clock();
            // ��ʼһ���µ� Tick 
            if(!okToRun) {
                Controller::lostGame(getScore()); // ��Ϸʧ�� 
            }
        }
    }
}

const Chessboard* Game::getChessboard() const {
    return mChessboard;
}

Chessboard* Game::getChessboard() {
    return mChessboard; // Ϊ�� process ʹ�� 
}

void Game::setSpeed(int degree) {
    int discount = degree * TICK_LENGTH_STEP;
    Game::tickLength = TICK_LENGTH_MAX - discount;
}

void Game::saveGameMenu() const {
    App::saveGameMenu(this);
}

void Game::setScore(int score) {
    mScore = score;
}

void Game::inputFromFile(const char* fileName) { // ���ļ��м���һ����ͼ 
    mLastTickTime = clock();
    App::loadGame(fileName);
}

