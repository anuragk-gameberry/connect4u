//
//  ServerDriver.h
//  testproj
//
//  Created by Anurag Khugshal on 24/07/25.
//


#include "GameDriver.h"
#include "../Utils/WebSocketManager.h"
#include "../Entities/Player.h"
#include "../Message.h"

#pragma once

class ServerDriver: public GameDriver {
public:
    void processMove (int col, int row) override;
    ServerDriver (bool isbot, Player *p);
    void handleMessages (std::string msg);
    bool isBotGame;
    void rematch () override;
    ~ServerDriver();
    void stats () override;
    int currentPlayerTurn;
    
     
protected:
    
    WebSocketManager* wsm;
  
  
    bool GameStarted;
    
};




