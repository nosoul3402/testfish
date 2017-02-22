//
//  GMElementLayer.cpp
//  FishX
//
//  Created by peng on 13-1-9.
//
//

#include "GMElementLayer.h"

#include "../Config/GMHeaderConfig.h"
#include "GMGameLayer.h"

#define PaoPao_tag 10

#define ICE_TAG1         1000
#define ICE_TAG2         1001
#define ICE_TAG3         1002
#define ICE_TAG4         1004
#define ICE_TAG5         1005

#define Reward_TAG1      2001


#define WaterBatchNodeTag 100

#include "../PublicModels/UIRollNum.h"

CCScene* GMElementLayer::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    GMElementLayer *layer = GMElementLayer::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GMElementLayer::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    isShowReward = false;
    setPetrifaction(false);


	taskPrompt2 = NULL;

    otherSkill			  = NULL;
	petrifactionBatchNode = NULL;
	baoJiBatchNode		  = NULL;

    return true;
}

void GMElementLayer::loadingData(int index)
{
    switch (index) {
        case 0:{
            initElement();
        }  break;
        case 1:{
            initWater();
        }  break;
        case 2:{
            initBaoJi();
        }   break;
        case 3:{
            initFishBulletExplosionEffect();
        }   break;
        case 4:{
            initNumberFile();
        }   break;
        case 5:{//技能图片数据
            initSpriteFrames();
        }   break;
        default:
            break;
    }
}

void GMElementLayer::initElement()
{
    isShow = false;
    countSkillTime = 0;
}

//#pragma mark - 游戏里的能量精灵
void GMElementLayer::addEnergeBlink(CCPoint point,float scale)
{
    CCSprite *energe = CCSprite::create("game/energe.png");
    energe->setPosition( point );
    energe->setScale(scale);
    this->addChild(energe,1);
    moveEnerge(energe);
}

void GMElementLayer::moveEnerge(CCSprite *sprite)
{
    addParticles(Particles1,sprite->getPosition());
    
    CCMoveTo *moveTo = CCMoveTo::create(1, ccp(25*Scale_X, 30*Scale_X));
    CCActionInterval *action = (CCActionInterval*)CCSpawn::create(moveTo,NULL);
    CCCallFuncN *callfuncn = CCCallFuncN::create(this, callfuncN_selector(GMElementLayer::scaleEffect));
    CCActionInterval* sequence = (CCActionInterval*)CCSequence::create(action,callfuncn,NULL);
    sprite->runAction(sequence);
}

void GMElementLayer::scaleEffect(CCNode *pNode){

	CCSprite *sprite = (CCSprite *)pNode;
    sprite->setOpacity(100);
    CCScaleTo* scale0 = CCScaleTo::create(0.5, sprite->getScale()+0.5);
    CCScaleTo* scale1 = CCScaleTo::create(0.5, sprite->getScale());
    CCCallFuncN *callfuncn = CCCallFuncN::create(this, callfuncN_selector(GMElementLayer::removeEffect));
    CCActionInterval* sequence = (CCActionInterval*)CCSequence::create(scale0,scale1,callfuncn,NULL);
    sprite->runAction(sequence);
}

void GMElementLayer::removeEffect(CCNode *pNode)
{
	CCSprite *sprite = (CCSprite *)pNode;
    ((GMGameLayer*)delegateGame)->showEnergeDialog();

    this->removeChild(sprite, true);
    sprite = NULL;
}

//#pragma mark - 粒子特效
void GMElementLayer::addParticles(const char *name,CCPoint point)
{
    if (name==Particles1) {
        CCParticleSystem *explodePar = CCParticleSystemQuad::create(Particles1);
        explodePar->setAutoRemoveOnFinish(true);
        explodePar->setPosition(point); //setPosition(point);
        this->addChild(explodePar, 0, 100);
        explodePar->setScale(1);
        
//        explodePar->setAutoRemoveOnFinish(true);
        
        CCMoveTo *moveTo = CCMoveTo::create(1, ccp(20, 15));
        CCActionInterval *action = (CCActionInterval*)CCSpawn::create(moveTo,NULL);
        CCCallFuncN *callfuncn = CCCallFuncN::create(this, callfuncN_selector(GMElementLayer::removeParticles));
//        CCFiniteTimeAction *sequence = (CCFiniteTimeAction*)CCSequence::create(moveTo,callfuncn,NULL);
        CCActionInterval* sequence = (CCActionInterval*)CCSequence::create(action,callfuncn,NULL);
        explodePar->runAction(sequence);
    }
}


void GMElementLayer::showParticles(const char *name,CCPoint point)
{
    CCParticleSystem *explodePar = CCParticleSystemQuad::create(name);
    explodePar->setPosition(point);
    this->addChild(explodePar, 0, 100);
    explodePar->setScale(1);
}

void GMElementLayer::removeParticles(CCNode *object)
{
    CCParticleSystem *particles = (CCParticleSystem*)object;
    this->removeChild(particles,true);
    particles =  NULL;
}

//#pragma mark - 显示数字
void GMElementLayer::showNumber(int value, CCPoint point)
{
    CCLayer *showNumber = CCLayer::create();
    CCSprite *x = CCSprite::create("game/mainmenu050.png");
    CCRect rect = Get_Box(x);
    x->setPosition(ccp(Get_W(rect)/2, Get_H(rect)/2));
    showNumber->addChild(x);
    int num = GMPublicMethod::getScoreNum(value);
    
    UIRollNum *number = UIRollNum::create();
    number->setEffect("game/mainmenu051.png",num,34,33,NumStyleNormal0);
    number->setNumber(value);
    number->setPosition(ccp( Get_W(rect)+num*34, 33/2));
    showNumber->addChild(number);
    
    showNumber->setContentSize(CCSize(Get_W(rect)+num*34, 33));
    showNumber->setPosition(point);
    showNumber->setAnchorPoint(ccp(0.5,0.5));
    this->addChild(showNumber);
    SetScale2(showNumber,Scale_X);
    
    CCMoveTo *moveTo = CCMoveTo::create(1, ccp(point.x,point.y+20));
    CCCallFuncN *callFunc = CCCallFuncN::create(this, callfuncN_selector(GMElementLayer::removeNumber));
    CCFiniteTimeAction *sequence = CCSequence::create(moveTo,callFunc,NULL);
    showNumber->runAction(sequence);
//    number->setScale(0.5);
    
}

