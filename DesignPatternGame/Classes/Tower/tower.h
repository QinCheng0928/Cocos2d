#ifndef __TOWER_H__
#define __TOWER_H__

#include "cocos2d.h"
#include "../Enemies/Enemy.h"
#include "../Utils/Observer/observer.h"
#include "../Utils/Subject/subject.h"
#include <vector>

USING_NS_CC;

class Tower : public Sprite, public Observer {
protected:
    int level; // 等级
    int cost; // 成本
    int upgradeCost; // 升级费用
    float speed; // 攻击速度
    int damage; // 伤害
    float range; // 攻击范围
    int state; // 状态
    double squart;
    Vector<Enemy*> atk_enemies; // 攻击目标列表
    int maxLockNum; // 最大锁定数
public:
    Tower();
    virtual bool init();
    void onEnter();
    void onExit();
    void running_act();
    virtual void attack_act();
    Enemy* search();
    Vector<Enemy*> multiSearch();
    void set(int new_level, int new_cost, float new_speed, int new_damage, int new_range);
    int get_level();
    float get_distance(Enemy* enemy, Tower* tower);
    virtual int getCost();
    virtual void levelup(int) = 0;
    virtual std::string getPicName() = 0;
    void clickCallback();
    bool judgeListenerCallback(Touch* touch, Event* event);
    void remove_zidan(float dt);
    void update(float dt);

    // Observer方法
    void update(Subject* subject) override {
        Enemy* enemy = dynamic_cast<Enemy*>(subject);
        if (enemy) {
            handleEnemyUpdate(enemy);
        }
    }

private:
    void handleEnemyUpdate(Enemy* enemy);
};

#endif // __TOWER_H__