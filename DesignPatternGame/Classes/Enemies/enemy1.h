#ifndef __ENEMY1_H__
#define __ENEMY1_H__
#include "cocos2d.h"
#include "enemy.h"
USING_NS_CC;
class mike :public enemy {
public:
	virtual bool init();
	static mike* create();
	mike();
};
#endif