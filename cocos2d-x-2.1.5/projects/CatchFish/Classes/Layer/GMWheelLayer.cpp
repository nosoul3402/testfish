//
//  GMWheelLayer.cpp
//  FishX
//
//  Created by peng on 13-2-28.
//
//

#include "GMWheelLayer.h"
#include "GMGameLayer.h"

CCScene* GMWheelLayer::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    GMWheelLayer *layer = GMWheelLayer::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

GMWheelLayer::GMWheelLayer()
{
    
}

// on "init" you need to initialize your instance
bool GMWheelLayer::init()
{
    if ( !CCLayerColor::init() )
    {
        return false;
    }

    this->setColor(ccc3(0, 0, 0));
    this->setOpacity(200);
    initWheelOfFortune();
    countTimes = 0;

    return true;
}

//#pragma mark - 转盘
void GMWheelLayer::initWheelOfFortune()
{
    CCAddSpriteFramesWithFile(luck_plist);
    wheelBatchNode = CCSpriteBatchNode::create(luck_png);
    this->addChild(wheelBatchNode);
    
//    CCAddSpriteFramesAndTextureFile(luck_plist,luck_png);
    
    isStop = false;
    direction = 1;
    speed_change = 0;
    speed = 1.0;
    isOk = false;
}
void GMWheelLayer::showWheelOfFortune(float angle)
{
    CCSprite *luck000 = CCSprite::createWithSpriteFrameName("luck000.png");
    luck000->setPosition(ccp(WINSIZE_W/2, WINSIZE_H-75*Scale_X));
    this->addChild(luck000,1);
    SetScale2(luck000, Scale_Y);
    //
    luck001 = CCSprite::createWithSpriteFrameName("luck001.png");
    CCRect luckRect = Get_Rect(luck001);
    luck001->setPosition(ccp(WINSIZE_W/2, WINSIZE_H/2-20));
    this->addChild(luck001);
    SetScale2(luck001, Scale_Y);
    
    float midpointX = Get_W(luckRect)/2;
    float midpointY = Get_H(luckRect)/2+10;
    luck002 = CCSprite::createWithSpriteFrameName("luck002.png");
    luck002->setPosition(ccp(midpointX, Get_H(luckRect)/2+10));
    luck001->addChild(luck002,1,1);
    CCRect luckRect1 = Get_Rect(luck002);
    float midpointX1 = Get_W(luckRect1)/2;
    float midpointY1 = Get_W(luckRect1)/2;
//    CCRotateBy *ratateTo = CCRotateBy::create(2, 90);
//    CCRepeatForever *repeateF = CCRepeatForever::create(ratateTo);
//    luck002->runAction(repeateF);
    
    CCSprite *luck011 = CCSprite::createWithSpriteFrameName("luck011.png");
    luck011->setPosition(ccp(midpointX, midpointY));
    luck001->addChild(luck011,2,2);
    
    CCSprite *luck013 = CCSprite::createWithSpriteFrameName("luck013.png");
    luck013->setPosition(ccp(midpointX, midpointY));
    luck001->addChild(luck013,3,3);
    
    luck012 = CCSprite::createWithSpriteFrameName("luck012.png");
    luck012->setAnchorPoint(ccp(0.5, 0));
    luck012->setPosition(ccp(midpointX, midpointY));
    luck001->addChild(luck012,2,4);
    
//    CCRotateBy *ratateTo1 = CCRotateBy::create(0.1,50);
//    CCRepeatForever *repeateF1 = CCRepeatForever::create(ratateTo1);
//    luck012->runAction(repeateF1);
    
    char lunckName[30] = {0};
    for (int i = 0; i < 8; i++) {
        sprintf(lunckName, "luck%03d.png",i+3);
        CCSprite *luck = CCSprite::createWithSpriteFrameName(lunckName);
        CCRect rect = Get_Rect(luck);
        float a = DADIANS_TO_DEGREES1(360.0-i*45.0);
        float tempx = sinf(a)*(midpointX1-Get_H(rect)/2-10);
        float tempy = cosf(a)*(midpointX1-Get_H(rect)/2-10);
        luck->setPosition(ccp(midpointX1+tempx, midpointY1+tempy ));
        
        luck002->addChild(luck,2,i+10);
    }
    
    this->schedule(schedule_selector(GMWheelLayer::update), 0.001);
    chooseAngle = angle;
}

