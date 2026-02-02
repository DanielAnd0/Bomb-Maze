#include "../headers/Bomb.h"

#include "../headers/Exceptions.h"
#include "../headers/Player.h"

sf::Texture Bomb::texture;

void Bomb::loadTexture() {
        bool is_loaded = texture.loadFromFile("Sprites/Bomb.png");
        if (!is_loaded) throw FileLoadFail();
}


Bomb::Bomb():sprite(texture) {
    timer = 0;
    radius = 24; //one tile and half
    sprite.setTextureRect(sf::IntRect({0, 0}, {16, 16}));
    sprite.setOrigin(sf::Vector2f(8, 8));
}

float Bomb::get_radius() const {
    return radius;
}
void Bomb::deploy(const float position_x, float position_y) {
    sprite.setPosition({position_x, position_y});
    deployed_position = {position_x, position_y};
    deployed = true;
    exploded = false;
}
sf::Vector2f Bomb::getPosition() const {
    return deployed_position;
}
bool Bomb::isDeployed() const {
    return deployed;
}
bool Bomb::isExploded() const {
    return exploded;
}
sf::FloatRect Bomb::getBounds() const {
    return sprite.getGlobalBounds();
}

void Bomb::Update(const float deltaTime) {
    exploded = false;
    if(deployed) {
        timer+=deltaTime;
        if (timer >= duration) { //BOMB EXPLODES IN 3 SECONDS
            deployed = false;
            exploded = true;
            Notify();
            timer = 0;
            sprite.setTextureRect(sf::IntRect({0, 0}, {16, 16}));
        }
        if (timer >= 0.2) Notify();
        if (timer >= duration/3)
            sprite.setTextureRect(sf::IntRect({18, 0}, {14, 16}));
        if (timer >= 2*duration/3)
            sprite.setTextureRect(sf::IntRect({33, 0}, {16, 16}));
    }
}
void Bomb::draw(sf::RenderWindow &window) const {
    if (deployed)window.draw(sprite);
}

// ostream& operator<<(ostream& os, const Bomb& bomb) {
//    // os << "Bomba de raza "<<bomb.radius<<" la pozitia ("<<bomb.position_x<<", "<<bomb.position_y<<")\n";
//     return os;
// }

