#include "../Block/baseBlock.h"
#include "../Level/baseLevel.h"
#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"
#include "../Enemies/Enemy.h"
#include "../Enemies/SoldierEnemy.h"
#include "../Tower/dianmei.h"
#include "../GameSaveManager/GameSaveManager.h"
#include "../HelloWorldScene.h"
#include "../Tower/r99.h"
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

bool baseLevel::init()
{
	//初始化一些基本参数
	superInit();

	//设置怪物行走路径、起始点、萝卜位置
	spawnInit();

	//打印ui界面
	uiInit();

	//每帧都要更新的东西进行初始化
	scheduleInit();

	//初始化波次信息
	waveInit();

	//开始出怪
	monsterSpawn(1);

	return true;
}


void baseLevel::superInit()
{
	//设置各个变量的初始值
	moneyAndHpSet();
	currentWave = 0;
	stop = 0;

	//初始化所有格子为空格子
	for (int i = 1; i <= BLOCK_X_NUM; ++i) {
		for (int j = 1; j <= BLOCK_Y_NUM; ++j) {
			auto block = BaseBlock::create();
			block->setTag(coordToTag(i, j));//格子的tag = (y - 1) * BLOCK_X_NUM + x
			block->setAnchorPoint(Vec2(0.5, 0.5));
			block->setPosition(Vec2(i * BLOCK_LEN + 0.5 * BLOCK_LEN, j * BLOCK_LEN + 0.5 * BLOCK_LEN));
			block->setZOrder(1);

			this->addChild(block);
		}
	}

	//背景图
	auto background = Sprite::create("BG.png");
	background->setPosition(Director::getInstance()->getVisibleSize() / 2);
	this->addChild(background);
}

void baseLevel::moneyAndHpSet()
{
	money = 5000;
	healthPoint = 10;
}

void baseLevel::spawnInit()
{
	//根据关卡不同自己调整怪物的出生位置
	spawnPointSet();

	//把当前位置的格子移除，用路径格子作为替代
	this->removeChildByTag(coordToTag(spawnPoint.x, spawnPoint.y));

	auto spawn = PathBlock::create();

	spawn->setPosition(Vec2(spawnPoint.x * BLOCK_LEN + 0.5 * BLOCK_LEN, spawnPoint.y * BLOCK_LEN + 0.5 * BLOCK_LEN));
	spawn->setZOrder(0);
	
	//把出生格子加入路径序列
	path.pushBack(spawn);

	this->addChild(spawn);

	//根据需要设置怪物的移动路径
	pathSet();

	//在终点添加一个萝卜图层
	auto carrot = Sprite::create("carrot.png");
	carrot->setAnchorPoint(Vec2(0.5, 0));
	carrot->setPosition(path.back()->getPosition());
	carrot->setScale(2);
	carrot->setName("carrot");
	this->addChild(carrot);

	//for test
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

	/*auto r99 = r99::create();
	r99->setPosition(Vec2(6 * BLOCK_LEN + 0.5 * BLOCK_LEN, 5 * BLOCK_LEN + 0.5 * BLOCK_LEN));
	r99->running_act();
	r99->setScale(0.3);
	r99->levelup(3);
	addChild(r99, 0);*/
}

void baseLevel::uiInit()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();

	//显示剩余金钱
	auto currentMoney = Label::createWithTTF("Current money: " + std::to_string(this->money), "fonts/Marker Felt.ttf", 50);
	currentMoney->setName("currentMoney");
	currentMoney->setPosition(Vec2(visibleSize.width * 0.2, visibleSize.height - 0.5 * BLOCK_LEN));
	currentMoney->setZOrder(0);
	this->addChild(currentMoney);

	//显示当前波次
	auto wave = Label::createWithTTF("1", "fonts/Marker Felt.ttf", 50);
	wave->setName("currentWave");
	wave->setPosition(Vec2(visibleSize.width * 0.5, visibleSize.height - 0.5 * BLOCK_LEN));
	wave->setZOrder(0);
	this->addChild(wave);

	//显示剩余血量
	auto hp = Label::createWithTTF("1", "fonts/Marker Felt.ttf", 50);
	hp->setName("hp");
	hp->setPosition(Vec2(visibleSize.width * 0.8, visibleSize.height - 0.5 * BLOCK_LEN));
	hp->setZOrder(0);
	this->addChild(hp);

	//右上角返回菜单
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

	//左上角重新开始游戏
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
	////暂停界面的场景
	//auto pauseScene = Scene::create();

	////场景的背景图
	//auto background = Sprite::create("BG.png");
	//background->setPosition(pauseScene->getContentSize() / 2);

	////重新开始按钮
	//auto restartButton = ui::Button::create("restart_normal.png", "restart_selected.png");
	//restartButton->setPosition(Vec2(pauseScene->getContentSize().width / 2, pauseScene->getContentSize().height / 2));
	////按下就会重新开始当前关卡
	//restartButton->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
	//	switch (type)
	//	{
	//	case ui::Widget::TouchEventType::ENDED:
	//		Director::getInstance()->popScene();
	//		restart();
	//	}
	//});

	////继续按钮
	//auto continueButton = ui::Button::create("continue_normal.png", "continue_selected.png");
	//continueButton->setPosition(Vec2(pauseScene->getContentSize().width / 2, pauseScene->getContentSize().height * 0.7));
	////按下就会继续当前关卡
	//continueButton->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
	//	switch (type)
	//	{
	//	case ui::Widget::TouchEventType::ENDED:
	//		Director::getInstance()->popScene();
	//	}
	//});

	////返回菜单按钮
	//auto returnButton = ui::Button::create("select_menu_normal.png", "select_menu_normal.png");
	//returnButton->setPosition(Vec2(pauseScene->getContentSize().width / 2, pauseScene->getContentSize().height * 0.3));
	////按下就会返回关卡选择界面
	//returnButton->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
	//	switch (type)
	//	{
	//	case ui::Widget::TouchEventType::ENDED:
	//		Director::getInstance()->popScene();
	//		Director::getInstance()->popScene();
	//	}
	//});
	//
	//pauseScene->addChild(background);
	//pauseScene->addChild(restartButton);
	//pauseScene->addChild(continueButton);
	//pauseScene->addChild(returnButton);
	//Director::getInstance()->pushScene(pauseScene);
}

