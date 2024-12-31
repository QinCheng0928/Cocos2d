#ifndef __BULLET_H__
#define __BULLET_H__
#include "cocos2d.h"
#include "../Enemies/enemy.h"
#include "../Level/baseLevel.h"
USING_NS_CC;
/*子弹类实现*/
class bullet :public Sprite {
protected:
	int speed;//子弹移速 // ——公共
	int damage;//子弹伤害 // ——公共
	enemy* trackEnemy;//子弹锁定的敌人 // ——公共
public:
	int state;//状态
	bullet();//构造函数
	virtual bool init();
	void onEnter();//初始化函数
	void update(float dt);//计时器函数
	static bullet* create(const std::string& filename);//创建函数
	void setTrack(enemy* trackIt);//设置锁敌
	void setSpeed(int newSpeed);//设置飞行速度
	void setDamage(int damage);
	void trackAndAttack(float dt);//计时器下调用的函数，搜索敌人，如果搜索成功则进行攻击
	virtual void causeDamage();// 重写，每种子弹伤害方式不同
	// void booom(float dt);//子弹爆炸的实现
	float get_distance(enemy* enemy, bullet* bullet);//计算子弹与敌人的距离
};

class ExplodeBullet :public bullet {
	int boomDamage;
public:
	ExplodeBullet();
	static ExplodeBullet* create(const std::string& filename);//创建函数
	void setBoomDamage(int damage);
	void causeDamage();
	Vector<enemy*> multiSearch();
	void booom();
};

class NoxBullet :public bullet {
	int noxDamage;
public:
	NoxBullet();
	static NoxBullet* create(const std::string& filename);//创建函数
	void setNoxDamage(int damage);
	void causeDamage();
	void noxHit(float dt);
	void noxDown(float dt);
};

#endif