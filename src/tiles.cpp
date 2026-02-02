//
// Created by Daniel on 04.12.2025.
//

#include "../headers/tiles.h"
#include "../headers/Exceptions.h"

sf::Texture tiles::texture;

void tiles::loadTexture() {
        bool is_loaded = texture.loadFromFile("Sprites/Tiles.png");
        if (!is_loaded)throw FileLoadFail();
}

sf::FloatRect tiles::getBounds() const {
    return sprite.getGlobalBounds();
}
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
sf::Vector2f tiles::get_position() const {
    return {static_cast<float>(position_x), static_cast<float>(position_y)};
}

