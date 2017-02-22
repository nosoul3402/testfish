//
//  GMHelpLayer.cpp
//  FishX
//
//  Created by peng on 12-12-21.
//
//

#include "GMHelpLayer.h"
//#include "GMIntroLayer.h"
#include "../Config/GMHeaderConfig.h"
#include "GMPauseLayer.h"

using namespace cocos2d;

CCScene* GMHelpLayer::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    GMHelpLayer *layer = GMHelpLayer::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

GMHelpLayer::~GMHelpLayer(){
//    setBgColor( ccc3(0, 0, 0) ,255);
    ZPLog("~GMHelpLayer");
}
// on "init" you need to initialize your instance
bool GMHelpLayer::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayerColor::init() )
    {
        return false;
    }

    this->setTouchEnabled(true);
//    setBgColor( ccc3(0, 0, 0) ,125);
//    this->setColor(color);
    this->setOpacity(125);
//    CCRemoveUnusedSpriteFrames();
//    
//    CCSprite *background = CCSprite::create("z01_2.jpg");
//	background->setPosition(ccp(WINSIZE_W/2, WINSIZE_H/2));
////    background->setScale(SCALE/2);
//    this->addChild(background,0);
    
//    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("help.plist");
//    helpNode =CCSpriteBatchNode::create("help.png");
//    this->addChild(helpNode);
    
    initElement();
    return true;
}

void GMHelpLayer::initElement()
{
    CCSprite *bg1 = CCSprite::create("Help/help007.png");
    bg1->setPosition(ccp(WINSIZE_W/2,WINSIZE_H/2));
    SetScale2(bg1,Scale_Y);
    this->addChild(bg1);
    
    float bgW = Get_W(Get_Rect(bg1));
    float bgH = Get_H(Get_Rect(bg1));
//    CCSprite *title1 = CCSprite::create("Help/help001.png");
//    title1->setPosition(ccp(bgW/2, bgH-Get_H(Get_Box(title1))/2));
//    bg1->addChild(title1 ,1);
    
    CCSprite *title2 = CCSprite::create("Help/help002.png");
    title2->setPosition(ccp(bgW/2, bgH-Get_H(Get_Box(title2))+6.5));
    bg1->addChild(title2,1);
    
    CCMenuItem *closeItem = CCMenuItemImage::create("Help/help005.png", "Help/help006.png", this, menu_selector(GMHelpLayer::backAction));
    CCMenu *closeMenu = CCMenu::create(closeItem,NULL);
    closeMenu->setPosition(bgW-Get_W(Get_Box(closeItem))/2-26,bgH-Get_H(Get_Box(closeItem))/2-10);
    bg1->addChild(closeMenu , 1, 1);
    
//    CCMenuItem *nextItem = CCMenuItemImage::create("Help/help003.png", "Help/help004.png", this, menu_selector(GMHelpLayer::nextAction));
//    CCMenu *nextMenu = CCMenu::create(nextItem,NULL);
//    nextMenu->setPosition(bgW-Get_W(Get_Box(nextItem))/2-36,Get_H(Get_Box(nextItem))/2+50);    
//    bg1->addChild(nextMenu ,1 ,1);

    
    CCSprite *help008 = CCSprite::create("Help/help008.png");
    help008->setPosition(ccp(bgW/2,bgH/2+45));
    bg1->addChild(help008);
    
    CCSprite *help009 = CCSprite::create("Help/help009.png");
    help009->setAnchorPoint(ccp(0.5,0));
    help009->setPosition(ccp(bgW/2,60));
    bg1->addChild(help009);
}


void GMHelpLayer::registerWithTouchDispatcher()
{
    //1.x
    //CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate(this, std::numeric_limits <int> ::min() , true);
    //2.x
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, /*std::numeric_limits <int> ::min()*/kCCMenuHandlerPriority, true);
    //使用int最小值做最高优先级,并且吞掉事件true
    
    CCLayer::registerWithTouchDispatcher();
}

void GMHelpLayer::removeHelpTouchDelegate()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
    this->setTouchEnabled(false);
    //    setBgColor( ccc3(0, 0, 0) ,0);
    this->setOpacity(0);
    
}

void GMHelpLayer::backAction(CCObject *pSender)
{
    GMAudioPlay::sharedAudioPlay()->playButtonEffect();
    
    if (_delegate) {
        ((GMPauseLayer*)_delegate)->closeHelpAction();
    }
    else {
        removeHelpTouchDelegate();
        this->removeAllChildrenWithCleanup(true);
    }
}

void GMHelpLayer::nextAction()
{
    
}

bool GMHelpLayer::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    
    return true;
}

void GMHelpLayer::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{

}

void GMHelpLayer::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
}

void GMHelpLayer::ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent)
{
    
}










