#include "board.h"
#include <iostream>
using std::cout;
using std::endl;

int main() {

    string inputFile = "exampleBoard.txt";

    vector<vector<int>> exampleBoard = {
    {3, 0, 6, 5, 0, 8, 4, 0, 0},
    {5, 2, 0, 0, 0, 0, 0, 0, 0},
    {0, 8, 7, 0, 0, 0, 0, 3, 1},
    {0, 0, 3, 0, 1, 0, 0, 8, 0},
    {9, 0, 0, 8, 6, 3, 0, 0, 5},
    {0, 5, 0, 0, 9, 0, 6, 0, 0},
    {1, 3, 0, 0, 0, 0, 2, 5, 0},
    {0, 0, 0, 0, 0, 0, 0, 7, 4},
    {0, 0, 5, 2, 0, 6, 3, 0, 0}};
    cout << "Solving example board..." << endl;
    board myBoard(exampleBoard);
    myBoard.solveBoard();
    myBoard.printBoard();

    cout << "Solving board from file: " << inputFile << endl;
    board textBoard(inputFile);
    textBoard.solveBoard();
    textBoard.printBoard();

    return 0;
}