#ifndef __BULLETFACTORY_H__
#define __BULLETFACTORY_H__

#include "cocos2d.h"
#include <unordered_map>
#include <string>

class BulletFactory : public cocos2d::Ref {
public:
    // Cache for bullet types
    static std::unordered_map<std::string, cocos2d::Texture2D*> textureCache;

    BulletFactory() {}

    static cocos2d::Texture2D* getBulletTexture(const std::string& filename) {
        cocos2d::Texture2D* texture = nullptr;
        if (textureCache.find(filename) == textureCache.end()) {
            // 如果纹理未加载，加载并缓存
            texture = cocos2d::Director::getInstance()->getTextureCache()->addImage(filename);
            if (!texture) {
                CCLOG("Failed to load texture: %s", filename.c_str());
                return nullptr;
            }
            textureCache[filename] = texture;
        }
        else {
            // 如果纹理已存在，直接使用缓存中的纹理
            texture = textureCache[filename];
        }
		return texture;
    }
};

#endif // __BULLETFACTORY_H__
