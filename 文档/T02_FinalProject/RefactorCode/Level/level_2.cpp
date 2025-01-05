#include "level_2.h"
#include "../Block/baseBlock.h"
#include "baseLevel.h"
#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"
#include "../Enemies/enemy.h"

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
	enemyFactories.insert("Soldier", new SoldierEnemyFactory);
	enemyFactories.insert("Tank", new TankEnemyFactory);
	enemyFactories.insert("Boss", new BossEnemyFactory);

	WaveList wave1;
	wave1.spawnInterval = 1;
	for (int i = 0; i < 6; i++) {
		auto soldier = enemyFactories.at("Soldier")->createEnemy();
		soldier->setPosition(path.front()->getPosition());
		wave1.sequence.pushBack(soldier);
		auto tank = enemyFactories.at("Tank")->createEnemy();
		tank->setPosition(path.front()->getPosition());
		wave1.sequence.pushBack(tank);
	}

	wave.push_back(wave1);

	WaveList wave2;
	wave2.spawnInterval = 0.7;
	for (int i = 0; i < 20; i++) {
		auto soldier = enemyFactories.at("Soldier")->createEnemy();
		soldier->setPosition(path.front()->getPosition());
		wave2.sequence.pushBack(soldier);
		auto boss = enemyFactories.at("Boss")->createEnemy();
		boss->setPosition(path.front()->getPosition());
		wave2.sequence.pushBack(boss);
	}
	wave.push_back(wave2);

	
}

void Level_2::restart()
{
	Director::getInstance()->replaceScene(Level_2::create());
}


