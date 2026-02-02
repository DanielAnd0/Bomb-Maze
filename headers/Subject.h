//
// Created by Daniel on 29.01.2026.
//

#ifndef OOP_SUBJECT_H
#define OOP_SUBJECT_H

#include <iostream>
#include <SFML/Graphics.hpp>

class Observer;

class Subject {
public:
    virtual ~Subject();
    virtual void Attach(Observer*);
    virtual void Detach(Observer*);
    virtual void Notify();
protected:
    Subject() = default;
private:
    std::vector<Observer*> _observers;
};



#endif //OOP_SUBJECT_H