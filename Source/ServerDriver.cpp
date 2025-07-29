//
//  ServerDriver.cpp
//  testproj
//
//  Created by Anurag Khugshal on 24/07/25.
//

#include "ServerDriver.h"
#include "../JsonHandler.h"
#include <chrono>
#include <ctime>
#include <sstream>
#include <iomanip>
#include <axmol.h>

std::string getCurrentTimestamp() {
    // Get current time as time_t
    auto now = std::chrono::system_clock::now();
    std::time_t now_time = std::chrono::system_clock::to_time_t(now);

    // Format time to string
    std::stringstream ss;
    ss << std::put_time(std::localtime(&now_time), "%Y-%m-%d %H:%M:%S");
    return ss.str();
}
//void ServerDriver::stats() {
//    std::string statsmsg =   JsonHandler::getJson("stats", p->playerId,0 );
//    this->wsm->sendMessage(statsmsg);
//}
void ServerDriver::  processMove(int col, int row){
   
    std::string move =   JsonHandler::getJson("move", p->playerId,col );
    this->wsm->sendMessage(move);
}

void ServerDriver::handleMessages (std::string msg){
    Message m = JsonHandler::parseJson(msg);
    auto eventdispatcher = ax::Director::getInstance()->getEventDispatcher();
    if (m.type == "start"){
        AXLOG("GameStart");
        std::vector <int> data = {m.start};
        eventdispatcher->dispatchCustomEvent("startMatch", &data);
        
    }
    
    for (const auto& [turn, col] : m.moves) {
        std::vector <int> Data =  {turn,col};
        int turndata = !turn;
        eventdispatcher->dispatchCustomEvent("placeToken", &Data);
        eventdispatcher->dispatchCustomEvent("switchTurn", &turndata);
    }
    
    for (const auto& [turn, col] : m.winningpoints) {
        std::pair <int,int> Data =  {turn,col};
        eventdispatcher->dispatchCustomEvent("coinGlow", &Data);
    }
    if (m.winningpoints.size() > 0){
        eventdispatcher->dispatchCustomEvent("gameFinished");
    }
    
    if (m.type == "RematchStart"){
        this->turn = m.turn;
        int start = m.start;
        eventdispatcher->dispatchCustomEvent("switchTurn", &start);
        
    }
}


ServerDriver :: ServerDriver (bool isbot) {
    this->isBotGame = isbot;
    this->wsm = new WebSocketManager();
    AXLOG("reached here1");
    this->wsm->onMessageReceived = [this](std::string& msg) {
        this->handleMessages(msg);
    };
    AXLOG("reached here2");
    std:: string id =  getCurrentTimestamp();
    this->wsm->connect("ws://localhost:8081/ws");
    AXLOG("reached here6");
    this->p = new Player(id, id, 0);
    AXLOG("reached here7");
    
    
    std::string init =   JsonHandler::getJson("init", p->playerId, 0);
    this->wsm->sendMessage(init);
    
    AXLOG("reached here8");
   
//    std::string start =   JsonHandler::getJson("startBot", p->playerId, 0);
    std::string startQueue =   JsonHandler::getJson("startQueue", p->playerId, 0);
    std::string startBot =   JsonHandler::getJson("startBot", p->playerId, 0);
    
    if (this->isBotGame){
        this->wsm->sendMessage(startBot);
        AXLOG("startbot...");
    }
    else {
        this->wsm->sendMessage(startQueue);
        AXLOG("startQueue...");

    }
    
    
    
}

void ServerDriver:: rematch () {
    this-> gameboard = std::vector<std::vector<int>> (7);
    this->turn = true;
    auto eventdispatcher = ax::Director::getInstance()->getEventDispatcher();
    eventdispatcher->dispatchCustomEvent("rematch");
    std::string rematch =   JsonHandler::getJson("rematch", p->playerId, 0);
    this->wsm->sendMessage(rematch);
    
}

