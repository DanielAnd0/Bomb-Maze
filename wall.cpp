//
// Created by Daniel on 04.12.2025.
//

#include "wall.h"

wall::wall(const unsigned int position_x, const unsigned int position_y) : tiles(position_x,position_y){
    sprite.setTextureRect(sf::IntRect({static_cast<int>(2*size_x), 0},{static_cast<int>(size_x), static_cast<int>(size_y)}));
}
bool wall::detect_colision(sf::FloatRect& hitBox){
    auto tile_bounds = sf::FloatRect({static_cast<float>(sprite.getPosition().x), static_cast<float>(sprite.getPosition().y)},{static_cast<float>(size_y), static_cast<float>(size_x)});
    if (tile_bounds.findIntersection(hitBox)) {
        return true;
    }
    return false;
}

tiles* wall::clone() {
    return new wall(*this);
}