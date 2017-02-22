//
//  GMBossOctopus.cpp
//  FishX
//
//  Created by peng on 13-4-1.
//
//

#include "GMBossOctopus.h"
#include "../Config/GMHeaderConfig.h"
#include "../Layer/GMGameLayer.h"

#define octopus1_plist   "fish/octopus1.plist"
#define octopus1_png     "fish/octopus1.png"

#define octopus2_plist   "fish/octopus2.plist"
#define octopus2_png     "fish/octopus2.png"

bool GMBossOctopus::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayerColor::init() )
    {
        return false;
    }

    initElement();
    setFrozen(false);
    isMove = false;
    return true;
}

GMBossOctopus::~GMBossOctopus()
{
    this->cleanup();
    CCRemoveSpriteFramesAndTextureForKey(octopus2_plist,octopus2_png);
    CCRemoveSpriteFramesAndTextureForKey(octopus1_plist,octopus1_png);
    
    ZPLog("~GMBossOctopus");
}

void GMBossOctopus::initElement()
{
    CCAddSpriteFramesAndTextureFile(octopus2_plist,octopus2_png);
    CCAddSpriteFramesAndTextureFile(octopus1_plist,octopus1_png);
    
    for (int i = 0; i < 5; i ++) {
        isShootBullet[i] = false;
        isHurt[i]		 = false;
		octopus[i]		 = NULL;
    }

	octopus[0] = GMEnemyAction::create();
	if (octopus[0]) {
		octopus[0]->initWithSpriteFrameName("octopus001.png");
		octopus[0]->setInitValue();
		GMPublicMethod::setRepeatAnimation(octopus[0], 1, 8, "octopus", "png", 0.1,true);
		octopus[0]->setAnchorPoint(ccp(0.5,0.5));
		octopus[0]->setPosition(ccp(WINSIZE_W/2,WINSIZE_H+177*Scale_X/2));
		this->addChild(octopus[0],3);
		SetScale2(octopus[0], Scale_X);
	}
    
    shootBulletTime = 6;
    reverse = 1;
    moveTo = NULL;
    isShow[0] = false;
    isShow[1] = false;
    countShootBulletTime = 0;
    countBossNum = 5;
    
    this->scheduleOnce(schedule_selector(GMBossOctopus::showBoss), 1);
}

void GMBossOctopus::showBoss(float dt)
{
    CCMoveTo *moveTo = CCMoveTo::create(1, ccp(WINSIZE_W/2, WINSIZE_H-177*Scale_X/2));
    CCCallFunc *callFunc = CCCallFunc::create(this, callfunc_selector(GMBossOctopus::setMove));
    CCFiniteTimeAction *sequence = CCSequence::create(moveTo,callFunc,NULL);
    octopus[0]->runAction(sequence);
}

void GMBossOctopus::setMove(){
    isMove = true;
}
void GMBossOctopus::setOctopusMove()
{
    if (isMove == true) {
        if (octopus[0]) {
            CCPoint oldP = octopus[0]->getPosition();
            float tempSpace = WINSIZE_W-188*Scale_X/2;
            if ( oldP.x>=tempSpace ) {
                reverse = 0;
            }
            else if( oldP.x<=188*Scale_X/2){
                reverse = 1;
            }
            if (reverse == 1) {
                oldP.x+=5;
            }
            else if(reverse == 0){
                oldP.x-=5;
            }
            
            CCPoint newP = oldP;
            octopus[0]->setPosition(newP);
            
            if (newP.x == WINSIZE_W/2) {
                checkAllLife();
            }
        }
    }
}

void GMBossOctopus::setCountShootBulletTime()
{
    setShootBulletBefore();
}

void GMBossOctopus::setShootBulletBefore()
{
    for (int i = 0; i < 5; i++) {
        if(octopus[i]){
            octopus[i]->setAttackTime(1);
            ZPLog("attack time %d == %f",octopus[i]->getAttackTime(),octopus[i]->_bullet_firing_frequency);
            if(octopus[i]->getFrozen() == false && octopus[i]->_bullet_firing_frequency == octopus[i]->getAttackTime()) {
                CCPoint newPoint = octopus[i]->getPosition();
                float cocosAngle = GMPublicMethod::pointToAngle(newPoint, ccp(WINSIZE_W/2,30*Scale_X), 1);
                newPoint = ccp(octopus[i]->getPosition().x,WINSIZE_H-187*Scale_Y);
               
                ((GMGameLayer*)_delegate)->setOctopusShootBullet(newPoint,cocosAngle);
                octopus[i]->setAttackTime(0);
            }
        }
    }
}

void GMBossOctopus::setAllFrozen(bool frozen)
{
    for (int i = 0; i < 5; i++) {
        if(octopus[i] && octopus[i]->getFrozen() == false) {
            octopus[i]->setScale(frozen);
        }
    }
}


float GMBossOctopus::getSubBossWidth(int index)
{
    if(octopus[index]){
        return octopus[index]->boundingBox().size.width;
    }
    return 0.0f;
}

CCPoint GMBossOctopus::getBossPoint(int index){
    if(octopus[index]){
        return octopus[index]->getPosition();
    }
    return CCPointZero;
}
void GMBossOctopus::setBossHurt(int index ,float hurt)
{    
    if(octopus[index]){
        octopus[index]->_life = octopus[index]->_life-hurt;
        ZPLog("伤害 %d  %f",index,octopus[index]->_life);
        isHurt[index] = false;
        octopus[index]->setHurtEffect();
        if (octopus[index]->_life<=0) {
            countBossNum--;
            showDeathEffect(index);
        }
    }
}
/*
 *
 */
