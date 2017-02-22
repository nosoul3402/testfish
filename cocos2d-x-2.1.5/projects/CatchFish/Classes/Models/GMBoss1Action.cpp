//
//  GMBoss1Action.cpp
//  FishX
//
//  Created by peng on 13-2-4.
//
//

#include "GMBoss1Action.h"
#include "GMBullet.h"
#include "../Config/GMHeaderConfig.h"
#include "../Layer/GMGameLayer.h"

#define boss01_plist    "fish/boss01.plist"
#define boss01_png      "fish/boss01.png"

bool GMBoss1Action::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCSprite::init() )
    {
        return false;
    }

    _isSkill1 = false;
    _index = -1;

    initBatchNode();
    initBoss();
    
    countHead = 0;
    _mouthAttackNum = 0;
    isDeath = false;

    return true;
}

GMBoss1Action::~GMBoss1Action()
{
    CCRemoveSpriteFrameByName(boss01_plist);
}

void GMBoss1Action::initBatchNode()
{
    CCAddSpriteFramesWithFile(boss01_plist);
    CCSpriteBatchNode *bossSheet = CCSpriteBatchNode::create(boss01_png);
    this->addChild(bossSheet,Bullet_Layer);
    
    CCAddSpriteFramesWithFile(boss1hand1_plist);
    CCSpriteBatchNode *boss1hand1Sheet = CCSpriteBatchNode::create(boss1hand1_png);
    this->addChild(boss1hand1Sheet,Bullet_Layer);
    
}

void GMBoss1Action::initBoss()
{
    snakeHeadsArray = new CCArray();
    _countLife = _life = 100;
    GameMode gameMode = GMPublicMethod::sharedPublicMethod()->getGameMode();
    if(gameMode == Boot_Mode)
        _shells_affect_rates = 0.5;
    else
        _shells_affect_rates = 0.1;
    //头饰
    boss01000 = CCSprite::createWithSpriteFrameName("boss01000.png");
    boss01000->setPosition(ccp(0,10));
//    this->addChild(boss01000,3,0);
    
    mouthSprite = CCSprite::createWithSpriteFrameName("boss01001.png");
    rect = Get_Box(mouthSprite);
    mouthSprite->setPosition(ccp(0,0));
    this->addChild(mouthSprite,1,1);
    
    boss01000->setPosition(ccp(Get_W(rect)/2,Get_H(rect)/2+10));
    mouthSprite->addChild(boss01000,3);
    
    //四个蛇头 左->右
    CCSprite *boss02001 = CCSprite::createWithSpriteFrameName("boss02001.png");
    boss02001->setAnchorPoint(ccp(1, 0.5));
    boss02001->setPosition(ccp(Get_W(rect)/2-40,Get_H(rect)/2+15));
    point[0] = boss02001->getPosition();
    mouthSprite->addChild(boss02001,2,2);
    GMPublicMethod::setRepeatAnimation(boss02001, 1, 8, "boss02", "png",0.1,true);
    snakeHeadsArray->addObject(boss02001);
    
    CCSprite *boss03001 = CCSprite::createWithSpriteFrameName("boss03001.png");
    boss03001->setAnchorPoint(ccp(0, 0.5));
    boss03001->setPosition(ccp(Get_W(rect)/2+40,Get_H(rect)/2+15));
    point[1] = boss03001->getPosition();;
    mouthSprite->addChild(boss03001,2,3);
    GMPublicMethod::setRepeatAnimation(boss03001, 1, 8, "boss03", "png",0.1,true);
    snakeHeadsArray->addObject(boss03001);
    
    CCSprite *boss04001 = CCSprite::createWithSpriteFrameName("boss04001.png");
    boss04001->setAnchorPoint(ccp(1, 1));
    boss04001->setPosition(ccp(Get_W(rect)/2-30,Get_H(rect)/2 ));
    point[2] = boss04001->getPosition();
    mouthSprite->addChild(boss04001,1,4);
    GMPublicMethod::setRepeatAnimation(boss04001, 1, 8, "boss04", "png",0.1,true);
    snakeHeadsArray->addObject(boss04001);
    
    CCSprite *boss05001 = CCSprite::createWithSpriteFrameName("boss05001.png");
    boss05001->setAnchorPoint(ccp(0, 1));
    boss05001->setPosition(ccp(Get_W(rect)/2+30,Get_H(rect)/2));
    point[3] = boss05001->getPosition();
    mouthSprite->addChild(boss05001,1,5);
    GMPublicMethod::setRepeatAnimation(boss05001, 1, 8, "boss05", "png",0.1,true);
    snakeHeadsArray->addObject(boss05001);
    
    //手
    boss06001 = CCSprite::createWithSpriteFrameName("boss06001.png");
    boss06001->setAnchorPoint(ccp(1, 0.5));
    boss06001->setPosition(ccp(-35,Get_H(rect)/2-80));
    this->addChild(boss06001,0,6);
    GMPublicMethod::setRepeatAnimation(boss06001, 1, 8, "boss06", "png",0.1,true);
    point[4] = boss06001->getPosition();
    
    boss07001 = CCSprite::createWithSpriteFrameName("boss07001.png");
    boss07001->setAnchorPoint(ccp(0, 0.5));
    boss07001->setPosition(ccp(35,Get_H(rect)/2-80));
    this->addChild(boss07001,0,7);
    GMPublicMethod::setRepeatAnimation(boss07001, 1, 8, "boss07", "png",0.1,true);
    point[5] = boss07001->getPosition();
}