void GMElementLayer::removeNumber(CCNode *pNode)
{
	CCSprite *sprite = (CCSprite *)pNode;
    CCLayer *tempLayer = (CCLayer*)sprite;
    this->removeChild(tempLayer, true);
}

//#pragma mark - skill

void GMElementLayer::initSpriteFrames()
{
    CCAddSpriteFramesWithFile(blood_plist);
    CCSpriteBatchNode *bloodBatchNode = CCSpriteBatchNode::create(blood_png);
    this->addChild(bloodBatchNode);
    
//    CCAddSpriteFramesAndTextureFile(blood_plist,blood_png);
    
    CCAddSpriteFramesWithFile(payskill_plist);
    CCSpriteBatchNode *payskillBatchNode = CCSpriteBatchNode::create(payskill_png);
    this->addChild(payskillBatchNode);
//    CCAddSpriteFramesAndTextureFile(payskill_plist,payskill_png);
    
    CCAddSpriteFramesWithFile(iceage_plist);
    CCSpriteBatchNode *iceBatchNode = CCSpriteBatchNode::create(iceage_png);
    this->addChild(iceBatchNode);
//    CCAddSpriteFramesAndTextureFile(iceage_plist,iceage_png);
    payTittle = NULL;

}
/*
 *  加血
 */
void GMElementLayer::showBloodEffect(float scale)
{
    CCSprite *bloodEffect = CCSprite::createWithSpriteFrameName("blood001.png");
    GMPublicMethod::setSpriteAnimation(bloodEffect,1,11, "blood", this, callfuncN_selector(GMElementLayer::removeBloodEffect));
    bloodEffect->setScale(scale);
    bloodEffect->setPosition(ccp(WINSIZE_W/2, Get_H(Get_Box(bloodEffect))/2));
    this->addChild(bloodEffect);
}

void GMElementLayer::removeBloodEffect(CCNode *pNode){
	CCSprite *sprite = (CCSprite *)pNode;
    removeSprite(sprite);
    ((GMGameLayer*)delegateGame)->removeBloodEffect();
}
/*
 *  漩涡
 */
void GMElementLayer::showPayskillEffect()
{
    CCSprite *skilEffect = CCSprite::createWithSpriteFrameName("payskill001.png");
    GMPublicMethod::setSpriteAnimation(skilEffect,1,15,"payskill", this, callfuncN_selector(GMElementLayer::removePayskillEffect));
    skilEffect->setPosition(ccp(WINSIZE_W/2, Get_H(Get_Box(skilEffect))/2 * FISH_SCALE));
    this->addChild(skilEffect);
    SetScale2(skilEffect, FISH_SCALE);
    
    payTittle = CCSprite::createWithSpriteFrameName("payskill000.png");
    payTittle->setPosition(ccp(WINSIZE_W/2, -20));
    payTittle->retain();
    this->addChild(payTittle);
    
}

void GMElementLayer::showPayTittle(float move){
    if (payTittle) {
        float pointY = payTittle->getPosition().y;
        pointY += move;
        payTittle->setPosition(ccp(WINSIZE_W/2, pointY));
    }
}

void GMElementLayer::removePayskillEffect(CCNode *pNode)
{
	CCSprite *skilEffect = (CCSprite *)pNode;
    GMGameLayer *temp = (GMGameLayer*)delegateGame;
    temp->removePayskillEffect();
    removeSprite(skilEffect);
    
    payTittle->release();
    this->removeChild(payTittle, true);
    payTittle = NULL;
}
/*
 *  冰冻
 */
void GMElementLayer::showIceEffect()
{
    countIceTime = 0;
    isIcetopMove = false;
    
    CCSprite *iceEffect1 = CCSprite::createWithSpriteFrameName("iceage001.png");
    SetScale2(iceEffect1, Scale_Y);
    iceEffect1->setPosition(ccp(WINSIZE_W/2, 0));
    iceEffect1->setAnchorPoint(ccp(0.5,1));
    this->addChild(iceEffect1,2,ICE_TAG1);
    
    CCSprite *iceEffect2 = CCSprite::createWithSpriteFrameName("iceage002.png");
    SetScale2(iceEffect1, Scale_Y);
    iceEffect2->setPosition(ccp(0, WINSIZE_H/2));
    iceEffect2->setAnchorPoint(ccp(1,0.5));
    this->addChild(iceEffect2,1,ICE_TAG2);
    
    CCSprite *iceEffect3 = CCSprite::createWithSpriteFrameName("iceage003.png");
    SetScale2(iceEffect1, Scale_Y);
    iceEffect3->setPosition(ccp(WINSIZE_W, WINSIZE_H/2));
    iceEffect3->setAnchorPoint(ccp(0,0.5));
    this->addChild(iceEffect3,1,ICE_TAG3);
}

