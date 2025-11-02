#include<iostream>
#include "Bomb.h"

using namespace std;

Bomb::Bomb(){
    radius = 1;
    position_x = -1;
    position_y = -1;
}
Bomb::Bomb(int radius, int position_x, int position_y) {
    this->radius = radius;
    this->position_x = position_x;
    this->position_y = position_y;
    cout<<"Boooom"<<endl;
}
int Bomb::get_radius() const{
    return radius;
}
int Bomb::get_position_x() const{
    return position_x;
}
int Bomb::get_position_y() const {
    return position_y;
}

