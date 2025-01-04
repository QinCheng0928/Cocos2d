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
    std::vector<Enemy*> currentEnemies; // 新增：存活敌人列表

    // Private constructor to prevent external instantiation
    EnemyNotifyManager() {}
    // Disable copy constructor
    EnemyNotifyManager(const EnemyNotifyManager&) = delete; 
    // Disable assignment operator
    EnemyNotifyManager& operator=(const EnemyNotifyManager&) = delete; 


public:
    // Public static method to provide access to the Singleton instance
    static EnemyNotifyManager* getInstance() {
        if (instance == nullptr) {
            instance = new EnemyNotifyManager();
        }
        return instance;
    }

    void addObserver(IEnemyObserver* observer) {
        observers.push_back(observer);
        // 将现有敌人通知给新观察者
        for (auto e : currentEnemies) {
            observer->updateEnemyList(e, true);
        }
        CCLOG("EnemyNotifyManager: addObserver");
    }

    void removeObserver(IEnemyObserver* observer) {
        auto it = std::find(observers.begin(), observers.end(), observer);
        if (it != observers.end()) {
            observers.erase(it);
        }
    }

    void notifyObservers(Enemy* enemy, bool isCreated) {
        // 同步维护 currentEnemies
        if (isCreated) {
            currentEnemies.push_back(enemy);
        } else {
            auto it = std::find(currentEnemies.begin(), currentEnemies.end(), enemy);
            if (it != currentEnemies.end()) {
                currentEnemies.erase(it);
            }
        }

        for (auto observer : observers) {
            observer->updateEnemyList(enemy, isCreated);
            CCLOG("EnemyNotifyManager: notifyObservers");
        }
    }
};

#endif // __ENEMY_NOTIFY_MANAGER_H__
