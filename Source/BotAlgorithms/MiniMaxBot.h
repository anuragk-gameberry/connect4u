//
// MiniMaxBot.h
// testproj
//
// Created by Anurag Khugshal on 15/07/25.
//

#ifndef MINIMAXBOT_H
#define MINIMAXBOT_H

#include <vector>
#include "BotAlgorithm.h"
using std::vector;


class MiniMax: public BotAlgorithm {
    
public:
    
   
    
    MiniMax(int rows, int cols);
   
    bool checkWin(const Board& board, int player);
    vector<int> getValidMoves(const Board& board);
    int scoreWindow(vector<int>& window, int player);
    int evaluateBoard(vector<vector<int>>& board, int player);
    int minimax(Board board, int depth, int alpha, int beta, bool maximizingPlayer);
    int  getBestMove(Board board) override;
    
private:
    const int AI_PLAYER;
    const int HUMAN_PLAYER ;
    const int EMPTY_SLOT ;
    const int MAX_DEPTH;
    const int INF ;
    const int ROWS ;
    const int COLS ;
    
};
#endif // MINIMAXBOT_H
