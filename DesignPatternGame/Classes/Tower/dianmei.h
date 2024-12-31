#ifndef __dianmei_H__
#define __dianmei_H__
#include "cocos2d.h"
#include "Tower.h"
#include "../Enemies/Enemy.h"
USING_NS_CC;
class dianmei :public Tower {
public:
	dianmei();
	virtual bool init();
	static dianmei* create();
	void onEnter();
	virtual void levelup(int key);
	void dianmei::attackOneEnemy(Enemy* attack_enemy);
	virtual void attack_act();
	virtual std::string getPicName();
	void updateEnemyList(Enemy* e, bool isCreated);//更新敌人列表
};
#endif