void baseLevel::waveInit()
{
	//自行定制波次、怪物数量以及刷新间隔
	waveSet();

	maxWave = wave.size();
	waveIter = wave.begin();
	currentIter = waveIter->sequence.begin();
}


void baseLevel::scheduleInit()
{
	//更新ui的显示
	schedule(schedule_selector(baseLevel::uiUpdate));
	//判断是否胜利/失败
	schedule(schedule_selector(baseLevel::winCheck));
}

PathBlock* baseLevel::addPath(int x, int y)
{
	auto ppath = PathBlock::create();

	//根据x，y的坐标把相应的位置变为怪物的路径
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
	

	auto label = this->getChildByName("currentMoney");
	if (label) {
		dynamic_cast<Label*>(label)->setString("Current money: " + std::to_string(money));
	}

	//更新波次信息
	auto wave = this->getChildByName("currentWave");
	if (wave) {
		dynamic_cast<Label*>(wave)->setString("Current wave/Max wave: " + std::to_string(currentWave) + "/" + std::to_string(maxWave));
	}

	//更新血量信息
	auto hp = this->getChildByName("hp");
	if (hp) {
		dynamic_cast<Label*>(hp)->setString("Current hp: " + std::to_string(healthPoint));
	}
}

void baseLevel::monsterSpawn(float dt)
{

	//每隔特定的时间就从生成序列中的一只怪
	scheduleOnce(schedule_selector(baseLevel::spawnOne), waveIter->spawnInterval);
}

void baseLevel::spawnOne(float dt)
{
	//如果是新的一波怪，则更新当前波次
	if (currentIter == waveIter->sequence.begin())
		currentWave++;
	//用迭代器来遍历序列中的所有怪
	auto enemy = *currentIter;
	enemy->setOpacity(255);
	this->addChild(enemy);
	currentIter++;
	//如果不是最后一只怪，则准备生成下一只怪
	if (currentIter != waveIter->sequence.end() && waveIter != wave.end())
		scheduleOnce(schedule_selector(baseLevel::spawnOne), waveIter->spawnInterval);
	else { //如果是最后一只怪，只有在当前波次所有怪都被消灭，且不是最后一波的情况下才会开始生成下一波怪
		schedule(schedule_selector(baseLevel::checkElimination));
	}
}

void baseLevel::checkElimination(float dt)
{
	auto iter = waveIter->sequence.begin();
	bool flag = 1;
	while (iter != waveIter->sequence.end()) { //判断当前波次的怪物是否都已经被消灭
		if ((*iter)->getParent()) {
			flag = 0;
		}
		iter++;
	}
	if (flag == 1) { //如果已经都被消灭，则准备生成下一波怪（或者结束游戏，因为所有波次都已经结束）
		waveIter++;
		this->unschedule(schedule_selector(baseLevel::checkElimination));
		if (waveIter != wave.end()) //还有未进行的波次，则继续出怪
		{
			currentIter = waveIter->sequence.begin();
			scheduleOnce(schedule_selector(baseLevel::spawnOne), waveIter->spawnInterval);
		}
		else { //更新波次数以结束游戏
			currentWave++;
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
	if (healthPoint <= 0) { //血量为0则判输
		loseDisplay();
		unschedule(schedule_selector(baseLevel::winCheck));
	}
	else if (currentWave > maxWave) { // 所有怪物都已经消灭则判赢
		winDisplay();
		unschedule(schedule_selector(baseLevel::winCheck));
	}
}

void baseLevel::winDisplay()
{
	//解锁第二关
	levelpass = 1;
	// 在需要保存玩家分数时调用，比如玩家过关或者得到分数时
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

	//重新开始按钮
	tryAgainButton->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
		switch (type)
		{
		case ui::Widget::TouchEventType::ENDED:
			Director::getInstance()->popScene();
			restart();
		}
	});

	//返回菜单按钮
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

	tryAgainButton->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
		switch (type)
		{
		case ui::Widget::TouchEventType::ENDED:
			Director::getInstance()->popScene();
			restart();
		}
	});

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




