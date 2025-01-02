初始化money和HP
初始化空格子和背景（固定）
初始化enemy出生点位置
出生点格子初始化
设置enemy的移动路径
添加一个萝卜图层
打印ui界面（固定）
每帧都要更新的东西进行初始化scheduleInit()（固定）
初始化波次信息
开始出怪（固定）

```c++
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
```

后续子类只需要按需重写：

```c++
moneyAndHpSet();
spawnPointSet();
pathSet();
waveSet();
```

