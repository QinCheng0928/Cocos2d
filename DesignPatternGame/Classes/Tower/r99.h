#ifndef __R99_H__
#define __R99_H__
#include "cocos2d.h"
#include "tower.h"
#include "../Enemies/Enemy.h"
USING_NS_CC;
class r99 :public Tower {
public:
	int counter;//�Ѿ�������ӵ�����
	r99();
	int getDamage();//�����ӵ��˺�
	virtual bool init();
	static r99* create();
	void onEnter();
	void levelup(int key);//����
	void dadada();//�ӵ��������
	void load();//װ�����
	void start(float dt);//��ʼ���ӵ���Ŀ��������⺯��
	void bulletCounter(float dt);//�ӵ���Ŀ���
	void attackOneEnemy(Enemy* attack_enemy);//����һ���������
	virtual void attack_act();//�����������
	virtual std::string getPicName();//��ȡ����ͼƬ
};
#endif