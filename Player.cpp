#include<iostream>
#include "Player.h"

sf::Texture Player::playerTexture("Sprites/Player.png");
int Player::player_size_x = 18;
int Player::player_size_y = 24;

Player::Player() : playerSprite(playerTexture) {
    lifes = 3;
    speed = 1;
    life_status = true;
    playerSprite.setTextureRect(sf::IntRect({0, 0}, {player_size_x, player_size_y}));
    playerSprite.setOrigin(sf::Vector2f(0, static_cast<float>(player_size_y)));
}

Player::Player(const int position_x, const int position_y) : playerSprite(playerTexture) {
    lifes = 3;
    speed = 1;
    life_status = true;
    playerSprite.setTextureRect(sf::IntRect({0, 0}, {player_size_x, player_size_y}));
    playerSprite.setOrigin(sf::Vector2f(0, static_cast<float>(player_size_y)));
    playerSprite.setPosition({static_cast<float>(position_x),static_cast<float>(position_y)});
}

int Player::get_lifes() const{
    return lifes;
}

bool Player::get_life_status() const{
    return life_status;
}
int Player::get_speed() const {
    return speed;
}
void Player::doNotMove() {
    can_player_move = false;
}
void Player::change_position(const int direction, const float deltaX) {
    constexpr int up = 0;
    constexpr int down = 1;
    constexpr int left = 2;
    constexpr int right = 3;
    switch (direction) {
        case up:
            this->playerSprite.move({0,-deltaX});
            break;
        case down:
            this->playerSprite.move({0,+deltaX});
            break;
        case left:
            this->playerSprite.move({-deltaX, 0});
            break;
        case right:
            this->playerSprite.move({deltaX, 0});
            break;
        default:
            break;
    }
}
void Player::set_speed(int Speed){
    this->speed = Speed;
}
void Player::Move(){

    int constexpr states[4][total_Sprite_States_per_move] = {
        {37, 56, 56, 75},
        {0, 18, 18, 37},
        {75, 95, 75, 115},
        {95, 115, 95, 135},
    };
    constexpr int up = 0;
    constexpr int down = 1;
    constexpr int left = 2;
    constexpr int right = 3;
    int player_size_X = player_size_x;
    int player_size_Y = player_size_y;
    float distance = 32/6.f;

    //moves up
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)){
        if(next_move_state[up] >= 2) player_size_X = -player_size_x;
        playerSprite.setTextureRect(sf::IntRect({states[up][next_move_state[up]], 0}, {player_size_X,player_size_Y}));
        if (can_player_move)
            change_position(up, distance);
        last_direction = up;
        next_move_state[up]++;
        if (next_move_state[up] >= total_Sprite_States_per_move) next_move_state[up] = 0;
    }
    //moves down
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
        if (next_move_state[down]>=2) player_size_X = -player_size_x;
        playerSprite.setTextureRect(sf::IntRect({states[down][next_move_state[down]], 0}, {player_size_X,player_size_Y}));
        if (can_player_move)
            change_position(down, distance);
        last_direction = down;
        next_move_state[down]++;
        if (next_move_state[down] >= total_Sprite_States_per_move) next_move_state[down] = 0;
    }
    //moves left
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
        playerSprite.setTextureRect(sf::IntRect({states[left][next_move_state[left]], 0}, {player_size_X,player_size_Y}));
        if (can_player_move)
            change_position(left, distance);
        last_direction = left;
        next_move_state[left]++;
        if (next_move_state[left] >= total_Sprite_States_per_move) next_move_state[left] = 0;
    }
    //moves right
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
        player_size_X = -player_size_x;
        playerSprite.setTextureRect(sf::IntRect({states[right][next_move_state[right]], 0}, {player_size_X,player_size_Y}));
        if (can_player_move)
            change_position(right, distance);
        last_direction = right;
        next_move_state[right]++;
        if (next_move_state[right] >= total_Sprite_States_per_move) next_move_state[right] = 0;
    }
    else {
        //player is not moving
        next_move_state[up]=0;
        next_move_state[down]=0;
        next_move_state[left]=0;
        next_move_state[right]=0;
        switch (last_direction) {
            case up:
                next_move_state[up]=1;
                playerSprite.setTextureRect(sf::IntRect({states[up][0], 0}, {player_size_X,player_size_Y}));
                break;
            case down:
                next_move_state[down]=1;
                playerSprite.setTextureRect(sf::IntRect({states[down][0], 0}, {player_size_X,player_size_Y}));
                break;
            case left:
                next_move_state[left]=1;
                playerSprite.setTextureRect(sf::IntRect({states[left][0], 0}, {player_size_X,player_size_Y}));
                break;
            case right:
                player_size_X = -player_size_x;
                next_move_state[right]=1;
                playerSprite.setTextureRect(sf::IntRect({states[right][0], 0}, {player_size_X,player_size_Y}));
                break;
            default: ;
        }
    }
    can_player_move = true;
}
sf::FloatRect Player::getBounds() const {
    sf::Sprite playerSpriteCopy = playerSprite;
    playerSpriteCopy.setScale(sf::Vector2f({static_cast<float>(player_size_x)/4, static_cast<float>(player_size_y)}));
    return playerSpriteCopy.getGlobalBounds();
}

