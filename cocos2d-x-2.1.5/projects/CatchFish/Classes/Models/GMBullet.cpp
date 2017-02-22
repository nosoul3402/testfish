//
//  GMBullet.cpp
//  FishX
//
//  Created by peng on 12-12-21.
//
//

#include "GMBullet.h"
#include "../Config/GMFashion_Config.h"
#include "../Config/GMConfig.h"
#include "../Layer/GMGameLayer.h"

using namespace cocos2d;

const int GMBullet::_actor[]={3,3,3,3,6,6};

bool GMBullet::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCSprite::init() )
    {
        return false;
    }
    
    return true;
}

GMBullet::GMBullet()
{
    for (int i = 0; i < MAX_BULLET_NUM; i++) {
        m_nNotesFishTag[i] = 0;
        if (i< MAX_BULLET_NUM_1)
            m_nNotesBulletTag[i] = 0;
    }
}

GMBullet* GMBullet::createBulletName(const char *name)
{
    GMBullet *bullet = (GMBullet*)CCSprite::create(name);
    
    return bullet;
}

GMBullet* GMBullet::createBulletFrame(CCSpriteFrame *frame)
{
    GMBullet *bullet = (GMBullet*)CCSprite::createWithSpriteFrame(frame);
    return bullet;
}

GMBullet* GMBullet::createBulletFrameName(const char *pszSpriteFrameName)
{
    GMBullet *bullet = (GMBullet*)CCSprite::createWithSpriteFrameName(pszSpriteFrameName);
    return bullet;
}

void GMBullet::setCannonBullerValue(int index,float angle,float cannonX){
    char bulletName[30] = {0};
    sprintf(bulletName,"bomb%02d%03d.png",index,1);

    this->initWithSpriteFrameName(bulletName);
    isLaser = false;
    _grade = index;
    float tempy = 75*Scale_Y;
    float a = DADIANS_TO_DEGREES1(angle);
    float tempx = tempy*sinf(a);
    tempy = tempy*cosf(a);
    tempx = cannonX+tempx;
    CCPoint point = ccp(tempx, tempy);
    this->setPosition(point);
    this->setRotation(angle);
    this->setBullerAnimation(index);
    SetScale2(this, FISH_SCALE);
}

void GMBullet::setFishBullerValue(int bulletId,CCPoint point,GMFishBullet*value){
    _id = bulletId;
    char fishBullet[20] = {0};
    sprintf(fishBullet,"bullet_%d_1_000.png",_id);
    this->initWithSpriteFrameName(fishBullet);
    sprintf(fishBullet,"bullet_%d_1_",_id);
                            //1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18
//    const int _bExplosion[] = {0,0,0,0,0,0,0,0,0, 0, 0, 0, 0, 3, 0, 0, 0, 0,3};
    int index = GMPublicMethod::_bExplosion[bulletId-1];
    if(index>0)
        GMPublicMethod::setRepeatAnimation(this, 0, index, fishBullet, "png", 0.1, false);
    this->setPosition( point );
    setValue(value);
   
    if (index==0) {
        CCRotateBy *rotate = CCRotateBy::create(0.5, 30);
        CCRepeatForever *repeateF = CCRepeatForever::create(rotate);
        this->runAction(repeateF);
    }
    
    SetScale2(this, FISH_SCALE);
    _k = (point.y-20)/(point.x-WINSIZE_W/2);
}

void GMBullet::setValue(GMFishBullet *value)
{
    if (value) {
        _id = value->_id;
        _speed = value->_speed;
        _hurt_Value = value->_hurt_Value;
        _angle_Value = value->_angle_Value;
        _life_Value = value->_life_Value;
        _rates_Value = value->_rates_Value;
        isRotationAndMove = false;
    }
}

void GMBullet::setBullerAnimation(int index)
{
    CCArray *temp = CCArray::create();
    char strName[40] = {0};
    
    int tempA = _actor[index-1];
    
    for (int j = 1; j <= tempA; j++) {
        sprintf(strName,"bomb%02d%03d.png",index,j);
        CCSpriteFrame *spriteFrame  = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(strName);
        temp->addObject(spriteFrame);
    }
    CCAnimation *m_pAnimation = CCAnimation::createWithSpriteFrames(temp,0.1);
    CCAnimate *animate = CCAnimate::create(m_pAnimation);
    CCRepeatForever *repeateF = CCRepeatForever::create(animate);
    CCFiniteTimeAction *sequence = CCSequence::create(repeateF,NULL);
    this->runAction(sequence);
}

