//
//  ServerDriver.cpp
//  testproj
//
//  Created by Anurag Khugshal on 24/07/25.
//

#include "../ServerDriver.h"
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
        std::vector <int> data = {m.start,m.turn};
        eventdispatcher->dispatchCustomEvent("startMatch", &data);
        if (m.start != m.turn){
            eventdispatcher->dispatchCustomEvent("switchTurn", &m.start);
        }
        
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
        std::string myturn = "";
        eventdispatcher->dispatchCustomEvent("switchTurn", &start);
        if (m.turn != m.start){
            eventdispatcher->dispatchCustomEvent("switchPlayerName", &myturn);
        }
        else{
            myturn = "Your Turn";
            eventdispatcher->dispatchCustomEvent("switchPlayerName", &myturn);
        }
       
        
    }
    
    if (m.type == "gameStats"){
       
       
            
            eventdispatcher->dispatchCustomEvent("stats", &m.stats);
            
        
       
        
    }
}


ServerDriver :: ServerDriver (bool isbot, Player *p) {
    this->isBotGame = isbot;
    this->p = p;
    this->wsm = new WebSocketManager();
//    AXLOG("reached here1");
    this->wsm->onMessageReceived = [this](std::string& msg) {
        this->handleMessages(msg);
    };
//    AXLOG("reached here2");
    std:: string id =  getCurrentTimestamp();
   
//    AXLOG("reached here6");
//    this->p = new Player(p->playerId, p->playerId, 0);
//    AXLOG("reached here7");
    
    
    
    
    this->wsm->initialize = [this]() {
            std::string init = JsonHandler::getJson("init", this->p->playerId, 0);
            wsm->sendMessage(init);

            std::string startQueue = JsonHandler::getJson("startQueue", this->p->playerId, 0);
            std::string startBot = JsonHandler::getJson("startBot", this->p->playerId, 0);

           
            if (this->isBotGame) {
                wsm->sendMessage(startBot);
            }
            else {
                wsm->sendMessage(startQueue);
            }

            AXLOG("Sent init/startQueue/startBot");
        };
    
    
    
    
    
    
    
    
    
    
    
//    std::string init =   JsonHandler::getJson("init", p->playerId, 0);
//    this->wsm->sendMessage(init);
     this->wsm->connect("ws://localhost:8081/ws");
    AXLOG("reached here8");
   
//    std::string start =   JsonHandler::getJson("startBot", p->playerId, 0);
    std::string startQueue =   JsonHandler::getJson("startQueue", p->playerId, 0);
    std::string startBot =   JsonHandler::getJson("startBot", p->playerId, 0);
    
    if (this->isBotGame){
//        this->wsm->sendMessage(startBot);
        AXLOG("startbot...");
    }
    else {
//        this->wsm->sendMessage(startQueue);
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

void ServerDriver::stats()
{
    AXLOG("stats request sending..");
    std::string statmsg = JsonHandler::getJson("stats", this->p->playerId, 0);
    this->wsm->sendMessage(statmsg);
    auto ed = ax::Director::getInstance()->getEventDispatcher();
//    ed->dispatchCustomEvent("stats");
    
    
}
ServerDriver:: ~ServerDriver() {
    AXLOG("*************ServerDriver destroyed*****************");
}
