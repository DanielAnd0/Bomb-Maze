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
    [[nodiscard]]int get_radius() const;
    [[nodiscard]]int get_position_x() const;
    [[nodiscard]]int get_position_y() const;
    friend ostream& operator<<(ostream& os, const Bomb& bomb);
};

#endif //OOP_BOMB_H