#include <iostream>
#include "Enemies.h"

using namespace std;

Enemies::Enemies() {
    position_x = -1;
    position_y = -1;
    life_status = true;
}
Enemies::Enemies(int position_x, int position_y) {
    this->position_x = position_x;
    this->position_y = position_y;
    life_status = true;
}
int Enemies::get_position_x() const {
    return position_x;
}
int Enemies::get_position_y() const {
    return position_y;
}
void Enemies::set_position(int x, int y) {
    position_x = x;
    position_y = y;
}
bool Enemies::get_life_status() const {
    return life_status;
}
void Enemies::kill() {
    life_status = false;
    position_x = -1;
    position_y = -1;
}
ostream& operator<<(ostream& os, const Enemies& enemy) {
    os << "Inamic la pozitia ("<<enemy.position_x<<", "<<enemy.position_y<<")\n";
    return os;
}





