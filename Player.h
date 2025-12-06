
#ifndef OOP_PLAYER_H
#define OOP_PLAYER_H

#include "Bomb.h"
#include <SFML/Graphics.hpp>

class Player{
     int lifes;
     int speed;
     bool life_status; // true - alive, false = dead
     static sf::Texture playerTexture;
     static int player_size_x;
     static int player_size_y;
     sf::Sprite playerSprite;
     static constexpr int total_Sprite_States_per_move = 4;
     int next_move_state[4] ={ 0,0,0,0 };
     bool can_player_move = true;
     int last_direction = -1;

public:
     Player();
     Player(int position_x, int position_y);
     [[nodiscard]]int get_lifes() const;
     [[nodiscard]]bool get_life_status() const;
     [[nodiscard]]int get_speed() const;
     void change_position(int direction, float deltaX);
     void doNotMove();
     void set_speed(int Speed);
     void Move();
     sf::FloatRect getBounds() const;
     void draw(sf::RenderWindow& window) const;
     void life_update();
     [[nodiscard]]Bomb Drop_Bomb() const;
     void die();
     friend ostream& operator<<(ostream& os, const Player& player);
};

#endif //OOP_PLAYER_H