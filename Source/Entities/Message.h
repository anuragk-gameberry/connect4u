//
//  message.h
//  testproj
//
//  Created by Anurag Khugshal on 27/07/25.
//

#pragma once
#include <vector>
#include "Stat.h"
#include "axmol.h"
class Message {
public:
    std::string type;
    int turn;
    std:: vector<std::pair<int,int>> moves ;
    std:: vector<std::pair<int,int>> winningpoints ;
    std:: vector<Stat*> stats;
    int start;
    std:: string date;
     
    ~Message () {
        AXLOG("Message deleted");
    }
    
};