void GMBossOctopus::showThreeBoos(int num)
{
    CCMoveTo *moveTo[5];
    for (int i = 1;  i < num; i++) {
        if (octopus[i]) {
            this->removeChild(octopus[i], true);
            octopus[i] = NULL;
        }
        octopus[i] = GMEnemyAction::create();
        if (octopus[i]) {
            octopus[i]->initWithSpriteFrameName("octopus001.png");
            octopus[i]->setInitValue();
            GMPublicMethod::setRepeatAnimation(octopus[i], 1, 8, "octopus", "png", 0.1,true);
            octopus[i]->setAnchorPoint(ccp(0.5,0.5));
            float tempY = WINSIZE_H-177*Scale_X/2;
            octopus[i]->setPosition(ccp(WINSIZE_W/2,tempY));
            this->addChild(octopus[i],2);
            SetScale2(octopus[i], Scale_X/2);
            octopus[i]->_bullet_firing_frequency = octopus[0]->_bullet_firing_frequency*2;
            octopus[i]->_shells_affect_rates = octopus[0]->_shells_affect_rates;
            if (i < 3) {
                octopus[i]->_life = 20.0f;
                float tempW = WINSIZE_W*((i-1+i)/4.0)+(i==1 ? 1 : -1)*(188*Scale_X/2)/2;
                moveTo[i] = CCMoveTo::create(0.5, ccp(tempW,tempY));
            }
            else {
                octopus[i]->_life = 30.0f;
                float tempW = (WINSIZE_W*(i-3)-((i-3 == 0 ? -1 :1))*((188*Scale_X/2)/2));
                moveTo[i] = CCMoveTo::create(0.5, ccp(tempW,tempY));
            }
            
            octopus[i]->runAction(moveTo[i]);
        }
    }
}

bool GMBossOctopus::checkCollision(float collisionW,CCPoint collisionP,float scale1,float scale2,int index)
{
    bool isCollision = false;
//    for (int i = 0; i < 5; i ++) {
        if (octopus[index]) {
            float tempW  = octopus[index]->boundingBox().size.width;
            CCPoint p1 = octopus[index]->getPosition();
            if (GMPublicMethod::getCollisionValue(0,0,tempW*0.5,collisionW*scale2,p1,collisionP)) {
                isHurt[index] = true;
                return true;
            }
        }
//    }
    return isCollision;
}

//#pragma mark - value
void GMBossOctopus::setValue(GMEnemy *enemy)
{
    octopus[0]->setValue(enemy);
    ZPLog("boss章鱼的当前生命值 %f",octopus[0]->_life);
}

float GMBossOctopus::getOctousLife(){
    if (octopus[0]) {
        return octopus[0]->_life;
    }
    return 0.0f;
}

bool GMBossOctopus::setAllValue(float hurt){
    if (octopus[0] && octopus[0]->_life<=0) {
        for (int i = 0; i < 5; i ++) {
            if (octopus[i]) {
                 showDeathEffect(i);
            }
//            this->removeChild(octopus[i], true);
//            octopus[i] = NULL;
        }
        return true;
    }
    return false;
}

bool GMBossOctopus::setAllValue(float hurt,int index){
    if (octopus[index] && octopus[index]->_life<=0) {
        if (octopus[index]) {
            showDeathEffect(index);
        }
        return true;
    }
    return false;
}

float GMBossOctopus::getHurt(float grade)
{
    if(octopus[0]){
        float hurt = octopus[0]->_shells_affect_rates*grade;
        return hurt;
    }
    return 0.0f;
}

bool GMBossOctopus::getHurtBOLL()
{
    return isHurt[0];
}

void GMBossOctopus::setHurt(float hurt)
{
    for (int i = 0; i < 5; i ++) {
        if (octopus[i] && isHurt[i] == true) {
            octopus[i]->_life = octopus[i]->_life-hurt;
            ZPLog("伤害 %d  %f",i,octopus[i]->_life);
            isHurt[i] = false;
            octopus[i]->setHurtEffect();
            
            if (octopus[i]->_life<=0) {
                countBossNum--;
                showDeathEffect(i);
            }
        }
    }
}

void GMBossOctopus::checkAllLife(){
    ZPLog("boss章鱼的当前生命值 %f",octopus[0]->_life);
    if(octopus[0]->_life >= 40 && octopus[0]->_life < 69 && isShow[0] == false){
        countBossNum = 2;
        showThreeBoos(3);
        isShow[0] = true;
        shootBulletTime = 5;
//        isMove = false;
        countShootBulletTime = 0;
        
    }
    else if(octopus[0]->_life < 40.0 && isShow[1] == false){
        countBossNum = 4;
        showThreeBoos(5);
        isShow[1] = true;
        shootBulletTime = 4;
        countShootBulletTime = 0;
//        isMove = false;
    }
}

void GMBossOctopus::showDeathEffect(int index)
{
    CCSprite *sprite = CCSprite::createWithSpriteFrameName("octopus030.png");
    GMPublicMethod::setSpriteAnimation(sprite, 30, 34, "octopus", this, callfuncN_selector(GMBossOctopus::removeBoss));
    sprite->setPosition(ccp(octopus[index]->getTextureRect().size.width/2, octopus[index]->getTextureRect().size.height/2));
    sprite->setTag(index);
    octopus[index]->addChild(sprite);
    
    CCFadeOut *Fadeout = CCFadeOut::create(0.1);
    octopus[index]->runAction(Fadeout);
}

void GMBossOctopus::removeBoss(CCNode *pNode)
{
	CCSprite *effect = (CCSprite*)pNode;
    int index = effect->getTag();
    this->removeChild(octopus[index], true);
    octopus[index] = NULL;
}