void Player::draw(sf::RenderWindow& window) const {
    window.draw(playerSprite);
}
void Player::life_update() {
    lifes = lifes - 1;
    cout<<"Minus 1 life. Player lifes left: "<<lifes<<endl;
}
Bomb Player::Drop_Bomb() const{
  //Bomb bomb(1, position_x, position_y);
  // return bomb;
}
void Player::die() {
    life_status = false;
}
ostream& operator<<(ostream& os, const Player& player) {
   // os << "Jucatorul se afla la pozitia (" <<player.position_x<<", "<<player.position_y<<")\n";
    os << "Vieti ramase: "<< player.lifes <<endl;
    os << "Viteza: "<<player.speed <<endl;
    return os;
}



/*
 #include<iostream>
#include <SFML/Graphics.hpp>

int main() {
    const sf::VideoMode video_mode({800,600});
    sf::RenderWindow window(video_mode, "Bomb-Maze");
    const sf::Texture texture("Sprites/player.png");
    sf::Sprite sprite(texture);
    sprite.setTextureRect(sf::IntRect({0,0}, {24, 24}));
    //definim variabila frame
    int frame = 0;
    //dimensiunile unui frame
    int size_x = 24;
    int size_y = 24;
    //contorul pentru indicele frame-ului corespunzator directiei
    int right = 0;
    int left = 0;
    int up = 0;
    int down = 0;

    //window.setKeyRepeatEnabled(false); - pt imbunatatirea miscarii - TODO
    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
            if (event->is<sf::Event::KeyReleased>()) {
                auto* key = event->getIf<sf::Event::KeyReleased>();
                switch (key->scancode) {
                    case sf::Keyboard::Scan::Right
                        : frame = 99; break;
                    case sf::Keyboard::Scan::Left
                        : frame = 75; break;
                    case sf::Keyboard::Scan::Up
                        : frame = 150; break;
                    case sf::Keyboard::Scan::Down
                        : frame = 0; break;
                    default: break;
                }
                right = 0;
                left = 0;
                up = 0;
                down = 0;
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
            constexpr int frame_right[] ={99,124,149};
            sprite.move({32/6.f, 0});
            frame = frame_right[right];
            right++;
            if (right == 3)
                right = 0;
            size_x = -24;
            size_y = 24;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
            constexpr int frame_up[] ={150,175,200};
            sprite.move({0, -32/6.f});
            frame = frame_up[up];
            up++;
            if (up == 3)
                up = 0;
            size_x = 24;
            size_y = 24;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
            constexpr int frame_left[] ={75,100,125};
            sprite.move({-32/6.f, 0});
            frame = frame_left[left];
            left++;
            if (left == 3)
                left = 0;
            size_x = 24;
            size_y = 24;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
            constexpr int frame_down[] ={0,25,50};
            sprite.move({0, 32/6.f});
            frame = frame_down[down];
            down++;
            if (down == 3)
                down = 0;
            size_x = 24;
            size_y = 24;
        }
        window.clear(sf::Color::White);
        sprite.setTextureRect(sf::IntRect({frame, 0}, {size_x, size_y}));
        sf::sleep(sf::seconds(0.05));
        window.draw(sprite);
        sf::sleep(sf::seconds(0.05));
        window.display();
    }
}
 */