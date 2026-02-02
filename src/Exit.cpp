//
// Created by Daniel on 09.12.2025.
//

#include "../headers/Exit.h"

Exit::Exit(const unsigned int position_x, const unsigned int position_y): tiles(position_x,position_y) {
    locked = true;
    sprite.setTextureRect(sf::IntRect({0, 0},{static_cast<int>(size_x),static_cast<int>(size_y)}));
}
bool Exit::detect_colision(sf::FloatRect hitBox) {
    sf::FloatRect tile_bounds = sprite.getGlobalBounds();
    if (locked && tile_bounds.findIntersection(hitBox)) {
        return true;
    }
    return false;
}
void Exit::unlock() {
    locked = false;
    sprite.setTextureRect(sf::IntRect({static_cast<int>(size_x)*3, 0},{static_cast<int>(size_x),static_cast<int>(size_y)}));
}
Exit* Exit::clone() {
    return new Exit(*this);
}
