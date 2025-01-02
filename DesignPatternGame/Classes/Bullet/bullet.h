#ifndef __BULLET_H__
#define __BULLET_H__
#include "cocos2d.h"
#include "../Enemies/Enemy.h"
#include "../Level/baseLevel.h"
USING_NS_CC;
/*�ӵ���ʵ��*/

//// ����ӿ�
//class bulletComponent : public Sprite {
//public:
//	virtual void causeDamage() = 0;
//	virtual void update(float dt) = 0;
//	virtual void trackAndAttack(float dt) = 0;
//	virtual float get_distance(enemy* enemy, bulletComponent* bullet) = 0;//�����ӵ�����˵ľ���
//};

// �������������ͨ�ӵ�
class Bullet :public Sprite {
protected:
	int speed;//�ӵ�����
	int damage;//�ӵ��˺�
	int boomDamage;//�ӵ���ը�˺�
	Enemy* trackEnemy;//�ӵ������ĵ���
public:
	int state;//״̬
	Bullet();//���캯��
	Bullet(const Bullet& other);  // ���ƹ��캯��
	virtual bool init();
	void onEnter();//��ʼ������
	static Bullet* create(const std::string& filename);//��������
	void update(float dt);//��ʱ������
	void trackAndAttack(float dt);//��ʱ���µ��õĺ������������ˣ���������ɹ�����й���
	void setTrack(Enemy* trackIt);//��������
	void setSpeed(int newSpeed);//���÷����ٶ�
	void setDamage(int damage);
	float get_distance(Enemy* enemy, Bullet* bullet);
	virtual void causeDamage();// ��д��ÿ���ӵ��˺���ʽ��ͬ
};

//// װ����������
//class BulletDecorator :public bulletComponent {
//protected:
//	bulletComponent* baseBullet;
//public:
//	BulletDecorator(bulletComponent* baseBullet): baseBullet(baseBullet){}
//	virtual void causeDamage() override {
//		baseBullet->causeDamage();
//	}
//	void update(float dt) override {
//		baseBullet->update(dt);
//	}
//	void trackAndAttack(float dt) override {
//		baseBullet->trackAndAttack(dt);
//	}
//	float get_distance(enemy* enemy, bulletComponent* bullet) override {
//		return baseBullet->get_distance(enemy, bullet);
//	}
//};

class ExplodeDecorator :public Bullet {
	int boomDamage;
public:
	ExplodeDecorator(Bullet* wrappee);
	static ExplodeDecorator* create(const std::string& filename, Bullet* wrappee);
	void causeDamage() override;
	void setBoomDamage(int damage);
	Vector<Enemy*> multiSearch();
	void booom();
};

class NoxDecorator :public Bullet {
	int noxDamage;
public:
	NoxDecorator(Bullet* wrappee);
	static NoxDecorator* create(const std::string& filename, Bullet* wrappee);//��������
	void setNoxDamage(int damage);
	void causeDamage() override;
};

// �����࣬������ɳ����˺�
class Nox :public Sprite {
	int noxDamage;
	Enemy* trackEnemy;
public:
	Nox();//���캯��
	virtual bool init();
	void onEnter();//��ʼ������
	static Nox* create(const std::string& filename);//��������
	void setNoxDamage(int damage);
	void setTrack(Enemy* enemy);
	void noxHit(float dt);
	void noxDown(float dt);
};


#endif