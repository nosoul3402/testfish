//
//  GMMainLayer.cpp
//  FishX
//
//  Created by peng on 12-12-25.
//
//
/*
 捕鱼小技巧：连击越多，得分加成越高。
 捕鱼小技巧：怒气满了，点击屏幕即可发射超级激光哦！
 捕鱼小技巧：根据情况合理选择武器才能过关哦！
 捕鱼小技巧：高倍模式虽好，可不能常用哦！
 捕鱼小技巧：你是捕鱼达人吗？快去无尽模式和全国玩家一决胜负吧！
*/

#include "GMMainLayer.h"
#include "../Config/GMHeaderConfig.h"
#include "../PublicModels/ZPJNIHelper.h"
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
//#include <jni.h>
//#include "platform/android/jni/JniHelper.h"
//#include <android/log.h>
//#define CLASS_NAME "com/cocos2dGamedo/fish/JniInterface"
//#endif

using namespace cocos2d;

const char* GMMainLayer::mainPrompt[6] = {
    "连击越多，得分加成越高。",
    "怒气满了，点击屏幕即可发射超级激光哦！", 
    "根据情况合理选择武器才能过关哦！",
    "高倍模式虽好，可不能常用哦！",
    "你是捕鱼达人吗？快去无尽模式和全国玩家一决胜负吧！",
};

CCScene* GMMainLayer::scene()
{
    CCScene *scene = CCScene::create();
    GMMainLayer *layer = GMMainLayer::create();
    scene->addChild(layer);
    return scene;
}

// on "init" you need to initialize your instance
bool GMMainLayer::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }

    GMPublicMethod::getGoldCoinsTime();
    
//    CCRemoveUnusedSpriteFrames();
    GMAudioPlay::sharedAudioPlay()->stopMyAllEffects();
    GMAudioPlay::sharedAudioPlay()->stopBGMusic();
    GMAudioPlay::sharedAudioPlay()->playBGMusic(Audio_Gmae1);
    
    CCRemoveUnusedAllSpriteFrames();
     
    gameLayer = new GMGameLayer();//GMGameLayer::create();
//    this->addChild(gameLayer,0);
    
    int bgIndex = GMPublicMethod::sharedPublicMethod()->getCheckpointsIndex();
    char bgName[20] = {0};
    sprintf(bgName,"iPhone/bg_%d.jpg",bgIndex);
    CCSprite *background = CCSprite::create(bgName);
    CCRect rect = background->getTextureRect();
	background->setPosition(ccp(WINSIZE_W/2, WINSIZE_H/2));
    if (Get_W(Get_Rect(background)) != WINSIZE_W) {
        SetScale(background);
    }
    this->addChild(background,0,111);
    
    loadingBg = CCSprite::create("home/homepage008.jpg");
    loadingBg->setPosition(ccp(WINSIZE_W/2, WINSIZE_H/2));
    SetScale(loadingBg);
    this->addChild(loadingBg,1,111);

    layer = CCLayerColor::create();
    layer->setOpacity(178.5);
    layer->setPosition(ccp(0, 0));
    this->addChild(layer,50);

    CCAddSpriteFramesWithFile(Loading_plist);
    loadBatchNode = CCSpriteBatchNode::create(Loading_png);
    layer->addChild(loadBatchNode,0);
    
    CCSprite *loadingBg0 = CCSprite::createWithSpriteFrameName("Loading03.png");
    loadingBg0->setPosition(ccp(WINSIZE_W/2,WINSIZE_H/2-100*Scale_X));
    layer->addChild(loadingBg0,0);
    SetScale(loadingBg0);
    
    CCSprite *tempLoading = CCSprite::createWithSpriteFrameName("Loading02.png");
    loadingW = Get_W(Get_Rect(tempLoading));
    loading= CCProgressTimer::create(tempLoading);
    loading->setPosition(ccp(WINSIZE_W/2,WINSIZE_H/2-100*Scale_X));
    loading->setType(kCCProgressTimerTypeBar);//
    loading->setMidpoint(ccp(0, 1));
    loading->setBarChangeRate(ccp(1, 0));
    layer->addChild(loading ,2 ,91);
    SetScale2(loading, Scale_X);
    mPercentage = 0;
    loading->setPercentage(mPercentage);
    
    loadingBg2 = CCSprite::createWithSpriteFrameName("Loading01.png");
    loadingBg2->setPosition(ccp(WINSIZE_W/2,WINSIZE_H/2-100*Scale_X));
    layer->addChild(loadingBg2,3);
    SetScale2(loadingBg2, Scale_X);
    
    loadingW = loadingW/100;
    
    loadEffect = CCSprite::createWithSpriteFrameName("Loading04.png");
    CCArray *temploading = CCArray::create();
    char strName[30] = {0};
    for (int j = 4; j <= 9; j++) {
        sprintf(strName,"Loading%02d.png",j);
        CCSpriteFrame *spriteFrame  = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(strName);
        temploading->addObject(spriteFrame);
    }
    CCAnimation *m_pAnimation = CCAnimation::createWithSpriteFrames(temploading,0.1);
    CCAnimate *animate = CCAnimate::create(m_pAnimation);
    CCRepeatForever *repeateF = CCRepeatForever::create(animate);
    CCFiniteTimeAction *sequence = CCSequence::create(repeateF,NULL);
    loadEffect->runAction(sequence);
    loadEffect->setAnchorPoint(ccp(1,0));
    loadEffect->setPosition(ccp(50,0));
    loadingBg2->addChild(loadEffect,4);
