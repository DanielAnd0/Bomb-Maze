//
// Created by Daniel on 04.12.2025.
//

#ifndef OOP_PATH_H
#define OOP_PATH_H

#include "tiles.h"

class path: public tiles{
public:
    path(unsigned int position_x, unsigned int position_y);
    bool detect_colision(Player &player) override;
};

#endif //OOP_PATH_H