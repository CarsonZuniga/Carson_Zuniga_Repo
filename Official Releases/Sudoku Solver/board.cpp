#include "board.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cmath>
using std::stringstream;
using std::ifstream;
using std::cout;
using std::endl;

board::board(vector<vector<int>> inputBoard) {
	gameBoard = inputBoard;
    width = gameBoard[0].size();
    height = gameBoard.size();
    if(width != 9 || height != 9) {
        cout << "Invalid board dimensions (" << width << " x " << height << "). Try using (3x3)." << endl;
        exit(EXIT_FAILURE);
    }
}

board::board(string fileName) {
    vector<vector<int>> temp(9, vector<int> (9, 0));
    gameBoard = temp;

    ifstream my_file;
    my_file.open(fileName);
    if(!my_file){
        cout << "Could Not Open File: " << fileName << endl;
        exit(EXIT_FAILURE);
    }

    string line;
    int num_rows = 0;
    while(getline(my_file, line) && num_rows < 9){
        int num_cols = 0;
        stringstream s_stream(line);
        while(s_stream.good() && num_cols < 9){
            string substring;
            // parse data by comma
            getline(s_stream, substring, ',');
            substring.erase(remove(substring.begin(), substring.end(), ' '), substring.end());
            //cout << ":" << substring << ":" << endl;
            gameBoard[num_rows][num_cols] = stoi(substring);
            num_cols++;
        }
        num_rows++;
    }
    my_file.close();
    width = gameBoard[0].size();
    height = gameBoard.size();
}

void board::printBoard() {
    for(int i = 0; i < height; i++) {
        if(i % 3 == 0){
            for(int x = 0; x < width-1; x++)
                cout << "---";
            cout << endl;
        }
        for(int j = 0; j < width; j++) {
            if(j % 3 == 0)
                cout << "| ";
            cout << gameBoard[i][j] << " ";
            if(j == width - 1)
                cout << "|";
        }
        cout << endl;
    }
    for(int x = 0; x < width-1; x++)
        cout << "---";
    cout << endl;
}

void board::solveBoard() {
    if(solveBoard(0, 0))
        cout << "Found solution!" << endl;
    else
        cout << "Could not find solution." << endl;
}

bool board::solveBoard(int row, int col) {
    if(row == width - 1 && col == height)
        return true;
    if(col == height) {
        row++;
        col = 0;
    }
    if(gameBoard[row][col] != 0)
        return solveBoard(row, col + 1);

    for (int num = 1; num <= 9; num++) {
        if(canPlace(num, row, col)) {
            gameBoard[row][col] = num;
            if(solveBoard(row, col + 1))
                return true;
        }
        gameBoard[row][col] = 0;
    }
    return false;
}

bool board::inCol(int num, int col) {
    for(int i = 0; i < height; i++) {
        if(gameBoard[i][col] == num) {
            return true;
        }
    }
    return false;
}

bool board::inRow(int num, int row) {
    for(int i = 0; i < width; i++) {
        if(gameBoard[row][i] == num) {
            return true;
        }
    }
    return false;
}

bool board::inSquare(int num, int row, int col) {
    int startingRow = 3 * (row / 3);
    int startingCol = 3 * (col / 3);
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            if(gameBoard[startingRow + i][startingCol + j] == num) {
                return true;
            }
        }
    }
    return false;
}

bool board::canPlace(int num, int row, int col) {
    if(inCol(num, col) || inRow(num, row) || inSquare(num, row, col))
        return false;
    return true;
}