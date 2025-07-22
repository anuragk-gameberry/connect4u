//
//  BotDriver.cpp
//  testproj
//
//  Created by Anurag Khugshal on 17/07/25.
//
#include "BotDriver.h"
#include "axmol.h"
#include "../BotAlgorithms/MiniMaxBot.h"

BotDriver:: BotDriver(BotAlgorithm* algo){
    this->algo = algo;
}

void BotDriver:: processMove(int col, int row)  {
    auto eventdispatcher = ax::Director::getInstance()->getEventDispatcher();
 
    if (finished || row >=6){
        return;
    }
    
    this->gameboard[col].push_back(turn);
    
   
    
    auto v = GameLogic::didwin(gameboard, col, row);
   
    std::vector <int> Data =  {turn,col,row};
    
    
    eventdispatcher->dispatchCustomEvent("placeToken", &Data);
    if (v[0]){
        finished = true;
        releaseWinEvents(v, col, row);
       
        eventdispatcher->dispatchCustomEvent("gameFinished");
    }
   
    
    int nextcol =  algo->getBestMove(gameboard);
    
    
    turn = !turn;
    
    row = (int)gameboard[nextcol].size();
    gameboard[nextcol].push_back(turn);
    

    Data =  {turn,nextcol,row};
    
    eventdispatcher->dispatchCustomEvent("placeToken", &Data);
    v = GameLogic::didwin(gameboard, nextcol, row);
    if (v[0]){
        finished = true;
        releaseWinEvents(v, nextcol, row);
        eventdispatcher->dispatchCustomEvent("gameFinished");

    }
    
    turn =!turn;
    
    
}
