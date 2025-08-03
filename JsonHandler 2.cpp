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
#include "../Message.h"


using namespace rapidjson;



std::string JsonHandler::getJson (std:: string action,  std:: string playerid, int col ){
    Document d;
    d.SetObject();
    Document::AllocatorType& allocator = d.GetAllocator();
    d.AddMember("Action", Value(action.c_str(), allocator) ,allocator);
    d.AddMember("PlayerId", Value(playerid.c_str(),allocator), allocator);
    d.AddMember("Col", col,allocator);
    

    // Serialize to string
    StringBuffer buffer;
    Writer<StringBuffer> writer(buffer);
    d.Accept(writer);

    return buffer.GetString();
}


Message JsonHandler:: parseJson( std::string& jsonStr) {
    Document d;
    d.Parse(jsonStr.c_str());
    Message m = Message();
//    return m;
    if (d.HasParseError()) {
        std::cout << "JSON parse error\n";
        return m ;
    }

   if (!d.HasMember("type") || !d["type"].IsString()) {
       std::cout << "Missing or invalid Type field\n";
       return m;
   }

   std::string type = d["type"].GetString();
   

   if (!d.HasMember("data") || !d["data"].IsObject()) {
       std::cerr << "Missing or invalid Data object\n";
       return m;
   }
    auto eventdispatcher = ax::Director::getInstance()->getEventDispatcher();
    const Value& data = d["data"];
    
    
   
    
    if ( type == "Start"  && data.HasMember("Turn")) {
        m.type = "start";
        m.start = data["Start"].GetInt();
        m.turn = data["Turn"].GetInt();
        return m;
    }
    if ( type == "RematchStart" && data.HasMember("Turn")) {
        m.type = "RematchStart";
        m.start = data["Start"].GetInt();
        m.turn = data["Turn"].GetInt();
        return m;
    }
    
   
    
   if (data.HasMember("Moves") && data["Moves"].IsArray()) {
       const Value& movesArray = data["Moves"];
       m.type = "Moves";
      

       for (SizeType i = 0; i < movesArray.Size(); ++i) {
           const Value& move = movesArray[i];
           if (move.HasMember("Turn") && move["Turn"].IsInt() &&
               move.HasMember("Col") && move["Col"].IsInt()) {
               int turn = move["Turn"].GetInt();
               int col = move["Col"].GetInt();
               m.moves.emplace_back(turn, col);
           } else {
               std::cerr << "Invalid move at index " << i << "\n";
           }
       }
      
   }

       
   if (data.HasMember("Winningpoints") && data["Winningpoints"].IsArray()) {
       std::cerr << "No Winner yet\n";
       const Value& winningArray = data["Winningpoints"];
       for (SizeType i = 0; i < winningArray.Size(); i++) {
               const Value& point = winningArray[i];
               if (!point.HasMember("Col") || !point.HasMember("Row")) {
                   continue;
               }
               int col = point["Col"].GetInt();
               int row = point["Row"].GetInt();
               std::pair<int,int> Data = {col, row};
               m.winningpoints.emplace_back(Data);
   //            eventdispatcher->dispatchCustomEvent("coinGlow", &Data);
       }
       return m;
   }
    
//    std::pair<int,int> Data;
    
    
   
    if (data.HasMember("gameStats") && data["gameStats"].IsArray()) {
        const Value& statsArray = data["gameStats"];

        for (SizeType i = 0; i < statsArray.Size(); ++i) {
            const Value& stat = statsArray[i];
            if (stat.HasMember("Winner") && stat["Winner"].IsString()) {
                Stat* s = new Stat();
                s->Winner = stat["Winner"].GetString();
//                s->Players =  std::vector<std::string>();
                m.stats.push_back(s);
            }
        }

        m.type = "gameStats";
    }
    return m;
   
   
       
    
}

