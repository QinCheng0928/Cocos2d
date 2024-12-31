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
	//��ʼ��һЩ��������
	superInit();

	//���ù�������·������ʼ�㡢�ܲ�λ��
	spawnInit();

	//��ӡui����
	uiInit();

	//ÿ֡��Ҫ���µĶ������г�ʼ��
	scheduleInit();

	//��ʼ��������Ϣ
	waveInit();

	//��ʼ����
	monsterSpawn(1);

	return true;
}


void baseLevel::superInit()
{
	//���ø��������ĳ�ʼֵ
	moneyAndHpSet();
	currentWave = 0;
	stop = 0;

	//��ʼ�����и���Ϊ�ո���
	for (int i = 1; i <= BLOCK_X_NUM; ++i) {
		for (int j = 1; j <= BLOCK_Y_NUM; ++j) {
			auto block = BaseBlock::create();
			block->setTag(coordToTag(i, j));//���ӵ�tag = (y - 1) * BLOCK_X_NUM + x
			block->setAnchorPoint(Vec2(0.5, 0.5));
			block->setPosition(Vec2(i * BLOCK_LEN + 0.5 * BLOCK_LEN, j * BLOCK_LEN + 0.5 * BLOCK_LEN));
			block->setZOrder(1);

			this->addChild(block);
		}
	}

	//����ͼ
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
	//���ݹؿ���ͬ�Լ���������ĳ���λ��
	spawnPointSet();

	//�ѵ�ǰλ�õĸ����Ƴ�����·��������Ϊ���
	this->removeChildByTag(coordToTag(spawnPoint.x, spawnPoint.y));

	auto spawn = PathBlock::create();

	spawn->setPosition(Vec2(spawnPoint.x * BLOCK_LEN + 0.5 * BLOCK_LEN, spawnPoint.y * BLOCK_LEN + 0.5 * BLOCK_LEN));
	spawn->setZOrder(0);
	
	//�ѳ������Ӽ���·������
	path.pushBack(spawn);

	this->addChild(spawn);

	//������Ҫ���ù�����ƶ�·��
	pathSet();

	//���յ����һ���ܲ�ͼ��
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

	//��ʾʣ���Ǯ
	auto currentMoney = Label::createWithTTF("Current money: " + std::to_string(this->money), "fonts/Marker Felt.ttf", 50);
	currentMoney->setName("currentMoney");
	currentMoney->setPosition(Vec2(visibleSize.width * 0.2, visibleSize.height - 0.5 * BLOCK_LEN));
	currentMoney->setZOrder(0);
	this->addChild(currentMoney);

	//��ʾ��ǰ����
	auto wave = Label::createWithTTF("1", "fonts/Marker Felt.ttf", 50);
	wave->setName("currentWave");
	wave->setPosition(Vec2(visibleSize.width * 0.5, visibleSize.height - 0.5 * BLOCK_LEN));
	wave->setZOrder(0);
	this->addChild(wave);

	//��ʾʣ��Ѫ��
	auto hp = Label::createWithTTF("1", "fonts/Marker Felt.ttf", 50);
	hp->setName("hp");
	hp->setPosition(Vec2(visibleSize.width * 0.8, visibleSize.height - 0.5 * BLOCK_LEN));
	hp->setZOrder(0);
	this->addChild(hp);

	//���ϽǷ��ز˵�
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

	//���Ͻ����¿�ʼ��Ϸ
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
	////��ͣ����ĳ���
	//auto pauseScene = Scene::create();

	////�����ı���ͼ
	//auto background = Sprite::create("BG.png");
	//background->setPosition(pauseScene->getContentSize() / 2);

	////���¿�ʼ��ť
	//auto restartButton = ui::Button::create("restart_normal.png", "restart_selected.png");
	//restartButton->setPosition(Vec2(pauseScene->getContentSize().width / 2, pauseScene->getContentSize().height / 2));
	////���¾ͻ����¿�ʼ��ǰ�ؿ�
	//restartButton->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
	//	switch (type)
	//	{
	//	case ui::Widget::TouchEventType::ENDED:
	//		Director::getInstance()->popScene();
	//		restart();
	//	}
	//});

	////������ť
	//auto continueButton = ui::Button::create("continue_normal.png", "continue_selected.png");
	//continueButton->setPosition(Vec2(pauseScene->getContentSize().width / 2, pauseScene->getContentSize().height * 0.7));
	////���¾ͻ������ǰ�ؿ�
	//continueButton->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
	//	switch (type)
	//	{
	//	case ui::Widget::TouchEventType::ENDED:
	//		Director::getInstance()->popScene();
	//	}
	//});

	////���ز˵���ť
	//auto returnButton = ui::Button::create("select_menu_normal.png", "select_menu_normal.png");
	//returnButton->setPosition(Vec2(pauseScene->getContentSize().width / 2, pauseScene->getContentSize().height * 0.3));
	////���¾ͻ᷵�عؿ�ѡ�����
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
	//���ж��Ʋ��Ρ����������Լ�ˢ�¼��
	waveSet();

	maxWave = wave.size();
	waveIter = wave.begin();
	currentIter = waveIter->sequence.begin();
}


