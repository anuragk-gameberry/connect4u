//
//  JsonHanfder.cpp
//  testproj
//
//  Created by Anurag Khugshal on 22/07/25.
//
#include "JsonHandler.h"
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include <iostream>
#include "axmol.h"

using namespace rapidjson;



std::string JsonHandler::getJson (std:: string action,  std:: string playerid, int col ){
    Document d;
    d.SetObject();
    const char* p = playerid.c_str();
    Document::AllocatorType& allocator = d.GetAllocator();
    d.AddMember("Action", Value(action.c_str(), allocator) ,allocator);
    d.AddMember("PlayerId", "Anurag", allocator);
    d.AddMember("Col", col,allocator);
    

    // Serialize to string
    StringBuffer buffer;
    Writer<StringBuffer> writer(buffer);
    d.Accept(writer);

    return buffer.GetString();
}


void JsonHandler:: parseJson( std::string& jsonStr) {
    Document d;
    d.Parse(jsonStr.c_str());

    if (d.HasParseError()) {
        std::cout << "JSON parse error\n";
        return;
    }

   if (!d.HasMember("type") || !d["type"].IsString()) {
       std::cout << "Missing or invalid Type field\n";
       return;
   }

   std::string type = d["type"].GetString();
   if (type != "Moves" && type!="Winner") {
       std::cerr << "Unhandled Type: " << type << "\n";
       return;
   }

   if (!d.HasMember("data") || !d["data"].IsObject()) {
       std::cerr << "Missing or invalid Data object\n";
       return;
   }
    auto eventdispatcher = ax::Director::getInstance()->getEventDispatcher();
   const Value& data = d["data"];
   if (data.HasMember("Moves") && data["Moves"].IsArray()) {
       const Value& movesArray = data["Moves"];
       std::vector<std::pair<int, int>> moves;

       for (SizeType i = 0; i < movesArray.Size(); ++i) {
           const Value& move = movesArray[i];
           if (move.HasMember("Turn") && move["Turn"].IsInt() &&
               move.HasMember("Col") && move["Col"].IsInt()) {
               int turn = move["Turn"].GetInt();
               int col = move["Col"].GetInt();
               moves.emplace_back(turn, col);
           } else {
               std::cerr << "Invalid move at index " << i << "\n";
           }
       }
       for (const auto& [turn, col] : moves) {
           std::vector <int> Data =  {turn,col};
           
           
           eventdispatcher->dispatchCustomEvent("placeToken", &Data);
       }
   }

   

   // Print extracted moves
   
    
       
   if (!data.HasMember("Winningpoints") || !data["Winningpoints"].IsArray()) {
       std::cerr << "No Winner yet\n";
       return;
   }
    const Value& winningArray = data["Winningpoints"];
    for (SizeType i = 0; i < winningArray.Size(); i++) {
            const Value& point = winningArray[i];

            if (!point.HasMember("Col") || !point.HasMember("Row")) {
                continue;
            }

            int col = point["Col"].GetInt();
            int row = point["Row"].GetInt();

        AXLOGD("col found for winner {} {}",col,row);
            std::pair<int,int> Data = {col, row};
            eventdispatcher->dispatchCustomEvent("coinGlow", &Data);
    }
   
   
       
    
}

