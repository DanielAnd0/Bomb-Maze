
#ifndef OOP_COLLISIONMANAGER_H
#define OOP_COLLISIONMANAGER_H

#include <SFML/Graphics.hpp>

template <class T>
class CollisionManager {
    T* mover;
    sf::FloatRect solid;
public:
    CollisionManager(T* _mover, sf::FloatRect _solid):solid(_solid){
        mover = _mover;
    }
    bool checkCollision(){
        sf::FloatRect hitBox = mover->getHitBox();
        auto intersection = hitBox.findIntersection(solid);
        if (!intersection)
            return false;
        return true;
    }
    void solve(){

        sf::FloatRect hitBox = mover->getHitBox();
        auto intersection = hitBox.findIntersection(solid);
        if (!intersection)
            return;

        const sf::FloatRect& overlap = *intersection;
        if (overlap.size.x < overlap.size.y) {
            if (hitBox.position.x < solid.position.x)
                mover->change_position(2, overlap.size.x);
            else
                mover->change_position(3, overlap.size.x);
        } else {
            if (hitBox.position.y < solid.position.y)
                mover->change_position(0, overlap.size.y);
            else
                mover->change_position(1, overlap.size.y);
        }
    }
};


#endif //OOP_COLLISIONMANAGER_H