//    SetScale2(loadEffect, Scale_X);
    
    GMPublicMethod::sharedPublicMethod()->setGameObject(gameLayer);
    
    int index = rand()%5;
    
    _mainLabelt = CCLabelTTF::create(mainPrompt[index], "Verdana-Bold", 25,CCSize(WINSIZE_W, 69), kCCTextAlignmentCenter);
    _mainLabelt->setVerticalAlignment(kCCVerticalTextAlignmentCenter);
    _mainLabelt->setAnchorPoint(ccp(0, 0));
    _mainLabelt->setPosition( ccp( 0 , 26*Scale_X ));
    _mainLabelt->setColor(ccc3(0,183,238));
    layer->addChild(_mainLabelt,51);
//    SetScale2(_mainLabelt, Scale_X);
    tempEnemyAction = NULL;
    this->schedule(schedule_selector(GMMainLayer::runAction), 0);
    

    isLoading = true;
    return true;
}

void GMMainLayer::runAction(float dt)
{
    mPercentage+=1;
    if (mPercentage>100 && isLoading == true) {
        isLoading = false;
        
        removeSubLayer();
        
        this->unschedule(schedule_selector(GMMainLayer::runAction));
    }
    if (isLoading) {
        loading->setPercentage(mPercentage);
        gameLayer->loadData(mPercentage);
        CCPoint tempP = ccp(50+mPercentage*loadingW,0);
        loadEffect->setPosition(tempP);
        if(tempEnemyAction)
            tempEnemyAction->setPosition(ccp(tempP.x, tempEnemyAction->getPosition().y));
    }
    if(mPercentage == 3){
        ZPJNIHelper::sharedJNIHelper()->playCartoonVideo();
    }
    else if (mPercentage == 5) {
        addLoadFish();
    }
}

void GMMainLayer::addLoadFish()
{
    tempEnemyAction = new GMEnemyAction();
    tempEnemyAction->setInitValue();
    tempEnemyAction->_id = rand()%9+1;
    tempEnemyAction->setInitTheseProperties(this, NULL,1+Scale_X);
    tempEnemyAction->setAnchorPoint(ccp(0.5, 0.5));
    tempEnemyAction->setPosition(ccp(0,(26/2)));
    loadingBg2->addChild(tempEnemyAction,55);
//    SetScale2(tempEnemyAction, Scale_X);
    tempEnemyAction->setRotation(90);
//    CCMoveTo *moveTo = CCMoveTo::create(2, ccp(WINSIZE_W-253*Scale_X, WINSIZE_H/2));
//    tempEnemyAction->runAction(moveTo);
}

void GMMainLayer::removeSubLayer()
{
    loadEffect->stopAllActions();
    tempEnemyAction->stopAllActions();
    loadingBg2->removeChild(tempEnemyAction, true);
    tempEnemyAction->release();
    tempEnemyAction = NULL;
    
    layer->removeChild(_mainLabelt, true);
    _mainLabelt = NULL;
    
    this->removeChild(layer, true);
    this->addChild(gameLayer,0);
    
    gameLayer->setFirstBootMode();
    
    this->removeChild(loadingBg, true);
    loadingBg = NULL;
    layer = NULL;
    loading = NULL;
    loadEffect = NULL;
    loadingBg2 = NULL;
}

GMMainLayer::~GMMainLayer()
{
    GMPublicMethod::sharedPublicMethod()->setGameObject(NULL);
    
    gameLayer->release();
    gameLayer = NULL;
    
    loadBatchNode = NULL;
    gameLayer = NULL;
    CCRemoveSpriteFrameByName(Loading_plist);
    CCRemoveTextureForKey(Loading_png);
    this->cleanup();

    ZPLog("~GMMainLayer");
}




