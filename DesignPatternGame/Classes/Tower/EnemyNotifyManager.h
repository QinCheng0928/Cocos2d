#ifndef __ENEMY_NOTIFY_MANAGER_H__
#define __ENEMY_NOTIFY_MANAGER_H__

#include "cocos2d.h"
#include <vector>
#include "IEnemyObserver.h"

USING_NS_CC;

// 前向声明
class Enemy;

class EnemyNotifyManager {
private:
    static EnemyNotifyManager* instance;
    std::vector<IEnemyObserver*> observers;

    EnemyNotifyManager() {}  // 修正构造函数，移除递归创建

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
