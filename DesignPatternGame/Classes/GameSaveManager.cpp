// GameSaveManager.cpp
#include "GameSaveManager.h"

#include "cocos2d.h"

#include"HelloWorldScene.h"


USING_NS_CC;


void GameDataManager::saveValue(const std::string& fileName, int value) {
    std::ofstream file(fileName);
    if (file.is_open()) {
        file << value;
        file.close();
    }
}

int GameDataManager::loadValue(const std::string& fileName, int defaultValue) {
    std::ifstream file(fileName);
    int value = defaultValue;
    if (file.is_open()) {
        file >> value;
        file.close();
    }
    return value;
}