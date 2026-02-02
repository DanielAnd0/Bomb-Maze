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
    bool get_status() const;
    void destroy();
    bool detect_colision(sf::FloatRect hitBox) override;
    tiles* clone() override;
};

#endif //OOP_FALSEWALL_H