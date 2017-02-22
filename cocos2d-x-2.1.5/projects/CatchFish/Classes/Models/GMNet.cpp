//
//  GMNet.cpp
//  FishX
//
//  Created by peng on 13-1-15.
//
//

#include "GMNet.h"
#include "../Layer/GMGameLayer.h"
#include "../Config/GMHeaderConfig.h"

bool GMNet::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    return true;
}

//GMNet* GMNet::createBulletName(const char *name)
//{
//    GMNet *net = (GMNet*)CCSprite::create(name);
//    return net;
//}
//
//GMNet* GMNet::createBulletFrame(CCSpriteFrame *frame)
//{
//    GMNet *net = (GMNet*)CCSprite::createWithSpriteFrame(frame);
//    return net;
//}
//
//GMNet* GMNet::createBulletFrameName(const char *pszSpriteFrameName)
//{
//    GMNet *net = (GMNet*)CCSprite::createWithSpriteFrameName(pszSpriteFrameName);
//    return net;
//}
GMNet::GMNet()
{
    for (int i = 0; i < MAX_NUM; i++) {
        m_nNotesFishTag[i] = 0;
        m_nNotesBulletTag[i] = 0;
    }
    
    setHitBossValue(false);
}

void GMNet::addNet(CCPoint point, int index,CCObject *target,float scale)
{
    _delegate = target;
    isRmove = false;
    countHitNum = 0;
    _index = index;
    _point = point;
    char strName[40] = {0};
    sprintf(strName,"net%d_1.png",index);
    net = CCSprite::createWithSpriteFrameName(strName);
    net->setPosition(point);
    net->setScale(scale);
    this->addChild(net);
//    net->retain();
    scaleValue = scale;
    
    setNetAnimation(NULL,NULL);
    addParticle();

}

void GMNet::setNetAnimation(CCObject* pSelectorTarget, SEL_CallFuncN selector)
{
    isRmove = true;
    CCArray *temp = CCArray::create();
    char strName[40] = {0};
    for (int j = 1; j <= 6; j++) {
        sprintf(strName,"net%d_%d.png",_index,j);
        CCSpriteFrame * spriteFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(strName);
        temp->addObject(spriteFrame);
    }
    CCAnimation *m_pAnimation = CCAnimation::createWithSpriteFrames(temp,0.15);
    CCAnimate *animate = CCAnimate::create(m_pAnimation);
    CCCallFunc *callFuncN = CCCallFunc::create(this, callfunc_selector(GMNet::removeNet));
    CCFiniteTimeAction *sequence = CCSequence::create(animate,callFuncN,NULL);
    net->runAction(sequence);
}

CCRect GMNet::getNetBox(){
    return net->boundingBox();
}

float GMNet::getNetWidth(){
    return net->getContentSize().width;
}

void GMNet::removeNet(){
    GMGameLayer *temp = (GMGameLayer*)_delegate;
    temp->removeNet(countHitNum,this);
}

void GMNet::addParticle()
{
    netParticle = CCParticleSystemQuad::create(Particles3);
    netParticle->setAutoRemoveOnFinish(true);
    netParticle->setPosition(_point); 
    this->addChild(netParticle, 3, 100);
    netParticle->setScale(0.07*scaleValue);
    
//    char strName[20] = {0};
//    sprintf(strName,"particles/partucle%d.plist",_index);
//    starParticle = CCParticleSystemQuad::create(strName);
//    netParticle->setAutoRemoveOnFinish(true);
//    starParticle->setPosition(_point);
//    this->addChild(starParticle, 3, 100);
//    starParticle->setScale(0.4);
   
    if (_index==2) {
        netParticle->setScale(0.12*scaleValue);
//        starParticle->setScale(0.4);
    }
    else if (_index==3) {
        netParticle->setScale(0.18*scaleValue);
//        starParticle->setScale(0.4);
    }
    else if (_index==4) {
        netParticle->setScale(0.22*scaleValue);
//        starParticle->setScale(0.4);
    }
    else if (_index==5) {
        netParticle->setScale(0.28*scaleValue);
//        starParticle->setScale(0.5);
    }
    else if (_index==6) {
        netParticle->setScale(0.35*scaleValue);
//        starParticle->setScale(0.6);
    }
    this->scheduleOnce(schedule_selector(GMNet::showStarParticle), 0.05);
}

void GMNet::showStarParticle(float dt)
{
    char strName[64] = {0};
    sprintf(strName,"particles/partucle%d.plist",_index);
    starParticle = CCParticleSystemQuad::create(strName);
    netParticle->setAutoRemoveOnFinish(true);
    starParticle->setPosition(_point);
    this->addChild(starParticle, 3, 100);
    starParticle->setScale(0.4*scaleValue);
    
    if (_index==2) {
//        netParticle->setScale(0.12);
        starParticle->setScale(0.4*scaleValue);
    }
    else if (_index==3) {
//        netParticle->setScale(0.18);
        starParticle->setScale(0.4*scaleValue);
    }
    else if (_index==4) {
//        netParticle->setScale(0.22);
        starParticle->setScale(0.4*scaleValue);
    }
    else if (_index==5) {
//        netParticle->setScale(0.28);
        starParticle->setScale(0.5*scaleValue);
    }
    else if (_index==6) {
//        netParticle->setScale(0.35);
        starParticle->setScale(0.6*scaleValue);
    }
}

//#pragma mark - fish  tag
void GMNet::setNotesFishTag(int tag)
{
    for (int i = 0; i < MAX_NUM; i ++) {
        if (m_nNotesFishTag[i] == 0) {
            m_nNotesFishTag[i] = tag;
            break;
        }
    }
}

bool GMNet::getNotesFishTag(int tag)
{
    for (int i = 0; i < MAX_NUM; i ++) {
        if (m_nNotesFishTag[i] == tag) {
            return true;
        }
    }
    return false;
}

//#pragma mark - bullet tag
void GMNet::setNotesBulletTag(int tag)
{
    for (int i = 0; i < MAX_NUM; i ++) {
        if (m_nNotesBulletTag[i] == 0) {
            m_nNotesBulletTag[i] = tag;
            break;
        }
    }
}

bool GMNet::getNotesBulletTag(int tag)
{
    for (int i = 0; i < MAX_NUM; i ++) {
        if (m_nNotesBulletTag[i] == tag) {
            return true;
        }
    }
    return false;
}

GMNet::~GMNet()
{
//    ZPLog("~GMNet");
    this->unschedule(schedule_selector(GMNet::showStarParticle));
    _delegate = NULL;
    this->removeChild(net, true);
    this->removeChild(netParticle, true);
    this->removeChild(starParticle, true);
    starParticle = NULL;
    netParticle = NULL;
    net = NULL;
    this->cleanup();
}




