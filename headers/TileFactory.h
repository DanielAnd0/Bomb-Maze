//
// Created by Daniel on 30.01.2026.
//

#ifndef OOP_TILEFACTORY_H
#define OOP_TILEFACTORY_H

#include <iostream>
#include "../headers/Exit.h"
#include "../headers/wall.h"
#include "../headers/path.h"
#include "../headers/falseWall.h"
#include "../headers/Exceptions.h"


enum class TileType {
    FalseWall = 0,
    Path  = 1,
    Wall  = 2,
    Exit  = 3
};

class TileFactory {
public:
    static tiles* create(TileType type, const unsigned int x, const unsigned int y)
    {
        switch (type) {
            case TileType::Exit:
                return new Exit(x, y);
            case TileType::Wall:
                return new wall(x, y);
            case TileType::Path:
                return new path(x, y);
            case TileType::FalseWall:
                return new falseWall(x, y);
            default:
                throw InvalidTileNumber(static_cast<int>(type));
        }
    }
};


#endif //OOP_TILEFACTORY_H