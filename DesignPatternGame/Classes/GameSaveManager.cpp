// GameSaveManager.cpp
#include "GameSaveManager.h"

#include "cocos2d.h"

#include"HelloWorldScene.h"


USING_NS_CC;


void GameDataManager::saveValue(const std::string& fileName, int value) {
    std::ofstream file(fileName, std::ios::out | std::ios::trunc);
    if (file.is_open()) {
        file << value;
        file.close();
        std::cout << "Value saved successfully." << std::endl;
    }
    else {
        std::cerr << "Failed to open the file for writing." << std::endl;
    }
}

int GameDataManager::loadValue(const std::string& fileName, int defaultValue) {
    std::ifstream file(fileName);
    int value = defaultValue;
    if (file.is_open()) {
        file >> value;
        file.close();
    }
    else {                       
        std::ofstream newFile(fileName);
        if (newFile.is_open()) {         
            newFile << defaultValue; 
            newFile.close();
        }
    }
    return value;
}