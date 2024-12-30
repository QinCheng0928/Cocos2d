#include "SimpleAudioEngine.h"
#include "tower.h"
#include "../Level/baseLevel.h"
#include<cmath>
USING_NS_CC;
using namespace std;
inline bool tower::init()
{
	return true;
}

tower::tower()
{
	level = 1;
	cost = 1;
	speed = 1.0f;//攻击间隔
	damage = 60;
	squart = 500.0f;
	state = 1;
	//attack_enemy = nullptr;
	maxLockNum = 1;
}



void tower::onEnter()
{
	Sprite::onEnter();

	//获得事件分发器
	auto* disp = Director::getInstance()->getEventDispatcher();

	//创建一个监听器
	auto listener = EventListenerTouchOneByOne::create();
	//不会吞没事件
	listener->setSwallowTouches(false);

	listener->onTouchBegan = [](Touch* touch, Event* event) {
		return true;
		};
	listener->onTouchEnded = CC_CALLBACK_2(tower::judgeListenerCallback, this); //按键抬起才会触发

	//把监听器添加到BaseBlock中
	disp->addEventListenerWithSceneGraphPriority(listener, this);
	this->schedule(static_cast<cocos2d::SEL_SCHEDULE>(&tower::update), speed);
}
void tower::onExit()
{
	Sprite::onExit();

	//移除该对象所有的监听
	auto* disp = Director::getInstance()->getEventDispatcher();
	disp->removeEventListenersForTarget(this);
}
void tower::set(int new_level, int new_cost, float new_speed, int new_damage,int new_squart) 
{
	level = new_level;
	cost = new_cost;
	speed = new_speed;
	damage = new_damage;
	squart = new_squart;
}

int tower::got_level()
{
	return level;
}

void tower::running_act()
{
	//待机动作
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

void tower::attack_act()
{

}

float tower::get_distance(enemy* enemy,tower* tower)
{
	float enemy_x = enemy->getPosition().x;
	float enemy_y = enemy->getPosition().y;
	float tower_x = tower->getPosition().x;
	float tower_y = tower->getPosition().y;
	float distance = std::sqrt((fabs(enemy_x - tower_x)) * (fabs(enemy_x - tower_x)) + (fabs(enemy_y - tower_y)) * (fabs(enemy_y - tower_y)));
	return distance;
}

int tower::getCost()
{
	return cost;
}

void tower::clickCallback()
{
	// 创建一个DrawNode
	auto drawNode = cocos2d::DrawNode::create();
	this->getParent()->addChild(drawNode);
	drawNode->setName("yuan");

	// 画空心圆表示攻击范围
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

bool tower::judgeListenerCallback(cocos2d::Touch* touch, cocos2d::Event* event)
{
	//获取事件对象（就是Block自己）
	auto target = static_cast<Sprite*>(event->getCurrentTarget());
	//获取点击的世界位置
	Vec2 tworld = touch->getLocation();
	//将世界位置转换为本地位置（Block的相对位置）
	Vec2 tlocal = target->convertToNodeSpace(tworld);

	//获取对象的尺寸
	auto size = target->getContentSize();
	auto rect = Rect(0, 0, size.width, size.height);

	//如果点击的位置是在Block上，则会真正触发回调
	if (rect.containsPoint(tlocal)) {
		clickCallback();
		return true;
	}
	return false;
}
//搜索单个敌人（弃用）
enemy* tower::search()
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
					if (distance <= tower::squart)
					{
						return (*i);
					}
				}
			}
		}
	}
	return nullptr;
}
//搜索一至多个敌人
Vector<enemy*> tower::multiSearch()
{
	Vector<enemy*> temp;
	//获取当前波次所有怪物
	auto cur_baseLevel = dynamic_cast<baseLevel*>(this->getParent());
	if(cur_baseLevel!=nullptr)
	{
		if (cur_baseLevel->waveIter != cur_baseLevel->wave.end())
		{
			auto cur_enemy = cur_baseLevel->waveIter->sequence.begin();
			if ((*cur_enemy) != nullptr)
			{
				//将符合条件的怪物加入列表
				for (auto i = cur_enemy; i != cur_baseLevel->waveIter->sequence.end(); i++)
				{
					float distance = this->get_distance((*i), this);
					if (distance <= tower::squart && temp.size()<maxLockNum)
					{
						temp.pushBack(*i);
						CCLOG("temp.size()==%d", temp.size());
					}
				}
			}
		}
	}
	return temp;
}

void tower::update(float dt)
{
	//判断当前炮塔是什么状态
	//if (attack_enemy == nullptr || attack_enemy->getParent() == nullptr || get_distance(attack_enemy, this) > this->squart)//
	//	state = 1;
	int flag1 = 0, flag2 = 0;
	for (auto i = atk_eny.begin(); i != atk_eny.end(); i++)
	{
		if ((*i)->getParent() != nullptr)
			flag1 = 1;//存在怪物
	}
	if (flag1 == 0)
		state = 1;
	for (auto i = atk_eny.begin(); i != atk_eny.end(); i++)
	{
		if (get_distance((*i), this) > this->squart)
			flag2 = 1;//存在范围内怪物
	}
	if (flag2 == 0)
		state = 1;

	if ((atk_eny.empty() == 1) || flag1 == 0 || flag2 == 0)//如果当前波次存在怪物，则进入搜索状态
		state = 1;

	if (state == 1)
	{
		CCLOG("enemy::state==1 searching...\n");
		Vector<enemy*> cur_enemy = this->multiSearch();//搜索怪物
		if (cur_enemy.size()!=0)
		{
			state = 2;
			atk_eny = cur_enemy;//更新炮塔锁敌列表
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
			Vector<enemy*> cur_enemy = this->multiSearch();//更新敌人列表
			atk_eny = cur_enemy;
		}
		CCLOG("attack %d enemy...\n", atk_eny.size());
		this->stopAllActions();
		this->attack_act();
		atk_eny.clear();//每次攻击之后清空
	}
}

void tower::remove_zidan(float dt)
{
	this->removeFromParent();
}