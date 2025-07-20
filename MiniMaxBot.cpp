//
//  MiniMaxBot.cpp
//  testproj
//
//  Created by Anurag Khugshal on 15/07/25.
//

#include "MiniMaxBot.h"
#include "GameLogic/GameLogic.h"
#include <vector>
using namespace std;
const int AI_PLAYER = 1;
const int HUMAN_PLAYER = 2;
const int MAX_DEPTH = 5;
const int INF = numeric_limits<int>::max();
typedef vector<vector<int>> Board;



bool checkWin(const Board& board, int player) {
    // Horizontal
    for (int r = 0; r < ROWS; ++r) {
        for (int c = 0; c < COLS - 3; ++c) {
            bool win = true;
            for (int i = 0; i < 4; ++i) {
                if (board[c + i].size() <= r || board[c + i][r] != player)
                    win = false;
            }
            if (win) return true;
        }
    }

    // Vertical
    for (int c = 0; c < COLS; ++c) {
        if (board[c].size() >= 4) {
            for (int r = 0; r <= board[c].size() - 4; ++r) {
                if (board[c][r] == player && board[c][r+1] == player &&
                    board[c][r+2] == player && board[c][r+3] == player)
                    return true;
            }
        }
    }

    // Positive Diagonal (/)
    for (int c = 0; c < COLS - 3; ++c) {
        for (int r = 0; r < ROWS - 3; ++r) {
            bool win = true;
            for (int i = 0; i < 4; ++i) {
                if (board[c + i].size() <= r + i || board[c + i][r + i] != player)
                    win = false;
            }
            if (win) return true;
        }
    }

    // Negative Diagonal (\)
    for (int c = 0; c < COLS - 3; ++c) {
        for (int r = 3; r < ROWS; ++r) {
            bool win = true;
            for (int i = 0; i < 4; ++i) {
                if (board[c + i].size() <= r - i || board[c + i][r - i] != player)
                    win = false;
            }
            if (win) return true;
        }
    }

    return false;
}


vector<int> getValidMoves(const Board& board) {
    vector<int> validCols;
    for (int col = 0; col < COLS; ++col) {
        if (board[col].size() < ROWS)
            validCols.push_back(col);
    }
    return validCols;
}


int scoreWindow( vector<int>& window, int player) {
    int score = 0;
    int opp = (player == 0) ? 0 : 1;
    int p = (int)count(window.begin(), window.end(), player);
    int o = (int)count(window.begin(), window.end(), opp);
    int e = (int)count(window.begin(), window.end(), 0);

    if (p == 4) score += 100;
    else if (p == 3 && e == 1) score += 10;
    else if (p == 2 && e == 2) score += 4;
    if (o == 3 && e == 1) score -= 80;

    return score;
}

int evaluateBoard(vector<vector<int>> &board, int player) {
    int score = 0;

    // Center bonus
    int center = COLS / 2;
    int centerCount = 0;
    for (int r = 0; r < board[center].size(); ++r)
        if (board[center][r] == player) centerCount++;
    score += centerCount * 3;

    // Horizontal
    for (int r = 0; r < ROWS; ++r) {
        for (int c = 0; c < COLS - 3; ++c) {
            vector<int> window;
            for (int i = 0; i < 4; ++i)
                window.push_back((board[c + i].size() > r) ? board[c + i][r] : 0);
            score += scoreWindow(window, player);
        }
    }

    // Vertical
    for (int c = 0; c < COLS; ++c) {
        for (int r = 0; r < board[c].size() - 3; ++r) {
            vector<int> window = {
                board[c][r], board[c][r + 1],
                board[c][r + 2], board[c][r + 3]
            };
            score += scoreWindow(window, player);
        }
    }

    // Positive Diagonal
    for (int c = 0; c < COLS - 3; ++c) {
        for (int r = 0; r < ROWS - 3; ++r) {
            vector<int> window;
            for (int i = 0; i < 4; ++i)
                window.push_back((board[c + i].size() > r + i) ? board[c + i][r + i] : 0);
            score += scoreWindow(window, player);
        }
    }

    // Negative Diagonal
    for (int c = 0; c < COLS - 3; ++c) {
        for (int r = 3; r < ROWS; ++r) {
            vector<int> window;
            for (int i = 0; i < 4; ++i)
                window.push_back((board[c + i].size() > r - i) ? board[c + i][r - i] : 0);
            score += scoreWindow(window, player);
        }
    }

    return score;
}


int minimax(Board board, int depth, int alpha, int beta, bool maximizingPlayer) {
    if (checkWin(board, AI_PLAYER)) return 1000000;
    if (checkWin(board, HUMAN_PLAYER)) return -1000000;
    if (depth == 0 || getValidMoves(board).empty()) return evaluateBoard(board, AI_PLAYER);

    if (maximizingPlayer) {
        int maxEval = -INF;
        for (int col : getValidMoves(board)) {
            Board tempBoard = board;
            tempBoard[col].push_back(AI_PLAYER);
            int eval = minimax(tempBoard, depth - 1, alpha, beta, false);
            maxEval = max(maxEval, eval);
            alpha = max(alpha, eval);
            if (beta <= alpha) break;
        }
        return maxEval;
    } else {
        int minEval = INF;
        for (int col : getValidMoves(board)) {
            Board tempBoard = board;
            tempBoard[col].push_back(HUMAN_PLAYER);
            int eval = minimax(tempBoard, depth - 1, alpha, beta, true);
            minEval = min(minEval, eval);
            beta = min(beta, eval);
            if (beta <= alpha) break;
        }
        return minEval;
    }
}
int getBestMove(Board board) {
    int bestScore = -INF;
    int bestCol = 0;
    for (int col : getValidMoves(board)) {
        Board temp = board;
        temp[col].push_back(AI_PLAYER);
        int score = minimax(temp, MAX_DEPTH, -INF, INF, false);
        if (score > bestScore) {
            bestScore = score;
            bestCol = col;
        }
    }
    return bestCol;
}

