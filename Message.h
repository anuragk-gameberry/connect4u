//
//  message.h
//  testproj
//
//  Created by Anurag Khugshal on 27/07/25.
//

#pragma once
#include <vector>
class Message {
public:
    std::string type;
    int turn;
    std:: vector<std::pair<int,int>> moves ;
    std:: vector<std::pair<int,int>> winningpoints ;
    int start;
     
    
    
};
