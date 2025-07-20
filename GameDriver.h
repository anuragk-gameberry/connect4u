//
//  GameDriver.h
//  testproj
//
//  Created by Anurag Khugshal on 15/07/25.
//

#ifndef GAME_DRIVER_H
#define GAME_DRIVER_H
#include <vector>
#include "../GameLogic/GameLogic.h"

class GameDriver {
public:
    virtual void processMove (int col, int row);
    GameDriver();
    ~GameDriver();
    
protected:
    void releaseWinEvents(std::vector<int> v, int col, int row);
    
private:
    int turn;
    std::vector<std::vector<int>> gameboard;
    bool finished;
    
};

#endif


