#include "BulletFactory.h"
// This part is refactored using the Flyweight pattern.

// Define the static member variable
std::unordered_map<std::string, cocos2d::Texture2D*> BulletFactory::textureCache; 
