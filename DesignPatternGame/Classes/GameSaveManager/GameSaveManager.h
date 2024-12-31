// GameSaveManager.h
#pragma once
#include <fstream>
#include <iostream>

class GameDataManager
{
public:
    // ����ֵ
    static void saveValue(const std::string& fileName, int value);

    // ����ֵ
    static int loadValue(const std::string& fileName, int defaultValue);
};

