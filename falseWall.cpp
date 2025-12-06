//
// Created by Daniel on 04.12.2025.
//

#include "falseWall.h"

falseWall::falseWall(const unsigned int position_x, const unsigned int position_y) : tiles(position_x,position_y) {
    sprite.setTextureRect(sf::IntRect({0,0}, {static_cast<int>(size_x),static_cast<int>(size_y)}));
    destroyed = false;
}
void falseWall::destroy() {
    destroyed = true;
    sprite.setTextureRect(sf::IntRect({static_cast<int>(size_x),0}, {static_cast<int>(size_x),static_cast<int>(size_y)}));
}
bool falseWall::detect_colision(Player &player) {
    sf::FloatRect player_bounds = player.getBounds();
    sf::FloatRect tile_bounds = sprite.getGlobalBounds();
    if (tile_bounds.findIntersection(player_bounds) && destroyed==false) {
        return true;
    }
    return false;
}
