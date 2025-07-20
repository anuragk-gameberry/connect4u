//
//  WinLogic.cpp
//  testproj
//
//  Created by Anurag Khugshal on 13/07/25.
//
#include <vector>
#include "GameLogic.h"
#include <iostream>

using namespace std;

    vector<int> GameLogic::didwin (vector <vector<int>> &gameboard, int col, int row){
        
        vector <int> ret(1);
        int currplayer = gameboard[col][row];
        
        //horizontal check
        int count = 0;
        int left= col, right =col;
        //move left
        while (left>=0 && gameboard[left].size()>row && gameboard[left][row] == currplayer){
            cout << left;
            left--;
        }
        while (right <gameboard.size() && gameboard[right].size()>row && gameboard[right][row] == currplayer){
            cout << right;
            right++;
        }
        if ( right-left-1 >3) {
            ret[0] = 1;
            
            ret.push_back(left+1);
            ret.push_back(right-1);
            return ret;
        }
       
        
        
        //vertical check
        int down = row, up = row;
       while (down >= 0  && gameboard[col][down] == currplayer)
           down--;
       while (up < gameboard[col].size() && gameboard[col][up] == currplayer)
           up++;

       if (up - down - 1 > 3) {
           ret[0] = 2;  // Win
           ret.push_back(down + 1);
           ret.push_back(up - 1);
           return ret;
       }
         
        int d1_left_col = col, d1_left_row = row;
        int d1_right_col = col, d1_right_row = row;
        while (d1_left_col >= 0 && d1_left_row >= 0 &&
               gameboard[d1_left_col].size() > d1_left_row &&
               gameboard[d1_left_col][d1_left_row] == currplayer) {
            d1_left_col--;
            d1_left_row--;
        }

           
        while (d1_right_col < gameboard.size() && gameboard[d1_right_col].size() > d1_right_row && gameboard[d1_right_col][d1_right_row] == currplayer) {
            d1_right_col++;
            d1_right_row++;
        }

        if (d1_right_col - d1_left_col - 1 > 3) {
            ret[0] = 3;
            ret.push_back(d1_left_col + 1);
            ret.push_back(d1_right_col - 1);
            
            return ret;
        }
    
        int d2_left_col = col, d2_left_row = row;
        int d2_right_col = col, d2_right_row = row;

        // move down-left (↙)
        while (d2_left_col >= 0 &&
               d2_left_row < gameboard[d2_left_col].size() &&
               gameboard[d2_left_col][d2_left_row] == currplayer) {
            d2_left_col--;
            d2_left_row++;
        }

        // move up-right (↗)
        while (d2_right_col < gameboard.size() && d2_right_row >= 0 && gameboard[d2_right_col].size() > d2_right_row && gameboard[d2_right_col][d2_right_row] == currplayer) {
            d2_right_col++;
            d2_right_row--;
        }

        if (d2_right_col - d2_left_col - 1 >= 4) {
            ret[0] = 4;  
            ret.push_back(d2_left_col + 1);
            ret.push_back(d2_right_col - 1);
            return ret;
        }
        
        

        return ret;
        
        
        
       
        
    }


