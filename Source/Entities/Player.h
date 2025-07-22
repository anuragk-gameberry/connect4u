//
//  Player.h
//  testproj
//
//  Created by Anurag Khugshal on 14/07/25.
//

#pragma once
#include <string>

class Player {
private:
    std::string name;
    int playerId;

public:
   
    Player(const std::string& name, int id) : name(name), playerId(id) {}

    std::string getName() const { return name; }
    int getId() const { return playerId; }

    void setName(const std::string& newName) { name = newName; }
    void setId(int id) { playerId = id; }
};

