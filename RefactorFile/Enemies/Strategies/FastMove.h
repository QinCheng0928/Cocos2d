#ifndef __FASTMOVE_H__
#define __FASTMOVE_H__
#include "MoveStrategy.h"

class FastMove : public MoveStrategy {
public:
    virtual void move(Enemy* enemy, float speed, float dt) override;
    virtual ~FastMove() {};
};

#endif
