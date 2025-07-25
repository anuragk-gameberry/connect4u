//
//  player.cpp
//  testproj
//
//  Created by Anurag Khugshal on 24/07/25.
//

#include "../Entities/Player.h"

// Constructor
Player::Player( std::string name, std::string playerId, int turn)
    : name(name), playerId(playerId), turn(turn) {}

// Getters
std::string Player::getName() const {
    return name;
}

std::string Player::getPlayerId() const {
    return playerId;
}

int Player::getTurn() const {
    return turn;
}

// Setters
void Player::setName(const std::string& newName) {
    name = newName;
}

void Player::setPlayerId(int newPlayerId) {
    playerId = newPlayerId;
}

void Player::setTurn(int newTurn) {
    turn = newTurn;
}
