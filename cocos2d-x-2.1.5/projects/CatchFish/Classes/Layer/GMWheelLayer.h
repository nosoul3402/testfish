//
//  GMWheelLayer.h
//  FishX
//
//  Created by peng on 13-2-28.
//
//

#ifndef __FishX__GMWheelLayer__
#define __FishX__GMWheelLayer__

#include "cocos2d.h"
#include "../Config/GMHeaderConfig.h"


USING_NS_CC;

class GMWheelLayer : public cocos2d::CCLayerColor
{
   
public:
    virtual bool init();
    GMWheelLayer();
    ~GMWheelLayer();
    CREATE_FUNC(GMWheelLayer);
    static cocos2d::CCScene* scene();
    
    CCNode              *delegateGame;
private:
    CCSpriteBatchNode *wheelBatchNode;
    CCSprite            *luck002;
    CCSprite            *luck012;
    CCSprite            *luck001;
    
    bool                isStop;//
    int                 countTimes;
    float               chooseAngle;
    int                 direction;
    float               speed_change;
    float               speed;
    
    bool                isOk;
    
    void initWheelOfFortune();
    void update(float time);
    
public:
    void showWheelOfFortune(float angle);
//    void checkReward(float angle);
private:
    ////////////////////////////////////////
    void onEnter();
    void onExit();
    
    virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    virtual void ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    virtual void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    virtual void ccTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
};


#endif /* defined(__FishX__GMWheelLayer__) */
