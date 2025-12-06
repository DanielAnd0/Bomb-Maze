//
// Created by Daniel on 02.11.2025.
//

#include<iostream>
#include "Maze.h"
#include "wall.h"
#include "falseWall.h"
#include "path.h"

bool Maze::is_in_maze(const int x, const int y) const {
    if (x < 0 || x >= width*tiles::getsize().x || y < 0 || y >= height*tiles::getsize().y) return false;
    return true;
}

Maze::Maze(const unsigned int width, const unsigned int height, const sf::Vector2u exit):width(width), height(height){
    this->exit.x = exit.x;
    this->exit.y = exit.y;
}
void Maze::loadtiles(const int* tilesData) {
    for (unsigned int i = 0; i < width; i++)
        for (unsigned int j = 0; j < height; j++) {
            sf::Vector2u tile_size = tiles::getsize();
            const int tileNumber = tilesData[i + j * width];
            constexpr int wallNumber = 2;
            constexpr int falseWallNumber = 0;
            constexpr int pathNumber = 1;
            switch (tileNumber) {
                case wallNumber:
                    Tiles.push_back(new wall(i*tile_size.x, j*tile_size.y));
                    break;
                case pathNumber:
                    Tiles.push_back(new path(i*tile_size.x, j*tile_size.y));
                    break;
                case falseWallNumber:
                    Tiles.push_back(new falseWall(i*tile_size.x, j*tile_size.y));
                    break;
                default:
                    break;
            }
        }
}
void Maze::drawMaze(sf::RenderWindow& window) const {
    for (const auto tile : Tiles) {
        tile->drawTile(window);
    }
}
bool Maze::can_player_move(Player &player) const {
    for (const auto tile : Tiles){
        if (tile->detect_colision(player) == true)
        return true;
    }
    return false;
}
Maze::~Maze() {
    for (const auto* i : Tiles)
        delete i;
    Tiles.clear();
}


/*
Maze::Maze(const Maze& other) : exit{other.exit.x,other.exit.y} {
    rows = other.rows;
    cols = other.cols;
    if (other.player)
        player = new Player(*other.player);
    else
        player = nullptr;
    for (auto i : other.enemies)
        enemies.push_back(i);
}
*/
/*
Maze& Maze::operator=(const Maze& other) {
    if (this != &other) {
        rows = other.rows;
        cols = other.cols;
        exit.x = other.exit.x;
        exit.y = other.exit.y;
        player = other.player;
        for (auto i : other.enemies) {
            enemies.clear();
            enemies.push_back(i);
        }
    }
    return *this;
}
ostream& operator<<(ostream& os, const Maze& maze) {
    for (int i = 0; i < maze.rows; i++) {
        for (int j = 0; j < maze.cols; j++) {
            os<<maze.maze[i][j]<<" ";
        }
        os<<endl;
    }
    os << *maze.player;
    if (maze.enemies.size() != 0) {
        for (const auto i : maze.enemies) {
            os << i;
        }
    }
    return os;
}
int Maze::checkGame() const{ //return 0 daca s-a terminat jocul
    int pos_x = player->get_position_x();
    int pos_y = player->get_position_y();
    if (pos_x == exit.x && pos_y == exit.y && enemies.size() == 0) {
        cout<<"----------"<<endl;
        cout<<"GAME WON!"<<endl;
        cout<<"----------"<<endl;
        return 0;
    }
    if (player->get_life_status()==false) {
        cout<<"----------"<<endl;
        cout<<"GAME OVER!"<<endl;
        cout<<"----------"<<endl;
        return 0;
    }
    return 1;
}
*/