#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include"tower.h"
#include"enemy.h"
#include"enemy1.h"
#include"enemy2.h"
#include"enemy3.h"
#include"dianmei.h"

USING_NS_CC;
class zzytest : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(zzytest);
};


#endif