This part is refactored using the Template Method pattern.

```c++
bool baseLevel::init()
{
    moneyAndHpSet();    // Initialize money and HP
    baseBlockInit();    // Initialize empty blocks 								(fixed)
    backgroundInit();   // Initialize the background layer 						(fixed)
    spawnPointSet();    // Initialize enemy spawn point positions
    spawnBlockInit();   // Initialize spawn point blocks						(fixed)
    pathSet();          // Set the enemy movement path
    carrotSet();        // Add the carrot layer									(fixed)
    uiInit();           // Initialize the UI interface 							(fixed)
    scheduleInit();     // Initialize the per-frame update logic 				(fixed)
    waveSet();          // Initialize wave information
    waveInit();         // Set up the specific wave details						(fixed)
    monsterSpawn(1);    // Start spawning the first wave of enemies				(fixed)

    return true;        // Return initialization success
}
```

Subsequent subclasses only need to override as needed:

```c++
moneyAndHpSet();
spawnPointSet();
pathSet();
waveSet();
```

