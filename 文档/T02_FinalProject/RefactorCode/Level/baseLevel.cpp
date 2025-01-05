#include "../Block/baseBlock.h"
#include "../Level/baseLevel.h"
#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"
#include "../Enemies/Enemy.h"
#include "../Enemies/SoldierEnemy.h"
#include "../Tower/FlameTower.h"
#include "../GameSaveManager/GameSaveManager.h"
#include "../HelloWorldScene.h"
#include "../Tower/ElectroTower.h"
USING_NS_CC;

extern bool levelpass;

int baseLevel::coordToTag(int x, int y)
{
	return (y - 1) * BLOCK_X_NUM + x;
}

cocos2d::Scene* baseLevel::createScene()
{
	return baseLevel::create();
}

// This part is refactored using the Template Method pattern.
bool baseLevel::init()
{
	moneyAndHpSet();
	baseBlockInit();
	backgroundInit();
	spawnPointSet();
	spawnBlockInit();
	pathSet();
	carrotSet();
	uiInit();
	scheduleInit();
	waveSet();
	waveInit();
	monsterSpawn(1);

	return true;
}

void baseLevel::moneyAndHpSet()
{
	money = 5000;
	healthPoint = 10;
}

void baseLevel::baseBlockInit()
{
	currentWave = 0;
	stop = 0;
	// Initialize all grid blocks as empty blocks
	for (int i = 1; i <= BLOCK_X_NUM; ++i) {
		for (int j = 1; j <= BLOCK_Y_NUM; ++j) {
			auto block = BaseBlock::create();
			block->setTag(coordToTag(i, j));// Grid tag = (y - 1) * BLOCK_X_NUM + x
			block->setAnchorPoint(Vec2(0.5, 0.5));
			block->setPosition(Vec2(i * BLOCK_LEN + 0.5 * BLOCK_LEN, j * BLOCK_LEN + 0.5 * BLOCK_LEN));
			block->setZOrder(1);

			this->addChild(block);
		}
	}
}

void baseLevel::backgroundInit()
{
	auto background = Sprite::create("BG.png");
	background->setPosition(Director::getInstance()->getVisibleSize() / 2);
	this->addChild(background);
}

void baseLevel::spawnBlockInit()
{
	// Remove the current block at spawn point and replace it with a path block
	this->removeChildByTag(coordToTag(spawnPoint.x, spawnPoint.y));
	auto spawn = PathBlock::create();
	spawn->setPosition(Vec2(spawnPoint.x * BLOCK_LEN + 0.5 * BLOCK_LEN, spawnPoint.y * BLOCK_LEN + 0.5 * BLOCK_LEN));
	spawn->setZOrder(0);
	// Add path block to the path sequence
	path.pushBack(spawn);
	this->addChild(spawn);
}

void baseLevel::carrotSet()
{
	// Add a carrot sprite at the end point
	auto carrot = Sprite::create("carrot.png");
	carrot->setAnchorPoint(Vec2(0.5, 0));
	carrot->setPosition(path.back()->getPosition());
	carrot->setScale(2);
	carrot->setName("carrot");
	this->addChild(carrot);
}


void baseLevel::spawnPointSet()
{
	spawnPoint.x = 3;
	spawnPoint.y = 4;
}

void baseLevel::pathSet()
{
	for (int i = 4; i <= 12; i++)
		addPath(i, 4);
}

void baseLevel::uiInit()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();

	// Display remaining money
	auto currentMoney = Label::createWithTTF("Current money: " + std::to_string(this->money), "fonts/Marker Felt.ttf", 50);
	currentMoney->setName("currentMoney");
	currentMoney->setPosition(Vec2(visibleSize.width * 0.2, visibleSize.height - 0.5 * BLOCK_LEN));
	currentMoney->setZOrder(0);
	this->addChild(currentMoney);

	// Display current wave
	auto wave = Label::createWithTTF("1", "fonts/Marker Felt.ttf", 50);
	wave->setName("currentWave");
	wave->setPosition(Vec2(visibleSize.width * 0.5, visibleSize.height - 0.5 * BLOCK_LEN));
	wave->setZOrder(0);
	this->addChild(wave);

	// Display remaining health
	auto hp = Label::createWithTTF("1", "fonts/Marker Felt.ttf", 50);
	hp->setName("hp");
	hp->setPosition(Vec2(visibleSize.width * 0.8, visibleSize.height - 0.5 * BLOCK_LEN));
	hp->setZOrder(0);
	this->addChild(hp);

	// Menu button at the top right corner
	auto menuSelector = ui::Button::create("operation-bottom-normal.png", "operation-bottom-selected.png");
	menuSelector->setPosition(Vec2(15.5 * 120, 8.5 * 120));
	menuSelector->setScale(0.7);
	menuSelector->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
		switch (type)
		{
		case ui::Widget::TouchEventType::ENDED:
			switchToPauseMenu();
		}
	});
	this->addChild(menuSelector);

	// Restart button at the top left corner
	auto pauseButton = ui::Button::create("back-normal.png", "back-selected.png");
	pauseButton->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
		switch (type)
		{
		case ui::Widget::TouchEventType::ENDED:
			restart();
		}
		});

	pauseButton->setScale(0.2);
	pauseButton->setPosition(Vec2(0.5 * 120, 8.5 * 120));
	this->addChild(pauseButton);
}

