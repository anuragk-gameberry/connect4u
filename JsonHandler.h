//
//  Json.h
//  testproj
//
//  Created by Anurag Khugshal on 22/07/25.
//
#pragma once
#include <string>

class JsonHandler {
public:
    static std::string getJson (std:: string action,  std:: string playerid, int col = 0);
    static void parseJson( std::string& jsonStr);
};
    
