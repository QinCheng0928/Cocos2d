#ifndef _LEVEL_2_H_
#define _LEVEL_2_H_

#include "cocos2d.h"
#include"baseLevel.h"

class Level_2 : public baseLevel
{
public:

    virtual bool init();

    virtual void spawnPointSet();
    virtual void pathSet();
    virtual void moneyAndHpSet();
    virtual void waveSet();
    virtual void restart();

    CREATE_FUNC(Level_2);
};

#endif // __LEVEL_2_SCENE_H__