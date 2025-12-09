
#ifndef OOP_PLAYER_H
#define OOP_PLAYER_H

#include "Bomb.h"
#include <SFML/Graphics.hpp>

class Player{
     sf::Vector2f startPosition;
     int lifes;
     float speed;
     bool life_status; // true - alive, false = dead
     static sf::Texture playerTexture;
     Bomb playerBomb;
     static int player_size_x;
     static int player_size_y;
     sf::Sprite playerSprite;
     sf::FloatRect playerHitBox;
     static constexpr int total_Sprite_States_per_move = 4;
     int next_move_state[4] ={ 0,0,0,0 };
     float stateTime = 0.0f;
     int last_direction = 0;
     bool moveStart=true;
public:
     Player();
     Player(float position_x, float position_y);
     static void loadTexture();
     [[nodiscard]]bool get_life_status() const;
     [[nodiscard]]float get_speed() const;
     [[nodiscard]]Bomb& get_bomb();
     [[nodiscard]]int get_direction() const;
     void change_position(int direction, float deltaX);
     void set_speed(float Speed);
     void Update(float deltaTime);
     void restart();
     sf::FloatRect getHitBox() const;
     void draw(sf::RenderWindow& window) const;
     void life_update();
    // friend ostream& operator<<(ostream& os, const Player& player);
};

#endif //OOP_PLAYER_H