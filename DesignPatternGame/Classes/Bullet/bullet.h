#ifndef __BULLET_H__
#define __BULLET_H__
#include "cocos2d.h"
#include "../Enemies/Enemy.h"
#include "../Level/baseLevel.h"
USING_NS_CC;
/*�ӵ���ʵ��*/

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

class ExplodeDecorator :public Bullet {
	int boomDamage;
public:
	ExplodeDecorator(Bullet* wrappee, int damage);
	static ExplodeDecorator* create(const std::string& filename, Bullet* wrappee, int damage);
	void causeDamage() override;
	Vector<Enemy*> multiSearch();
	void booom();
};

class NoxDecorator :public Bullet {
	int noxDamage;
public:
	NoxDecorator(Bullet* wrappee, int damage);
	static NoxDecorator* create(const std::string& filename, Bullet* wrappee, int damage);//��������
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