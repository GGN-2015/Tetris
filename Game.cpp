#include <ctime>

#include "App.h"
#include "Game.h"
#include "ChessBoard.h"
#include "Controller.h" 

int Game::tickLength = TICK_LENGTH_MAX; // 600 ms

Game::Game() {
    mLastTickTime = clock(); // 上一个 tick 更新的时间 
    mChessboard = new Chessboard;
}

void Game::newGame() {
    mLastTickTime = clock(); // 上一个 tick 更新的时间 
    delete mChessboard;
    mChessboard = new Chessboard;
}

Game& Game::getInstance() {
    static Game game; // 懒得写指针了，直接静态单例 
    return game; 
}

int Game::getScore() const {
    return mScore;
}

void Game::runTick() { // 试图运行一个 tick 
    if(mLastTickTime < 0) {
        mLastTickTime = clock();
    }else {
        if(clock() - mLastTickTime >= tickLength) {
            bool okToRun = true;
            mScore += mChessboard -> moveDown(okToRun); // 让游戏进行一个 tick 
            mLastTickTime = clock();
            // 开始一个新的 Tick 
            if(!okToRun) {
                Controller::lostGame(getScore()); // 游戏失败 
            }
        }
    }
}

const Chessboard* Game::getChessboard() const {
    return mChessboard;
}

Chessboard* Game::getChessboard() {
    return mChessboard; // 为了 process 使用 
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

void Game::inputFromFile(const char* fileName) { // 从文件中加载一个地图 
    mLastTickTime = clock();
    App::loadGame(fileName);
}

