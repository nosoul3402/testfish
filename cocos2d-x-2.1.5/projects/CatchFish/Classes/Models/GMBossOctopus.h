//
//  GMBossOctopus.h
//  FishX
//
//  Created by peng on 13-4-1.
//
//

/*
 70%血以上正常左右移动攻击。  6秒一发。
 40%-69%血左右各分出1个分身，分身拥有本体20%的生命值，70%大小。（打分身BOSS血条不掉落）5秒
 低于40%时，再次左右分出2个分身，分身拥有本体30%的生命值，70%大小。（打分身BOSS血条不掉落） 4秒
 */

#ifndef __FishX__GMBossOctopus__
#define __FishX__GMBossOctopus__

#include <iostream>
#include "GMEnemyAction.h"
#include "../Config/GMFashionConfig.h"

class GMBossOctopus : public CCLayerColor
{
public:
    virtual bool init();
    CREATE_FUNC(GMBossOctopus);
    ~GMBossOctopus();
    
private:
    CCObject        *_delegate;
    
    CCMoveTo        *moveTo;
//    GMEnemy         *octopus[5];
    GMEnemyAction     *octopus[5];
    bool            isShootBullet[5];
    bool            isHurt[5];
    int             reverse;
    int             shootBulletTime;
    int             countShootBulletTime;
    bool            isShow[2];
    bool            isMove;
    int             countBossNum;
    bool            _isFrozen;//释放冰冻
private:
    void initElement();
    void setShootBulletBefore();
    void showThreeBoos(int num);
    void checkAllLife();
    void showBoss(float dt);
    void setMove();
    void showDeathEffect(int index);
    void removeBoss(CCNode *pNode);
public:
    /*
     *  释放冰冻
     */
    void setFrozen(bool frozen) { _isFrozen = frozen;}
    bool getFrozen() { return _isFrozen;}
    
    void setAllFrozen(bool frozen);
    
    float getSubBossWidth(int index);
    CCPoint getBossPoint(int index);
    void setBossHurt(int index ,float hurt);
public:
    void setDelegate(CCObject *target) { _delegate = target; }
    void setOctopusMove();
    void setCountShootBulletTime();
    bool checkCollision(float collisionW,CCPoint collisionP,float scale1,float scale2,int index);
    void setValue(GMEnemy *enemy);
    float getHurt(float grade);
    void  setHurt(float hurt);
    bool setAllValue(float hurt);
    bool setAllValue(float hurt,int index);
    float getOctousLife();
    bool getHurtBOLL();
protected:
};


#endif /* defined(__FishX__GMBossOctopus__) */
