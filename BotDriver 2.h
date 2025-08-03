//
//  BotDriver.h
//  testproj
//
//  Created by Anurag Khugshal on 17/07/25.
//
#include "GameDriver.h"
#include "../BotAlgorithms/BotAlgorithm.h"
#pragma once

class BotDriver: public GameDriver {
public:
     void processMove (int col, int row) override;
     BotDriver (BotAlgorithm* algo);
     void rematch () override;
protected:
    BotAlgorithm* algo;
    int playerturn = 0;
};