void GMElementLayer::iceMoveAction()
{
    GMSkill type = GMPublicMethod::sharedPublicMethod()->getSkillType();
    if (type == SKILL_ICE) {
        CCPoint newPoint;
        CCPoint point;
        CCSprite *iceEffect1 = (CCSprite*)this->getChildByTag(ICE_TAG1);
        CCSprite *iceEffect2 = (CCSprite*)this->getChildByTag(ICE_TAG2);
        CCSprite *iceEffect3 = (CCSprite*)this->getChildByTag(ICE_TAG3);
        if (!isIcetopMove) {
            point = iceEffect2->getPosition();
            newPoint.x = point.x+40;
            newPoint.y = point.y;
            char strName[30] = {};
            sprintf(strName,"iceage004.png");
            CCSpriteFrame *spriteFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(strName);
            if (newPoint.x == WINSIZE_W/3) {
                iceEffect2->setDisplayFrame(spriteFrame);
            }
            else if (newPoint.x >= WINSIZE_W/2+5) {
                newPoint.x = WINSIZE_W/2+8.5;
            }
            iceEffect2->setPosition(newPoint);
            
            point = iceEffect3->getPosition();
            newPoint.x = point.x-40;
            newPoint.y = point.y;
            sprintf(strName,"iceage005.png");
            spriteFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(strName);
            if (newPoint.x == WINSIZE_W-WINSIZE_W/3) {
                iceEffect3->setDisplayFrame(spriteFrame);
            }
            else if (newPoint.x <= WINSIZE_W/2-5) {
                newPoint.x = WINSIZE_W/2-8.5;
            }
            iceEffect3->setPosition(newPoint);
            
            point = iceEffect1->getPosition();
            newPoint.x = point.x;
            newPoint.y = point.y+10;
            if (newPoint.y >= WINSIZE_H/2+20) {
                newPoint.y = WINSIZE_H/2+20;
                isIcetopMove = true;
            }
            iceEffect1->setPosition(newPoint);
        }
        else {
            countIceTime ++;
            
            if (countIceTime==10) {
                
                this->removeChild(iceEffect2, true);
                this->removeChild(iceEffect3, true);
                
                CCSprite *iceDemolish = CCSprite::createWithSpriteFrameName("iceage006.png");
                SetScale1(iceDemolish);
                GMPublicMethod::setSpriteAnimation(iceDemolish, 6, 10, "iceage", this, callfuncN_selector(GMElementLayer::removeSprite1));
                iceDemolish->setPosition(ccp(WINSIZE_W/2,WINSIZE_H/2));
                this->addChild(iceDemolish);
                
            }
            else if(countIceTime > 10){
                point = iceEffect1->getPosition();
                newPoint.x = point.x;
                newPoint.y = point.y+10;

                float opacity = iceEffect1->getOpacity();
                opacity -= 30;
                iceEffect1->setOpacity( opacity );
                iceEffect1->setPosition(newPoint);
                if (opacity <= 0) {
                    this->removeChild(iceEffect1, true);
                    iceEffect1 = NULL;
                    GMPublicMethod::sharedPublicMethod()->setSkillType(SKILL_NONE);
                }
            }
        }
    }
}
/*
 *  暴击
 */
void GMElementLayer::initBaoJi()
{
    CCAddSpriteFramesWithFile(baoji1_plist);
    baoJiBatchNode = CCSpriteBatchNode::create(baoji1_png);
    this->addChild(baoJiBatchNode);
}

void GMElementLayer::showBaoJiEffect()
{
    CCSprite *baoji002 = CCSprite::createWithSpriteFrameName("baoji002.png");
    GMPublicMethod::setSpriteAnimation(baoji002, 2, 18, "baoji", this, callfuncN_selector(GMElementLayer::removeBaoJiEffect));
    baoji002->setPosition(ccp(WINSIZE_W/2, WINSIZE_H/2));
    baoJiBatchNode->addChild(baoji002,1,1);
    
    CCSprite *baoji001 = CCSprite::createWithSpriteFrameName("baoji001.png");
    baoji001->setPosition(ccp(WINSIZE_W/2, WINSIZE_H/2));
    baoJiBatchNode->addChild(baoji001,2,2);
    SetScale2(baoji001, Scale_X);
    showBaoJiEffect1();
}

void GMElementLayer::baoJiTitleMove()
{
    CCSprite *baoji001 = (CCSprite*)baoJiBatchNode->getChildByTag(2);
    if (baoji001) {
        CCPoint oldP = baoji001->getPosition();
        oldP.y += 2;
        baoji001->setPosition(ccp(oldP.x,oldP.y));
       
        int opacity = baoji001->getOpacity();
        opacity -= 5;
        baoji001->setOpacity(opacity);
    }
}

void GMElementLayer::removeBaoJiEffect(CCNode *pNode)
{
	CCSprite *object = (CCSprite *)pNode;
    baoJiBatchNode->removeChild(object, true);
    object = NULL;
    CCSprite *baoji001 = (CCSprite*)baoJiBatchNode->getChildByTag(2);
    baoJiBatchNode->removeChild(baoji001, true);
    baoji001 = NULL;
}

void GMElementLayer::showBaoJiEffect1()
{
    CCSprite *baoji019 = CCSprite::createWithSpriteFrameName("baoji019.png");
    baoji019->setAnchorPoint(ccp(0.5,0));
    SetScale2(baoji019, Scale_X);
    GMPublicMethod::setRepeatAnimation(baoji019, 19, 23, "baoji", "png", 0.1,true);
    baoji019->setPosition(ccp(WINSIZE_W/2, 0));
    baoJiBatchNode->addChild(baoji019,1,3);
}

void GMElementLayer::setbaojiRotation(float rotate)
{
    if (baoJiBatchNode) {
        CCSprite *baoji019 = (CCSprite*)baoJiBatchNode->getChildByTag(3);
        if (baoji019) {
            baoji019->setRotation(rotate);
        }
    }
}

