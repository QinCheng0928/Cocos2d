#ifndef _BASE_LEVEL
#define _BASE_LEVEL

#include "cocos2d.h"
#include "../Block/baseBlock.h"
#include "../Tower/tower.h"
#include "../Enemies/Factories/EnemyFactory.h"
#include "../Enemies/Factories/SoldierEnemyFactory.h"
#include "../Enemies/Factories/TankEnemyFactory.h"
#include "../Enemies/Factories/BossEnemyFactory.h"

/*
�ؿ�����
���ܣ�
1���������и��ӵ�λ��
2�����ĸ�������
3���洢����
4���洢����
5���洢�ܲ�Ѫ��
6��ʤ��/ʧ�ܽ���
7����ͣ����
*/
class baseLevel : public cocos2d::Scene
{
friend class tower;
public:
//λ����������µ�����
#define BLOCK_X_NUM 14
#define BLOCK_Y_NUM 7
#define BLOCK_LEN 120

	int healthPoint;
	int money;
	int currentWave;
	int maxWave;
	bool stop;

	cocos2d::Map<std::string, EnemyFactory*> enemyFactories;

	struct Spawn
	{
		int x;
		int y;
	}spawnPoint;

	//ÿһ���ε���Ϣ
	struct WaveList
	{
		//���ּ��ʱ��
		float spawnInterval;
		//����˳��
		Vector<Enemy*> sequence;
	};

	Vector<PathBlock*> path;

	//�洢���в��ε���Ϣ
	std::vector<WaveList> wave;
	//ָ��ǰ���εĵ�����
	std::vector<WaveList>::iterator waveIter;
	//ָ�򼴽����ɵĹ���ĵ�����
	Vector<Enemy*>::iterator currentIter;

	Vector<tower*> currentTowers;

	int coordToTag(int x, int y);

	static cocos2d::Scene* createScene();
	//��ʼ��
	virtual bool init();
	//����������ĳ�ʼ��
	void superInit();
	//��Ѫ���Լ���ʼ��ҽ�������
	virtual void moneyAndHpSet();
	//�Գ������Լ�·����������
	void spawnInit();
	//�Գ������λ�ý�������
	virtual void spawnPointSet();
	//�Թ�����ƶ�·����������
	virtual void pathSet();
	//��ui��������
	void uiInit();
	//�������л�����ͣ����
	void switchToPauseMenu();
	//�Բ�����Ϣ��������
	void waveInit();
	virtual void waveSet(){}
	//��ÿ֡���µ����ݽ�������
	void scheduleInit();
	//�Զ�����һ������·��
	PathBlock* addPath(int x, int y);
	//���µ�ǰ���á����Ρ�Ѫ��
	void uiUpdate(float dt);
	//���³���
	void monsterSpawn(float dt);
	//������������һֻ����
	void spawnOne(float dt);
	//�жϵ�ǰ�Ƿ�ʤ��
	void winCheck(float dt);
	//���Ž��㻭��
	void winDisplay();
	void loseDisplay();
	//�жϵ�ǰ�������й����Ƿ��ѱ�����
	void checkElimination(float dt);
	//���¿�ʼ��ǰ����
	virtual void restart();
	//�����й���ֹͣ�ƶ�������ֹͣ����
	void setStop();
	//�����й��￪ʼ���ƶ���������ʼ����
	void setMove();

	CREATE_FUNC(baseLevel);
};

//long getCurrentTime()
//{
//	struct timeval tv;
//	gettimeofday(&tv, NULL);
//	return tv.tv_sec * 1000 + tv.tv_usec / 1000;
//}

#endif // _BASE_LEVEL
