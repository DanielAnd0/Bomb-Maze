//
// Created by Daniel on 02.11.2025.
//

#ifndef OOP_MAZE_H
#define OOP_MAZE_H


#include<vector>
#include "tiles.h"

class Maze{
    const unsigned int width, height;
    std::vector<tiles*>Tiles;
    sf::Vector2u exit;
    [[nodiscard]]bool is_in_maze(int x, int y)const;
public:
    Maze(unsigned int width, unsigned int height, sf::Vector2u exit);
    void loadtiles(const int* tiles);
    void drawMaze(sf::RenderWindow& window) const;
    bool can_player_move(Player& player) const;
    //Maze(const Maze& other);
    ~Maze();
 //   void create_maze();
   // Maze& operator=(const Maze& other);
 //   friend ostream& operator<<(ostream& os, const Maze& maze);
 //   int checkGame() const;
};

#endif //OOP_MAZE_H