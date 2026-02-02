#include "../headers/Player.h"
#include "../headers/Exceptions.h"
#include "../headers/Bomb.h"
#include <cmath>
#include "../headers/CollisionManager.h"
sf::Texture Player::playerTexture;




void Player::loadTexture() {
    bool is_loaded = playerTexture.loadFromFile("Sprites/Player.png");
    if (!is_loaded)throw FileLoadFail();
}

int Player::player_size_x = 18;
int Player::player_size_y = 24;

Player::Player() : startPosition({0,0}), playerSprite(playerTexture){
    lifes = 3;
    speed = 1;
    life_status = true;
    playerSprite.setTextureRect(sf::IntRect({0, 0}, {player_size_x, player_size_y}));
    const float offset_x = 0.20f * static_cast<float>(player_size_x);
    const float offset_y = 0.67f * static_cast<float>(player_size_y);
    playerHitBox=sf::FloatRect({0.f+offset_x,0.f+offset_y},{static_cast<float>(player_size_x)-2.f*offset_x, static_cast<float>(player_size_y)-offset_y-2});
    //playerSprite.setOrigin({0, static_cast<float>(player_size_y)});
}

Player::Player(const float position_x, const float position_y) : startPosition({position_x, position_y}),playerSprite(playerTexture) {
    lifes = 3;
    speed = 1;
    life_status = true;
    playerSprite.setTextureRect(sf::IntRect({0, 0}, {player_size_x, player_size_y}));
    playerSprite.setPosition({position_x,position_y});
    const float offset_x = 0.20f * static_cast<float>(player_size_x);
    const float offset_y = 0.67f * static_cast<float>(player_size_y);
    playerHitBox=sf::FloatRect({position_x+offset_x,position_y+offset_y},{static_cast<float>(player_size_x)-2.f*offset_x, static_cast<float>(player_size_y)-offset_y-2});
    //playerSprite.setOrigin({0, static_cast<float>(player_size_y)});
}


int Player::get_direction()const {
    return last_direction;
}
bool Player::get_life_status() const{
    return life_status;
}

bool Player::can_deploy() const {
    return can_deploy_bomb;
}

void Player::restart() {
    playerSprite.setPosition(startPosition);
}
void Player::change_position(const int direction, const float deltaX) {

    switch (direction) {
        case 0:
            this->playerSprite.move({0,-deltaX});
            break;
        case 1:
            this->playerSprite.move({0,+deltaX});
            break;
        case 2:
            this->playerSprite.move({-deltaX, 0});
            break;
        case 3:
            this->playerSprite.move({deltaX, 0});
            break;
        default:
            break;
    }
    const float offset_x = 0.20f * static_cast<float>(player_size_x);
    const float offset_y = 0.67f * static_cast<float>(player_size_y);
    playerHitBox.position.x = playerSprite.getPosition().x + offset_x;
    playerHitBox.position.y = playerSprite.getPosition().y + offset_y;
}
void Player::set_speed(const float Speed){
    this->speed = Speed;
}
void Player::set_deploy_status(bool status) {
    can_deploy_bomb = status;
}

void Player::Update(Subject* theChangedSubject) {
    const Bomb* explodedBomb = dynamic_cast<Bomb*>(theChangedSubject);
    if (explodedBomb != nullptr) {
        if (explodedBomb->isExploded()){
        //Bomb destroys player
            can_deploy_bomb = true;
            const sf::Vector2 bomb_explosion = explodedBomb->getPosition();
            const float center_x = playerHitBox.getCenter().x;
            const float center_y = playerHitBox.getCenter().y;
            float distance = std::sqrt((center_x-bomb_explosion.x)*(center_x-bomb_explosion.x) + (center_y-bomb_explosion.y)*(center_y-bomb_explosion.y));
            float radius = explodedBomb->get_radius();
            if (distance <= radius) {
                life_update();
                restart();
            }
    }
        //detect colision
        if (explodedBomb->isDeployed()) {
            sf::FloatRect bounds = explodedBomb->getBounds();
            CollisionManager<Player> colision(this, bounds);
            if (colision.checkCollision()) colision.solve();
    }
    }
}

void Player::Update(const float deltaTime){

    //FOR ANIMATION
    int constexpr states[4][total_Sprite_States_per_move] = {
        {37, 56, 56, 75},
        {0, 18, 18, 37},
        {75, 95, 75, 115},
        {95, 115, 95, 135},
    };

    constexpr int up = 0;
    constexpr int down = 1;
    constexpr int right = 3;

    int player_size_X = player_size_x;
    int player_size_Y = player_size_y;

    stateTime += deltaTime;

    //FOR MOVEMENT
    bool is_moving = false;
    int dir = last_direction;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
        dir = up;
        change_position(up, speed * deltaTime);
        is_moving = true;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
        dir = down;
        change_position(down, speed * deltaTime);
        is_moving = true;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
        constexpr int left = 2;
        dir = left;
        change_position(left, speed * deltaTime);
        is_moving = true;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
        dir = right;
        change_position(right, speed * deltaTime);
        is_moving = true;
    }

//FOR Animation
    if (is_moving) {
        if (moveStart==true) {
            next_move_state[dir]=1;
            moveStart = false;
        }
        if (constexpr float switch_time = 0.1666f; stateTime >= switch_time) {
            stateTime -= switch_time;
            next_move_state[dir]++;
            if (next_move_state[dir] >= total_Sprite_States_per_move)
                next_move_state[dir] = 0;
        }
    }
    else {
        // Idle = frame 0
        moveStart = true;
        next_move_state[dir] = 0;
        stateTime = 0;
    }

    int frame = states[dir][next_move_state[dir]];
    last_direction = dir;
    if (dir == right || (dir == up && next_move_state[dir] >= 2) || (dir == down && next_move_state[dir] >= 2))
        player_size_X = -player_size_x;

    playerSprite.setTextureRect(sf::IntRect({frame, 0}, {player_size_X, player_size_Y}));
}


sf::FloatRect Player::getHitBox() const {
    return playerHitBox;
}

sf::Vector2f Player::getPlayerPosition() const {
    float center_x = playerSprite.getPosition().x + static_cast<float>(player_size_x)/2.0f;
    float center_y = playerSprite.getPosition().y + static_cast<float>(player_size_y)/2.0f;
    return {center_x, center_y};
}

void Player::draw(sf::RenderWindow& window) const {
    window.draw(playerSprite);
}
void Player::life_update() {
    lifes = lifes - 1;
    if (lifes <= 0) life_status = false;
}