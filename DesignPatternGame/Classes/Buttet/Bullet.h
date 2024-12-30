#ifndef __BULLET_H__
#define __BULLET_H__
#include "cocos2d.h"
#include "../Enemies/enemy.h"
#include "../Level/baseLevel.h"
USING_NS_CC;
/*�ӵ���ʵ��*/
class bullet :public Sprite {
protected:
	int speed;//�ӵ�����
	int damage;//�ӵ��˺�
	int boomDamage;//�ӵ���ը�˺�
	enemy* trackEnemy;//�ӵ������ĵ���
public:
	int state;//״̬
	bullet();//���캯��
	virtual bool init();
	void onEnter();//��ʼ������
	void update(float dt);//��ʱ������
	static bullet* create(const std::string& filename);//��������
	void setTrack(enemy* trackIt);//��������
	void setSpeed(int newSpeed);//���÷����ٶ�
	void trackAndAttack(float dt);//��ʱ���µ��õĺ������������ˣ���������ɹ�����й���
	void removeBullet(float dt);//�Ӹ����Ƴ��ӵ�
	void booom(float dt);//�ӵ���ը��ʵ��
	float get_distance(enemy* enemy, bullet* bullet);//�����ӵ�����˵ľ���
	Vector<enemy*> bullet::multiSearch();//�������ˣ����ط��ϵ��ڵĵ�������
};

#endif