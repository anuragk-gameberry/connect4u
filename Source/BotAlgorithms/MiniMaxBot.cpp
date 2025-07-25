#include "MiniMaxBot.h"
#include "GameLogic/GameLogic.h"
#include <vector>
#include <limits>
#include <algorithm>

using namespace std;


MiniMax::MiniMax(int rows, int cols)
    : AI_PLAYER(1),
      HUMAN_PLAYER(0),
      EMPTY_SLOT(-1),
      MAX_DEPTH(3),
      INF(std::numeric_limits<int>::max()),
      ROWS(rows),
      COLS(cols) {}


bool MiniMax::checkWin(const Board& board, int player) {
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

vector<int> MiniMax::getValidMoves(const Board& board) {
    vector<int> validCols;
    for (int col = 0; col < COLS; ++col) {
        if (board[col].size() < ROWS)
            validCols.push_back(col);
    }
    return validCols;
}

int MiniMax::scoreWindow(vector<int>& window, int player) {
    int score = 0;
    int opp = (player == AI_PLAYER) ? HUMAN_PLAYER : AI_PLAYER;

    int p = count(window.begin(), window.end(), player);
    int o = count(window.begin(), window.end(), opp);
    int e = count(window.begin(), window.end(), EMPTY_SLOT);

    if (p == 4) score += 100;
    else if (p == 3 && e == 1) score += 10;
    else if (p == 2 && e == 2) score += 4;
    if (o == 3 && e == 1) score -= 80;

    return score;
}

int MiniMax::evaluateBoard(Board &board, int player) {
    int score = 0;

    // Center column bonus
    int center = COLS / 2;
    int centerCount = 0;
    for (int r = 0; r < board[center].size(); ++r)
        if (board[center][r] == player) centerCount++;
    score += centerCount * 3;  // Optionally tune weight

    // Horizontal (check rows by scanning across columns)
    for (int r = 0; r < ROWS; ++r) {
        for (int c = 0; c < COLS - 3; ++c) {
            vector<int> window;
            for (int i = 0; i < 4; ++i) {
                int val = (board[c + i].size() > r) ? board[c + i][r] : EMPTY_SLOT;
                window.push_back(val);
            }
            score += scoreWindow(window, player);
        }
    }

    // Vertical
    for (int c = 0; c < COLS; ++c) {
        for (int r = 0; r <= (int)board[c].size() - 4; ++r) {
            // Only access if we have 4 or more elements
            if (r + 3 < board[c].size()) {
                vector<int> window = {
                    board[c][r],
                    board[c][r + 1],
                    board[c][r + 2],
                    board[c][r + 3]
                };
                score += scoreWindow(window, player);
            }
        }
    }

    // Positive Diagonal (/)
    for (int c = 0; c < COLS - 3; ++c) {
        for (int r = 0; r < ROWS - 3; ++r) {
            vector<int> window;
            for (int i = 0; i < 4; ++i) {
                int col = c + i;
                int row = r + i;
                int val = (board[col].size() > row) ? board[col][row] : EMPTY_SLOT;
                window.push_back(val);
            }
            score += scoreWindow(window, player);
        }
    }

    // Negative Diagonal (\)
    for (int c = 0; c < COLS - 3; ++c) {
        for (int r = 3; r < ROWS; ++r) {
            vector<int> window;
            for (int i = 0; i < 4; ++i) {
                int col = c + i;
                int row = r - i;
                int val = (board[col].size() > row) ? board[col][row] : EMPTY_SLOT;
                window.push_back(val);
            }
            score += scoreWindow(window, player);
        }
    }

    return score;
}


int MiniMax::minimax(Board board, int depth, int alpha, int beta, bool maximizingPlayer) {
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

int MiniMax::getBestMove(Board board) {
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

