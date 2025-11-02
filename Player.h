
#ifndef OOP_PLAYER_H
#define OOP_PLAYER_H

#include<iostream>
#include "Bomb.h"
using namespace std;

class Player{
     int lifes;
     int speed;
     bool life_status; // true - alive, false = dead
     int position_x, position_y;
public:
     Player();
     Player(int position_x, int position_y);
     int get_lifes() const;
     int get_position_x() const;
     int get_position_y() const;
     void set_position(int x, int y);
     void Move(int direction);
     void life_update();
     Bomb Drop_Bomb() const;
     void die();
};

#endif //OOP_PLAYER_H