void baseLevel::switchToPauseMenu()
{
	Director::getInstance()->popScene();

}

void baseLevel::waveInit()
{
	maxWave = wave.size();
	waveIter = wave.begin();
	currentIter = waveIter->sequence.begin();
}


void baseLevel::scheduleInit()
{
	// Update the UI display
	schedule(schedule_selector(baseLevel::uiUpdate));
	// Check for victory/loss
	schedule(schedule_selector(baseLevel::winCheck));
}

PathBlock* baseLevel::addPath(int x, int y)
{
	auto ppath = PathBlock::create();

	// Mark the position with x, y as a monster path
	this->removeChildByTag(coordToTag(x, y));
	ppath->setPosition(Vec2(x * BLOCK_LEN + 0.5 * BLOCK_LEN, y * BLOCK_LEN + 0.5 * BLOCK_LEN));
	ppath->setZOrder(0);
	this->addChild(ppath);

	path.back()->link = ppath;
	path.pushBack(ppath);

	return ppath;
}

void baseLevel::uiUpdate(float dt)
{
	
	// Update money information
	auto label = this->getChildByName("currentMoney");
	if (label) {
		dynamic_cast<Label*>(label)->setString("Current money: " + std::to_string(money));
	}

	// Update wave information
	auto wave = this->getChildByName("currentWave");
	if (wave) {
		dynamic_cast<Label*>(wave)->setString("Current wave/Max wave: " + std::to_string(currentWave) + "/" + std::to_string(maxWave));
	}

	// Update health information
	auto hp = this->getChildByName("hp");
	if (hp) {
		dynamic_cast<Label*>(hp)->setString("Current hp: " + std::to_string(healthPoint));
	}
}

void baseLevel::monsterSpawn(float dt)
{
	// Spawn a monster from the spawn sequence at specific intervals
	scheduleOnce(schedule_selector(baseLevel::spawnOne), waveIter->spawnInterval);
}

void baseLevel::spawnOne(float dt)
{
	// If it's a new wave, update the current wave
	if (currentIter == waveIter->sequence.begin())
		currentWave++;
	// Use an iterator to traverse through all monsters in the sequence
	auto enemy = *currentIter;
	enemy->setOpacity(255);
	this->addChild(enemy);
	currentIter++;
	// If it's not the last monster, prepare to spawn the next one
	if (currentIter != waveIter->sequence.end() && waveIter != wave.end())
		scheduleOnce(schedule_selector(baseLevel::spawnOne), waveIter->spawnInterval);
	else { // If it's the last monster, only spawn the next wave after all monsters are eliminated and it's not the last wave
		schedule(schedule_selector(baseLevel::checkElimination));
	}
}

void baseLevel::checkElimination(float dt)
{
	auto iter = waveIter->sequence.begin();
	bool flag = 1;
	while (iter != waveIter->sequence.end()) { // Check if all monsters in the current wave are eliminated
		if ((*iter)->getParent()) {
			flag = 0;
		}
		iter++;
	}
	if (flag == 1) { // If all monsters are eliminated, prepare to spawn the next wave (or end the game if it's the last wave)
		if (currentWave == maxWave) {
			Director::getInstance()->replaceScene(HelloWorld::createScene());
		}
		else {
			waveIter++;
			currentIter = waveIter->sequence.begin();
			monsterSpawn(1.0f);
		}
	}
}

void baseLevel::restart()
{
	Director::getInstance()->replaceScene(baseLevel::create());
}

