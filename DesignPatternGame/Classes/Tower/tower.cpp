#include "SimpleAudioEngine.h"
#include "tower.h"
#include "../Enemies/Enemy.h"
#include "../Level/baseLevel.h"
#include <cmath>
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
	state = 1;
	//attack_enemy = nullptr;
	maxLockNum = 1;
}



void Tower::onEnter()
{
	Sprite::onEnter();

	//����¼��ַ���
	auto* disp = Director::getInstance()->getEventDispatcher();

	//����һ��������
	auto listener = EventListenerTouchOneByOne::create();
	//������û�¼�
	listener->setSwallowTouches(false);

	listener->onTouchBegan = [](Touch* touch, Event* event) {
		return true;
		};
	listener->onTouchEnded = CC_CALLBACK_2(Tower::judgeListenerCallback, this); //����̧��Żᴥ��

	//�Ѽ��������ӵ�BaseBlock��
	disp->addEventListenerWithSceneGraphPriority(listener, this);
	this->schedule(static_cast<cocos2d::SEL_SCHEDULE>(&Tower::update), speed);
}
void Tower::onExit()
{
	Sprite::onExit();

	//�Ƴ��ö������еļ���
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

int Tower::get_level()
{
	return level;
}

void Tower::running_act()
{
	//��������
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

}

float Tower::get_distance(Enemy* enemy, Tower* tower)
{
	float enemy_x = enemy->getPosition().x;
	float enemy_y = enemy->getPosition().y;
	float tower_x = tower->getPosition().x;
	float tower_y = tower->getPosition().y;
	float distance = std::sqrt((fabs(enemy_x - tower_x)) * (fabs(enemy_x - tower_x)) + (fabs(enemy_y - tower_y)) * (fabs(enemy_y - tower_y)));
	return distance;
}

int Tower::getCost()
{
	return cost;
}

void Tower::clickCallback()
{
	// ����һ��DrawNode
	auto drawNode = cocos2d::DrawNode::create();
	this->getParent()->addChild(drawNode);
	drawNode->setName("yuan");

	// ������Բ��ʾ������Χ
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
	//��ȡ�¼����󣨾���Block�Լ���
	auto target = static_cast<Sprite*>(event->getCurrentTarget());
	//��ȡ���������λ��
	Vec2 tworld = touch->getLocation();
	//������λ��ת��Ϊ����λ�ã�Block�����λ�ã�
	Vec2 tlocal = target->convertToNodeSpace(tworld);

	//��ȡ����ĳߴ�
	auto size = target->getContentSize();
	auto rect = Rect(0, 0, size.width, size.height);

	//��������λ������Block�ϣ�������������ص�
	if (rect.containsPoint(tlocal)) {
		clickCallback();
		return true;
	}
	return false;
}
//�����������ˣ����ã�
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
//����һ���������
Vector<Enemy*> Tower::multiSearch()
{
	Vector<Enemy*> temp;
	//��ȡ��ǰ�������й���
	auto cur_baseLevel = dynamic_cast<baseLevel*>(this->getParent());
	if(cur_baseLevel!=nullptr)
	{
		if (cur_baseLevel->waveIter != cur_baseLevel->wave.end())
		{
			auto cur_enemy = cur_baseLevel->waveIter->sequence.begin();
			if ((*cur_enemy) != nullptr)
			{
				//�����������Ĺ�������б�
				for (auto i = cur_enemy; i != cur_baseLevel->waveIter->sequence.end(); i++)
				{
					float distance = this->get_distance((*i), this);
					if (distance <= Tower::squart && temp.size()<maxLockNum)
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

// 处理敌人更新
void Tower::handleEnemyUpdate(Enemy* enemy) {
    if (!enemy) return;

    float distance = this->get_distance(enemy, this);

    if (distance <= this->range) {
        if (atk_enemies.size() < this->maxLockNum && !atk_enemies.contains(enemy)) {
            atk_enemies.pushBack(enemy);
            this->attack_act();
        }
    } else {
        atk_enemies.eraseObject(enemy);
    }
}


void Tower::update(float dt)
{
	//�жϵ�ǰ������ʲô״̬
	//if (attack_enemy == nullptr || attack_enemy->getParent() == nullptr || get_distance(attack_enemy, this) > this->squart)//
	//	state = 1;
	int flag1 = 0, flag2 = 0;
	for (auto i = atk_enemies.begin(); i != atk_enemies.end(); i++)
	{
		if ((*i)->getParent() != nullptr)
			flag1 = 1;//���ڹ���
	}
	if (flag1 == 0)
		state = 1;
	for (auto i = atk_enemies.begin(); i != atk_enemies.end(); i++)
	{
		if (get_distance((*i), this) > this->squart)
			flag2 = 1;//���ڷ�Χ�ڹ���
	}
	if (flag2 == 0)
		state = 1;

	if ((atk_enemies.empty() == 1) || flag1 == 0 || flag2 == 0)//�����ǰ���δ��ڹ�����������״̬
		state = 1;

	if (state == 1)
	{
		CCLOG("enemy::state==1 searching...\n");
		Vector<Enemy*> cur_enemy = this->multiSearch();//��������
		if (cur_enemy.size()!=0)
		{
			state = 2;
			atk_enemies = cur_enemy;//�������������б�
		}
		else
		{
			this->stopAllActions();
			//this->running_act();
		}
	}
	if (state == 2)
	{
		if (atk_enemies.size() < maxLockNum)
		{
			Vector<Enemy*> cur_enemy = this->multiSearch();//���µ����б�
			atk_enemies = cur_enemy;
		}
		CCLOG("attack %d enemy...\n", atk_enemies.size());
		this->stopAllActions();
		this->attack_act();
		atk_enemies.clear();//ÿ�ι���֮�����
	}
}

void Tower::remove_zidan(float dt)
{
	this->removeFromParent();
}