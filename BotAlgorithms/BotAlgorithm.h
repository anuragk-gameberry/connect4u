//
//  BotAlgorithm.h
//  testproj
//
//  Created by Anurag Khugshal on 20/07/25.
//

#pragma once
#include <vector>
typedef std::vector<std::vector<int>> Board;

class BotAlgorithm {
    virtual int getBestMove(Board board);
};
