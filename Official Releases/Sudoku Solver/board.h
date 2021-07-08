#pragma once

#include <vector>
#include <string>

using std::vector;
using std::string;

class board {
    private:
		  vector<vector<int>> gameBoard;  // vector of rows gameBoard[0][3] refers to the 4th col in the top row
      int width;
      int height;
    public:
		  board(vector<vector<int>> inputBoard);
      board(string fileName);
      void printBoard();

      void solveBoard();
      bool solveBoard(int row, int col);
      bool inCol(int num, int col);
      bool inRow(int num, int row);
      bool inSquare(int num, int row, int col);
      bool canPlace(int num, int row, int col);
};