void GMElementLayer::removeBaoji019Sprite()
{
    if (baoJiBatchNode) {
        CCSprite *baoji019 = (CCSprite*)baoJiBatchNode->getChildByTag(3);
        if (baoji019) {
            baoJiBatchNode->removeChild(baoji019, true);
        }
    }
}

//
void GMElementLayer::removeSprite1(CCNode *pNode){
	CCSprite *sprite = (CCSprite *)pNode;
    sprite->cleanup();
    this->removeChild(sprite, true);
    sprite = NULL;
}

void GMElementLayer::removeSprite(CCSprite *sprite)
{
    sprite->cleanup();
    this->removeChild(sprite, true);
    sprite = NULL;
}

//#pragma mark - 水波纹
void GMElementLayer::initWater()
{
    CCAddSpriteFramesWithFile(water_plist);
    waterBatchNode = CCSpriteBatchNode::create(water_png);
    this->addChild(waterBatchNode,WaterBatchNodeTag);
}

void GMElementLayer::showWater(CCPoint point)
{
    CCSprite *water = CCSprite::createWithSpriteFrameName("water001.png");
    GMPublicMethod::setSpriteAnimation(water, 1, 5, "water", this, callfuncN_selector(GMElementLayer::removeSprite1));
    water->setPosition(point);
    this->addChild(water);
}


//#pragma mark - 鱼的子弹爆炸效果
/*
 *  鱼的的子弹爆炸效果
 */
void GMElementLayer::initFishBulletExplosionEffect()
{
    CCAddSpriteFramesWithFile(explosionEffect_plist);
    CCSpriteBatchNode *explosionBatchNode = CCSpriteBatchNode::create(explosionEffect_png);
    this->addChild(explosionBatchNode);
}

void GMElementLayer::bulletExplosionAnimation(int _id,CCPoint point,float scale)
{
    int num = GMPublicMethod::_eExplosion[_id-1];
    if (num != 0) {
        char strName[40] = {};
        sprintf(strName,"yu%dd001.png",_id);
        CCSprite *explosion = CCSprite::createWithSpriteFrameName(strName);
        sprintf(strName,"yu%dd",_id);
        GMPublicMethod::setSpriteAnimation(explosion, 1, num, strName, this, callfuncN_selector(GMElementLayer::removeExplosion));
        explosion->setPosition(point);
        explosion->setScale(scale);
        this->addChild(explosion);
    }
}
/*
 *  boss 的子弹爆炸效果
 */
void GMElementLayer::initBoss1BulletExplosionEffect()
{
    CCAddSpriteFramesWithFile(explosionEffect1_plist);
    CCSpriteBatchNode *explosionBatchNode = CCSpriteBatchNode::create(explosionEffect1_png);
    this->addChild(explosionBatchNode);
}

void GMElementLayer::boss1ExplosionAnimation(int _id,CCPoint point)
{
    if(_id==2){
        _id = 1;
    }
    const int _bExplosion[] = {4,0,0,0,0,0,0,0,0,0,0,0,0,5};
    int num = _bExplosion[_id-1];
    if (num != 0) {
        char strName[40] = {};
        sprintf(strName,"bossgx%d001.png",_id);
        CCSprite *explosion = CCSprite::createWithSpriteFrameName(strName);
        sprintf(strName,"bossgx%d",_id);
        GMPublicMethod::setSpriteAnimation(explosion, 1, num, strName, this, callfuncN_selector(GMElementLayer::removeExplosion));
        explosion->setPosition(point);
        this->addChild(explosion);
    }
}

void GMElementLayer::removeExplosion(CCNode *pNode)
{
	CCSprite *sprite = (CCSprite*)pNode;
    sprite->cleanup();
    this->removeChild(sprite, true);
    sprite = NULL;
}

//#pragma mark - 特效
/*
 *  打中特殊鱼的奖励 Reward
 */
void GMElementLayer::showRewardEffect(int score)
{
    if (isShowReward==false) {
        GMAudioPlay::sharedAudioPlay()->playOtherEffect(Audio_Rewarad,false);
        
//        CCLayerColor *rewardLayer = CCLayerColor::create(ccc4(0, 0, 0, 125));
        CCLayer *rewardLayer = CCLayer::create();
        rewardLayer->setContentSize(CCSizeMake(338,338));
        rewardLayer->setAnchorPoint(ccp(0, 0));
        this->addChild( rewardLayer, 1, Reward_TAG1);
        
        CCParticleSystem *particlesEnerge = CCParticleSystemQuad::create(Particles_Energe);
        particlesEnerge->setAutoRemoveOnFinish(true);
        particlesEnerge->setPosition(ccp(338/2,338/2+50));
        rewardLayer->addChild(particlesEnerge, 0, 100);
        
        CCSprite *reward = CCSprite::create("game/jiangli002.png");
        reward->setPosition(ccp(338/2,338/2));
        rewardLayer->addChild(reward,0,1);
        
        CCRotateBy *ratateTo = CCRotateBy::create(1, 90);
        CCRepeatForever *repeateF = CCRepeatForever::create(ratateTo);
        reward->runAction(repeateF);
        //你真牛
        CCSprite *reward1 = CCSprite::create("game/jiangli001.png");
        reward1->setPosition(ccp(338/2,338/2));
        rewardLayer->addChild(reward1,1,2);
        
        int num = GMPublicMethod::getScoreNum(score);
        ZPLog("显示你真牛的分数 ： %d  num = %d",score,num);
        UIRollNum *rScore = UIRollNum::create();
        rScore->setEffect1("game/jiangli003.png",num,44,63,NumStyleNormal0);
        rScore->setNumber(score);
        rScore->setPosition( ccp((338)/2, 130 ));
        rewardLayer->addChild(rScore,1,3);
        //
        SetScale2(rewardLayer, Scale_Y);
        rewardLayer->setPosition(ccp((WINSIZE_W-338*Scale_Y)/2,(WINSIZE_H-338*Scale_Y)/2));
        isShowReward = true;
        showRewardTime = 0;
    }
}

