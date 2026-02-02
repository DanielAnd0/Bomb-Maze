//
// Created by Daniel on 02.11.2025.
//

#ifndef OOP_MAZE_H
#define OOP_MAZE_H


#include<vector>
#include "tiles.h"
#include "Enemies.h"
#include "Player.h"
#include "observer.h"



class Maze : public Observer{
    const unsigned int width, height;
    std::vector<tiles*>Tiles;
    std::vector<Enemies*>enemies;
    sf::Vector2f exit;
public:
    [[nodiscard]]bool is_in_maze(float x, float y)const;
    Maze(unsigned int width, unsigned int height);
    void load(const int* data);
    [[nodiscard]] sf::Vector2f get_exit() const;
    void add_enemy(float position_x, float position_y);
    void drawMaze(sf::RenderWindow& window) const;
    void Update(Subject* theChangedSubject) override;
    void Update(Player& player, float deltaTime) const;
     Maze(const Maze& other);
    ~Maze() override;
     Maze& operator=(const Maze& other);
};

#endif //OOP_MAZE_H