void baseLevel::scheduleInit()
{
	//����ui����ʾ
	schedule(schedule_selector(baseLevel::uiUpdate));
	//�ж��Ƿ�ʤ��/ʧ��
	schedule(schedule_selector(baseLevel::winCheck));
}

PathBlock* baseLevel::addPath(int x, int y)
{
	auto ppath = PathBlock::create();

	//����x��y���������Ӧ��λ�ñ�Ϊ�����·��
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

	//���²�����Ϣ
	auto wave = this->getChildByName("currentWave");
	if (wave) {
		dynamic_cast<Label*>(wave)->setString("Current wave/Max wave: " + std::to_string(currentWave) + "/" + std::to_string(maxWave));
	}

	//����Ѫ����Ϣ
	auto hp = this->getChildByName("hp");
	if (hp) {
		dynamic_cast<Label*>(hp)->setString("Current hp: " + std::to_string(healthPoint));
	}
}

void baseLevel::monsterSpawn(float dt)
{

	//ÿ���ض���ʱ��ʹ����������е�һֻ��
	scheduleOnce(schedule_selector(baseLevel::spawnOne), waveIter->spawnInterval);
}

void baseLevel::spawnOne(float dt)
{
	//������µ�һ���֣�����µ�ǰ����
	if (currentIter == waveIter->sequence.begin())
		currentWave++;
	//�õ����������������е����й�
	auto enemy = *currentIter;
	enemy->setOpacity(255);
	this->addChild(enemy);
	currentIter++;
	//����������һֻ�֣���׼��������һֻ��
	if (currentIter != waveIter->sequence.end() && waveIter != wave.end())
		scheduleOnce(schedule_selector(baseLevel::spawnOne), waveIter->spawnInterval);
	else { //��������һֻ�֣�ֻ���ڵ�ǰ�������йֶ��������Ҳ������һ��������²ŻῪʼ������һ����
		schedule(schedule_selector(baseLevel::checkElimination));
	}
}

void baseLevel::checkElimination(float dt)
{
	auto iter = waveIter->sequence.begin();
	bool flag = 1;
	while (iter != waveIter->sequence.end()) { //�жϵ�ǰ���εĹ����Ƿ��Ѿ�������
		if ((*iter)->getParent()) {
			flag = 0;
		}
		iter++;
	}
	if (flag == 1) { //����Ѿ�����������׼��������һ���֣����߽�����Ϸ����Ϊ���в��ζ��Ѿ�������
		waveIter++;
		this->unschedule(schedule_selector(baseLevel::checkElimination));
		if (waveIter != wave.end()) //����δ���еĲ��Σ����������
		{
			currentIter = waveIter->sequence.begin();
			scheduleOnce(schedule_selector(baseLevel::spawnOne), waveIter->spawnInterval);
		}
		else { //���²������Խ�����Ϸ
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
	if (healthPoint <= 0) { //Ѫ��Ϊ0������
		loseDisplay();
		unschedule(schedule_selector(baseLevel::winCheck));
	}
	else if (currentWave > maxWave) { // ���й��ﶼ�Ѿ���������Ӯ
		winDisplay();
		unschedule(schedule_selector(baseLevel::winCheck));
	}
}

void baseLevel::winDisplay()
{
	//�����ڶ���
	levelpass = 1;
	// ����Ҫ������ҷ���ʱ���ã�������ҹ��ػ��ߵõ�����ʱ
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

	//���¿�ʼ��ť
	tryAgainButton->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
		switch (type)
		{
		case ui::Widget::TouchEventType::ENDED:
			Director::getInstance()->popScene();
			restart();
		}
	});

	//���ز˵���ť
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




