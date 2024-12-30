#ifndef __SUBJECT_H__
#define __SUBJECT_H__

#include <vector>
#include "../Observer/observer.h"
#include <algorithm>

class Subject {
private:
    std::vector<Observer*> observers;
public:
    void addObserver(Observer* observer) {
        observers.push_back(observer);
    }

    void removeObserver(Observer* observer) {
        observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
    }

    void notifyObservers() {
        for(auto observer : observers) {
            observer->update(this);
        }
    }
};

#endif // __SUBJECT_H__