void GMBoss1Action::setBossHurtEffect()
{
    CCTintTo *tintTo11 = CCTintTo::create(0.2f,214,0,0);
    CCTintTo *tintTo12 = CCTintTo::create(0.2f,255,255,255);
    CCActionInterval *sequence = (CCActionInterval*)CCSequence::create(tintTo11,tintTo12, NULL);
    boss01000->runAction(sequence);
    
    CCTintTo *tintTo21 = CCTintTo::create(0.2f,214,0,0);
    CCTintTo *tintTo22 = CCTintTo::create(0.2f,255,255,255);
    CCActionInterval *sequence2 = (CCActionInterval*)CCSequence::create(tintTo21,tintTo22, NULL);
    mouthSprite->runAction(sequence2);
    
    CCTintTo *tintTo31 = CCTintTo::create(0.2f,214,0,0);
    CCTintTo *tintTo32 = CCTintTo::create(0.2f,255,255,255);
    CCActionInterval *sequence3 = (CCActionInterval*)CCSequence::create(tintTo31,tintTo32, NULL);
    boss06001->runAction(sequence3);
    
    CCTintTo *tintTo41 = CCTintTo::create(0.2f,214,0,0);
    CCTintTo *tintTo42 = CCTintTo::create(0.2f,255,255,255);
    CCActionInterval *sequence4 = (CCActionInterval*)CCSequence::create(tintTo41,tintTo42, NULL);
    boss07001->runAction(sequence4);
}


void GMBoss1Action::shootBossBullet()
{
    if (_isSkill1 == false) {
        
        if (snakeHeadsArray) {
            _index++;
//            _index = 3;
            int count = snakeHeadsArray->count();
            if (_index > count-1) {
                _index = 0;
            }
            if ( count>0 && _index < count) {
                shootBulletBefore();
            }
        }
        else {
            addMouthAnimation();
        }
    }
}

void GMBoss1Action::shootBulletBefore()
{
    CCSprite *boss0x = (CCSprite*)snakeHeadsArray->objectAtIndex(_index);
    if (boss0x) {
        _tag = boss0x->getTag();
        boss0x->stopAllActions();
        char bossSubName[40] = {0};
        sprintf(bossSubName,"boss%02da",_tag);
        if (boss0x->getTag() == 2) {
            boss0x->setPosition(ccp(point[0].x,point[0].y-20));
        }
        else if (boss0x->getTag() == 3) {
            boss0x->setPosition(ccp(point[1].x,point[1].y-20));
        }
        else if (boss0x->getTag() == 4) {
            boss0x->setPosition(ccp(point[2].x,point[2].y));
        }
        else if (boss0x->getTag() == 5) {
            boss0x->setPosition(ccp(point[3].x,point[3].y));
        }
        
        GMPublicMethod::setSpriteAnimation(boss0x,1,8,bossSubName,this,callfuncN_selector(GMBoss1Action::showButtleEffect));
//         GMPublicMethod::setSpriteAnimation(boss0x,1,8,bossSubName,NULL,NULL);
    }
}

