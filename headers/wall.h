//
// Created by Daniel on 04.12.2025.
//

#ifndef OOP_WALL_H
#define OOP_WALL_H

#include "tiles.h"

class wall: public tiles {
public:
    wall(unsigned int position_x, unsigned int position_y);
    bool detect_colision(sf::FloatRect hitBox) override;
    tiles* clone() override;
};


#endif //OOP_WALL_H