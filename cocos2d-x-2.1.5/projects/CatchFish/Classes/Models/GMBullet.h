//
//  GMBullet.h
//  FishX
//
//  Created by peng on 12-12-21.
//
//

#ifndef __FishX__GMBullet__
#define __FishX__GMBullet__

#include <iostream>
#include "cocos2d.h"
#include "GMFishBullet.h"

#define MAX_BULLET_NUM 100
#define MAX_BULLET_NUM_1 20

class GMBullet : public cocos2d::CCSprite
{
public:
    virtual bool init();
    // preprocessor macro for "static create()" constructor ( node() deprecated )
    CREATE_FUNC(GMBullet);
    virtual ~GMBullet(void);
    GMBullet();
    
public :
    int         _id;//子弹的id
    
    float       _speed;
    int         _hurt_Value;//伤害值
    int         _angle_Value;//爆后获得的能量
    float       _life_Value;//生命值
    float       _rates_Value;//炮弹影响率
    
    void setValue(GMFishBullet *value);
    
    float       _k;//斜率
private:
    bool        _isHitBoss;
public:
    int         _currentLifeValue;//生命值
    bool        isLaser;//是否是激光
    
    int         _grade;//等级
    
public:
    static GMBullet* createBulletName(const char *name);
    static GMBullet* createBulletFrame(cocos2d::CCSpriteFrame *frame);
    static GMBullet* createBulletFrameName(const char *pszSpriteFrameName);
    
    void setCannonBullerValue(int index,float angle,float cannonX);
    void setFishBullerValue(int bulletId,CCPoint point,GMFishBullet*value);
    //子弹的动画帧数
    static const int _actor[6];
    void setBullerAnimation(int index);
    void setLaserAnimation(CCObject* pSelectorTarget, cocos2d::SEL_CallFuncN selector);
    /*
     *  子弹的移动
     */
    void bulletMove();
    void cannonBulletMove();
    void setRotationAndMove();
    void fishBulletMove(CCPoint eP,float moveTime);
    
    bool checkCollision(float collisionW,CCPoint collisionP,float scale1,float scale2);
    bool checkCollision1(float collisionW,CCPoint collisionP,float collisionA);
   
    void setDelegate(CCObject *object) {_delegate = object;}
    
    void setBulletTag(int tag);
    
    void setNotesFishTag(int tag);
    bool getNotesFishTag(int tag);
    
    void setNotesBulletTag(int tag);
    bool getNotesBulletTag(int tag);
    
    void setHitBossValue(bool hit) {_isHitBoss = hit;}
    bool getHitBossValue() { return _isHitBoss; }
    
private:
    CCObject      *_delegate;
    void removeBullet(CCNode *pNode);
    void removeCollisionBullet(CCNode *pNode);
    
    bool isRotationAndMove;
    
    int                 m_nNotesFishTag[MAX_BULLET_NUM];//激光记录鱼的tag
    int                 m_nNotesBulletTag[MAX_BULLET_NUM_1];
};



#endif /* defined(__FishX__GMBullet__) */
