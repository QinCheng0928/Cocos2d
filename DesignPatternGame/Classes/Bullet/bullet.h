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

// Specific Component - Generic Bullet
class Bullet : public Sprite {
protected:
	int speed;               // Bullet speed
	int damage;              // Bullet damage
	int boomDamage;          // Bullet explosion damage
	Enemy* trackEnemy;       // Enemy targeted by the bullet
public:
	int state;											// Bullet state (e.g., moving, exploding)
	Bullet();											// Constructor
	Bullet(const Bullet& other);						// Copy constructor
	virtual bool init();								// Initialization function
	void onEnter();										// Called when the bullet is added to a scene
	static Bullet* create(const std::string& filename); // Factory function to create a bullet
	void update(float dt);								// Timer function for periodic updates
	void trackAndAttack(float dt);						// Searches for enemies and attacks if found
	void setTrack(Enemy* trackIt);						// Sets the target enemy
	void setSpeed(int newSpeed);						// Sets the bullet's flying speed
	void setDamage(int damage);							// Sets the bullet's damage
	float get_distance(Enemy* enemy, Bullet* bullet);	// Calculates the distance between a bullet and an enemy
	virtual void causeDamage();							// Virtual function for applying damage (different types of bullets can override this)
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