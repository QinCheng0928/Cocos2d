// GameSaveManager.h
#pragma once
#include <fstream>
#include <iostream>

class GameDataManager
{
public:
    // 保存值
    static void saveValue(const std::string& fileName, int value);

    // 加载值
    static int loadValue(const std::string& fileName, int defaultValue);
};

