//
//  GMBossPoseidon.cpp
//  FishX
//
//  Created by peng on 13-5-7.
//
//

#include "GMBossPoseidon.h"
#include "../Layer/GMGameLayer.h"

//#pragma mark - GMBossPoseidon
GMBossPoseidon::GMBossPoseidon()
{
    initData();
}

GMBossPoseidon::~GMBossPoseidon()
{
    m_pBossPoseidon->release();
    m_pBossPoseidon = NULL;
    if(attackEffect){
        this->removeChild(attackEffect, true);
        attackEffect = NULL;
    }
    CCRemoveSpriteFramesAndTextureForKey(bossPoseidon1_plist, bossPoseidon1_png);
    CCRemoveSpriteFramesAndTextureForKey(bossPoseidon2_plist, bossPoseidon2_png);
    CCRemoveSpriteFramesAndTextureForKey(bossPoseidonEffect_plist, bossPoseidonEffect_png);
}

//#pragma mark - 初始

void GMBossPoseidon::initData()
{
    loadTime		= 0;
    _d				= 1;
    teleportTime	= 0;
    bulletNum		= 3;
	teleportStatus	= 0;
	teleportNum		= 0;

    attackEffect	= NULL;
    
    isTeleport		= true;
	isStopMove		= false;
    isDeath			= false;

    this->schedule(schedule_selector(GMBossPoseidon::updataStatus));
    loadTexture(loadTime);
}

//#pragma mark - 加载纹理
void GMBossPoseidon::updata()
{
    loadTime++;
    teleportTime ++;
    if(teleportStatus == 0 && loadTime == m_pBossPoseidon->_bullet_firing_frequency){
        isStopMove = true;
        m_pBossPoseidon->setAttackAnimation("c", this, callfuncN_selector(GMBossPoseidon::showBossPoseidonBullet));
        showAttackEffect();
        isTeleport = false;
    }
    else if((teleportStatus == 1 && teleportNum == 3 && isTeleport) ||
            (teleportStatus == 2 && teleportNum == 2 && isTeleport) ){
        isStopMove = false;
        isTeleport = false;
        loadTime = 0;
    }

    if ( (teleportStatus == 1 && teleportNum == 3 && loadTime == 2) ||
        (teleportStatus == 2 && teleportNum == 2 && loadTime == 1)) {
        isStopMove = true;
        m_pBossPoseidon->setAttackAnimation("c", this, callfuncN_selector(GMBossPoseidon::showBossPoseidonBullet));
        showAttackEffect();
    }
    
    if(((teleportStatus==1 && teleportTime==2) || (teleportStatus==2 && teleportTime==2))&& isTeleport){
        setTeleportMove();
    }
}

//#pragma mark - updataStatus
void GMBossPoseidon::updataStatus(float dt)
{
    if(isStopMove==false){
        CCPoint oldPoint = m_pBossPoseidon->getPosition();
        oldPoint.x += _d;
        if(oldPoint.x >= WINSIZE_W-m_pBossPoseidon->getContentSize().width/2*Scale_X)
            _d = -1;
        else if(oldPoint.x <= m_pBossPoseidon->getContentSize().width/2*Scale_X)
            _d = 1;
        m_pBossPoseidon->setPosition(oldPoint);
    }
    
    setBulletNum();
}

void GMBossPoseidon::loadTexture(int index)
{
//    switch (index) {
//        case 1:{
//            CCAddSpriteFramesAndTextureFile(bossPoseidon1_plist, bossPoseidon1_png);
//        }   break;
//        case 3:{
//            CCAddSpriteFramesAndTextureFile(bossPoseidon2_plist, bossPoseidon2_png);
//        }   break;
//        case 5:{
//            CCAddSpriteFramesAndTextureFile(bossPoseidonEffect_plist, bossPoseidonEffect_png);
//        }   break;
//        default:
//            break;
//    }
    CCAddSpriteFramesAndTextureFile(bossPoseidon1_plist, bossPoseidon1_png);
    CCAddSpriteFramesAndTextureFile(bossPoseidon2_plist, bossPoseidon2_png);
    CCAddSpriteFramesAndTextureFile(bossPoseidonEffect_plist, bossPoseidonEffect_png);
}

//#pragma mark - show