void GMElementLayer::countRewaradTime()
{
    if (isShowReward) {
        showRewardTime++;
        if (showRewardTime==2) {
            removeRewarad();
        }
    }
}

void GMElementLayer::removeRewarad()
{
    CCLayer *rewardLayer = (CCLayer*)this->getChildByTag(Reward_TAG1);
    this->removeChild(rewardLayer, true);
    isShowReward = false;
   
    if (paysStatus == 2 || paysStatus == 3) {
        GMGameLayer *temp = (GMGameLayer*)delegateGame;
        temp->rewaradPayskillEffect();
    }
}

//#pragma mark - boss1 显示提示2
/*
 *  显示提示2
 */
void GMElementLayer::showTaskPrompt2(int score)
{
    if(taskPrompt2 == NULL){
        taskPrompt2 = CCSprite::create("game/mainmenuTask009.png");
        taskPrompt2->setPosition(ccp(WINSIZE_W/2, WINSIZE_H/2));
        this->addChild(taskPrompt2,MENU_C_Layer);
        SetScale2(taskPrompt2, Scale_X);

        CCSprite *winSprite = CCSprite::create("game/winarrow009.png");
        winSprite->setAnchorPoint(ccp(0.2, 0));
        CCArray *temp1 = CCArray::create();
        char strName1[30] = {0};
        for (int j = 9; j <= 10; j++) {
            sprintf(strName1,"game/winarrow%03d.png",j);
            CCSpriteFrame *spriteFrame = CCSpriteFrame::create(strName1, CCRect(0,0,154,190));
            temp1->addObject(spriteFrame);
        }
        CCAnimation *m_pAnimation1 = CCAnimation::createWithSpriteFrames(temp1,0.1);
        CCAnimate *animate1 = CCAnimate::create(m_pAnimation1);
        CCRepeatForever *repeateF1 = CCRepeatForever::create(animate1);
        CCFiniteTimeAction *sequence1 = CCSequence::create(repeateF1,NULL);
        winSprite->runAction(sequence1);
        winSprite->setPosition(ccp(0, 0));
        taskPrompt2->addChild(winSprite,1,1);
        
        int num = GMPublicMethod::getScoreNum(score);
        UIRollNum *tempNum = UIRollNum::create();
        tempNum->setEffect("game/number11.png",num,25,33,NumStyleNormal0);
        tempNum->setNumber(score);
        tempNum->setPosition( ccp(372/2+40 , 33) );
        taskPrompt2->addChild(tempNum);
    }
}

void GMElementLayer::removeTaskPrompt2()
{
    if(taskPrompt2){
        CCSprite *winSprite = (CCSprite*)taskPrompt2->getChildByTag(1);
        taskPrompt2->removeChild(winSprite, true);
        
        CCLabelTTF *labelt = (CCLabelTTF*)taskPrompt2->getChildByTag(2);
        taskPrompt2->removeChild(labelt, true);
        
        this->removeChild(taskPrompt2, true);
        taskPrompt2 = NULL;
    }
}

//#pragma mark - boss1 的血条
void GMElementLayer::initBossbloodFile()
{
    bossbloodLayer = CCLayer::create();
    this->addChild(bossbloodLayer);
    CCAddSpriteFramesWithFile(bossblood1_plist);
    CCSpriteBatchNode *bossbloodBatchNode = CCSpriteBatchNode::create(bossblood1_png);
    bossbloodLayer->addChild(bossbloodBatchNode);
}

void GMElementLayer::showBoosBlood()
{
    CCSprite *bossblood001 = CCSprite::createWithSpriteFrameName("bossblood001.png");
    bossblood001->setAnchorPoint(ccp(0, 0.5));
    SetScale2(bossblood001, Scale_X);
    bossblood001->setPosition(ccp(10*Scale_X,WINSIZE_H/2+15));
    bossbloodLayer->addChild(bossblood001,1);
    
    CCSprite *bossblood002 = CCSprite::createWithSpriteFrameName("bossblood002.png");
    bossblood002->setAnchorPoint(ccp(0, 0.5));
    SetScale2(bossblood002, Scale_X);
    //    bossbloodBatchNode->addChild(bossblood001);
    
    bossbloodProgress = CCProgressTimer::create(bossblood002);
    //    SetScale1(loadingCt1);
    bossbloodProgress->setAnchorPoint(ccp(0, 0.5));
    bossbloodProgress->setPosition(ccp(10*Scale_X,WINSIZE_H/2+15));
    bossbloodProgress->setType(kCCProgressTimerTypeBar);//
    /*
     *应该使用kCCProgressTimerTypeBar这种类型，然后设置其起点midpoint属性为ccp（0,x），0<=x<=1，从左边开始，或者ccp（1,x），从右边开始。然后设置其barChangeRate属性为ccp（x，y），表示横竖两个方向的增长率，要进度条从左到右的话，设置成ccp(1,0)即可。
     */
    bossbloodProgress->setMidpoint(ccp(0, 1));
    bossbloodProgress->setBarChangeRate(ccp(0, 1));
    bossbloodLayer->addChild(bossbloodProgress ,2);
    bossbloodProgress->setPercentage(100); //当前进度
    SetScale2(bossbloodProgress,Scale_X);
    
    CCSprite *bossblood003 = CCSprite::createWithSpriteFrameName("bossblood003.png");
    bossblood003->setAnchorPoint(ccp(0, 0.5));
    SetScale2(bossblood003, Scale_X);
    bossblood003->setPosition(ccp(10*Scale_X,WINSIZE_H/2+15));
    bossbloodLayer->addChild(bossblood003,3);
}

