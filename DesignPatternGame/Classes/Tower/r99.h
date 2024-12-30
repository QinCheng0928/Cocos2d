#ifndef __R99_H__
#define __R99_H__
#include "cocos2d.h"
#include "tower.h"
#include "../Enemies/Enemy.h"
USING_NS_CC;
class r99 :public Tower {
public:
	int counter;//已经打出的子弹数量
	r99();
	int getDamage();//返回子弹伤害
	virtual bool init();
	static r99* create();
	void onEnter();
	void levelup(int key);//升级
	void dadada();//子弹攻击相关
	void load();//装载相关
	void start(float dt);//初始化子弹数目，启动侦测函数
	void bulletCounter(float dt);//子弹数目侦测
	void attackOneEnemy(Enemy* attack_enemy);//攻击一个敌人相关
	virtual void attack_act();//攻击动作相关
	virtual std::string getPicName();//获取升级图片
};
#endif