#include "SimpleAudioEngine.h"
#include "Tower.h"
#include "../Level/baseLevel.h"
#include<cmath>
#include "EnemyNotifyManager.h"
USING_NS_CC;
using namespace std;
inline bool Tower::init()
{
	return true;
}

Tower::Tower()
{
	level = 1;
	cost = 1;
	speed = 1.0f;
	damage = 60;
	squart = 500.0f;
	state = 1;
	//attack_enemy = nullptr;
	maxLockNum = 1;
}

void Tower::onEnter()
{
	Sprite::onEnter();
    EnemyNotifyManager::getInstance()->addObserver(this);
    CCLOG("Tower::onEnter() is running..");

	
	auto* disp = Director::getInstance()->getEventDispatcher();

	
	auto listener = EventListenerTouchOneByOne::create();
	
	listener->setSwallowTouches(false);

	listener->onTouchBegan = [](Touch* touch, Event* event) {
		return true;
		};
	listener->onTouchEnded = CC_CALLBACK_2(Tower::judgeListenerCallback, this); 

	
	disp->addEventListenerWithSceneGraphPriority(listener, this);
	this->schedule(static_cast<cocos2d::SEL_SCHEDULE>(&Tower::update), speed);
}
void Tower::onExit()
{
    EnemyNotifyManager::getInstance()->removeObserver(this);
	Sprite::onExit();

	
	auto* disp = Director::getInstance()->getEventDispatcher();
	disp->removeEventListenersForTarget(this);
}
void Tower::set(int new_level, int new_cost, float new_speed, int new_damage,int new_squart) 
{
	level = new_level;
	cost = new_cost;
	speed = new_speed;
	damage = new_damage;
	squart = new_squart;
}

int Tower::got_level()
{
	return level;
}

void Tower::running_act()
{
	
	auto rotateTo1 = RotateTo::create(0.6f, 5.0f);
	auto rotateTo2 = RotateTo::create(0.6f, -5.0f);
	//auto moveBy1 = MoveBy::create(0.3f, Vec2(0, 10));
	//auto moveBy2 = MoveBy::create(0.3f, Vec2(0, -10));

	auto seq1 = Sequence::create(rotateTo1, rotateTo2, nullptr);
	/*auto seq2 = Sequence::create(moveBy1, moveBy2, moveBy1, moveBy2, nullptr);
	auto Spawn1 = Spawn::createWithTwoActions(seq1, seq2);*/
	auto seqf = RepeatForever::create(seq1);
	this->runAction(seqf);
}

void Tower::attack_act()
{
	return;
}

float Tower::get_distance(Enemy* enemy,Tower* Tower)
{
	float enemy_x = enemy->getPosition().x;
	float enemy_y = enemy->getPosition().y;
	float Tower_x = Tower->getPosition().x;
	float Tower_y = Tower->getPosition().y;
	float distance = std::sqrt((fabs(enemy_x - Tower_x)) * (fabs(enemy_x - Tower_x)) + (fabs(enemy_y - Tower_y)) * (fabs(enemy_y - Tower_y)));
	return distance;
}

int Tower::getCost()
{
	return cost;
}

void Tower::clickCallback()
{
	
	auto drawNode = cocos2d::DrawNode::create();
	this->getParent()->addChild(drawNode);
	drawNode->setName("yuan");

	
	//drawNode->drawDot(this->getPosition(), this->squart, cocos2d::Color4F::WHITE);
	//drawNode->drawCircle(this->getPosition(), this->squart, 0, segments, false, lineWidth, cocos2d::Color4F::WHITE);
	drawNode->drawCircle(this->getPosition(), this->squart, 0, 100, false, cocos2d::Color4F::WHITE);

	const std::string filename = getPicName();
	auto upgradeButton = ui::Button::create(filename);
	auto sellButton = ui::Button::create("sell_button.png");

	auto myWidth = this->getContentSize().width;
	auto myHeight = this->getContentSize().height;

	auto myPosition = this->getPosition();
	auto myPosY = myPosition.y;
	auto myPosX = myPosition.x;

	upgradeButton->setPosition(Vec2(myPosX, myPosY + myWidth));
	sellButton->setPosition(Vec2(myPosX, myPosY - myWidth));

	upgradeButton->setName("upgrade");
	sellButton->setName("sell");

	upgradeButton->setSwallowTouches(false);
	sellButton->setSwallowTouches(false);


	upgradeButton->addTouchEventListener([&](Ref* Sender, ui::Widget::TouchEventType type) {
		switch (type)
		{
		default:
			break;
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED:
			this->getParent()->removeChildByName("upgrade");
			this->getParent()->removeChildByName("sell");
			this->getParent()->removeChildByName("layer");
			this->getParent()->removeChildByName("yuan");

			auto parent = dynamic_cast<baseLevel*>(this->getParent());
			if (parent->money >= upgradeCost)
			{
				levelup(this->level + 1);
				parent->money -= upgradeCost;
			}
			return true;
			break;
		}

	});

	sellButton->addTouchEventListener([&](Ref* Sender, ui::Widget::TouchEventType type) {
		switch (type)
		{
		default:
			break;
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED:
			this->getParent()->removeChildByName("upgrade");
			this->getParent()->removeChildByName("sell");
			this->getParent()->removeChildByName("layer");
			this->getParent()->removeChildByName("yuan");

			auto base = BaseBlock::create();
			base->setPosition(this->getPosition());
			this->getParent()->addChild(base);
			dynamic_cast<baseLevel*>(this->getParent())->money += 0.75 * cost;
			this->removeFromParent();

			return true;
			break;
		}

	});

	auto layer = Node::create();
	layer->setName("layer");
	auto* disp = Director::getInstance()->getEventDispatcher();

	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);

	listener->onTouchBegan = [](Touch* touch, Event* event) {
		return true;
		};

	listener->onTouchMoved = [](Touch* touch, Event* event) {

		};

	listener->onTouchEnded = [=](cocos2d::Touch* touch, cocos2d::Event* event) {
		this->getParent()->removeChildByName("upgrade");
		this->getParent()->removeChildByName("sell");
		this->getParent()->removeChildByName("layer");
		this->getParent()->removeChildByName("yuan");
		};

	upgradeButton->setZOrder(4);
	sellButton->setZOrder(4);
	layer->setZOrder(3);

	disp->addEventListenerWithSceneGraphPriority(listener, layer);

	this->getParent()->addChild(upgradeButton);
	this->getParent()->addChild(sellButton);
	this->getParent()->addChild(layer);
}

