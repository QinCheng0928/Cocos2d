#ifndef __ENEMY2_H__
#define __ENEMY2_H__
#include "cocos2d.h"
#include "enemy.h"
USING_NS_CC;
class nongp :public enemy {
public:
	virtual bool init();
	static nongp* create();
	nongp();
};
#endif