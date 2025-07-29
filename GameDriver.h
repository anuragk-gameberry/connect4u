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
#include "../Entities/Player.h"

class GameDriver {
public:
    virtual void processMove (int col, int row);
    virtual void rematch ();
//    virtual bool validateMove();
    GameDriver();
    ~GameDriver();
    bool finished;
    int totalPlayers;
    int turn;
    
protected:
    void releaseWinEvents(std::vector<int> v, int col, int row);

   
   
    
    std::vector<std::vector<int>> gameboard;
//    std::vector<std::vector<Player>> players;
   
    
};

#endif


