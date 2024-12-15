#ifndef _BASE_BLOCK_H
#define _BASE_BLOCK_H

#include "cocos2d.h"
#include "ui/CocosGUI.h"

class TestBlock : public cocos2d::Sprite
{
public:
	//virtual bool init();
	static TestBlock* create();
	//virtual Sprite* newInstance();

	void onEnter();
	void onExit();

	//鼠标触发的回调函数
	bool clickReact(cocos2d::Touch* touch, cocos2d::Event* event);
};


/*格子基类
功能：
1、点击打开建造界面
2、设置建造权限
3、计算当前位置的炮塔价格（如果有炮塔），以方便计算剩余金钱

*/
class BaseBlock : public cocos2d::Sprite
{
#define UNSELECTED_OPACITY 30
#define SELECTED_OPACITY 255

public:
	unsigned long int cost;

	virtual bool init();

	static BaseBlock* create();


	//入场时加入监听，退场时移除监听
	void onEnter();
	void onExit();

	//判断是否要触发回调函数
	bool judgeListenerCallback(cocos2d::Touch* touch, cocos2d::Event* event);
	//真正触发的回调函数
	virtual void clickCallback();
	//显示一串文字一小段时间
	void scheduleFunc(float dt);
	//设置当前格子的耗费
	int setCost(int m);
};


class PathBlock : public BaseBlock
{

public:
	PathBlock* link;

	virtual bool init();

	static PathBlock* create();

	//入场时加入监听，退场时移除监听
	void onEnter();

	PathBlock* getNextPath();
};

#endif // _PATH_BLOCK_H
