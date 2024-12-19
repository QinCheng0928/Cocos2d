#ifndef __dianmei_H__
#define __dianmei_H__
#include"cocos2d.h"
#include"tower.h"
#include"enemy.h"
USING_NS_CC;

class dianmei :public tower {
public:
	dianmei();
	virtual bool init();
	static dianmei* create();
	void onEnter();
	virtual void levelup(int key);
	void dianmei::attackOneEnemy(enemy* attack_enemy);
	virtual void attack_act();
	virtual std::string getPicName();
};
#endif