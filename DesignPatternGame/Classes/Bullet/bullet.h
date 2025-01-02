#ifndef __BULLET_H__
#define __BULLET_H__
#include "cocos2d.h"
#include "../Enemies/Enemy.h"
#include "../Level/baseLevel.h"
USING_NS_CC;
/*子弹类实现*/

//// 组件接口
//class bulletComponent : public Sprite {
//public:
//	virtual void causeDamage() = 0;
//	virtual void update(float dt) = 0;
//	virtual void trackAndAttack(float dt) = 0;
//	virtual float get_distance(enemy* enemy, bulletComponent* bullet) = 0;//计算子弹与敌人的距离
//};

// 具体组件——普通子弹
class bullet :public Sprite {
protected:
	int speed;//子弹移速
	int damage;//子弹伤害
	int boomDamage;//子弹爆炸伤害
	Enemy* trackEnemy;//子弹锁定的敌人
public:
	int state;//状态
	bullet();//构造函数
	bullet(const bullet& other);  // 复制构造函数
	virtual bool init();
	void onEnter();//初始化函数
	static bullet* create(const std::string& filename);//创建函数
	void update(float dt);//计时器函数
	void trackAndAttack(float dt);//计时器下调用的函数，搜索敌人，如果搜索成功则进行攻击
	void setTrack(enemy* trackIt);//设置锁敌
	void setSpeed(int newSpeed);//设置飞行速度
	void setDamage(int damage);
	float get_distance(enemy* enemy, bullet* bullet);
	virtual void causeDamage();// 重写，每种子弹伤害方式不同
};

//// 装饰器抽象类
//class BulletDecorator :public bulletComponent {
//protected:
//	bulletComponent* baseBullet;
//public:
//	BulletDecorator(bulletComponent* baseBullet): baseBullet(baseBullet){}
//	virtual void causeDamage() override {
//		baseBullet->causeDamage();
//	}
//	void update(float dt) override {
//		baseBullet->update(dt);
//	}
//	void trackAndAttack(float dt) override {
//		baseBullet->trackAndAttack(dt);
//	}
//	float get_distance(enemy* enemy, bulletComponent* bullet) override {
//		return baseBullet->get_distance(enemy, bullet);
//	}
//};

class ExplodeDecorator :public bullet {
	int boomDamage;
public:
	ExplodeDecorator(bullet* wrappee);
	static ExplodeDecorator* create(const std::string& filename, bullet* wrappee);
	void causeDamage() override;
	void setBoomDamage(int damage);
	Vector<enemy*> multiSearch();
	void booom();
};

class NoxDecorator :public bullet {
	int noxDamage;
public:
	NoxDecorator(bullet* wrappee);
	static NoxDecorator* create(const std::string& filename, bullet* wrappee);//创建函数
	void setNoxDamage(int damage);
	void causeDamage() override;
};

// 毒气类，用于造成持续伤害
class Nox :public Sprite {
	int noxDamage;
	enemy* trackEnemy;
public:
	Nox();//构造函数
	virtual bool init();
	void onEnter();//初始化函数
	static Nox* create(const std::string& filename);//创建函数
	void setNoxDamage(int damage);
	void setTrack(enemy* enemy);
	void noxHit(float dt);
	void noxDown(float dt);
};


#endif