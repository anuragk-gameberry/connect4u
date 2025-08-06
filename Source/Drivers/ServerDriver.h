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
    ServerDriver (bool isbot, Player *p, int cols, int rows);
    void handleMessages (std::string msg);
    void rematch () override;
    ~ServerDriver();
    void stats () override;
    void startGame();
    
    
    
     
protected:
    
    WebSocketManager* wsm;
  
  
    bool GameStarted;
    
};




