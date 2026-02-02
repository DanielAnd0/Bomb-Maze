//
// Created by Daniel on 02.11.2025.
//

#ifndef OOP_BOMB_H
#define OOP_BOMB_H


#include <SFML/Graphics.hpp>
#include "Subject.h"

class Bomb : public Subject{
    float radius;
    static sf::Texture texture;
    sf::Sprite sprite;
    const float duration = 2;
    float timer = 0;
    bool deployed = false;
    bool exploded = false;
    sf::Vector2f deployed_position = {-1, -1};
public:
    Bomb();
    static void loadTexture();
    bool get_status() const;
    float get_radius() const;
    void deploy(float position_x, float position_y);
    sf::Vector2f getPosition() const;
    bool isDeployed() const;
    bool isExploded() const;
    sf::FloatRect getBounds() const;
    void Update(float deltaTime);
    void draw(sf::RenderWindow &window) const;
   // friend ostream& operator<<(ostream& os, const Bomb& bomb);
};

#endif //OOP_BOMB_H