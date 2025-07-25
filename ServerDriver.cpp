//
//  ServerDriver.cpp
//  testproj
//
//  Created by Anurag Khugshal on 24/07/25.
//

#include "ServerDriver.h"
#include "../JsonHandler.h"


void ServerDriver::  processMove(int col, int row){
   
    std::string move =   JsonHandler::getJson("move", p->playerId,col );
    this->wsm->sendMessage(move);
}

ServerDriver :: ServerDriver () {
    this->wsm = new WebSocketManager();
    this->wsm->connect("ws://localhost:8080/ws");
    this->p = new Player("anurag", "anurag", 0);
    
    std::string init =   JsonHandler::getJson("init", p->playerId, 0);
    this->wsm->sendMessage(init);
    
    std::string start =   JsonHandler::getJson("startBot", p->playerId, 0);
    this->wsm->sendMessage(start);
    
}
