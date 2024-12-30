#ifndef __ENEMY3_H__
#define __ENEMY3_H__
#include "cocos2d.h"
#include "enemy.h"
USING_NS_CC;
class zy :public enemy {
public:
	virtual bool init();
	static zy* create();
	zy();
};
#endif