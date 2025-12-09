//
// Created by Daniel on 02.11.2025.
//

#include<iostream>
#include "Maze.h"
#include <cmath>

#include "Exceptions.h"
#include "wall.h"
#include "falseWall.h"
#include "path.h"
#include "Exit.h"

bool Maze::is_in_maze(const float x, const float y) const {
    if (x < 0 || x >= width*tiles::getsize().x || y < 0 || y >= height*tiles::getsize().y) return false;
    return true;
}

Maze::Maze(const unsigned int width, const unsigned int height, const sf::Vector2f exit):width(width), height(height){
    if (!is_in_maze(exit.x, exit.y)) {throw NotInMaze(exit.x, exit.y);}
    this->exit.x = exit.x;
    this->exit.y = exit.y;
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
                switch (Number) {
                    case 3:
                        Tiles.push_back(new Exit(i*tile_size.x, j*tile_size.y));
                        break;
                    case 2:
                        Tiles.push_back(new wall(i*tile_size.x, j*tile_size.y));
                        break;
                    case 1:
                        Tiles.push_back(new path(i*tile_size.x, j*tile_size.y));
                        break;
                    case 0:
                        Tiles.push_back(new falseWall(i*tile_size.x, j*tile_size.y));
                        break;
                    default:
                        throw InvalidTileNumber(Number);
                }
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
bool Maze::check_for_colisions(sf::FloatRect& hitBox) const {
    for (const auto tile : Tiles){
            if (tile->detect_colision(hitBox) == true)
                return true;
    }
    return false;
}
void Maze::Update(Player& player, const float deltaTime) const {
    //Check if bomb is exploded
    const sf::Vector2 bomb_explosion = player.get_bomb().getPosition();
    if (!is_in_maze(bomb_explosion.x, bomb_explosion.y) && player.get_bomb().isDeployed())throw NotInMaze(bomb_explosion.x, bomb_explosion.y);
    if (player.get_bomb().isExploded()){
        for (const auto tile : Tiles) {
            //bomb destroy falseWalls
            if (const auto is_false_wall = dynamic_cast<falseWall*>(tile)) {
                sf::Vector2f center_of_tile = is_false_wall->get_position();
                center_of_tile.x += static_cast<float>(tiles::getsize().x) / 2.f;
                center_of_tile.y += static_cast<float>(tiles::getsize().y) / 2.f;
                float distance = std::sqrt((center_of_tile.x-bomb_explosion.x)*(center_of_tile.x-bomb_explosion.x) + (center_of_tile.y-bomb_explosion.y)*(center_of_tile.y-bomb_explosion.y));
                float radius = player.get_bomb().get_radius();
                if (distance <= radius)
                    is_false_wall->destroy();
            }
        }
        //Bomb destroys enemy
        for (const auto enemy : enemies) {
            const float center_x = enemy->getHitBox().getCenter().x;
            const float center_y = enemy->getHitBox().getCenter().y;
            float distance = std::sqrt((center_x-bomb_explosion.x)*(center_x-bomb_explosion.x) + (center_y-bomb_explosion.y)*(center_y-bomb_explosion.y));
            float radius = player.get_bomb().get_radius();
            if (distance <= radius)
                enemy->kill();
        }
        //Bomb destroys player
        const float center_x = player.getHitBox().getCenter().x;
        const float center_y = player.getHitBox().getCenter().y;
        float distance = std::sqrt((center_x-bomb_explosion.x)*(center_x-bomb_explosion.x) + (center_y-bomb_explosion.y)*(center_y-bomb_explosion.y));
        float radius = player.get_bomb().get_radius();
        if (distance <= radius) {
            player.life_update();
            player.restart();
        }
    }

    //Enemies move on maze
    int remaining = 0;
    for (const auto enemy : enemies) {
        if (enemy->get_life_status()){
            remaining++;
            //check for deployed bombs
            int direction = enemy->get_direction();
            sf::FloatRect hitBox = enemy->getHitBox();
            if (check_for_colisions(hitBox) || (player.get_bomb().isDeployed() && hitBox.contains(player.get_bomb().getPosition()))) {
                enemy->change_position(enemy->get_direction(), (-enemy->get_speed()*deltaTime));
                srand(time(nullptr));
                direction = rand() % 4;
            }

            enemy->Update(deltaTime, direction);
            //check for colisions with player
            sf::FloatRect playerHitBox = player.getHitBox();
            if (playerHitBox.findIntersection(hitBox)) {
                player.life_update();
                player.restart();
            }
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