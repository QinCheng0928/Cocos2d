#ifndef __TOWER_H__
#define __TOWER_H__
#include "cocos2d.h"
#include "IEnemyObserver.h"
#include <vector>
USING_NS_CC;

class Enemy;

class Tower :public cocos2d::Sprite, public IEnemyObserver
{
protected:
	int level;//�ȼ�
	int cost;//����
	int upgradeCost;//��������
	float speed;//ÿ�ι����ļ��ʱ��
	int damage;//�˺�
	float squart;//������Χ
	int state;//״̬��������������״̬
	//enemy* attack_enemy;
	Vector<Enemy*>atk_eny;//�洢���е��б�
	int maxLockNum;//�����������
public:
	Tower();
	virtual bool init();
	//static tower* create(const std::string& filename);
	void onEnter();
	void onExit();
	void running_act();//��������
	virtual void attack_act();//��������
	Enemy* search();//�Ե������˽��������������������ã�
	Vector<Enemy*>multiSearch();//��һ�������������
	virtual void updateEnemyList(Enemy* enemy, bool isCreated);//���µ����б�

	void set(int new_level, int new_cost, float new_speed, int new_damage,int new_squart);//���ò���
	int got_level();//��ȡ�ȼ�
	float get_distance(Enemy* enemy,Tower* tower);//��ȡ����
	virtual int getCost();//��ȡ�۸�
	virtual void levelup(int) = 0;
	//��ȡ��Ӧ������ͼƬ
	virtual std::string getPicName() = 0;
	//�������ݻ������Ķ����˵�
	void clickCallback();
	//�ж��Ƿ�Ҫ�����ص�����
	bool judgeListenerCallback(cocos2d::Touch* touch, cocos2d::Event* event);
	void remove_zidan(float dt);//�Ƴ��ӵ�
	void update(float dt);
};


#endif