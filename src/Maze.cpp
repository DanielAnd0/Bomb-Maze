//
// Created by Daniel on 02.11.2025.
//

#include<iostream>
#include "../headers/Maze.h"
#include <cmath>

#include "../headers/Exceptions.h"
#include "../headers/TileFactory.h"
#include "../headers/Bomb.h"
#include "../headers/CollisionManager.h"


bool Maze::is_in_maze(const float x, const float y) const {
    if (x < 0 || x >= width*tiles::getsize().x || y < 0 || y >= height*tiles::getsize().y) return false;
    return true;
}

Maze::Maze(const unsigned int width, const unsigned int height):width(width), height(height){

}
sf::Vector2f Maze::get_exit() const{
    return exit;
}
void Maze::load(const int* data) {
    for (unsigned int i = 0; i < width; i++)
        for (unsigned int j = 0; j < height; j++) {
                const sf::Vector2u tile_size = tiles::getsize();
                const int Number = data[i + j * width];
                const auto positionX = static_cast<float>(tile_size.x * i);
                const auto positionY = static_cast<float>(tile_size.y * j);
                if (!is_in_maze(positionX, positionY)) {throw NotInMaze(positionX, positionY);}

                unsigned int x = i * tile_size.x;
                unsigned int y = j * tile_size.y;
                auto tile = TileFactory::create(static_cast<TileType>(Number), x, y);

                if (Number == 3) {
                exit = { static_cast<float>(x) + static_cast<float>(tile_size.x) / 2.f,
                          static_cast<float>(y) + static_cast<float>(tile_size.y) / 2.f};
                }

                Tiles.push_back(tile);
            }
}
void Maze::add_enemy(const float position_x,const float position_y) {
        enemies.push_back(new Enemies(position_x, position_y));
        if (!is_in_maze(position_x, position_y))throw NotInMaze(position_x, position_y);
}

void Maze::drawMaze(sf::RenderWindow& window) const {
    for (const auto tile : Tiles) {
        tile->drawTile(window);
    }
    for (const auto enemy : enemies) {
        if (enemy->get_life_status())
            enemy->draw(window);
    }
}

void Maze::Update(Subject *theChangedSubject) {

    const Bomb* explodedBomb = dynamic_cast<Bomb*>(theChangedSubject);
    if (explodedBomb != nullptr) {
        const sf::Vector2 bomb_explosion = explodedBomb->getPosition();
        if (!is_in_maze(bomb_explosion.x, bomb_explosion.y) && explodedBomb->isDeployed())throw NotInMaze(bomb_explosion.x, bomb_explosion.y);


        if (explodedBomb->isExploded()){
            for (const auto tile : Tiles) {
                //bomb destroy falseWalls
                if (const auto is_false_wall = dynamic_cast<falseWall*>(tile)) {
                    sf::Vector2f center_of_tile = is_false_wall->get_position();
                    center_of_tile.x += static_cast<float>(tiles::getsize().x) / 2.f;
                    center_of_tile.y += static_cast<float>(tiles::getsize().y) / 2.f;
                    float distance = std::sqrt((center_of_tile.x-bomb_explosion.x)*(center_of_tile.x-bomb_explosion.x) + (center_of_tile.y-bomb_explosion.y)*(center_of_tile.y-bomb_explosion.y));
                    float radius = explodedBomb->get_radius();
                    if (distance <= radius)
                        is_false_wall->destroy();
                }
            }
            //Bomb destroys enemy
            for (const auto enemy : enemies) {
                const float center_x = enemy->getHitBox().getCenter().x;
                const float center_y = enemy->getHitBox().getCenter().y;
                float distance = std::sqrt((center_x-bomb_explosion.x)*(center_x-bomb_explosion.x) + (center_y-bomb_explosion.y)*(center_y-bomb_explosion.y));
                float radius = explodedBomb->get_radius();
                if (distance <= radius)
                    enemy->kill();
            }
        }
        //solve colision
        if (explodedBomb->isDeployed()) {
            for (auto enemy : enemies){
                sf::FloatRect bounds = explodedBomb->getBounds();
                CollisionManager<Enemies> collision(enemy, bounds);
                if(collision.checkCollision()) {
                    enemy->set_direction((enemy->get_direction()+1)%4);
                    collision.solve();
                }
            }
        }
    }
}

void Maze::Update(Player& player, const float deltaTime) const {

    //solve player collisions
    for(const auto tile : Tiles){
        CollisionManager<Player> collision(&player, tile->getBounds());
        if (tile->detect_colision(player.getHitBox())){
            collision.solve();
        }
    }

    //Enemies move on maze
    int remaining = 0;
    for (const auto enemy : enemies) {
        if (enemy->get_life_status()) {
            remaining++;
            //enemies kill player
            CollisionManager<Enemies> colision(enemy, player.getHitBox());
            if (colision.checkCollision()) {
                    player.life_update();
                    player.restart();
                }
            int next_direction = enemy->get_direction();

            //solve colision for enemies
            for(const auto tile : Tiles){
            CollisionManager<Enemies> collision(enemy, tile->getBounds());
            if (tile->detect_colision(enemy->getHitBox())){
                collision.solve();
                next_direction = (next_direction+1)%4;
            }
            }
            enemy->Update(deltaTime, next_direction);
        }
    }
    //We unlock the exit if there are no enemies
    if (remaining == 0) {
        for (auto tile : Tiles) {
            if (const auto eXiT = dynamic_cast<Exit*>(tile)) {
                eXiT->unlock();
            }
        }
    }
}
Maze::Maze(const Maze &other) : width(other.width), height(other.height) {
    this->Tiles = other.Tiles;
    this->enemies = other.enemies;
    this->exit = other.exit;
}

Maze& Maze::operator=(const Maze &other) {
    this->Tiles = other.Tiles;
    this->enemies = other.enemies;
    this->exit = other.exit;
    return *this;
}

Maze::~Maze() {
    for (const auto* i : Tiles)
        delete i;
    Tiles.clear();
    for (const auto* i : enemies)
        delete i;
    enemies.clear();
}