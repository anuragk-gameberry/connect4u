//
//  GameDriver.cpp
//  testproj
//
//  Created by Anurag Khugshal on 15/07/25.
//
#include "Drivers/GameDriver.h"
#include "axmol.h"
#include <vector>


GameDriver:: GameDriver(int cols, int rows){
    this->cols =cols;
    this->rows = rows;
    this->gameboard = std::vector<std::vector<int>> (cols);
    this->finished = false;
    this->turn = 0;
  
}

GameDriver:: ~GameDriver(){
    AXLOG("***GamerDriver*** deleted"); 
}

void GameDriver::  rematch () {
    this-> gameboard = std::vector<std::vector<int>> (7);
    this->turn = 0;
    auto eventdispatcher = ax::Director::getInstance()->getEventDispatcher();
    eventdispatcher->dispatchCustomEvent("rematch");
    
}


void GameDriver:: processMove(int col, int row){
    if (row >= rows || finished){
        AXLOG("invalid row ");
        return;
    }
    this->gameboard[col].push_back(turn);
    
   
    
    auto v = GameLogic::didwin(gameboard, col, row);
    auto eventdispatcher = ax::Director::getInstance()->getEventDispatcher();
    std::vector <int> Data =  {turn,col,row};
    
    
    eventdispatcher->dispatchCustomEvent("placeToken", &Data);
    
    
 
    
    if (v[0]){
        releaseWinEvents(v, col, row);
        finished = true;
        eventdispatcher->dispatchCustomEvent("gameFinished");

    }
    turn = !turn;
    eventdispatcher->dispatchCustomEvent("switchTurn", &turn);
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
//
void GameDriver::stats(){
   
}