void GMBullet::setLaserAnimation(CCObject* pSelectorTarget, SEL_CallFuncN selector)
{
//    GMPublicMethod::setRepeatAnimation(this, 1, 5, "jiguang", "png", 0.1);
    
    CCArray *temp = CCArray::create();
    char strName[40] = {0};
    for (int j = 1; j <= 5; j++) {
        sprintf(strName,"jiguang%03d.png",j);
        CCSpriteFrame *spriteFrame  = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(strName);
        temp->addObject(spriteFrame);
    }
    CCAnimation *m_pAnimation = CCAnimation::createWithSpriteFrames(temp,0.2);
    CCAnimate *animate = CCAnimate::create(m_pAnimation);
//    CCRepeatForever *repeateF = CCRepeatForever::create(animate);
    CCCallFuncN *callFunc = CCCallFuncN::create(pSelectorTarget, selector);
    CCFiniteTimeAction *sequence = CCSequence::create(animate,callFunc,NULL);
    this->runAction(sequence);
}



void GMBullet::bulletMove()
{
    CCPoint oldPoint = this->getPosition();
    float tempx1 = _speed;
    float tempy1 = tempx1*_k;
    
//    CCLOG(" (%f,%f)",tempx1,tempy1);
    CCPoint newPoint;
    if (oldPoint.x-WINSIZE_W/2 == 0) {
        tempy1 = -_speed;
        newPoint = ccp(oldPoint.x,oldPoint.y+tempy1);
    }
    else {
        if(_k < -5){
            tempx1 = _speed/10;
            tempy1 = tempx1*_k;
//            CCLOG(" (%f,%f)",tempx1,tempy1);
            newPoint = ccp(oldPoint.x+tempx1,oldPoint.y+tempy1);
        }
        else if(_k < 0){
            newPoint = ccp(oldPoint.x+tempx1,oldPoint.y+tempy1);
        }
        else if(_k > 5 ){
            tempx1 = _speed/10;
            tempy1 = tempx1*_k;
            newPoint = ccp(oldPoint.x-tempx1,oldPoint.y-tempy1);
        }
        else if(_k > 0)
        {
            newPoint = ccp(oldPoint.x-tempx1,oldPoint.y-tempy1);
        }
        else{}
    }
    this->setPosition(newPoint);
}

void GMBullet::cannonBulletMove()
{
    CCPoint oldPoint = this->getPosition();
    float a = DADIANS_TO_DEGREES1(this->getRotation());
    _k = 10;
    float tempx = _k*sinf(a);
    float tempy = _k*cosf(a);
    CCPoint point = ccp(oldPoint.x+tempx, oldPoint.y+tempy);
    this->setPosition(point);
}

void GMBullet::fishBulletMove(CCPoint eP,float moveTime)
{
    float c =  (WINSIZE_W/2)*(WINSIZE_W/2)+WINSIZE_H*WINSIZE_H;
    float cc = (sqrtf(c));
//    CCPoint sP = this->getPosition();
//    float moveDiff = ccpDot(sP,eP);
//    float diff1 = sqrtf(moveDiff);
    
//    ZPLog("time = %f %f",cc,diff1);
    CCPoint shootVector = ccpSub(eP, this->getPosition());
    CCPoint normalizedShootVector = ccpNormalize(shootVector);
    CCPoint overshotVector = ccpMult(normalizedShootVector, cc);
    CCPoint offscreenPoint = ccpAdd(this->getPosition(), overshotVector);
    
//    float moveTime = (fabs( moveDiff / c )) * 5.0;
//    float dt = 2.0f;
//    ZPLog("time = %f",moveTime);
    CCMoveTo *moveTo = CCMoveTo::create(moveTime,offscreenPoint);
    CCCallFuncN *callfuncN = CCCallFuncN::create(this, callfuncN_selector(GMBullet::removeCollisionBullet));
    CCFiniteTimeAction* sequence = CCSequence::create(moveTo,callfuncN,NULL);
    this->runAction(sequence);
}

void GMBullet::removeCollisionBullet(CCNode *pNode)
{
	GMBullet *bullet = (GMBullet *)pNode;
    ((GMGameLayer*)_delegate)->removeCollisionFishBullet(bullet);

}

void GMBullet::setRotationAndMove()
{
    CCPoint oldPoint = this->getPosition();
    CCPoint newPoint;
    
    float anger = this->getRotation();
    anger += 50;
    this->setRotation(anger);
    if (!isRotationAndMove) {
        isRotationAndMove = true;
        this->stopAllActions();
        
        CCPoint moveToPoint = ccp(WINSIZE_W/2,WINSIZE_H/2);
        CCMoveTo *moveTo = CCMoveTo::create(0.6, moveToPoint);
        CCScaleTo *scaleTo = CCScaleTo::create(0.6, 0);
//        CCRotateBy *rotateBy = CCRotateBy::create(0.6,50);
        CCActionInterval * action = (CCActionInterval*)CCSpawn::create(moveTo, scaleTo,NULL);
        CCCallFuncN *callFunc = CCCallFuncN::create(this, callfuncN_selector(GMBullet::removeBullet));
        CCActionInterval* sequence = (CCActionInterval*)CCSequence::create(action,callFunc,NULL);
        this->runAction(sequence);
    }
}

//#pragma mark - 检查碰撞
/*
 *  激光
 */