void GMElementLayer::setBossBloodValue(float value)
{
    if (bossbloodLayer && bossbloodProgress ) {
        float life = bossbloodProgress->getPercentage();
        life = life-value;
        ZPLog("%f %f",bossbloodProgress->getPercentage(),life);
        bossbloodProgress->setPercentage(life);
    }
}

void GMElementLayer::removeBossBlood()
{
    this->removeChild(bossbloodLayer, true);
    bossbloodLayer = NULL;
    
    CCRemoveSpriteFrameByName(bossblood1_plist);
    CCRemoveTextureForKey(bossblood1_png);
}
//#pragma mark - boss1 的石化
void GMElementLayer::initPetrifactionFile()
{
    CCAddSpriteFramesWithFile(petrifaction1_plist);
    petrifactionBatchNode = CCSpriteBatchNode::create(petrifaction1_png);
    this->addChild(petrifactionBatchNode);
    
}

void GMElementLayer::showPetrifactionEffect()
{
    setPetrifaction(true);
    countPetrifactionTime = 0;
    CCSprite *bossgx020 = (CCSprite*)petrifactionBatchNode->getChildByTag(1);
    if (bossgx020) {
        return;
    }
    bossgx020 = CCSprite::createWithSpriteFrameName("bossgx_p_020.png");
    bossgx020->setAnchorPoint(ccp(0.5, 0));
    SetScale2(bossgx020, Scale_X);
    bossgx020->setPosition(ccp(WINSIZE_W/2, 50));
    petrifactionBatchNode->addChild(bossgx020,2,1);
    
    CCSprite *bossgx021 = CCSprite::createWithSpriteFrameName("bossgx_p_021.png");
    bossgx021->setAnchorPoint(ccp(0.5, 0));
    bossgx021->setPosition(ccp(WINSIZE_W/2, 0));
    petrifactionBatchNode->addChild(bossgx021,1,2);
}

void GMElementLayer::showPetrifactionEffect2()
{
    CCSprite *bossgx020 = (CCSprite*)petrifactionBatchNode->getChildByTag(1);
    CCFadeOut *fadeOut = CCFadeOut::create(1);
    bossgx020->runAction(fadeOut);
    
    CCSprite *bossgx021 = (CCSprite*)petrifactionBatchNode->getChildByTag(2);
    GMPublicMethod::setSpriteAnimation(bossgx021, 21, 25, "bossgx_p_", this, callfuncN_selector(GMElementLayer::removePetrifactionEffect2));
}

void GMElementLayer::removePetrifactionEffect2(CCNode *pNode)
{
	CCSprite *sprite = (CCSprite*)pNode;
    petrifactionBatchNode->removeChild(sprite, true);
    sprite = NULL;
    CCSprite *bossgx020 = (CCSprite*)petrifactionBatchNode->getChildByTag(1);
    bossgx020->stopAllActions();
    petrifactionBatchNode->removeChild(bossgx020, true);
    bossgx020 = NULL;
    
    setPetrifaction(false);
}
//#pragma mark - 换爆弹的提示
/*
 *  换爆弹的提示
 */
void GMElementLayer::initNumberFile()
{
    CCAddSpriteFramesWithFile(numbera_plist);
    CCSpriteBatchNode *numberBatchNode = CCSpriteBatchNode::create(numbera_png);
    this->addChild(numberBatchNode);
    numberSprite = NULL;
}

void GMElementLayer::changeShowNumeber(int num){
    char numName[30] = {0};
    sprintf(numName, "number%d001.png",num);
    if (numberSprite) {
        numberSprite->stopAllActions();
        this->removeChild(numberSprite, true);
        numberSprite = NULL;
    }
    numberSprite = CCSprite::createWithSpriteFrameName(numName);
    sprintf(numName, "number%d",num);
    GMPublicMethod::setSpriteAnimation(numberSprite, 1, 6, numName, this, callfuncN_selector(GMElementLayer::removeNumber1));
    SetScale2(numberSprite, Scale_X);
    numberSprite->setPosition(ccp(WINSIZE_W/2, 78*Scale_X));
    this->addChild(numberSprite);
}

void GMElementLayer::removeNumber1(CCNode *pNode)
{
	CCSprite *sprite = (CCSprite*)pNode;
    this->removeChild(numberSprite, true);
    numberSprite = NULL;
}

//#pragma mark - 闪红
void GMElementLayer::setRedlightningEffect()
{
    CCSprite *lightning = CCSprite::create("game/Redlightning.png");
    SetScale(lightning);
    lightning->setPosition(ccp(WINSIZE_W/2,WINSIZE_H/2));
    this->addChild(lightning,20);
    CCBlink *blink = CCBlink::create(0.3, 2);
    CCCallFuncN *callFunc = CCCallFuncN::create(this, callfuncN_selector(GMElementLayer::removeRedlightningEffect));
    CCActionInterval *sequence = (CCActionInterval*)CCSequence::create(blink,callFunc,NULL);
    lightning->runAction(sequence);
}

void GMElementLayer::removeRedlightningEffect(CCNode *pNode){
	CCSprite *sprite = (CCSprite*)pNode;
    this->removeChild(sprite, true);
    sprite = NULL;
}

