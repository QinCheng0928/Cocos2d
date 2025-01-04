#ifndef __BULLET_H__
#define __BULLET_H__
#include "cocos2d.h"
#include "../Enemies/Enemy.h"
#include "../Level/baseLevel.h"
USING_NS_CC;
/*子弹类实现*/

// 具体组件——普通子弹
class Bullet :public Sprite {
protected:
	int speed;//子弹移速
	int damage;//子弹伤害
	int boomDamage;//子弹爆炸伤害
	Enemy* trackEnemy;//子弹锁定的敌人
public:
	int state;//状态
	Bullet();//构造函数
	Bullet(const Bullet& other);  // 复制构造函数
	virtual bool init();
	void onEnter();//初始化函数
	static Bullet* create(const std::string& filename);//创建函数
	void update(float dt);//计时器函数
	void trackAndAttack(float dt);//计时器下调用的函数，搜索敌人，如果搜索成功则进行攻击
	void setTrack(Enemy* trackIt);//设置锁敌
	void setSpeed(int newSpeed);//设置飞行速度
	void setDamage(int damage);
	float get_distance(Enemy* enemy, Bullet* bullet);
	virtual void causeDamage();// 重写，每种子弹伤害方式不同
};

class ExplodeDecorator :public Bullet {
	int boomDamage;
public:
	ExplodeDecorator(Bullet* wrappee, int damage);
	static ExplodeDecorator* create(const std::string& filename, Bullet* wrappee, int damage);
	void causeDamage() override;
	Vector<Enemy*> multiSearch();
	void booom();
};

class NoxDecorator :public Bullet {
	int noxDamage;
public:
	NoxDecorator(Bullet* wrappee, int damage);
	static NoxDecorator* create(const std::string& filename, Bullet* wrappee, int damage);//创建函数
	void causeDamage() override;
};

// 毒气类，用于造成持续伤害
class Nox :public Sprite {
	int noxDamage;
	Enemy* trackEnemy;
public:
	Nox();//构造函数
	virtual bool init();
	void onEnter();//初始化函数
	static Nox* create(const std::string& filename);//创建函数
	void setNoxDamage(int damage);
	void setTrack(Enemy* enemy);
	void noxHit(float dt);
	void noxDown(float dt);
};


#endif