void GMBoss1Action::showButtleEffect(CCNode *pNode)
{
	CCSprite *sprite = (CCSprite*)pNode;
    CCSprite *bulletEffect = CCSprite::createWithSpriteFrameName("bossgx015.png");
    GMPublicMethod::setSpriteAnimation(bulletEffect, 15, 18, "bossgx", this, callfuncN_selector(GMBoss1Action::shootBullet));
//     GMPublicMethod::setRepeatAnimation(bulletEffect, 15, 18, "bossgx", "png",0.1);
    if (sprite->getTag() == 2) {
        bulletEffect->setPosition(ccp(-80, -150));
        bulletEffect->setScale(1.5);
    }
    else if (sprite->getTag() == 3) {
        bulletEffect->setPosition(ccp(80, -150));
        bulletEffect->setScale(1.5);
    }
    else if (sprite->getTag() == 4) {
        bulletEffect->setPosition(ccp(-55, -170));
//        bulletEffect->setScale(1.5);
    }
    else if (sprite->getTag() == 5) {
        bulletEffect->setPosition(ccp(55, -170));
        //        bulletEffect->setScale(1.5);
    }
    this->addChild(bulletEffect,0,8);
    
//    GMGameLayer *tempGame = (GMGameLayer*)delegate;
//    tempGame->shootBossBullet();
}

void GMBoss1Action::shootBullet(CCNode *pNode)
{
	CCSprite*sprtie = (CCSprite*)pNode;
    this->removeChild(sprtie, true);
    sprtie = NULL;
//    CCLOG("%d == %d ",snakeHeadsArray->count(),_index);
    if (snakeHeadsArray) {
        if (_index>= snakeHeadsArray->count()) {
            return;
        }
        CCSprite *boss0x = (CCSprite*)snakeHeadsArray->objectAtIndex(_index);
        if (boss0x) {
            int tag = boss0x->getTag();
            boss0x->stopAllActions();
            char bossSubName[40] = {0};
            sprintf(bossSubName,"boss%02d",tag);
            boss0x->setPosition(point[tag-2]);
            GMPublicMethod::setRepeatAnimation(boss0x, 1, 8, bossSubName, "png",0.1,true);
        }
    }
    
    _bulletId = 1;
    GMGameLayer *tempGame = (GMGameLayer*)delegate;
    tempGame->shootBossBullet();
    
}

void GMBoss1Action::continueAnimation(int tag)
{
    CCSprite *boss0100x = (CCSprite*)this->getChildByTag(tag);
    if (boss0100x) {
        char bossSubName[40] = {0};
        sprintf(bossSubName,"boss%02d",tag);
        GMPublicMethod::setRepeatAnimation(boss0100x, 1, 8, bossSubName, "png",0.15,true);
    }
}

void GMBoss1Action::removeSnakeheads()
{
    int count = snakeHeadsArray->count();
    if (count>0) {
//        _isSkill1 = true;
        int tag = rand()%count;
        CCSprite *temp1 = (CCSprite*)snakeHeadsArray->objectAtIndex(tag);
//        CCLOG("移除的数组上的id = %d，图层上的tag = %d",tag,temp1->getTag());
        temp1->stopAllActions();
        mouthSprite->removeChild(temp1, true);
        snakeHeadsArray->removeObjectAtIndex(tag);
        
        count = snakeHeadsArray->count();
        if (count==0) {
            snakeHeadsArray->release();
            snakeHeadsArray = NULL;
        }
    }
}

void GMBoss1Action::checkLife()
{
    ZPLog(" checkLife %f",_countLife);
//    if ( (_countLife < 86.0 && _countLife >= 85.0) || (_countLife < 71.0 && _countLife >= 70.0) ||
//         (_countLife < 56.0 && _countLife >= 55.0) || (_countLife < 41.0 && _countLife >= 40.0) ){
    
//    if ( (_countLife < 86.0 && _countLife >= 85.0) || (_countLife < 71.0 && _countLife >= 70.0) ||
//        (_countLife < 56.0 && _countLife >= 55.0) || (_countLife < 41.0 && _countLife >= 40.0) )
    if ((countHead == 0 && _countLife <= 85.0) ||
        (countHead == 1 && _countLife <= 70.0) ||
        (countHead == 2 && _countLife <= 55.0) ||
        (countHead == 3 && _countLife <= 40.0)  )
    {
        countHead++;
        removeSnakeheads();
        _isSkill1 = true;
        addEyeAnimation();
        petrifactionAnimation();
    }
}

