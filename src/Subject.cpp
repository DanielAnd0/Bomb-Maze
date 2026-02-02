//
// Created by Daniel on 29.01.2026.
//

#include "../headers/Subject.h"
#include "../headers/observer.h"

void Subject::Attach (Observer* o) {_observers.push_back(o); }
void Subject::Detach (Observer* o) {
    for (auto it = _observers.begin(); it != _observers.end(); )
    {
        if (*it == o)
            it = _observers.erase(it);
        else
            ++it;
    }
}
void Subject::Notify(){
    for (auto & _observer : _observers) {
        _observer->Update(this);
    }
}
Subject::~Subject() {
    _observers.clear();
}
