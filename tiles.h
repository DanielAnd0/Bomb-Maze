//
// Created by Daniel on 04.12.2025.
//

#ifndef OOP_TILES_H
#define OOP_TILES_H

#include<SFML/Graphics.hpp>
#include "Player.h"

class tiles{
    static sf::Texture texture;
    unsigned int position_x, position_y;
protected:
    sf::Sprite sprite;
    static unsigned int size_x;
    static unsigned int size_y;
public:
    static sf::Vector2u getsize();
    tiles(unsigned int position_x, unsigned int position_y);
    virtual ~tiles() = default;
    void drawTile(sf::RenderWindow& window) const;
    virtual bool detect_colision(Player& player) = 0;
};

#endif //OOP_TILES_H