void GMBossPoseidon::showBoss(CCObject *target,GMEnemy *enemy,CCPoint point,float scaleValue){
    _delegate = target;
    m_pBossPoseidon = new GMEnemyAction();
    m_pBossPoseidon->setInitValue();
//    m_pBossPoseidon->setInitTheseProperties(target,enemy,scaleValue);
    m_pBossPoseidon->setDelegate(target);
    if (enemy)
        m_pBossPoseidon->setValue(enemy);
    char fishName[20] = {0};
    sprintf(fishName,"yu%02d%s%03d.png",enemy->_id,"a",5);
    m_pBossPoseidon->initWithSpriteFrameName(fishName);
    sprintf(fishName,"yu%02d%s",enemy->_id,"a");
    GMPublicMethod::setRepeatAnimation(m_pBossPoseidon, 5, 10, fishName, "png", 0.1, true);
    m_pBossPoseidon->setScale(scaleValue);
    
    this->addChild(m_pBossPoseidon,2);
    m_pBossPoseidon->setPosition(ccp(WINSIZE_W/2,WINSIZE_H-GetSize(m_pBossPoseidon).height/2*scaleValue+50*Scale_X));
}

void GMBossPoseidon::showAttackEffect(){
    if (attackEffect) {
        return;
    }
    attackEffect = CCSprite::createWithSpriteFrameName("bosaidong020.png");
    GMPublicMethod::setRepeatAnimation(attackEffect, 20, 24, "bosaidong", "png", 0.1, false);
    CCPoint tempP = m_pBossPoseidon->getPosition();
    tempP.x = tempP.x+m_pBossPoseidon->getContentSize().width/4.5*Scale_X;
    tempP.y = tempP.y-m_pBossPoseidon->getContentSize().height/3.5*Scale_X;
    attackEffect->setPosition(tempP);
    SetScale2(attackEffect, Scale_X);
    this->addChild(attackEffect,1);
}


void GMBossPoseidon::showBossPoseidonBullet(CCNode *pNode){
    for (int i = 0; i < bulletNum; i ++) {
        CCSprite *bulletEffect = CCSprite::createWithSpriteFrameName("bullet_20_2_000.png");
        GMPublicMethod::setSpriteAnimation(bulletEffect, 0, 2, "bullet_20_2_", this,callfuncN_selector(GMBossPoseidon::removeBulletEffect));
        bulletEffect->setAnchorPoint(ccp(0.5,0));
        
        CCPoint tempPoint = ccp(100+i*150,WINSIZE_H);
        tempPoint.x = rand()%(int)(WINSIZE_W/bulletNum-GetSize(bulletEffect).width)+i*(WINSIZE_W/bulletNum);
        bulletEffect->setPosition(tempPoint);
        this->addChild(bulletEffect);
//        SetScale2(bulletEffect, Scale_X);
        float cocosAngle = GMPublicMethod::pointToAngle(bulletEffect->getPosition(), ccp(WINSIZE_W/2,30*Scale_X), 1);
        bulletEffect->setRotation(cocosAngle);
    }

    setAttackAfterValue();
}

//#pragma mark - set

void GMBossPoseidon::setAttackAfterValue(){
    if(teleportStatus == 0){
        isStopMove = false;
    }
    else if(teleportStatus == 1 || teleportStatus == 2){
        teleportNum = 0;
        teleportTime = 0;
        isTeleport = true;
        isStopMove = true;
    }
    
    loadTime = 0;
    if(attackEffect){
        this->removeChild(attackEffect, true);
        attackEffect = NULL;
    }
//    m_pBossPoseidon->setEnemyAnimation(true,"a");

    GMPublicMethod::setRepeatAnimation(m_pBossPoseidon, 5, 10, "yu20a", "png", 0.1, true);
}

void GMBossPoseidon::removeBulletEffect(CCNode *pNode){
	CCSprite *sprite = (CCSprite*)pNode;
    if(_delegate){
        CCPoint old = sprite->getPosition();
        float rotation = sprite->getRotation();
        float a = DADIANS_TO_DEGREES1( rotation );
        float tempx = sinf(a)*(93-58/2);
        float tempy = cosf(a)*(93-58/2);
        old.x = old.x + tempx;
        old.y = old.y + tempy;
        ((GMGameLayer*)_delegate)->showBossPoseidonBullet(old,rotation);
    }
    
    this->removeChild(sprite, true);
}

