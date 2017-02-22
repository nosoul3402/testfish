//
//  GMFashionConfig.h
//  FishX
//
//  Created by peng on 13-1-6.
//
//

#ifndef FishX_GMFashionConfig_h
#define FishX_GMFashionConfig_h



#include "../PublicModels/GMAccessData.h"
#include "../PublicModels/GMPublicMethod.h"

#include "cocos2d.h"
USING_NS_CC;

#define CCAddSpriteFramesWithFile(name)  \
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(name)

#define CCRemoveSpriteFrameByName(name)  \
    CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile(name);
//    CCSpriteFrameCache::sharedSpriteFrameCache()->removeUnusedSpriteFrames()

#define CCRemoveTextureForKey(name)    \
    CCTextureCache::sharedTextureCache()->removeTextureForKey(name);

#define CCRemoveUnusedSpriteFrames()    \
    CCSpriteFrameCache::sharedSpriteFrameCache()->removeUnusedSpriteFrames(); \
    CCTextureCache::sharedTextureCache()->removeUnusedTextures();

#define CCRemoveUnusedAllSpriteFrames()    \
    CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFrames();\
    CCTextureCache::sharedTextureCache()->removeAllTextures();


/*
 *  同时加载到缓存中
 */
#define CCAddSpriteFramesAndTextureFile(plistName,picName)  \
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(plistName,picName);

#define CCRemoveSpriteFramesAndTextureForKey(plistName,picName)    \
    CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile(plistName);\
    CCTextureCache::sharedTextureCache()->removeTextureForKey(picName);
    
#endif