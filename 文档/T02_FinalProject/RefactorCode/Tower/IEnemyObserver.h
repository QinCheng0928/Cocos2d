#ifndef __I_ENEMY_OBSERVER_H__
#define __I_ENEMY_OBSERVER_H__

class Enemy;

class IEnemyObserver {
public:
    virtual ~IEnemyObserver() {}
    virtual void updateEnemyList(Enemy* enemy, bool isCreated) = 0;
};

#endif
