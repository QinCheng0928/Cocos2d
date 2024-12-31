#ifndef __ENEMY_H__
#define __ENEMY_H__
#include "cocos2d.h"
#include "../Block/baseBlock.h"
USING_NS_CC;
class enemy :public cocos2d::Sprite
{
protected:
	int value;//��ֵ
	float speed;//�ƶ��ٶ�
	int hp;//Ѫ��
	int maxnhp;//���Ѫ��
	float speedScale;//�ٶȱ���
	PathBlock* nextPosition;//Ҫ�ƶ�������һ������
public:
	enemy();
	virtual bool init();
	static enemy* create(const std::string& filename);
	void set_hp_scale(int key);//����Ѫ������
	void onEnter();
	void get_hit(int damage);//�ܻ�����
	void move(float dt);//�ƶ�����
	void update(float dt);   //ÿһ֡����
	virtual void show();//������Ϣ������̨���
	void showhp();//��ʾѪ���Լ�Ѫ��
	float getSpeedScale();
	void setSpeedScale(float s);//�����ٶȱ���
};

#endif