//
//  GMNet.h
//  FishX
//
//  Created by peng on 13-1-15.
//
//

#ifndef __FishX__GMNet__
#define __FishX__GMNet__

#include <iostream>
#include "cocos2d.h"

#define MAX_NUM     10

using namespace cocos2d;

class GMNet : public CCLayer
{
public:
    virtual bool init();
    // preprocessor macro for "static create()" constructor ( node() deprecated )
    CREATE_FUNC(GMNet);
    GMNet();
    virtual ~GMNet(void);
    
private:
    CCSprite            *net;
    CCParticleSystem    *netParticle;
    CCParticleSystem    *starParticle;
    CCPoint             _point;
    int                 _index;
    int                 m_nNotesFishTag[MAX_NUM];
    int                 m_nNotesBulletTag[MAX_NUM];
    bool                _isHitBoss;//是否击中boss
public:
    bool        isLaser;//是否是激光
    bool        isRmove;
    int         countHitNum;//一网击中的数目
public:
//    static GMNet* createBulletName(const char *name);
//    static GMNet* createBulletFrame(CCSpriteFrame *frame);
//    static GMNet* createBulletFrameName(const char *pszSpriteFrameName);
//    void addNet(CCPoint point, int index);
    void addNet(CCPoint point, int index,CCObject *target,float scale);
    void setNetAnimation(CCObject* pSelectorTarget, SEL_CallFuncN selector);
    void addParticle();
    
    CCRect getNetBox();
    float  getNetWidth();
    CCPoint getPoint() {return _point;}
    
    void setNotesFishTag(int tag);
    bool getNotesFishTag(int tag);
    
    void setNotesBulletTag(int tag);
    bool getNotesBulletTag(int tag);
    
    void setHitBossValue(bool hit) {_isHitBoss = hit;}
    bool getHitBossValue() { return _isHitBoss; }
private:
    CCObject      *_delegate;
    float         scaleValue;
    void showStarParticle(float dt);
    void removeNet();
};

#endif /* defined(__FishX__GMNet__) */
