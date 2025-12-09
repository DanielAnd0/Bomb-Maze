//
// Created by Daniel on 09.12.2025.
//

#ifndef OOP_EXIT_H
#define OOP_EXIT_H

#include "tiles.h"
class Exit : public tiles{
    bool locked = true;
public:
    Exit(unsigned int position_x, unsigned int position_y);
    bool detect_colision(sf::FloatRect &hitBox) override;
    void unlock();
    Exit* clone() override;
};


#endif //OOP_EXIT_H