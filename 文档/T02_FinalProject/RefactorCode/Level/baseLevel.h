#ifndef _BASE_LEVEL
#define _BASE_LEVEL

#include "cocos2d.h"
#include "../Block/baseBlock.h"
#include "../Tower/tower.h"
#include "../Enemies/Factories/EnemyFactory.h"
#include "../Enemies/Factories/SoldierEnemyFactory.h"
#include "../Enemies/Factories/TankEnemyFactory.h"
#include "../Enemies/Factories/BossEnemyFactory.h"
// This part is refactored using the Template Method pattern.

/*
Base level class
Functionality:
1. Set the position of all grid blocks
2. Change the block type
3. Store economy (money)
4. Store wave information
5. Store carrot health
6. Victory/Failure screen
7. Pause screen
*/
class baseLevel : public cocos2d::Scene
{
	friend class tower;
public:
	// Position coordinates from bottom-left to top-right
#define BLOCK_X_NUM 14
#define BLOCK_Y_NUM 7
#define BLOCK_LEN 120

	int healthPoint;
	int money;
	int currentWave;
	int maxWave;
	bool stop;

	cocos2d::Map<std::string, EnemyFactory*> enemyFactories;

	struct Spawn
	{
		int x;
		int y;
	}spawnPoint;

	// Information for each wave
	struct WaveList
	{
		// Spawn interval between enemies
		float spawnInterval;
		// Spawn sequence of enemies
		Vector<Enemy*> sequence;
	};

	Vector<PathBlock*> path;

	// Store the information for all waves
	std::vector<WaveList> wave;
	// Iterator pointing to the current wave
	std::vector<WaveList>::iterator waveIter;
	// Iterator pointing to the next enemy to spawn
	Vector<Enemy*>::iterator currentIter;

	Vector<Tower*> currentTowers;

	int coordToTag(int x, int y);

	static cocos2d::Scene* createScene();
	// Initialization
	bool init();
	// Set health and initial money
	virtual void moneyAndHpSet();
	// Initialize the blocks
	void baseBlockInit();
	// Initialize the background
	void backgroundInit();
	// Set the spawn point position
	virtual void spawnPointSet();
	// Initialize the spawn block
	void spawnBlockInit();
	// Set the monster movement path
	virtual void pathSet();
	// Set the carrot position
	void carrotSet();
	// Initialize the UI
	void uiInit();
	// Switch to the pause menu scene
	void switchToPauseMenu();
	// Set the wave information
	void waveInit();
	virtual void waveSet() {}
	// Set up updates for each frame
	void scheduleInit();
	// Automatically add a new monster path
	PathBlock* addPath(int x, int y);
	// Update current economy, wave, and health
	void uiUpdate(float dt);
	// Spawn monsters
	void monsterSpawn(float dt);
	// Spawn a single monster from the sequence
	void spawnOne(float dt);
	// Check if the player has won
	void winCheck(float dt);
	// Display the win screen
	void winDisplay();
	void loseDisplay();
	// Check if all monsters in the current wave are eliminated
	void checkElimination(float dt);
	// Restart the current scene
	virtual void restart();
	// Stop all monsters and towers
	void setStop();
	// Resume all monsters and towers
	void setMove();

	CREATE_FUNC(baseLevel);
};

#endif // _BASE_LEVEL