/*
 *  眼睛动画
 */
void GMBoss1Action::addEyeAnimation()
{
    eyeSprite = CCSprite::createWithSpriteFrameName("bossgx002.png");
    GMPublicMethod::setRepeatAnimation(eyeSprite, 2, 4, "bossgx", "png", 0.1,true);
    eyeSprite->setPosition(ccp(Get_W(rect)/2,Get_H(rect)/2-35));
    mouthSprite->addChild(eyeSprite,2,10);
}

/*
 *  口吐子弹动画
 */
void GMBoss1Action::addMouthAnimation()
{    
//    GMPublicMethod::setRepeatAnimation(mouthSprite, 1, 8, "boss01", "png",0.1);
    if (_mouthAttackNum == 2) {
        _isSkill1 = true;
        addEyeAnimation();
        petrifactionAnimation();
        _mouthAttackNum = 0;
    }
    else{
        GMPublicMethod::setSpriteAnimation(mouthSprite, 1, 8, "boss01", this, callfuncN_selector(GMBoss1Action::shootMouthBulletEffect));
    }
}

void GMBoss1Action::shootMouthBulletEffect(CCNode *pNode)
{
    CCSprite *bossgx009 = CCSprite::createWithSpriteFrameName("bossgx009.png");
    bossgx009->setAnchorPoint(ccp(0.5,1));
    bossgx009->setPosition(ccp(0,-70));
    this->addChild(bossgx009,1,11);
    _tag = bossgx009->getTag();
    
    GMPublicMethod::setSpriteAnimation(bossgx009, 9, 11, "bossgx", this, callfuncN_selector(GMBoss1Action::shootMouthBullet));
}

void GMBoss1Action::shootMouthBullet(CCNode *pNode)
{
	CCSprite *sprite = (CCSprite *)pNode;
    _mouthAttackNum++;
    this->removeChild(sprite, true);;
    sprite = NULL;
    
    _bulletId = 2;
    GMGameLayer *tempGame = (GMGameLayer*)delegate;
    tempGame->shootBossBullet();
}
/*
 *  石化动作
 */
void GMBoss1Action::petrifactionAnimation()
{
    boss06001->stopAllActions();
    boss06001->setPosition(ccp(point[4].x,point[4].y-60));
//    GMPublicMethod::setRepeatAnimation(boss06001, 1, 8, "boss08", "png",0.1);
    GMPublicMethod::setSpriteAnimation(boss06001, 1, 12, "boss08", NULL, NULL);
    boss07001->stopAllActions();
    GMPublicMethod::setSpriteAnimation(boss07001, 1, 12, "boss09", NULL, NULL);
    boss07001->setPosition(ccp(point[5].x,point[5].y-60));
    
    CCMoveTo *moveTo1 = CCMoveTo::create(0.5, ccp(0, 30));
    CCMoveTo *moveTo2 = CCMoveTo::create(0.5, ccp(0, 0));
    CCCallFunc *callFunc = CCCallFunc::create(this, callfunc_selector(GMBoss1Action::petrifactionEffect));
    CCActionInterval *sequence = (CCActionInterval*)CCSequence::create(moveTo1,moveTo2,callFunc,NULL);
    mouthSprite->runAction(sequence);
}

void GMBoss1Action::petrifactionEffect()
{
    boss06001->stopAllActions();
    boss06001->setPosition(ccp(point[4].x,point[4].y));
    GMPublicMethod::setRepeatAnimation(boss06001, 1, 8, "boss06", "png",0.1,true);

    boss07001->stopAllActions();
    GMPublicMethod::setRepeatAnimation(boss07001, 1, 8, "boss07", "png",0.1,true);
    boss07001->setPosition(ccp(point[5].x,point[5].y));
    
    mouthSprite->removeChild(eyeSprite, true);
    eyeSprite = NULL;
    _isSkill1 = false;
    
    GMGameLayer *tempGame = (GMGameLayer*)delegate;
    tempGame->petrifactionEffect();
}





