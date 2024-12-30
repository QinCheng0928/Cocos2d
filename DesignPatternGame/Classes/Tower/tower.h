#ifndef __TOWER_H__
#define __TOWER_H__
#include "cocos2d.h"
#include "../Enemies/enemy.h"
#include <vector>
USING_NS_CC;
class tower :public cocos2d::Sprite
{
protected:
	int level;//等级
	int cost;//花费
	int upgradeCost;//升级花费
	float speed;//每次攻击的间隔时间
	int damage;//伤害
	float squart;//攻击范围
	int state;//状态，有搜索和锁敌状态
	//enemy* attack_enemy;
	Vector<enemy*>atk_eny;//存储锁敌的列表
	int maxLockNum;//最大锁敌人数
public:
	tower();
	virtual bool init();
	//static tower* create(const std::string& filename);
	void onEnter();
	void onExit();
	void running_act();//待机动作
	virtual void attack_act();//攻击动作
	enemy* search();//对单个敌人进行搜索并锁定（已弃用）
	Vector<enemy*>multiSearch();//对一至多个敌人锁定
	void set(int new_level, int new_cost, float new_speed, int new_damage,int new_squart);//设置参数
	int got_level();//获取等级
	float get_distance(enemy* enemy,tower* tower);//获取距离
	virtual int getCost();//获取价格
	virtual void levelup(int) = 0;
	//获取对应的升级图片
	virtual std::string getPicName() = 0;
	//升级、摧毁炮塔的二级菜单
	void clickCallback();
	//判断是否要触发回调函数
	bool judgeListenerCallback(cocos2d::Touch* touch, cocos2d::Event* event);
	void remove_zidan(float dt);//移除子弹
	void update(float dt);
};


#endif