//#pragma mark -  ------  等到的技能
void GMElementLayer::setOtheSkill(int goodId)
{
    if (!otherSkill) {
        otherSkill = CCMenu::create();
        this->addChild(otherSkill);
        otherSkill->setPosition(CCPointZero);
    }
    bool isExist = false;
    CCObject *object = NULL;
    CCMenuItemSprite *tempSkill = NULL;
    CCARRAY_FOREACH(otherSkill->getChildren(), object){
        tempSkill = (CCMenuItemSprite*)object;
//        if (tempSkill->getTag() == goodId) {
//            isExist = true;
//        }
        otherSkill->removeChild(tempSkill,true);
    }
    
    if (isExist == false) {
        CCSprite *normalSprite = NULL;
        if (goodId == 1) {
            normalSprite = CCSprite::createWithSpriteFrameName("luck003.png");
        }
        else if (goodId == 2) {
            normalSprite = CCSprite::createWithSpriteFrameName("luck009.png");
        }
        else if (goodId == 3) {
            normalSprite = CCSprite::createWithSpriteFrameName("luck005.png");
        }
        else if (goodId == 4) {
            normalSprite = CCSprite::createWithSpriteFrameName("luck007.png");
        }
        CCMenuItemSprite *tempSkill2 = CCMenuItemSprite::create(normalSprite, NULL, this, menu_selector(GMElementLayer::setOtheSkillEffect));
        otherSkill->addChild(tempSkill2);
        tempSkill2->setTag(goodId);
        tempSkill2->setAnchorPoint(ccp(1,0));
        tempSkill2->setPosition(ccp(WINSIZE_W/2,WINSIZE_H/2));
        tempSkill2->setScale(Scale_X);
        CCMoveTo *moveTo = CCMoveTo::create(0.5, ccp(WINSIZE_W - (10)*Scale_X, (10+92)*Scale_X));
        CCCallFunc *callFunc = CCCallFunc::create(this, callfunc_selector(GMElementLayer::setClickOtheSkill));
        CCFiniteTimeAction *sequence= CCSequence::create(moveTo,callFunc,NULL);
        tempSkill2->runAction(sequence);
        
        isShow = false;
        countSkillTime = 0;
    }
}

void GMElementLayer::setClickOtheSkill()
{
    isShow = true;
}

void GMElementLayer::setCountSillTime()
{
    if (isShow) {
        countSkillTime ++;
        if (countSkillTime == 15 || countSkillTime == 20) {
            CCObject *object = NULL;
            CCMenuItemSprite *tempSkill = NULL;
            CCARRAY_FOREACH(otherSkill->getChildren(), object){
                tempSkill = (CCMenuItemSprite*)object;
                if(countSkillTime == 15){
                    CCBlink *link = CCBlink::create(1, 5);
                    tempSkill->runAction(link);
                }
                else if(countSkillTime == 20){
                    otherSkill->removeChild(tempSkill, true);
                    tempSkill = NULL;
                }
            }
        }
    }
}

void GMElementLayer::removeOtherSkill()
{
    if (otherSkill) {
        CCObject *object = NULL;
        CCMenuItemSprite *tempSkill = NULL;
        CCARRAY_FOREACH(otherSkill->getChildren(), object){
            tempSkill = (CCMenuItemSprite*)object;
            otherSkill->removeChild(tempSkill, true);
            tempSkill = NULL;
        }
        isShow = false;
        countSkillTime = 0;
    }
}

void GMElementLayer::setOtheSkillEffect(CCObject *pSender)
{
	CCMenuItemSprite *itemSprite = (CCMenuItemSprite*)pSender;
    if(isShow && ((GMGameLayer*)delegateGame)->getBootModeCastSkill() == false){
        itemSprite->stopAllActions();
        ((GMGameLayer*)delegateGame)->setCastSkill(itemSprite->getTag());
        otherSkill->removeChild(itemSprite, true);
        itemSprite = NULL;
        
        isShow = false;
        countSkillTime = 0;
    }
}
//#pragma mark - 礼盒
void GMElementLayer::addGift(){
    giftLayer = NULL;
    
//    long time = GMPublicMethod::getTime();
//    struct tm * tm;
//    tm = localtime(&time);
//    int day1 = tm->tm_mday;
//    long time2 = GMAccessData::sharedAccessData()->getToday();
//    tm = localtime(&time2);
//    int day2 = tm->tm_mday;
    int index = GMAccessData::sharedAccessData()->getGiftStatus();
//    if(day1 == day2 && index <= 3){
    CCLog("当前礼盒状态1 %d",index);
        if(index <= 3){
            giftLayer = CCLayer::create();
            this->addChild(giftLayer);
            
            gift = CCSprite::create("billingPic/charging050.png");
            SetScale2(gift, Scale_X);
            float tempx = WINSIZE_W-Get_Box(gift).size.width/2-20*Scale_X;
            float tempy = WINSIZE_H-120*Scale_X;
            gift->setPosition(ccp(tempx,tempy));
            giftLayer->addChild(gift);
            
            giftmenuItem = CCMenuItemImage::create("billingPic/charging053.png",NULL, this,menu_selector(GMElementLayer::setGiftAtion));
            giftmenuItem->setPosition(ccp(tempx,tempy));
            giftmenuItem->setEnabled(false);
            
            CCMenu *menu = CCMenu::create(giftmenuItem,NULL);
            menu->setPosition(CCPointZero);
            giftLayer->addChild(menu);
            
            tempy = tempy-Get_Box(gift).size.height/2-20*Scale_X;
        
            int time = GMAccessData::sharedAccessData()->getGiftCountdown();
            int t1 = time/60;
            int t2 = time%60;
        
            minRollNum = UIRollNum::create();
            minRollNum->setEffect("game/number15.png",2,24.0,30.0,NumStyleNormal0);
            minRollNum->setNumber(t1);
            SetScale2(minRollNum, Scale_X);
            minRollNum->setPosition(ccp(tempx-16/2*Scale_X,tempy));
            giftLayer->addChild(minRollNum,MENU_NUM_Layer);
            
            CCSprite *temp = CCSprite::create("billingPic/charging055.png");
            temp->setPosition(ccp(tempx,tempy));
            SetScale2(temp, Scale_X);
            giftLayer->addChild(temp);
            
            secRollNum = UIRollNum::create();
            secRollNum->setEffect("game/number15.png",2,24.0,30.0,NumStyleNormal0);
            secRollNum->setNumber(t2);
            SetScale2(secRollNum, Scale_X);
            secRollNum->setPosition(ccp(tempx+16/2*Scale_X+24*Scale_X*2,tempy));
            giftLayer->addChild(secRollNum,MENU_NUM_Layer);
            isShowA = false;
        }
        else {
            isShowA = true;
        }
//    }
}

