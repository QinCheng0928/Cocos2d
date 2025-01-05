// GameSaveManager.h
#pragma once
#include <fstream>
#include <iostream>

class GameDataManager
{
public:
    // Save value
    static void saveValue(const std::string& fileName, int value);

    // Load value
    static int loadValue(const std::string& fileName, int defaultValue);
};
