//
// MiniMaxBot.h
// testproj
//
// Created by Anurag Khugshal on 15/07/25.
//

#ifndef MINIMAXBOT_H
#define MINIMAXBOT_H

#include <vector>

using std::vector;

const int ROWS = 6;
const int COLS = 7;

typedef vector<vector<int>> Board;

bool checkWin(const Board& board, int player);

vector<int> getValidMoves(const Board& board);

int scoreWindow(vector<int>& window, int player);

int evaluateBoard(vector<vector<int>>& board, int player);

int minimax(Board board, int depth, int alpha, int beta, bool maximizingPlayer);

int getBestMove(Board board);

#endif // MINIMAXBOT_H
