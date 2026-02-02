//
// Created by Daniel on 04.12.2025.
//

#include "../headers/path.h"


path::path(const unsigned int position_x, const unsigned int position_y): tiles(position_x,position_y) {
    sprite.setTextureRect(sf::IntRect({static_cast<int>(size_x), 0},{static_cast<int>(size_x),static_cast<int>(size_y)}));
}

bool path::detect_colision([[maybe_unused]]sf::FloatRect hitBox){
    return false;
}
tiles* path::clone() {
    return new path(*this);
}