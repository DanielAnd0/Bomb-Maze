//
// Created by Daniel on 04.12.2025.
//

#include "tiles.h"

sf::Texture tiles::texture("Sprites/Tiles.png");
unsigned int tiles::size_x = 16, tiles::size_y = 16;
sf::Vector2u tiles::getsize() {
    return {size_x, size_y};
}
tiles::tiles(const unsigned int position_x, const unsigned int position_y) : position_x(position_x), position_y(position_y), sprite(tiles::texture) {
    sprite.setPosition(sf::Vector2f(static_cast<float>(position_x),static_cast<float>(position_y)));
}
void tiles::drawTile(sf::RenderWindow& window) const {
    window.draw(sprite);
}
