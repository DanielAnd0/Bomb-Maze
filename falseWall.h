//
// Created by Daniel on 04.12.2025.
//

#ifndef OOP_FALSEWALL_H
#define OOP_FALSEWALL_H

#include "tiles.h"

class falseWall : public tiles {
    bool destroyed;
public:
    falseWall(unsigned int position_x, int unsigned position_y);
    void destroy();
    bool detect_colision(Player &player) override;
};

#endif //OOP_FALSEWALL_H