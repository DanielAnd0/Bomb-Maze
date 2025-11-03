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
bool Player::get_life_status() const{
    return life_status;
}
int Player::get_speed() const {
    return speed;
}
void Player::set_position(int x, int y) {
    this->position_x = x;
    this->position_y = y;
}
void Player::Move(int direction){
    switch(direction){
        case 1: position_x -= 1; break;
        case 2: position_y += 1; break;
        case 3: position_x += 1; break;
        case 4: position_y -= 1; break;
        default:
            cout<<"Direction is not in range 1-4!";
            break;
    }
}
void Player::life_update() {
    lifes = lifes - 1;
    cout<<"Minus 1 life. Player lifes left: "<<lifes<<endl;
}
Bomb Player::Drop_Bomb() const{
    Bomb bomb(1, position_x, position_y);
    return bomb;
}
void Player::die() {
    life_status = false;
}
ostream& operator<<(ostream& os, const Player& player) {
    os << "Jucatorul se afla la pozitia (" <<player.position_x<<", "<<player.position_y<<")\n";
    os << "Vieti ramase: "<< player.lifes <<endl;
    os << "Viteza: "<<player.speed <<endl;
    return os;
}