void GMBossPoseidon::setBulletNum(){
//    m_pBossPoseidon->_life = 50.0f;
    if(isDeath == false){
        if(m_pBossPoseidon->_life >= 70.0f){
            bulletNum = 3;
            teleportStatus = 0;
        }
        else if(m_pBossPoseidon->_life >= 50.0f && m_pBossPoseidon->_life < 70.0f && teleportStatus !=1){
            bulletNum = 4;
            teleportStatus = 1;
            isTeleport = true;
            teleportTime = 0;
            loadTime = 0;
        }
        else if(m_pBossPoseidon->_life < 50.0f && teleportStatus !=2){
            bulletNum = 5;
            teleportStatus = 2;
            teleportTime = 0;
            loadTime = 0;
            isTeleport = true;
        }
    }
    
    if (m_pBossPoseidon->_life <= 0.0f && isDeath == false) {
        isDeath = true;
        m_pBossPoseidon->stopAllActions();
        isTeleport = false;
        isStopMove = true;
        GMPublicMethod::setSpriteAnimation(m_pBossPoseidon, 1, 7, "yu20b", this, callfuncN_selector(GMBossPoseidon::removeBossPosidon));
    }
}

void GMBossPoseidon::setTeleportMove(){
    if(teleportStatus == 1 || teleportStatus == 2){
        isStopMove = true;
        CCPoint old = m_pBossPoseidon->getPosition();
        old.x = rand()%(int)(WINSIZE_W-GetSize(m_pBossPoseidon).width*Scale_X)+GetSize(m_pBossPoseidon).width/2*Scale_X;
//        old.y = rand()%(int)(WINSIZE_H-GetSize(m_pBossPoseidon).height*Scale_X)+GetSize(m_pBossPoseidon).height/2*Scale_X;
        m_pBossPoseidon->setPosition(old);
        teleportNum++;
        
        m_pBossPoseidon->stopAllActions();
        m_pBossPoseidon->setColor(ccc3(255,255,255));
        GMPublicMethod::setSpriteAnimation(m_pBossPoseidon, 1, 5, "yu20a", this, callfuncN_selector(GMBossPoseidon::setTeleportMoveAfter));
    }
}

void GMBossPoseidon::setTeleportMoveAfter(CCNode *pNode){
    GMPublicMethod::setRepeatAnimation(m_pBossPoseidon, 5, 10, "yu20a", "png", 0.1, true);
    teleportTime = 0;
}

bool GMBossPoseidon::checkBossCollision(float collisionW,CCPoint collisionP,float scale1,float scale2){
    bool isCollision = false;
    float enemyImageSize = 200/2*Scale_X;
    float collisionImageSize = collisionW;
    float collisionRadius = collisionImageSize;
    float maxCollisionDistance = enemyImageSize + collisionRadius;
   
    CCPoint p1 = getBossPoseidonPoint();
    float actualDistance = ccpDistance(p1, collisionP);
    if(actualDistance <= maxCollisionDistance){
        return true;
    }
    return isCollision;
}

void GMBossPoseidon::setHurtEffect(){
    m_pBossPoseidon->setHurtEffect();
}

void GMBossPoseidon::setBossLife(float hurt){
    m_pBossPoseidon->_life = m_pBossPoseidon->_life+hurt;
    ZPLog("m_pBossPoseidon->_life == %f",m_pBossPoseidon->_life);
}

CCPoint GMBossPoseidon::getBossPoseidonPoint(){
    float enemyImagew = 60*Scale_X;
    CCPoint p1 = ccp(m_pBossPoseidon->getPosition().x+enemyImagew,m_pBossPoseidon->getPosition().y);
    return p1;
}

float GMBossPoseidon::getShellAffectRates(){
    return m_pBossPoseidon->_shells_affect_rates;
}

void GMBossPoseidon::removeBossPosidon(CCNode *pNode){
    this->removeChild(m_pBossPoseidon, true);
    if(attackEffect){
        this->removeChild(attackEffect, true);
        attackEffect = NULL;
    }
    this->unschedule(schedule_selector(GMBossPoseidon::updataStatus));
    
    ((GMGameLayer*)_delegate)->removeBossPoseidon();
}

void GMBossPoseidon::pauseActions(bool pause){
    if(pause){
        this->pauseSchedulerAndActions();
        m_pBossPoseidon->pauseSchedulerAndActions();
    }else{
        this->resumeSchedulerAndActions();
        m_pBossPoseidon->resumeSchedulerAndActions();
    }
}