bool Tower::judgeListenerCallback(cocos2d::Touch* touch, cocos2d::Event* event)
{
	
	auto target = static_cast<Sprite*>(event->getCurrentTarget());
	
	Vec2 tworld = touch->getLocation();
	
	Vec2 tlocal = target->convertToNodeSpace(tworld);

	
	auto size = target->getContentSize();
	auto rect = Rect(0, 0, size.width, size.height);

	
	if (rect.containsPoint(tlocal)) {
		clickCallback();
		return true;
	}
	return false;
}

Enemy* Tower::search()
{
	auto cur_baseLevel = dynamic_cast<baseLevel*>(this->getParent());
	if(cur_baseLevel!=nullptr)
	{
		if (cur_baseLevel->waveIter != cur_baseLevel->wave.end())
		{
			auto cur_enemy = cur_baseLevel->waveIter->sequence.begin();
			if ((*cur_enemy) != nullptr)
			{
				for (auto i = cur_enemy; i != cur_baseLevel->waveIter->sequence.end(); i++)
				{
					float distance = this->get_distance((*i), this);
					if (distance <= Tower::squart)
					{
						return (*i);
					}
				}
			}
		}
	}
	return nullptr;
}

Vector<Enemy*> Tower::multiSearch()
{
	Vector<Enemy*> temp;
	for (auto e : observedEnemies) {
        float distance = this->get_distance(e, this);
        if (distance <= this->squart && temp.size() < maxLockNum) {
            temp.pushBack(e);
        }
    }
	return temp;
}
void Tower::updateEnemyList(Enemy* enemy, bool isCreated)
{
	return;
}


void Tower::update(float dt)
{
	
	//if (attack_enemy == nullptr || attack_enemy->getParent() == nullptr || get_distance(attack_enemy, this) > this->squart)//
	//	state = 1;
	int flag1 = 0, flag2 = 0;
	for (auto i = atk_eny.begin(); i != atk_eny.end(); i++)
	{
		if ((*i)->getParent() != nullptr)
			flag1 = 1;
	}
	if (flag1 == 0)
		state = 1;
	for (auto i = atk_eny.begin(); i != atk_eny.end(); i++)
	{
		if (get_distance((*i), this) > this->squart)
			flag2 = 1;
	}
	if (flag2 == 0)
		state = 1;

	if ((atk_eny.empty() == 1) || flag1 == 0 || flag2 == 0)
		state = 1;

	if (state == 1)
	{
		//CCLOG("enemy::state==1 searching...\n");
		Vector<Enemy*> cur_enemy = this->multiSearch();
		if (cur_enemy.size()!=0)
		{
			state = 2;
			atk_eny = cur_enemy;
		}
		else
		{
			this->stopAllActions();
			//this->running_act();
		}
	}
	if (state == 2)
	{
		if (atk_eny.size() < maxLockNum)
		{
			Vector<Enemy*> cur_enemy = this->multiSearch();
			atk_eny = cur_enemy;
		}
		CCLOG("attack %d enemy...\n", atk_eny.size());
		this->stopAllActions();
		this->attack_act();
		atk_eny.clear();
	}
}

void Tower::remove_zidan(float dt)
{
	this->removeFromParent();
}