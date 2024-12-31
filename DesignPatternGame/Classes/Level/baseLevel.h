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
关卡基类
功能：
1、设置所有格子的位置
2、更改格子类型
3、存储经济
4、存储波次
5、存储萝卜血量
6、胜利/失败界面
7、暂停界面
*/
class baseLevel : public cocos2d::Scene
{
friend class tower;
public:
//位置坐标从左下到右上
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

	//每一波次的信息
	struct WaveList
	{
		//出怪间隔时间
		float spawnInterval;
		//出怪顺序
		Vector<Enemy*> sequence;
	};

	Vector<PathBlock*> path;

	//存储所有波次的信息
	std::vector<WaveList> wave;
	//指向当前波次的迭代器
	std::vector<WaveList>::iterator waveIter;
	//指向即将生成的怪物的迭代器
	Vector<Enemy*>::iterator currentIter;

	Vector<tower*> currentTowers;

	int coordToTag(int x, int y);

	static cocos2d::Scene* createScene();
	//初始化
	virtual bool init();
	//进行最基本的初始化
	void superInit();
	//对血量以及初始金币进行设置
	virtual void moneyAndHpSet();
	//对出生点以及路径进行设置
	void spawnInit();
	//对出生点的位置进行设置
	virtual void spawnPointSet();
	//对怪物的移动路径进行设置
	virtual void pathSet();
	//对ui进行设置
	void uiInit();
	//将场景切换到暂停界面
	void switchToPauseMenu();
	//对波次信息进行设置
	void waveInit();
	virtual void waveSet(){}
	//对每帧更新的内容进行设置
	void scheduleInit();
	//自动增加一个怪物路径
	PathBlock* addPath(int x, int y);
	//更新当前经济、波次、血量
	void uiUpdate(float dt);
	//更新出怪
	void monsterSpawn(float dt);
	//从序列中生成一只怪物
	void spawnOne(float dt);
	//判断当前是否胜利
	void winCheck(float dt);
	//播放结算画面
	void winDisplay();
	void loseDisplay();
	//判断当前波次所有怪物是否都已被消灭
	void checkElimination(float dt);
	//重新开始当前场景
	virtual void restart();
	//让所有怪物停止移动，炮塔停止攻击
	void setStop();
	//让所有怪物开始以移动，炮塔开始攻击
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
