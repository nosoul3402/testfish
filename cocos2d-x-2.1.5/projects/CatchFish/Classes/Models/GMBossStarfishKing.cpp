//
//  GMBossStarfishKing.cpp
//  FishX
//
//  Created by peng on 13-4-16.
//
//

#include "GMBossStarfishKing.h"
#include "../Layer/GMGameLayer.h"

#define GemStarfishKing1_plist   "fish/GemStarfishKing1.plist"
#define GemStarfishKing1_png     "fish/GemStarfishKing1.png"

#define GemStarfishKing2_plist   "fish/GemStarfishKing2.plist"
#define GemStarfishKing2_png     "fish/GemStarfishKing2.png"

#define GemStarfishKing3_plist   "fish/GemStarfishKing3.plist"
#define GemStarfishKing3_png     "fish/GemStarfishKing3.png"
#define SPACE_TIME_1    10
#define SPACE_TIME_2    30

//bool GMBossStarfishKing::init()
//{
//    //////////////////////////////
//    // 1. super init first
//    if ( !CCSprite::init() )
//    {
//        return false;
//    }
//    initElement();
//    return true;
//}

GMBossStarfishKing::~GMBossStarfishKing()
{
//    CC_SAFE_RELEASE_NULL(m_pStarfishKing);
    this->cleanup();
    
    CCRemoveSpriteFramesAndTextureForKey(GemStarfishKing1_plist,GemStarfishKing1_png);
    CCRemoveSpriteFramesAndTextureForKey(GemStarfishKing2_plist,GemStarfishKing2_png);
    CCRemoveSpriteFramesAndTextureForKey(GemStarfishKing3_plist,GemStarfishKing3_png);
    ZPLog("~GMBossStarfishKing");
}

GMBossStarfishKing::GMBossStarfishKing()
{
    
}

void GMBossStarfishKing::initElement()
{
    CCAddSpriteFramesAndTextureFile(GemStarfishKing1_plist,GemStarfishKing1_png);
    CCAddSpriteFramesAndTextureFile(GemStarfishKing2_plist,GemStarfishKing2_png);
    CCAddSpriteFramesAndTextureFile(GemStarfishKing3_plist,GemStarfishKing3_png);
}

void GMBossStarfishKing::initStarfishKing(CCObject *target,GMEnemy *enemy)
{
    initElement();

    m_bIsMove		= true;
    m_nReverse		= 1;
    m_nCountTime	= 0;
    m_nCountNum		= 1;
    m_nCountTime2	= 0;
    m_nDTime		= 0;
    
    _delegate = target;
    
    setInitValue();
    setInitTheseProperties(target, enemy, 1);
}

void GMBossStarfishKing::setStarfishKingMove()
{
    if (m_bIsMove == true) {
        CCPoint oldP = this->getPosition();
        float tempSpace = WINSIZE_W-131/2;
        if ( oldP.x>=tempSpace ) {
            m_nReverse = 0;
        }
        else if(oldP.x<=131/2)
        {
            m_nReverse = 1;
        }
        if (m_nReverse == 1) {
            oldP.x+=5;
        }
        else if(m_nReverse == 0){
            oldP.x-=5;
        }
        CCPoint newP = oldP;
        this->setPosition(newP);
    }
}

