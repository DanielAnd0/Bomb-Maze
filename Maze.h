//
// Created by Daniel on 02.11.2025.
//

#ifndef OOP_MAZE_H
#define OOP_MAZE_H


#include<iostream>
#include<string>
#include<vector>

#include "Enemies.h"
#include "Player.h"


using namespace std;

class Maze{
    int rows, cols;
    vector<string> maze;
    Player *player;
    vector<Enemies*> enemies;
    struct Point{
        int x;
        int y;
    } exit;
    void show_maze() const;
public:
    Maze();
    Maze(int rows, int cols, int x, int y);
    ~Maze();
    void destroy_block(int x, int y);
    void place_player(int x, int y);
    void place_enemies();
    void destroy_enemies();
    void display();
};

#endif //OOP_MAZE_H