//
//  board.swift
//  Minesweeper iOS
//
//  Created by Carson Zuniga on 5/24/21.
//

import Foundation

class board {
    lazy var gameBoard: [[Int]] = getGameBoard()
    func getGameBoard() -> [[Int]] {
        return [[]]
    }
    var width: Int = 0
    var height: Int = 0
    var difficulty: Int = 0
    init(width_: Int, height_: Int, difficulty_ : Int, empty_: Bool) {
        width = width_
        height  = height_
        difficulty = difficulty_;
        
        if !empty_ {
            gameBoard = Array(repeating: Array(repeating: 0, count: width), count: height)
            bombify()
            solveBoard()
        }
        else {
            gameBoard = Array(repeating: Array(repeating: -3, count: width), count: height)
        }
        //printBoard()
    }
    func bombify() {
        for row in 0..<height {
            for col in 0..<width {
                let chance = Int.random(in: 0...100)
                if chance < (8 * difficulty) {
                    gameBoard[row][col] = -1
                }
            }
        }
    }
    func solveBoard() {
        for row in 0..<height {
            for col in 0..<width {
                if gameBoard[row][col] == -1 {
                    continue
                }
                var count : Int = 0
                // TOP LEFT
                if(row - 1 >= 0 && col - 1 >= 0) {
                    if(gameBoard[row - 1][col - 1] == -1) {
                        count += 1
                    }
                }
                    
                // TOP
                if(row - 1 >= 0) {
                    if(gameBoard[row - 1][col] == -1) {
                        count += 1
                    }
                }
                // TOP RIGHT
                if(row - 1 >= 0 && col + 1 < width) {
                    if(gameBoard[row - 1][col + 1] == -1) {
                        count += 1
                    }
                }
                // LEFT
                if(col - 1 >= 0) {
                    if(gameBoard[row][col - 1] == -1) {
                        count += 1
                    }
                }
                // RIGHT
                if(col + 1 < width) {
                    if(gameBoard[row][col + 1] == -1) {
                        count += 1
                    }
                }
                // BOTTOM LEFT
                if(row + 1 < height && col - 1 >= 0) {
                    if(gameBoard[row + 1][col - 1] == -1) {
                        count += 1
                    }
                }
                // BOTTOM
                if(row + 1 < height) {
                    if(gameBoard[row + 1][col] == -1) {
                        count += 1
                    }
                }
                // BOTTOM RIGHT
                if(row + 1 < height && col + 1 < width) {
                    if(gameBoard[row + 1][col + 1] == -1) {
                        count += 1
                    }
                }
                gameBoard[row][col] = count;
            }
        }
    }
    func printBoard() {
        for array in gameBoard {
            for value in array {
                print(value, terminator: " ")
            }
            print(" ")
        }
    }
}
