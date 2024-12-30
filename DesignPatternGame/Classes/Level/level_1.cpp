#include "level_1.h"
#include "../Block/baseBlock.h"
#include "baseLevel.h"
#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"
#include "../Enemies/Enemy.h"
#include "../Enemies/BossEnemy.h"
#include "../Enemies/SoldierEnemy.h"
#include "../Enemies/TankEnemy.h"

USING_NS_CC;

bool Level_1::init()
{
	return baseLevel::init();
}

void Level_1::spawnPointSet()
{
	spawnPoint.x = 2;
	spawnPoint.y = 7;
}

void Level_1::pathSet()
{
	addPath(2, 6);
	addPath(2, 5);
	addPath(2, 4);
	for (int i = 3; i <= 9; i++) {
		addPath(i, 4);
	}
	addPath(9, 3);
	addPath(9, 2);
}

void Level_1::moneyAndHpSet()
{
	money = 15000;
	healthPoint = 10;
}

void Level_1::waveSet()
{
	WaveList wave1;
	wave1.spawnInterval = 0.7;
	for (int i = 0; i < 5; i++) {
		auto enemy = BossEnemy::create();
		enemy->setPosition(path.front()->getPosition());
		wave1.sequence.pushBack(enemy);
	}
	wave.push_back(wave1);

	WaveList wave2;
	wave2.spawnInterval = 0.5;
	for (int i = 0; i < 10; i++) {
		auto enemy = SoldierEnemy::create();
		enemy->setPosition(path.front()->getPosition());
		wave2.sequence.pushBack(enemy);
	}
	wave.push_back(wave2);

	WaveList wave3;
	wave3.spawnInterval = 1;
	for (int i = 0; i < 3; i++) {
		auto enemy = TankEnemy::create();
		enemy->setPosition(path.front()->getPosition());
		wave3.sequence.pushBack(enemy);
	}
	wave.push_back(wave3);
}

void Level_1::restart()
{
	Director::getInstance()->replaceScene(Level_1::create());
}
