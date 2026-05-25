#include "../../Utils/utils.h"

using namespace std;

class Solution {
private:
   bool rows[9][9];
   bool cols[9][9];
   bool boxes[9][9];

   bool solve(vector<vector<char>>& board, int r, int c) {
      if (r == 9) {
         return true;
      }
      if (c == 9) {
         return solve(board, r + 1, 0);
      }
      if (board[r][c] != '.') {
         return solve(board, r, c + 1);
      }
      
      int b = (r / 3) * 3 + (c / 3);
      for (int d = 1; d <= 9; ++d) {
         int val = d - 1;
         if (!rows[r][val] && !cols[c][val] && !boxes[b][val]) {
            board[r][c] = '0' + d;
            rows[r][val] = true;
            cols[c][val] = true;
            boxes[b][val] = true;
            
            if (solve(board, r, c + 1)) {
               return true;
            }
            
            board[r][c] = '.';
            rows[r][val] = false;
            cols[c][val] = false;
            boxes[b][val] = false;
         }
      }
      
      return false;
   }

public:
   void solveSudoku(vector<vector<char>>& board) {
      for (int r = 0; r < 9; ++r) {
         for (int val = 0; val < 9; ++val) {
            rows[r][val] = false;
            cols[r][val] = false;
            boxes[r][val] = false;
         }
      }
      
      for (int r = 0; r < 9; ++r) {
         for (int c = 0; c < 9; ++c) {
            if (board[r][c] != '.') {
               int val = board[r][c] - '1';
               int b = (r / 3) * 3 + (c / 3);
               rows[r][val] = true;
               cols[c][val] = true;
               boxes[b][val] = true;
            }
         }
      }
      
      solve(board, 0, 0);
   }
};

int main() {
   vector<vector<char>> board(9, vector<char>(9));
   for (int r = 0; r < 9; ++r) {
      for (int c = 0; c < 9; ++c) {
         if (!(cin >> board[r][c])) return 0;
      }
   }
   
   Solution sol;
   sol.solveSudoku(board);
   
   for (int r = 0; r < 9; ++r) {
      for (int c = 0; c < 9; ++c) {
         cout << board[r][c] << (c == 8 ? "" : " ");
      }
      cout << endl;
   }
   
   return 0;
}
