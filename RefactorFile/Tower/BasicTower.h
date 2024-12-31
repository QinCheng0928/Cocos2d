#ifndef __BASIC_TOWER_H__
#define __BASIC_TOWER_H__

#include "tower.h"

class BasicTower : public Tower {
public:
    void updateEnemyList(Enemy* e, bool isCreated) override {
        if (isCreated) {
            // 检查敌人是否在攻击范围内
            if (get_distance(e, this) <= range) {
                // 检查是否未达到最大锁定数
                if (atk_enemies.size() < maxLockNum) {
                    atk_enemies.pushBack(e);
                }
            }
        } else {
            // 从攻击列表中移除死亡的敌人
            atk_enemies.eraseObject(e);
        }
    }
    
    // ...other BasicTower implementation...
};

#endif
