//
//  GMPauseLayer.h
//  FishX
//
//  Created by peng on 12-12-24.
//
//

#ifndef __FishX__GMPauseLayer__
#define __FishX__GMPauseLayer__

#include <iostream>
//#include "cocos2d.h"
#include "../Config/GMFashionConfig.h"
#include "GMHelpLayer.h"
#include "../PublicModels/GMNoTouchLayer.h"

class GMPauseLayer : public cocos2d::CCLayerColor
{
private:
    cocos2d::CCMenuItemSprite *item3;
    bool            isOpenVideo;
    CCSpriteBatchNode   *pauseBatchNode;
    GMHelpLayer         *helpLayer;
    
    GMNoTouchLayer      *exitLayer;
private:
    void initElement();
    
    void chooseCard(CCObject *pSender);
    void continueTheGame(CCObject *pSender);
    void enterFeedback(CCObject *pSender);
    void videoAction(CCObject *pSender);
    void helpAction(CCObject *pSender);
    void againAction(CCObject *pSender);
    void backAction(CCObject *pSender);
    
    void setExitLayer();
    void confirmAtion(CCObject *object);
    void cancelAtion(CCObject *object);
    
public:
    virtual bool init();
    GMPauseLayer();
    ~GMPauseLayer();
    static cocos2d::CCScene* scene();
    
    
    cocos2d::CCMenu *menu;
    bool m_bTouchedMenu;
    
    CREATE_FUNC(GMPauseLayer);
    
    CCNode              *delegateGame;
    
    void removeTouchDelegate();
    
    void closeHelpAction();
    bool        isShowHelp;
    ////////////////////////////////////////
    void onEnter();
    void onExit();
    
    virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    virtual void ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    virtual void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    virtual void ccTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
};

#endif /* defined(__FishX__GMPauseLayer__) */
