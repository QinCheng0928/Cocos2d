#ifndef __BULLET_H__
#define __BULLET_H__
#include "cocos2d.h"
#include "../Enemies/enemy.h"
#include "../Level/baseLevel.h"
USING_NS_CC;
/*�ӵ���ʵ��*/
class bullet :public Sprite {
protected:
	int speed;//�ӵ����� // ��������
	int damage;//�ӵ��˺� // ��������
	enemy* trackEnemy;//�ӵ������ĵ��� // ��������
public:
	int state;//״̬
	bullet();//���캯��
	virtual bool init();
	void onEnter();//��ʼ������
	void update(float dt);//��ʱ������
	static bullet* create(const std::string& filename);//��������
	void setTrack(enemy* trackIt);//��������
	void setSpeed(int newSpeed);//���÷����ٶ�
	void setDamage(int damage);
	void trackAndAttack(float dt);//��ʱ���µ��õĺ������������ˣ���������ɹ�����й���
	virtual void causeDamage();// ��д��ÿ���ӵ��˺���ʽ��ͬ
	// void booom(float dt);//�ӵ���ը��ʵ��
	float get_distance(enemy* enemy, bullet* bullet);//�����ӵ�����˵ľ���
};

class ExplodeBullet :public bullet {
	int boomDamage;
public:
	ExplodeBullet();
	static ExplodeBullet* create(const std::string& filename);//��������
	void setBoomDamage(int damage);
	void causeDamage();
	Vector<enemy*> multiSearch();
	void booom();
};

class NoxBullet :public bullet {
	int noxDamage;
public:
	NoxBullet();
	static NoxBullet* create(const std::string& filename);//��������
	void setNoxDamage(int damage);
	void causeDamage();
	void noxHit(float dt);
	void noxDown(float dt);
};

#endif