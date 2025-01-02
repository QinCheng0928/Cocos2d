#ifndef __p_H__
#define __p_H__
#include "cocos2d.h"
#include "Tower.h"
#include "../Enemies/Enemy.h"
#include "../Bullet/bullet.h"
USING_NS_CC;
class p :public Tower {
private:
	int noxDamage;
	int booomDamage;
public:
	p();
	virtual bool init();
	static p* create();
	void onEnter();
	int getNoxDamage();//获取毒气伤害
	int getBooomDamage();//获取毒气弹爆炸伤害
	virtual void levelup(int key);
	void attackOneEnemy(Enemy* attack_enemy);
	virtual void attack_act();
	virtual std::string getPicName();
	void remove_zidan(float dt);
	void updateEnemyList(Enemy* e, bool isCreated);//更新敌人列表
	void shootBoomBullet();
	void shootNoxBullet();
	void shootBoomAndNoxBullet();
};
#endif