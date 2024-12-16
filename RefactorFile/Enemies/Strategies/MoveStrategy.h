#ifndef __MOVESTRATEGY_H__
#define __MOVESTRATEGY_H__
#include "Enemy.h"

class MoveStrategy {
public:
    virtual void move(Enemy* enemy, float speed, float dt) = 0;  // Virtual function for moving
    virtual ~MoveStrategy() {};
};

#endif
