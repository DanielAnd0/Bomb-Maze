#include<iostream>
#include "Player.h"

using namespace std;

Player::Player() {
    lifes = 3;
    speed = 1;
    life_status = true;
    position_x = 1;
    position_y = 1;
}
Player::Player(int position_x, int position_y) {
    this->position_x = position_x;
    this->position_y = position_y;
    lifes = 3;
    speed = 1;
    life_status = true;
}
int Player::get_lifes() const{
    return lifes;
}
int Player::get_position_x() const{
    return position_x;
}
int Player::get_position_y() const{
    return position_y;
}
void Player::set_position(int x, int y) {
    this->position_x = x;
    this->position_y = y;
}
void Player::Move(int direction){
    switch(direction){
        case 1: position_x += speed; break;
        case 2: position_y += speed; break;
        case 3: position_x -= speed; break;
        case 4: position_y -= speed; break;
        default:
            cout<<"Direction is not in range 1-4!";
            break;
    }
}
void Player::life_update() {
    lifes = lifes - 1;
}
Bomb Player::Drop_Bomb() const{
    Bomb bomb(1, position_x, position_y);
    return bomb;
}

void Player::die() {
    life_status = false;
}
