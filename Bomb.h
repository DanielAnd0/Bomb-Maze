//
// Created by Daniel on 02.11.2025.
//

#ifndef OOP_BOMB_H
#define OOP_BOMB_H

#include<iostream>
using namespace std;

class Bomb {
    int radius;
    int position_x;
    int position_y;
public:
    Bomb();
    Bomb(int radius, int position_x, int position_y);
    int get_radius() const;
    int get_position_x() const;
    int get_position_y() const;
};

#endif //OOP_BOMB_H