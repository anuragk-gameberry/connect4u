//
//  ServerDriver.cpp
//  testproj
//
//  Created by Anurag Khugshal on 24/07/25.
//

#include "ServerDriver.h"
#include "Utils/JsonHandler.h"
#include <chrono>
#include <ctime>
#include <sstream>
#include <iomanip>
#include <axmol.h>



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


ServerDriver :: ServerDriver (bool isbot, Player *p, int cols, int rows) :GameDriver(cols,rows) {
    this->isBotGame = isbot;
    this->p = p;
    this->wsm = new WebSocketManager();

    this->wsm->onMessageReceived = [this](std::string& msg) {
        this->handleMessages(msg);
    };

    this->wsm->initialize = [this]() {
        std::string init = JsonHandler::getJson("init", this->p->playerId, 0);
        wsm->sendMessage(init);
        this->startGame();
       
        AXLOG("Sent init/startQueue/startBot");
    };
    
    
    
    
     this->wsm->connect("ws://localhost:8081/ws");

   
    
    
    
}
void ServerDriver::startGame(){
    std::string startQueue = JsonHandler::getJson("startQueue", this->p->playerId, 0);
    std::string startBot = JsonHandler::getJson("startBot", this->p->playerId, 0);

   
    if (this->isBotGame) {
        wsm->sendMessage(startBot);
    }
    else {
        wsm->sendMessage(startQueue);
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

}


ServerDriver:: ~ServerDriver() {
    AXLOG("*************ServerDriver destroyed*****************");
}
