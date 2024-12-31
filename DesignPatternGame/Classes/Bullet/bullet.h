#ifndef __BULLET_H__
#define __BULLET_H__
#include "cocos2d.h"
#include "../Enemies/enemy.h"
#include "../Level/baseLevel.h"
USING_NS_CC;
/*�ӵ���ʵ��*/

// ����ӿ�
class bulletComponent : public Sprite {
public:
	virtual void causeDamage() = 0;
	virtual void update(float dt) = 0;
	virtual void trackAndAttack(float dt) = 0;
	virtual void setTrack(enemy* trackIt) = 0;  // ��������
	virtual void setSpeed(int newSpeed) = 0;  // ���÷����ٶ�
	virtual void setDamage(int damage) = 0;   // �����˺�
	virtual float get_distance(enemy* enemy, bulletComponent* bullet) = 0;//�����ӵ�����˵ľ���
};

// �������
class bullet :public bulletComponent {
protected:
	int speed;//�ӵ����� // ��������
	int damage;//�ӵ��˺� // ��������
	enemy* trackEnemy;//�ӵ������ĵ��� // ��������
public:
	int state;//״̬
	bullet();//���캯��
	virtual bool init();
	void onEnter();//��ʼ������
	static bullet* create(const std::string& filename);//��������
	void update(float dt) override;//��ʱ������
	void trackAndAttack(float dt) override;//��ʱ���µ��õĺ������������ˣ���������ɹ�����й���
	void setTrack(enemy* trackIt) override;//��������
	void setSpeed(int newSpeed) override;//���÷����ٶ�
	void setDamage(int damage) override;
	float get_distance(enemy* enemy, bulletComponent* bullet) override;
	void causeDamage() override;// ��д��ÿ���ӵ��˺���ʽ��ͬ
};

// װ����������
class BulletDecorator :public bulletComponent {
protected:
	bulletComponent* baseBullet;
public:
	BulletDecorator(bulletComponent* baseBullet): baseBullet(baseBullet){}
	virtual void causeDamage() override {
		baseBullet->causeDamage();
	}
	void update(float dt) override {
		baseBullet->update(dt);
	}
	void trackAndAttack(float dt) override {
		baseBullet->trackAndAttack(dt);
	}
	void setTrack(enemy* trackIt) override {
		baseBullet->setTrack(trackIt);  // ���û����ӵ����������˷���
	}
	void setSpeed(int newSpeed) override {
		baseBullet->setSpeed(newSpeed);  // ���û����ӵ��������ٶȷ���
	}
	void setDamage(int damage) override {
		baseBullet->setDamage(damage);  // ���û����ӵ��������˺�����
	}
	float get_distance(enemy* enemy, bulletComponent* bullet) override {
		return baseBullet->get_distance(enemy, bullet);
	}
};

class ExplodeDecorator :public BulletDecorator {
	int boomDamage;
public:
	ExplodeDecorator(bulletComponent* wrappee);
	void causeDamage() override;
	void setBoomDamage(int damage);
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
};

// �����࣬������ɳ����˺�
class Nox :public Sprite {
	int noxDamage;
	enemy* trackEnemy;
public:
	Nox();//���캯��
	virtual bool init();
	void onEnter();//��ʼ������
	static Nox* create(const std::string& filename);//��������
	void setNoxDamage(int damage);
	void setTrack(enemy* enemy);
	void noxHit(float dt);
	void noxDown(float dt);
};


#endif