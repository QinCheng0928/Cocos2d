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

	// Mouse-triggered callback function
	bool clickReact(cocos2d::Touch* touch, cocos2d::Event* event);
};


/* Base block class
Functionality:
1. Open the build interface upon clicking
2. Set building permissions
3. Calculate the cost of the turret at the current position (if a turret exists), for convenience in calculating remaining money
*/
class BaseBlock : public cocos2d::Sprite
{
#define UNSELECTED_OPACITY 30
#define SELECTED_OPACITY 255

public:
	unsigned long int cost;

	virtual bool init();

	static BaseBlock* create();

	// Add listener on entry, remove listener on exit
	void onEnter();
	void onExit();

	// Determine whether to trigger the callback function
	bool judgeListenerCallback(cocos2d::Touch* touch, cocos2d::Event* event);
	// Actual callback function trigger
	virtual void clickCallback();
	// Display a string of text for a short time
	void scheduleFunc(float dt);
	// Set the current block's cost
	int setCost(int m);
};


class PathBlock : public BaseBlock
{

public:
	PathBlock* link;

	virtual bool init();

	static PathBlock* create();

	// Add listener on entry, remove listener on exit
	void onEnter();

	PathBlock* getNextPath();
};

#endif // _PATH_BLOCK_H
