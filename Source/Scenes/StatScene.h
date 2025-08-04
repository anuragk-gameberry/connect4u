//
//  StatScene.h
//  testproj
//
//  Created by Anurag Khugshal on 31/07/25.
//


#pragma once
#include <vector>
#include <axmol.h>
#include "Entities/Stat.h"

class StatScene : public ax::Scene {
public:
    bool init () override;
    std:: vector <Stat*> stats ;
    bool  initiateStats();
    CREATE_FUNC(StatScene);
};
