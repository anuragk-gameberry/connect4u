//
//  GameDriver.cpp
//  testproj
//
//  Created by Anurag Khugshal on 15/07/25.
//
#include "GameDriver.h"
#include "axmol.h"
#include <vector>

GameDriver:: GameDriver(){
    this-> gameboard = std::vector<std::vector<int>> (7);
    this->finished = false;
    this->turn = true;
}

GameDriver:: ~GameDriver(){
    
}

void GameDriver:: processMove(int col, int row){
    if (row >=6){
        return;
    }
    this->gameboard[col].push_back(turn);
    
    turn = !turn;
    
    auto v = GameLogic::didwin(gameboard, col, row);
    auto eventdispatcher = ax::Director::getInstance()->getEventDispatcher();
    std::vector <int> Data =  {turn,col,row};
    
    eventdispatcher->dispatchCustomEvent("placeToken", &Data);
    if (v[0]){
        releaseWinEvents(v, col, row);
    }
}



void GameDriver:: releaseWinEvents(std::vector <int> check, int col, int row) {
    auto eventdispatcher = ax::Director::getInstance()->getEventDispatcher();
    
    if (check [0] == 1){
        
        for (int x = check[1]; x<=check[2]; x++){
            std::pair <int,int> data =  {x,row};
            eventdispatcher->dispatchCustomEvent("coinGlow", &data);
        }
        
    }
    else if (check[0] == 2){
        for (int x = check[1]; x<=check[2]; x++){
            std::pair <int,int> data =  {col,x};
            eventdispatcher->dispatchCustomEvent("coinGlow", &data);
        }
    }
    
    else if (check[0] == 3){
        
        int c1 = check[1], c2 = check[2];
        int startRow = row - (col - c1);
        for (int x = c1; x<=c2; x++){
            std::pair <int,int> data =  {x,startRow};
            eventdispatcher->dispatchCustomEvent("coinGlow", &data);
            startRow++;
        }
    }
    else {
        int c1 = check[1], c2 = check[2];
        int startRow = row + (col - c1);
        for (int x = c1; x<=c2; x++){
            std::pair <int,int> data =  {x,startRow};
            startRow--;
            eventdispatcher->dispatchCustomEvent("coinGlow", &data);
        }
    }
}