void GMBossStarfishKing::setRunTime(int num)
{
    if (m_bIsMove) {
        m_nCountTime2++;
        
        if (m_nCountTime2 == SPACE_TIME_2 + m_nDTime && num!=0) {
            m_bIsMove = false;
            m_nDTime = 0;
            CCSprite *starEffect = CCSprite::createWithSpriteFrameName("octopus043.png");
            GMPublicMethod::setSpriteAnimation(starEffect, 42, 56, "octopus", this,callfuncN_selector(GMBossStarfishKing::setIncomeStarFish));
            starEffect->setPosition(ccp(131/2,131/2));
            this->addChild(starEffect);
            
            ((GMGameLayer*)_delegate)->setRestoreLife();
            
            m_nCountTime = 0;
            return;
        }
        else if(m_nCountTime2 == SPACE_TIME_2 && num == 0){
            m_nDTime = 10;
        }
        
        m_nCountTime++;
        if (m_nCountTime == 5) {
            CCSprite *bulletEffect = CCSprite::createWithSpriteFrameName("bullet_19_2_001.png");
            GMPublicMethod::setSpriteAnimation(bulletEffect, 1, 3, "bullet_19_2_", this,callfuncN_selector(GMBossStarfishKing::setshootStarFishBullet));
            bulletEffect->setAnchorPoint(ccp(0.5,0));
            bulletEffect->setPosition(ccp(131/2,0));
            this->addChild(bulletEffect);
            m_bIsMove = false;
        }
        else if(m_nCountTime == SPACE_TIME_1){
            m_bIsMove = false;
            CCSprite *starEffect = CCSprite::createWithSpriteFrameName("octopus043.png");
            GMPublicMethod::setSpriteAnimation(starEffect, 42, 56, "octopus", this,callfuncN_selector(GMBossStarfishKing::setCallTwoStarFish));
            starEffect->setPosition(ccp(131/2,131/2));
            this->addChild(starEffect);
        }
    }
}

void GMBossStarfishKing::setIncomeStarFish(CCNode *pNode)
{
	CCSprite *sprite = (CCSprite *)pNode;
    this->removeChild(sprite, true);
}

void GMBossStarfishKing::setCallTwoStarFish(CCNode *pNode)
{
	CCSprite *sprite = (CCSprite *)pNode;
    this->removeChild(sprite, true);
    m_nCountNum++;
    ((GMGameLayer*)_delegate)->setCallTwoStarFish(m_nCountNum);
    m_nCountTime = 0;
    m_bIsMove = true;
}

void GMBossStarfishKing::setshootStarFishBullet(CCNode *pNode)
{
	CCSprite *sprite = (CCSprite *)pNode;
    this->removeChild(sprite, true);
    CCPoint point = ccp(this->getPosition().x,this->getPosition().y-131/2);
    ((GMGameLayer*)_delegate)->setFishBullet(this->getRotation(),point,this->_id);
    m_bIsMove = true;
}

void GMBossStarfishKing::setRestoreLifeEffect(int num)
{
    CCSprite *lifeEffect = CCSprite::createWithSpriteFrameName("octopus031.png");
    GMPublicMethod::setSpriteAnimation(lifeEffect, 31, 42, "octopus", this,callfuncN_selector(GMBossStarfishKing::removeEffect));
    lifeEffect->setAnchorPoint(ccp(0.5,0));
    lifeEffect->setPosition(ccp(131/2,0));
    this->addChild(lifeEffect);
    
    float tempLifeValue = 100.0f*0.05*num;
    
    ((GMGameLayer*)_delegate)->setRestoreLifeValue(tempLifeValue);
    setStarfishKingLifeValue(tempLifeValue);
}

void GMBossStarfishKing::removeEffect(CCNode *pNode)
{
	CCSprite *sprite = (CCSprite *)pNode;
    this->removeChild(sprite, true);
    m_bIsMove = true;
    m_nCountTime2 = 0;
}


void GMBossStarfishKing::setStarfishKingLifeValue(float value)
{
    this->_life = _life+value;
//    ZPLog("伤害 %f",_life);
}

void GMBossStarfishKing::setDeathEffcet()
{
    if (_life <= 0) {
        CCPoint point = ccp(this->getContentSize().width/2,this->getContentSize().height/2);
        this->setOpacity(0);
        CCSprite *deathEffect = CCSprite::createWithSpriteFrameName("yu19d001.png");
        GMPublicMethod::setSpriteAnimation(deathEffect, 1, 3, "yu19d", this, callfuncN_selector(GMBossStarfishKing::removeDeathEffect));
        deathEffect->setPosition(point);
        this->addChild(deathEffect);
        this->stopAllActions();
        m_bIsMove = false;
    }
}

void GMBossStarfishKing::removeDeathEffect(CCNode *pNode)
{
	CCSprite *sprite = (CCSprite *)pNode;
    this->removeChild(sprite, true);
    ((GMGameLayer*)_delegate)->removeStarfishKing();
    
}
