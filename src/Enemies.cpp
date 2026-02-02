
#include "../headers/Enemies.h"
#include "../headers/Player.h"
#include "../headers/Exceptions.h"

sf::Texture Enemies::texture;
void Enemies::loadTexture() {
    bool is_loaded = texture.loadFromFile("Sprites/Enemy.png");
    if (!is_loaded)throw FileLoadFail();
}

float Enemies::speed = 50;
Enemies::Enemies():sprite(texture) {
    sprite.setTextureRect(sf::IntRect({0,0},{14,16}));
    sprite.setPosition({0,0});
    life_status = true;
    EnemyHitBox=sf::FloatRect({2.f,2.f},{13.f, 13.f});

}
Enemies::Enemies(const float position_x, const float position_y):sprite(texture){
    sprite.setTextureRect(sf::IntRect({0,0},{14,16}));
    sprite.setPosition({static_cast<float>(position_x),static_cast<float>(position_y)});
    life_status = true;
    EnemyHitBox=sf::FloatRect({position_x+2.f,position_y+2.f},{13.f, 13.f});
}

bool Enemies::get_life_status() const {
    return life_status;
}
int Enemies::get_direction() const {
    return last_direction;
}
float Enemies::get_speed() {
    return speed;
}
void Enemies::kill() {
    sprite.setTextureRect(sf::IntRect({53,0},{16,16}));
    life_status = false;
}
void Enemies::set_speed(const float new_speed) {
    speed = new_speed;

}
void Enemies::set_direction(const int new_direction) {
    last_direction = new_direction;
}

sf::FloatRect Enemies::getHitBox() const {
    return EnemyHitBox;
}

void Enemies::change_position(const int direction, float deltaX) {
    switch (direction) {
        case 0:
            this->sprite.move({0,-deltaX});
            break;
        case 1:
            this->sprite.move({0,+deltaX});
            break;
        case 2:
            this->sprite.move({-deltaX, 0});
            break;
        case 3:
            this->sprite.move({deltaX, 0});
            break;
        default:
            break;
    }
    EnemyHitBox.position.x = sprite.getPosition().x + 2.f;
    EnemyHitBox.position.y = sprite.getPosition().y + 2.f;
}
void Enemies::Update(float deltaTime, const int next_direction) {

    last_direction = next_direction;
    change_position(last_direction, speed*deltaTime);
    //Animation
    stateTime += deltaTime;
    if (constexpr float switch_time = 0.1666f; stateTime >= switch_time) {
        constexpr int states[6] = {0, 18, 36, 51, 33, 14};
        stateTime -= switch_time;
        int size_x = 16;
        if (move_state > 2)size_x = -16;
        if (move_state == 5)size_x = -14;
        sprite.setTextureRect(sf::IntRect({states[move_state], 0}, {size_x, 16}));
        move_state++;
        if (move_state >= 6) move_state = 0;
    }
}

void Enemies::draw(sf::RenderWindow &window) const {
    window.draw(sprite);
}

// ostream& operator<<(ostream& os, const Enemies& enemy) {
//     os << "Inamic la pozitia ("<<enemy.position_x<<", "<<enemy.position_y<<")\n";
//     return os;
// }