bool GMBullet::checkCollision(float collisionW,CCPoint collisionP,float scale1,float scale2)
{
    float tempW = this->getContentSize().width*0.5;
    
    bool isCollision = false;
    float collisionImageSize = collisionW;
    float collisionRadius = collisionImageSize * scale2;

    CCPoint p1 = this->getPosition();
    CCPoint p2 = collisionP;
    
    if(isLaser){
        float angle = this->getRotation();
//        ZPLog("%f",angle);
        for (int i = 0;  i <= 20; i++) {
            float tempWW =  (i==0) ? -1*tempW : i*tempW;
            //        ZPLog("jiguang %f",tempWW);
            if (GMPublicMethod::getCollisionValue(angle,tempWW,tempW,collisionRadius,p1,p2)) {
                return  true;
            }
        }
    }
    else {
        if (GMPublicMethod::getCollisionValue(0,0,tempW,collisionRadius,p1,p2)) {
            return  true;
        }
    }
    return isCollision;
}

bool GMBullet::checkCollision1(float collisionW,CCPoint collisionP,float collisionA)
{
    bool isCollision = false;
    
    if (GMPublicMethod::checkRectContainsPoint(CCRect(0, 0, WINSIZE_W, WINSIZE_H),collisionP)) {
    }
    else {
        return false;
    }
    
    CCPoint p2 = collisionP;

    float collisionW1 = 70;
    float a = DADIANS_TO_DEGREES1(collisionA);
    float tempx = sinf(a)*collisionW1;
    float tempy = cosf(a)*collisionW1;
    CCPoint p3 = ccp(p2.x+tempx,p2.y+tempy);
    if (checkCollision(collisionW,p3,1,0.25)) {
        return  true;
    }
    collisionW1 = 36;
    tempx = sinf(a)*collisionW1;
    tempy = cosf(a)*collisionW1;
    p3 = ccp(p2.x+tempx,p2.y+tempy);
    if (checkCollision(collisionW,p3,1,0.25)) {
        return  true;
    }
    collisionW1 = 0;
    tempx = sinf(a)*collisionW1;
    tempy = cosf(a)*collisionW1;
    p3 = ccp(p2.x+tempx,p2.y+tempy);
    if (checkCollision(collisionW,p3,1,0.2)) {
        return  true;
    }
    collisionW1 = -36;
    tempx = sinf(a)*collisionW1;
    tempy = cosf(a)*collisionW1;
    p3 = ccp(p2.x+tempx,p2.y+tempy);
    if (checkCollision(collisionW,p3,1,0.15)) {
        return  true;
    }
    collisionW1 = -50;
    tempx = sinf(a)*collisionW1;
    tempy = cosf(a)*collisionW1;
    p3 = ccp(p2.x+tempx,p2.y+tempy);
    if (checkCollision(collisionW,p3,1,0.1)) {
        return  true;
    }
    collisionW1 = -65;
    tempx = sinf(a)*collisionW1;
    tempy = cosf(a)*collisionW1;
    p3 = ccp(p2.x+tempx,p2.y+tempy);
    if (checkCollision(collisionW,p3,1,0.1)) {
        return  true;
    }
    collisionW1 = -80;
    tempx = sinf(a)*collisionW1;
    tempy = cosf(a)*collisionW1;
    p3 = ccp(p2.x+tempx,p2.y+tempy);
    if (checkCollision(collisionW,p3,1,0.1)) {
        return  true;
    }
    return isCollision;
}
//#pragma mark - bullet  tag
void GMBullet::setBulletTag(int tag){
    this->setTag(tag);
}

//#pragma mark - removeBullet
void GMBullet::removeBullet(CCNode *pNode)
{	
	GMBullet *bullet = (GMBullet *)pNode;
    ((GMGameLayer*)_delegate)->removeFishBullet(bullet);
}


//#pragma mark - fish  tag
void GMBullet::setNotesFishTag(int tag)
{
    for (int i = 0; i < MAX_BULLET_NUM; i ++) {
        if (m_nNotesFishTag[i] == 0) {
            m_nNotesFishTag[i] = tag;
            break;
        }
    }
}

bool GMBullet::getNotesFishTag(int tag)
{
    for (int i = 0; i < MAX_BULLET_NUM; i ++) {
        if (m_nNotesFishTag[i] == tag) {
            return true;
        }
    }
    return false;
}

//#pragma mark - bullet tag
void GMBullet::setNotesBulletTag(int tag)
{
    for (int i = 0; i < MAX_BULLET_NUM_1; i ++) {
        if (m_nNotesBulletTag[i] == 0) {
            m_nNotesBulletTag[i] = tag;
            break;
        }
    }
}

bool GMBullet::getNotesBulletTag(int tag)
{
    for (int i = 0; i < MAX_BULLET_NUM_1; i ++) {
        if (m_nNotesBulletTag[i] == tag) {
            return true;
        }
    }
    return false;
}

GMBullet::~GMBullet()
{
    _delegate = NULL;
    this->cleanup();
//    ZPLog("~GMBullet");
}



