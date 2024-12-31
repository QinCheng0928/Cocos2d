#ifndef __ENEMY_NOTIFY_MANAGER_H__
#define __ENEMY_NOTIFY_MANAGER_H__

#include "cocos2d.h"
#include <vector>
#include "Tower/Tower.h"
#include "Enemies/Enemy.h"

USING_NS_CC;

class EnemyNotifyManager {
private:
    static EnemyNotifyManager* instance;
    std::vector<Tower*> towers;

    EnemyNotifyManager() {
        instance = new EnemyNotifyManager();
    }

public:
    static EnemyNotifyManager* getInstance() {
        if (instance == nullptr) {
            instance = new EnemyNotifyManager();
        }
        return instance;
    }

    void addTower(Tower* tower) {
        towers.push_back(tower);
    }

    void removeTower(Tower* tower) {
        auto it = std::find(towers.begin(), towers.end(), tower);
        if (it != towers.end()) {
            towers.erase(it);
        }
    }

    // isCreated: true表示敌人创建，false表示敌人死亡
    void notifyTowers(Enemy* enemy, bool isCreated) {
        for (auto tower : towers) {
            tower->updateEnemyList(enemy, isCreated);
        }
    }
};

#endif // __ENEMY_NOTIFY_MANAGER_H__
