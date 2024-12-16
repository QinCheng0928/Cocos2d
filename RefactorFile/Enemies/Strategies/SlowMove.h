#ifndef __SLOWMOVE_H__
#define __SLOWMOVE_H__
#include "MoveStrategy.h"

class SlowMove : public MoveStrategy {
public:
    virtual void move(Enemy* enemy, float speed, float dt) override;
    virtual ~SlowMove() {}
};

#endif