//void GMWheelLayer::checkReward(float angle)
//{
//    float spacing = 22.5;
//    int goodsId = 0;
//    if( (angle <= spacing && angle>=0) ||(angle > 360-spacing && angle <360))
//    {
//        goodsId = 1;
//    }
//    else if( angle > 45.0-spacing && angle <= 45.0+spacing )
//    {
//        goodsId = 2;
//    }
//    else if( angle > 90.0-spacing && angle <= 90.0+spacing )
//    {
//        goodsId = 3;
//    }
//    else if( angle > 135.0-spacing && angle <= 135.0+spacing )
//    {
//        goodsId = 4;
//    }
//    else if( angle > 180.0-spacing && angle <= 180.0+spacing )
//    {
//        goodsId = 5;
//    }
//    else if( angle > 225.0-spacing && angle <= 225.0+spacing )
//    {
//        goodsId = 6;
//    }
//    else if( angle > 270.0-spacing && angle <= 270.0+spacing )
//    {
//        goodsId = 7;
//    }
//    else if( angle > 315.0-spacing && angle <= 315.0+spacing )
//    {
//        goodsId = 8;
//    }
//    CCLOG("goodsId %d",goodsId);
//}

void GMWheelLayer::update(float time)
{
    if (!isStop) {
        float rotation = luck002->getRotation();
       
        if (countTimes>20) {
            speed_change = 0.1;
        }
        
        speed += direction * speed_change;
		if (direction < 0 && speed < 1) {
			speed = 1;
			speed_change = 0;
		}
        
		rotation += speed;
        
		if (speed * direction >= 20) {
			speed_change = 0;
		}
        
		if (rotation * direction > 360*3) {
			direction *= -1;
			speed_change = 0.1f;
            isOk = true;
		}
        
        float tempp = (int)rotation % 360;
//      ZPLog("%f <==> %f",chooseAngle,tempp);
//      if (countTimes >800 && chooseAngle == tempp)
        if (countTimes > 400 &&  (tempp > chooseAngle-20.0 && tempp < chooseAngle+20.0) )
        {
            isStop = true;            
            CCSprite *luck020 = CCSprite::createWithSpriteFrameName("luck020.png");
            luck020->setAnchorPoint(ccp(0.5, 0));
            luck020->setPosition(ccp(luck012->getPosition().x, luck012->getPosition().y+12));
            GMPublicMethod::setSpriteAnimation(luck020, 20, 28, "luck", delegateGame, callfuncN_selector(GMGameLayer::removeWheelView));
            luck001->addChild(luck020,1,8);
            
            this->unschedule(schedule_selector(GMWheelLayer::update));
        }
    
        for (int i = 0; i < 8; i++) {
            CCSprite *temp = (CCSprite*)luck002->getChildByTag(i+10);
            if (isStop) {
                temp->setRotation(360.0-chooseAngle);
            }
            else {
                temp->setRotation(360.0-tempp);
            }
        }
        if (isStop) {
            luck002->setRotation(chooseAngle);
        }
        else {
            luck002->setRotation(rotation);
        }
        
        
        countTimes++;
    }
}

GMWheelLayer::~GMWheelLayer()
{
    ZPLog("~~GMWheelLayer");
    CCRemoveSpriteFrameByName(luck_plist);
    CCRemoveTextureForKey(luck_png);
    
    CCRemoveSpriteFramesAndTextureForKey(luck_plist,luck_png);
}

//#pragma mark - 重构
void GMWheelLayer::onEnter()
{
    CCLayer::onEnter();
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, kCCMenuHandlerPriority - 1, true);
}

void GMWheelLayer::onExit()
{
    CCLayer::onExit();
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
}

bool GMWheelLayer::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{

    return true;
}

void GMWheelLayer::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{

}

void GMWheelLayer::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{

}

void GMWheelLayer::ccTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
 
}

