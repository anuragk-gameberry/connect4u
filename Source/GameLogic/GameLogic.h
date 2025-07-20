//
//  GameLogic.h
//  testproj
//
//  Created by Anurag Khugshal on 13/07/25.
//

//
//  WinLogic.cpp
//  testproj
//
//  Created by Anurag Khugshal on 13/07/25.
//

#ifndef __GAME_LOGIC_H__
#define __GAME_LOGIC_H__

#include <vector>

class GameLogic {
public:
    // Check if the player has won after placing at (i, j)
    static std::vector<int> didwin( std::vector<std::vector<int>>& gameboard, int i, int j);
};

#endif // __GAME_LOGIC_H__


