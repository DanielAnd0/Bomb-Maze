//
// Created by Daniel on 04.12.2025.
//

#include "wall.h"

wall::wall(unsigned int position_x, unsigned int position_y) : tiles(position_x,position_y){
    sprite.setTextureRect(sf::IntRect({static_cast<int>(2*size_x), 0},{static_cast<int>(size_x), static_cast<int>(size_y)}));
}
bool wall::detect_colision(Player& player){
    sf::FloatRect player_bounds = player.getBounds();
    sf::FloatRect tile_bounds = sprite.getLocalBounds();
    if (tile_bounds.findIntersection(player_bounds)) {
        return true;
    }
    return false;
}