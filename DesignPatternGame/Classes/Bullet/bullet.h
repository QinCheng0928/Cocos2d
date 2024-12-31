#ifndef __BULLET_H__
#define __BULLET_H__
#include "cocos2d.h"
#include "../Enemies/enemy.h"
#include "../Level/baseLevel.h"
USING_NS_CC;
/*子弹类实现*/

// 组件接口
class bulletComponent : public Sprite {
public:
	virtual void causeDamage() = 0;
	virtual void update(float dt) = 0;
	virtual void trackAndAttack(float dt) = 0;
	virtual void setTrack(enemy* trackIt) = 0;  // 锁定敌人
	virtual void setSpeed(int newSpeed) = 0;  // 设置飞行速度
	virtual void setDamage(int damage) = 0;   // 设置伤害
	virtual float get_distance(enemy* enemy, bulletComponent* bullet) = 0;//计算子弹与敌人的距离
};

// 具体组件
class bullet :public bulletComponent {
protected:
	int speed;//子弹移速 // ——公共
	int damage;//子弹伤害 // ——公共
	enemy* trackEnemy;//子弹锁定的敌人 // ——公共
public:
	int state;//状态
	bullet();//构造函数
	virtual bool init();
	void onEnter();//初始化函数
	static bullet* create(const std::string& filename);//创建函数
	void update(float dt) override;//计时器函数
	void trackAndAttack(float dt) override;//计时器下调用的函数，搜索敌人，如果搜索成功则进行攻击
	void setTrack(enemy* trackIt) override;//设置锁敌
	void setSpeed(int newSpeed) override;//设置飞行速度
	void setDamage(int damage) override;
	float get_distance(enemy* enemy, bulletComponent* bullet) override;
	void causeDamage() override;// 重写，每种子弹伤害方式不同
};

// 装饰器抽象类
class BulletDecorator :public bulletComponent {
protected:
	bulletComponent* baseBullet;
public:
	BulletDecorator(bulletComponent* baseBullet): baseBullet(baseBullet){}
	virtual void causeDamage() override {
		baseBullet->causeDamage();
	}
	void update(float dt) override {
		baseBullet->update(dt);
	}
	void trackAndAttack(float dt) override {
		baseBullet->trackAndAttack(dt);
	}
	void setTrack(enemy* trackIt) override {
		baseBullet->setTrack(trackIt);  // 调用基础子弹的锁定敌人方法
	}
	void setSpeed(int newSpeed) override {
		baseBullet->setSpeed(newSpeed);  // 调用基础子弹的设置速度方法
	}
	void setDamage(int damage) override {
		baseBullet->setDamage(damage);  // 调用基础子弹的设置伤害方法
	}
	float get_distance(enemy* enemy, bulletComponent* bullet) override {
		return baseBullet->get_distance(enemy, bullet);
	}
};

class ExplodeDecorator :public BulletDecorator {
	int boomDamage;
public:
	ExplodeDecorator(bulletComponent* wrappee);
	void causeDamage() override;
	void setBoomDamage(int damage);
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