void baseLevel::setStop()
{
	for (auto j = waveIter->sequence.begin(); j != waveIter->sequence.end(); j++) {
		(*j)->setSpeedScale(0.00000001);
	}
	for (auto i = wave.begin(); i != wave.end(); i++) {
		//(*i).intervalScale = INT_MAX;
	}
}

void baseLevel::setMove()
{
	for (auto j = waveIter->sequence.begin(); j != waveIter->sequence.end(); j++) {
		(*j)->setSpeedScale(1);
	}
	for (auto i = wave.begin(); i != wave.end(); i++) {
		//(*i).intervalScale = 1;
	}
}
void baseLevel::winCheck(float dt)
{
	if (healthPoint <= 0) { // Lose if health reaches 0
		loseDisplay();
		unschedule(schedule_selector(baseLevel::winCheck));
	}
	else if (currentWave > maxWave) { // Win if all enemies are defeated
		winDisplay();
		unschedule(schedule_selector(baseLevel::winCheck));
	}
}

void baseLevel::winDisplay()
{
	// Unlock the next level
	levelpass = 1;
	// Save player progress, for example, when they pass a level or earn points
	GameDataManager::saveValue("savedata/player.txt", levelpass);

	auto winScene = Scene::create();
	auto tryAgainButton = ui::Button::create("try_again_normal.png", "try_again_selected.png");
	auto returnToMenuButton = ui::Button::create("select_menu_normal.png", "select_menu_selected.png");
	auto winLabel = Label::createWithTTF("You won!", "fonts/Marker Felt.ttf", 150);
	auto backGround = Sprite::create("BG.png");

	auto visibleSize = Director::getInstance()->getVisibleSize();

	tryAgainButton->setPosition(Vec2(0.3 * visibleSize.width, 0.3 * visibleSize.height));
	returnToMenuButton->setPosition(Vec2(0.7 * visibleSize.width, 0.3 * visibleSize.height));
	winLabel->setPosition(Vec2(0.5 * visibleSize.width, 0.6 * visibleSize.height));
	backGround->setPosition(Vec2(0.5 * visibleSize.width, 0.5 * visibleSize.height));

	// Try again button functionality
	tryAgainButton->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
		switch (type)
		{
		case ui::Widget::TouchEventType::ENDED:
			Director::getInstance()->popScene();
			restart();
		}
	});

	// Return to menu button functionality
	returnToMenuButton->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
		switch (type)
		{
		case ui::Widget::TouchEventType::ENDED:
			Director::getInstance()->popScene();
			Director::getInstance()->popScene();
		}
	});

	winScene->addChild(tryAgainButton, 1);
	winScene->addChild(returnToMenuButton, 1);
	winScene->addChild(winLabel, 1);
	winScene->addChild(backGround, 0);
	Director::getInstance()->pushScene(winScene);
}

void baseLevel::loseDisplay()
{
	auto winScene = Scene::create();
	auto tryAgainButton = ui::Button::create("try_again_normal.png", "try_again_selected.png");
	auto returnToMenuButton = ui::Button::create("select_menu_normal.png", "select_menu_selected.png");
	auto winLabel = Label::createWithTTF("You lose!", "fonts/Marker Felt.ttf", 150);
	auto backGround = Sprite::create("BG.png");

	auto visibleSize = Director::getInstance()->getVisibleSize();

	tryAgainButton->setPosition(Vec2(0.3 * visibleSize.width, 0.3 * visibleSize.height));
	returnToMenuButton->setPosition(Vec2(0.7 * visibleSize.width, 0.3 * visibleSize.height));
	winLabel->setPosition(Vec2(0.5 * visibleSize.width, 0.6 * visibleSize.height));
	backGround->setPosition(Vec2(0.5 * visibleSize.width, 0.5 * visibleSize.height));

	// Try again button functionality
	tryAgainButton->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
		switch (type)
		{
		case ui::Widget::TouchEventType::ENDED:
			Director::getInstance()->popScene();
			restart();
		}
	});

	// Return to menu button functionality
	returnToMenuButton->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
		switch (type)
		{
		case ui::Widget::TouchEventType::ENDED:
			Director::getInstance()->popScene();
			Director::getInstance()->popScene();
		}
	});

	winScene->addChild(tryAgainButton, 1);
	winScene->addChild(returnToMenuButton, 1);
	winScene->addChild(winLabel, 1);
	winScene->addChild(backGround, 0);
	Director::getInstance()->pushScene(winScene);
}





