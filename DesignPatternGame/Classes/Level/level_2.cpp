#include "level_2.h"
#include "../Block/baseBlock.h"
#include "baseLevel.h"
#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"
#include "../Enemies/Enemy.h"
#include "../Enemies/BossEnemy.h"
#include "../Enemies/SoldierEnemy.h"
#include "../Enemies/TankEnemy.h"
USING_NS_CC;

bool Level_2::init()
{
	return baseLevel::init();
}

void Level_2::spawnPointSet()
{
	spawnPoint.x = 3;
	spawnPoint.y = 3;
}

void Level_2::pathSet()
{
	for (int i = 4; i <= 12; i++) {
		addPath(i, 3);
	}
	addPath(12, 4);
	addPath(12, 5);
	for (int i = 11; i >= 3; i--) {
		addPath(i, 5);
	}
}

void Level_2::moneyAndHpSet()
{
	money = 15000;
	healthPoint = 10;
}

void Level_2::waveSet()
{
	WaveList wave1;
	wave1.spawnInterval = 1;
	for (int i = 0; i < 6; i++) {
		auto enemy = SoldierEnemy::create();
		enemy->setPosition(path.front()->getPosition());
		wave1.sequence.pushBack(enemy);
		auto enemy2 = TankEnemy::create();
		enemy2->setPosition(path.front()->getPosition());
		wave1.sequence.pushBack(enemy2);
	}

	wave.push_back(wave1);

	WaveList wave2;
	wave2.spawnInterval = 0.7;
	for (int i = 0; i < 20; i++) {
		auto enemy = SoldierEnemy::create();
		enemy->setPosition(path.front()->getPosition());
		wave2.sequence.pushBack(enemy);
		auto enemy3 = BossEnemy::create();
		enemy3->setPosition(path.front()->getPosition());
		wave2.sequence.pushBack(enemy3);
	}
	wave.push_back(wave2);

	
}

void Level_2::restart()
{
	Director::getInstance()->replaceScene(Level_2::create());
}


