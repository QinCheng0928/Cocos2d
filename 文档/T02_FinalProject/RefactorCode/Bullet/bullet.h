#ifndef __BULLET_H__
#define __BULLET_H__
#include "cocos2d.h"
#include "../Enemies/Enemy.h"
#include "../Level/baseLevel.h"
USING_NS_CC;

// This part is refactored using the Decorator pattern.

// Component Interface
class BulletComponent : public Sprite {
public:
	virtual void causeDamage() = 0;
	virtual void update(float dt) = 0;
	virtual void trackAndAttack(float dt) = 0;
	virtual Enemy* getTrackEnemy() = 0;
	virtual float get_distance(Enemy* enemy, BulletComponent* bullet) = 0; // Calculates the distance between a bullet and an enemy
};

// Specific Component - Generic Bullet
class Bullet : public BulletComponent {
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
	Enemy* getTrackEnemy();                             // Get the current track enemy
	void setTrack(Enemy* trackIt);						// Sets the target enemy
	void setSpeed(int newSpeed);						// Sets the bullet's flying speed
	void setDamage(int damage);							// Sets the bullet's damage
	float get_distance(Enemy* enemy, BulletComponent* bullet);	// Calculates the distance between a bullet and an enemy
	void causeDamage();									// Apply damage to a single enemy

	void reset();										// Reset the bullet's state to be reused
};

// Decorative base class
class BulletDecorator :public BulletComponent {
protected:
	BulletComponent* baseBullet; // Stores a reference to the encapsulated object
public:
	BulletDecorator(BulletComponent* baseBullet): baseBullet(baseBullet){}
	BulletDecorator();
	// All work is delegated to the encapsulated object.
	virtual void causeDamage() override {
		baseBullet->causeDamage();
	}
	void update(float dt) override {
		baseBullet->update(dt);
	}
	void trackAndAttack(float dt) override {
		baseBullet->trackAndAttack(dt);
	}
	Enemy* getTrackEnemy() override {
		return baseBullet->getTrackEnemy();
	}
	float get_distance(Enemy* enemy, BulletComponent* bullet) override {
		return baseBullet->get_distance(enemy, bullet);
	}
};

// Specific decoration - explosive decoration
class ExplodeDecorator :public BulletDecorator {
	int boomDamage;
public:
	ExplodeDecorator(BulletComponent* wrappee, int boomDamage);
	void causeDamage() override;
	Vector<Enemy*> multiSearch();
	void booom();
};

// Specific decoration - poison gas decoration
class NoxDecorator :public BulletDecorator {
	int noxDamage;
public:
	NoxDecorator(BulletComponent* wrappee, int noxDamage);
	void causeDamage() override;
};

// Poison gases, which are used to deal damage over time
class Nox :public Sprite {
	int noxDamage;
	Enemy* trackEnemy;
public:
	Nox();
	virtual bool init();
	void onEnter();
	static Nox* create(const std::string& filename);
	void setNoxDamage(int damage);
	void setTrack(Enemy* enemy);
	void noxHit(float dt);
	void noxDown(float dt);
};


#endif