void GMElementLayer::setGiftTime(int time){
    if (isShowA == false && giftLayer) {
        if(time<=0)
            time = 0;
        int t1 = time/60;
        int t2 = time%60;
        minRollNum->setNumber(t1);
        secRollNum->setNumber(t2);
        
        if(time == 0){
            setAnimation();
            isShowA = true;
            giftmenuItem->setEnabled(true);
            GMAccessData::sharedAccessData()->saveGiftCountdown(0);
        }
    }
}

void GMElementLayer::setAnimation(){
    if(giftLayer){
        CCArray *temp = CCArray::create();
        char strName[40] = {0};
        for (int j = 50; j <= 52; j++) {
            sprintf(strName,"billingPic/charging%03d.png",j);
            CCSpriteFrame *spriteFrame =  CCSpriteFrame::create(strName, CCRect(0,0,94,111));
            temp->addObject(spriteFrame);
        }
        CCAnimation *m_pAnimation = CCAnimation::createWithSpriteFrames(temp,0.1);
        CCAnimate *animate = CCAnimate::create(m_pAnimation);
        CCRepeatForever *repeateF = CCRepeatForever::create(animate);
        gift->runAction(repeateF);
    }
}

void GMElementLayer::setGiftAtion(CCObject *pSender){
    ((GMGameLayer*)delegateGame)->setGiftAtion();
}

void GMElementLayer::setGiftValue(){
    if(giftLayer){
        gift->stopAllActions();
        giftmenuItem->setEnabled(false);
        isShowA = false;
        
        int index = GMAccessData::sharedAccessData()->getGiftStatus();
        if(index>3){
            if(giftLayer){
                this->removeChild(giftLayer, true);
                giftLayer = NULL;
            }
        }
    }
}
//#pragma mark - 结束提示

void GMElementLayer::showOverView()
{
    CCSprite *overSprite = CCSprite::create("game/timeup007.png");
    SetScale2(overSprite, Scale_X);
    overSprite->setPosition(ccp(-Get_W(Get_Box(overSprite))/2, WINSIZE_H/2));
    this->addChild(overSprite,Index_Pause,10000000);

    CCMoveTo *moveTo = CCMoveTo::create(0.5, ccp(WINSIZE_W/2, WINSIZE_H/2));
    CCActionInterval *action = (CCActionInterval*)CCSpawn::create(moveTo,NULL);
    overSprite->runAction(action);
}


CCSprite *GMElementLayer::getOverSprite()
{
    CCSprite *tempSprite = (CCSprite*)this->getChildByTag(10000000);
    return tempSprite;
}

void GMElementLayer::removeOverSprite()
{
    CCSprite *tempSprite = (CCSprite*)this->getChildByTag(10000000);
    if(tempSprite)
        this->removeChild(tempSprite, true);
}

//#pragma mark - 析构函数
GMElementLayer::~GMElementLayer()
{
    this->cleanup();
    
    if (petrifactionBatchNode) {
        petrifactionBatchNode->cleanup();
    }

    this->removeChild(petrifactionBatchNode, true);
    petrifactionBatchNode = NULL;
    
    payTittle = NULL;
    if (baoJiBatchNode) {
         baoJiBatchNode->cleanup();
    }

    this->removeChild(baoJiBatchNode, true);
    baoJiBatchNode = NULL;
    
    bossbloodProgress = NULL;
    removeBossBlood();
    delegateGame = NULL;
    taskPrompt2 = NULL;
    CCRemoveSpriteFrameByName(numbera_plist);
    CCRemoveTextureForKey(numbera_png);
    
    CCRemoveSpriteFrameByName(explosionEffect1_plist);
    CCRemoveTextureForKey(explosionEffect1_png);
    CCRemoveSpriteFrameByName(explosionEffect_plist);
    CCRemoveTextureForKey(explosionEffect_png);
    
    CCRemoveSpriteFrameByName(water_plist);
    CCRemoveTextureForKey(water_png);
    
    CCRemoveSpriteFrameByName(blood_plist);
    CCRemoveTextureForKey(blood_png);
    
    CCRemoveSpriteFrameByName(payskill_plist);
    CCRemoveTextureForKey(payskill_png);
    
    CCRemoveSpriteFrameByName(iceage_plist);
    CCRemoveTextureForKey(iceage_png);
    
    CCRemoveSpriteFrameByName(petrifaction1_plist);
    CCRemoveTextureForKey(petrifaction1_png);
    
    CCRemoveSpriteFrameByName(bossblood1_plist);
    CCRemoveTextureForKey(bossblood1_png);
    
    CCRemoveSpriteFrameByName(baoji1_plist);
    CCRemoveTextureForKey(baoji1_png);
    
    this->removeChild(otherSkill, true);
    otherSkill = NULL;
    
    numberSprite = NULL;

    this->removeChild(waterBatchNode, true);
    waterBatchNode = NULL;
  
    ZPLog("~~GMElementLayer");
}

