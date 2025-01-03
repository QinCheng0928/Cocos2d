#ifndef __p_H__
#define __p_H__
#include "cocos2d.h"
#include "Tower.h"
#include "../Enemies/Enemy.h"
#include "../Bullet/bullet.h"
USING_NS_CC;
class FrostTower :public Tower {
private:
	int noxDamage;
	int booomDamage;
public:
	FrostTower();
	virtual bool init();
	static FrostTower* create();
	void onEnter();
	int getNoxDamage();//��ȡ�����˺�
	int getBooomDamage();//��ȡ��������ը�˺�
	virtual void levelup(int key);
	void attackOneEnemy(Enemy* attack_enemy);
	virtual void attack_act();
	virtual std::string getPicName();
	void remove_zidan(float dt);
	void updateEnemyList(Enemy* e, bool isCreated);//���µ����б�
	void shootBoomBullet();
	void shootNoxBullet();
	void shootBoomAndNoxBullet();
};
#endif