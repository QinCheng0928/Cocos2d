#ifndef __FlameTower_H__
#define __FlameTower_H__
#include "cocos2d.h"
#include "Tower.h"
#include "../Enemies/Enemy.h"
USING_NS_CC;
class FlameTower :public Tower {
public:
	FlameTower();
	virtual bool init();
	static FlameTower* create();
	void onEnter();
	virtual void levelup(int key);
	void FlameTower::attackOneEnemy(Enemy* attack_enemy);
	virtual void attack_act();
	virtual std::string getPicName();
	void updateEnemyList(Enemy* e, bool isCreated);//更新敌人列表
};
#endif