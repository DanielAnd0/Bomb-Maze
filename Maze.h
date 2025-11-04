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
    vector<Enemies> enemies;
    struct Point{
        int x;
        int y;
    } exit;
    [[nodiscard]]int is_in_maze(int x, int y)const;
    void destroy_enemy(int x, int y);
public:
    Maze();
    Maze(int rows, int cols, int x, int y);
    Maze(const Maze& other);
    ~Maze();
    void create_maze();
    void replace_player(int x, int y);
    int Move_Player(int direction); // 1 - a reusit mutarea
    void Player_Bomb();
    void place_enemy(int x, int y);
    Maze& operator=(const Maze& other);
    friend ostream& operator<<(ostream& os, const Maze& maze);
    int checkGame() const;
};

/*
 Legend:
 * = block
 o = false block
 P = player
 E = enemy

*/

#endif //OOP_MAZE_H