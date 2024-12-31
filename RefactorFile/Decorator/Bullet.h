#ifndef __BULLET_H__
#define __BULLET_H__
#include "cocos2d.h"
#include "enemy.h"
#include "baseLevel.h"
USING_NS_CC;
/*子弹类实现*/
class bullet :public Sprite {
protected:
	int speed;//子弹移速
	int damage;//子弹伤害
	int boomDamage;//子弹爆炸伤害
	enemy* trackEnemy;//子弹锁定的敌人
public:
	int state;//状态
	bullet();//构造函数
	virtual bool init();
	void onEnter();//初始化函数
	void update(float dt);//计时器函数
	static bullet* create(const std::string& filename);//创建函数
	void setTrack(enemy* trackIt);//设置锁敌
	void setSpeed(int newSpeed);//设置飞行速度
	void trackAndAttack(float dt);//计时器下调用的函数，搜索敌人，如果搜索成功则进行攻击
	void removeBullet(float dt);//从父类移除子弹
	void booom(float dt);//子弹爆炸的实现
	float get_distance(enemy* enemy, bullet* bullet);//计算子弹与敌人的距离
	Vector<enemy*> bullet::multiSearch();//搜索敌人，返回符合调节的敌人序列
};

class BulletComponent :public Sprite{
public:
	virtual void trackAndAttack(float dt) = 0;
}

#endif