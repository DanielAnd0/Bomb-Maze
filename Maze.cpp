//
// Created by Daniel on 02.11.2025.
//

#include<iostream>
#include "Maze.h"
#include <fstream>

ifstream
using namespace std;

void Maze::show_maze() const{
    for (int i  = 0; i < rows; i++) {
        for (int j  = 0; j < cols; j++) {
            cout<<maze[i][j]<<" ";
        }
        cout<<endl;
    }
}
Maze::Maze() {
    rows = 10;
    cols = 10;
    player = new Player;

}