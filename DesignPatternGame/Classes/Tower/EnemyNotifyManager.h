#ifndef __ENEMY_NOTIFY_MANAGER_H__
#define __ENEMY_NOTIFY_MANAGER_H__

#include "cocos2d.h"
#include <vector>
#include "IEnemyObserver.h"

USING_NS_CC;

class Enemy;

class EnemyNotifyManager {
private:
    static EnemyNotifyManager* instance;
    std::vector<IEnemyObserver*> observers;

    // Fix the constructor to remove recursive creation
    EnemyNotifyManager() {}

public:
    static EnemyNotifyManager* getInstance() {
        if (instance == nullptr) {
            instance = new EnemyNotifyManager();
        }
        return instance;
    }

    void addObserver(IEnemyObserver* observer) {
        observers.push_back(observer);
    }

    void removeObserver(IEnemyObserver* observer) {
        auto it = std::find(observers.begin(), observers.end(), observer);
        if (it != observers.end()) {
            observers.erase(it);
        }
    }

    void notifyObservers(Enemy* enemy, bool isCreated) {
        for (auto observer : observers) {
            observer->updateEnemyList(enemy, isCreated);
        }
    }
};

#endif // __ENEMY_NOTIFY_MANAGER_H__
