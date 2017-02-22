//
//  GMMainLayer.h
//  FishX
//
//  Created by peng on 12-12-25.
//
//

#ifndef __FishX__GMMainLayer__
#define __FishX__GMMainLayer__

#include <iostream>
//#include "cocos2d.h"
#include "../Config/GMFashionConfig.h"
//#include "AppDelegate.h"

#include "GMGameLayer.h"
#include "../PublicModels/GMNoTouchLayer.h"

class GMMainLayer : public cocos2d::CCLayer
{
protected:
    CCSprite            *loadEffect;
private:
    CCSpriteBatchNode   *loadBatchNode;
    CCProgressTimer     *loading;
    
    int                 mPercentage;
    bool                isLoading;
    CCLayerColor        *layer;
//    GMNoTouchLayer      *layer;
//    AppDelegate         *deleagte;
    GMGameLayer         *gameLayer;
    
    float               loadingW;
    static const char   *mainPrompt[];
    CCLabelTTF          *_mainLabelt;
    CCSprite            *loadingBg;
    GMEnemyAction       *tempEnemyAction;
    CCSprite            *loadingBg2;
private:

    void initElement();
    void backAction();
    void runAction(float dt);
    
    void addLoadFish();
    void removeSubLayer();
public:
    virtual bool init();
    virtual ~GMMainLayer(void);
    static cocos2d::CCScene* scene();
    
    CREATE_FUNC(GMMainLayer);
};
#endif /* defined(__FishX__GMMainLayer__) */
