#ifndef __BULLETFACTORY_H__
#define __BULLETFACTORY_H__

#include "cocos2d.h"
#include <unordered_map>
#include <string>

// BulletFactory class definition
// This class manages a cache of textures for bullets to optimize memory usage
class BulletFactory : public cocos2d::Ref {
public:
    // Cache for bullet textures, using an unordered_map to store textures by filename
    static std::unordered_map<std::string, cocos2d::Texture2D*> textureCache;

    BulletFactory() {}

    // Static function to get a texture for a bullet by filename
    static cocos2d::Texture2D* getBulletTexture(const std::string& filename) {
        cocos2d::Texture2D* texture = nullptr;
        
        if (textureCache.find(filename) == textureCache.end()) 
        {
            // If the texture is not in the cache, load it from file and cache it
            texture = cocos2d::Director::getInstance()->getTextureCache()->addImage(filename);
            if (!texture) {
                CCLOG("Failed to load texture: %s", filename.c_str());
                return nullptr;
            }
            // Store the loaded texture in the cache
            textureCache[filename] = texture;
        }
        else 
        {
            // If the texture is already cached, retrieve it from the cache
            texture = textureCache[filename];
        }
		return texture;
    }
};

#endif // __BULLETFACTORY_H__
