//
//  ContentView.swift
//  Minesweeper iOS
//
//  Created by Carson Zuniga on 5/22/21.
//

import SwiftUI

var width = 7
var height = 13
var difficulty = 3

struct ContentView: View {
    @State var data = board(width_: width, height_: height, difficulty_: difficulty, empty_: true).gameBoard
    
    @State var ourdata = board(width_: width, height_: height, difficulty_: difficulty, empty_: true).gameBoard
    
    var imageData = [0: "0", 1: "1", 2: "2", 3: "3", 4: "4", 5: "5", 6: "6", 7: "7", 8: "8", -1: "untapped_bomb", -2: "tapped_bomb", -3: "square"]
    

    var body: some View {

        ZStack {
            Image("background")
            VStack {
                Button(action: {
                    data = board(width_: width, height_: height, difficulty_: difficulty, empty_: false).gameBoard
                    ourdata = board(width_: width, height_: height, difficulty_: difficulty, empty_: true).gameBoard
                }) {
                    Text("Generate New Board")
                        .font(.largeTitle)
                        .foregroundColor(.purple)
                }
                ForEach(0..<height) { row in
                    HStack {
                        ForEach(0..<width) { col in
                            Button(action: {
                                ourdata[row][col] = data[row][col]
                            }) {
                            Image(imageData[ourdata[row][col]]!)
                            }
                        }
                    }
                }
            }
        }
    }
}

struct ContentView_Previews: PreviewProvider {
    static var previews: some View {
        ContentView()
            .previewDevice("iPhone 11")
    
    }
}
