//
// Created by Daniel on 02.11.2025.
//

#ifndef OOP_ENEMIES_H
#define OOP_ENEMIES_H

#include <iostream>
using namespace std;

class Enemies {
    int position_x;
    int position_y;
    bool life_status;
public:
    Enemies();
    Enemies(int position_x, int position_y);
    int get_position_x() const;
    int get_position_y() const;
    void set_position(int x, int y);
    bool get_life_status() const;
    void kill();
};
#endif //OOP_ENEMIES_H