//
//  BotDriver.cpp
//  testproj
//
//  Created by Anurag Khugshal on 17/07/25.
//
#include "BotDriver.h"
#include "axmol.h"

void BotDriver:: processMove(int col, int row)  {
    if (finished || row >=6){
        return;
    }
    this->gameboard[col].push_back(turn);
    
   
    
    auto v = GameLogic::didwin(gameboard, col, row);
    auto eventdispatcher = ax::Director::getInstance()->getEventDispatcher();
    std::vector <int> Data =  {turn,col,row};
    
    eventdispatcher->dispatchCustomEvent("placeToken", &Data);
    if (v[0]){
        finished = true;
        releaseWinEvents(v, col, row);
    }
    turn = !turn;
}
