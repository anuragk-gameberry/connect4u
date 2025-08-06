//
//  GameDriver.h
//  testproj
//
//  Created by Anurag Khugshal on 15/07/25.
//

#ifndef GAME_DRIVER_H
#define GAME_DRIVER_H
#include <vector>
#include "GameLogic/GameLogic.h"
#include "Entities/Player.h"

class GameDriver {
public:
    bool finished;
    bool isBotGame;
    int turn;
    Player* p;
    int rows;
    int cols;
    int totalPlayers;
    virtual void processMove (int col, int row);
    virtual void rematch ();
    virtual void stats ();
    GameDriver(int cols, int rows);
    ~GameDriver();
    
    
protected:
    std::vector<std::vector<int>> gameboard;
    void releaseWinEvents(std::vector<int> v, int col, int row);
   
   
    
};

#endif


