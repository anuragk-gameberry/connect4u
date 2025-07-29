//
//  BotDriver.cpp
//  testproj
//
//  Created by Anurag Khugshal on 17/07/25.
//
#include "BotDriver.h"
#include "axmol.h"
#include "../BotAlgorithms/MiniMaxBot.h"
#include <AsyncTaskPool.h>
using namespace ax;

BotDriver:: BotDriver(BotAlgorithm* algo){
    this->algo = algo;
}

void BotDriver:: processMove(int col, int row)  {
    auto eventdispatcher = ax::Director::getInstance()->getEventDispatcher();
 
    if (finished || row >=6 || turn!=playerturn){
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
   
    
    
    
    
    turn = (turn+1)%2;
   
    eventdispatcher->dispatchCustomEvent("switchTurn", &turn);
    
//    int nextcol =  algo->getBestMove(gameboard);
//    row = (int)gameboard[nextcol].size();
//    gameboard[nextcol].push_back(turn);
//    
//
//    Data =  {turn,nextcol,row};
    
//    eventdispatcher->dispatchCustomEvent("placeToken", &Data);
//    v = GameLogic::didwin(gameboard, nextcol, row);
//    if (v[0]){
//        finished = true;
//        releaseWinEvents(v, nextcol, row);
//        eventdispatcher->dispatchCustomEvent("gameFinished");
//    
//    }
    AsyncTaskPool::getInstance()->enqueue(
        AsyncTaskPool::TaskType::TASK_OTHER,
       
        [this,eventdispatcher](void* param) {
//            auto self = static_cast<BotDriver*>(param);
//            self->turn = !self->turn;
            int nextcol =  algo->getBestMove(gameboard);
            int row = (int)gameboard[nextcol].size();
            gameboard[nextcol].push_back(turn);
            

            std::vector<int> Data =  {turn,nextcol,row};
            eventdispatcher->dispatchCustomEvent("placeToken", &Data);
            std::vector<int> v = GameLogic::didwin(gameboard, nextcol, row);
            if (v[0]){
                finished = true;
                releaseWinEvents(v, nextcol, row);
                eventdispatcher->dispatchCustomEvent("gameFinished");
            
            }
            turn = (turn+1)%2;
            eventdispatcher->dispatchCustomEvent("switchTurn", &turn);
        },
        this,
        
        []() {
            std::this_thread::sleep_for(std::chrono::seconds(3));
            // simulate delay / heavy task
        }
    );


//    turn = (turn+1)%2;
//    eventdispatcher->dispatchCustomEvent("switchTurn", &turn);
    
    
    
    
}
