#ifndef __ENEMY_H__
#define __ENEMY_H__
#include "Enemy.h"

class Enemy {
public:
    virtual Enemy* createEnemy() = 0; 
    virtual ~Enemy() {}
};

#endif
