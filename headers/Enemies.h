//
// Created by Daniel on 02.11.2025.
//

#ifndef OOP_ENEMIES_H
#define OOP_ENEMIES_H

#include <SFML/Graphics.hpp>

class Enemies{
    static sf::Texture texture;
    sf::Sprite sprite;
    static float speed;
    bool life_status = true;
    int  last_direction = 0;
    sf::FloatRect EnemyHitBox;
    float stateTime = 0;
    int move_state=0;
public:
    Enemies();
    Enemies(float position_x, float position_y);
    static void loadTexture();
    [[nodiscard]]bool get_life_status() const;
    [[nodiscard]]int get_direction() const;
    void kill();
    static void set_speed(float new_speed);
    void set_direction(int new_direction);
    void change_position(int direction, float deltaX);
    void Update(float deltaTime, int next_direction);
    sf::FloatRect getHitBox() const;
    void draw(sf::RenderWindow& window) const;
};
#endif //OOP_ENEMIES_H