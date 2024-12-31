#ifndef _LEVEL_1_H_
#define _LEVEL_1_H_

#include "cocos2d.h"
#include "../Level/baseLevel.h"

class Level_1 : public baseLevel
{
public:

    virtual bool init();

    virtual void spawnPointSet();
    virtual void pathSet();
    virtual void moneyAndHpSet();
    virtual void waveSet();
    virtual void restart();

    CREATE_FUNC(Level_1);
};

#endif // __LEVEL_1_SCENE_H__