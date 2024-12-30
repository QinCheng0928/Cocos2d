#ifndef __p_H__
#define __p_H__
#include "cocos2d.h"
#include "tower.h"
#include "../Enemies/Enemy.h"
#include "../Buttet/Bullet.h"
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
	int getNoxDamage();//��ȡ�����˺�
	int getBooomDamage();//��ȡ��������ը�˺�
	virtual void levelup(int key);
	void attackOneEnemy(Enemy* attack_enemy);
	virtual void attack_act();
	virtual std::string getPicName();
	void remove_zidan(float dt);
};
#endif