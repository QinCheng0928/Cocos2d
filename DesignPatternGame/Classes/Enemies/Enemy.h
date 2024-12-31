#ifndef __ENEMY_H__
#define __ENEMY_H__
#include "cocos2d.h"
#include "../Block/baseBlock.h"
USING_NS_CC;
class enemy :public cocos2d::Sprite
{
protected:
	int value;//价值
	float speed;//移动速度
	int hp;//血量
	int maxnhp;//最大血量
	float speedScale;//速度倍数
	PathBlock* nextPosition;//要移动到的下一个格子
public:
	enemy();
	virtual bool init();
	static enemy* create(const std::string& filename);
	void set_hp_scale(int key);//设置血量倍数
	void onEnter();
	void get_hit(int damage);//受击函数
	void move(float dt);//移动函数
	void update(float dt);   //每一帧更新
	virtual void show();//调试信息，控制台输出
	void showhp();//显示血量以及血条
	float getSpeedScale();
	void setSpeedScale(float s);//设置速度倍数
};

#endif