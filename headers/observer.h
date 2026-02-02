

#ifndef OOP_OBSERVER_H
#define OOP_OBSERVER_H

class Subject;

class Observer{
public:
        virtual ~Observer() = default;
        virtual void Update(Subject* theChangedSubject) = 0;
protected:
        Observer() = default;
};


#endif //OOP_OBSERVER_H