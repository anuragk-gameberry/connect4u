//
//  Player.h
//  testproj
//
//  Created by Anurag Khugshal on 14/07/25.
//

#pragma once
#include <string>

class Player {
public:
    std::string name;
    std::string playerId;
    int turn;

    Player (string name, string playerId, int turn);
    
    std::string getName() const;
    int getPlayerId() const;
    int getTurn() const;
    
    void setName(const std::string& newName);
    void setPlayerId(std::string newPlayerId);
    void setTurn(int newTurn);
};

