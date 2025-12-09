//
// Created by Daniel on 04.12.2025.
//

#ifndef OOP_TILES_H
#define OOP_TILES_H

#include<SFML/Graphics.hpp>

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
    static void loadTexture();
    virtual ~tiles() = default;
    void drawTile(sf::RenderWindow& window) const;
    virtual bool detect_colision(sf::FloatRect& hitBox) = 0;
    virtual tiles* clone() = 0;
    sf::Vector2f get_position() const;
};

#endif //OOP_TILES_H