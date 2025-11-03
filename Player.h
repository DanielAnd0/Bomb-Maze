
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
     [[nodiscard]]int get_lifes() const;
     [[nodiscard]]int get_position_x() const;
     [[nodiscard]]int get_position_y() const;
     [[nodiscard]]bool get_life_status() const;
     [[nodiscard]]int get_speed() const;
     void set_position(int x, int y);
     void Move(int direction);
     void life_update();
     [[nodiscard]]Bomb Drop_Bomb() const;
     void die();
     friend ostream& operator<<(ostream& os, const Player& player);
};

#endif //OOP_PLAYER_H