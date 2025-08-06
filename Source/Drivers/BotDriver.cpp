//
//  BotDriver.cpp
//  testproj
//
//  Created by Anurag Khugshal on 17/07/25.
//
#include "Drivers/BotDriver.h"
#include "axmol.h"
#include "BotAlgorithms/MiniMaxBot.h"
#include <AsyncTaskPool.h>
using namespace ax;


BotDriver::BotDriver(BotAlgorithm* algo, int cols, int rows)
: GameDriver(cols, rows), algo(algo){
    
    this->algo = algo;
}

void BotDriver:: processMove(int col, int row)  {
    auto eventdispatcher = ax::Director::getInstance()->getEventDispatcher();
 
    if (finished || row >=rows || turn!=playerturn){
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

    AsyncTaskPool::getInstance()->enqueue(
        AsyncTaskPool::TaskType::TASK_OTHER,
       
        [this,eventdispatcher](void* param) {
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
            std::this_thread::sleep_for(std::chrono::seconds(1));
          
        }
    );



    
    
    
    
}

void BotDriver::rematch(){
    this-> gameboard = std::vector<std::vector<int>> (7);
    this->turn = this->playerturn;
    auto eventdispatcher = ax::Director::getInstance()->getEventDispatcher();
    eventdispatcher->dispatchCustomEvent("rematch");
   
    eventdispatcher->dispatchCustomEvent("switchTurn", &this->playerturn);
    
}
