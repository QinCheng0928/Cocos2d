#ifndef __ENEMY_H__
#define __ENEMY_H__
#include "cocos2d.h"
USING_NS_CC;
class enemy :public cocos2d::Sprite
{
private:
	int speed;
	int hp;
public:
	virtual bool init();
	static enemy* create(const std::string& filename);
	void onEnter();
	void get_hit(int damage);
	void move();
	void update(float dt);   
	void Move(float dt);
	void show();
	void showhp();
};

#endif