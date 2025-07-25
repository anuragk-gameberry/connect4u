//
//  ServerDriver.h
//  testproj
//
//  Created by Anurag Khugshal on 24/07/25.
//


#include "GameDriver.h"
#include "WebSocketManager.h"
#include "../Entities/Player.h"

#pragma once

class ServerDriver: public GameDriver {
public:
    void processMove (int col, int row) override;
    ServerDriver();
     
protected:
    WebSocketManager* wsm;
    Player* p;
    
};




