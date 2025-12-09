//
// Created by Daniel on 02.11.2025.
//

#ifndef OOP_MAZE_H
#define OOP_MAZE_H


#include<vector>
#include "tiles.h"
#include "Enemies.h"
#include "Player.h"
class Maze{
    const unsigned int width, height;
    std::vector<tiles*>Tiles;
    std::vector<Enemies*>enemies;
    sf::Vector2f exit;
public:
    [[nodiscard]]bool is_in_maze(float x, float y)const;
    Maze(unsigned int width, unsigned int height, sf::Vector2f exit);
    void load(const int* data);
    sf::Vector2f get_exit() const;
    void add_enemy(float position_x, float position_y);
    void drawMaze(sf::RenderWindow& window) const;
    bool check_for_colisions(sf::FloatRect& hitBox) const;
    void Update(Player& player, float deltaTime) const;
     Maze(const Maze& other);
    ~Maze();
     Maze& operator=(const Maze& other);
};

#endif //OOP_MAZE_H