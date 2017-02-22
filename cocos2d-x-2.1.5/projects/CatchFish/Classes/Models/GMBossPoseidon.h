//
//  GMBossPoseidon.h
//  FishX
//
//  Created by peng on 13-5-7.
//
//
/*
 波塞冬AI：
 70%~100%生命横版左右移动，每隔5秒攻击一次，屏幕上方（外）召唤3颗子弹攻击玩家。
 50%~70%，开始瞬移，每瞬移3次发动一次攻击，屏幕上方（外）召唤4颗子弹攻击玩家。
 50%以下，瞬移频率加快，每瞬移2次发动一次攻击，屏幕上方（外）召唤5颗子弹攻击玩家。
 
 瞬移的概念：
 第2阶段的瞬移后移动2秒发动攻击。
 第3阶段的瞬移后移动1秒发动攻击。
 */
 
#ifndef __FishX__GMBossPoseidon__
#define __FishX__GMBossPoseidon__

#include <iostream>
#include "GMEnemyAction.h"
#include "../Config/GMHeaderConfig.h"


class GMBossPoseidon : public CCLayer
{
public:
    //    virtual bool init();
    //    CREATE_FUNC(GMBossStarfishKing);
    GMBossPoseidon();
    ~GMBossPoseidon();
    
private:
    CCObject        *_delegate;
    
    GMEnemyAction   *m_pBossPoseidon;
    CCSprite        *attackEffect;
    
    int             loadTime;
    int             _d;
    bool            isStopMove;
    int             bulletNum;
    int             teleportStatus;//是否瞬移 0 不瞬移，1瞬移3次 2瞬移2次
    int             teleportNum;
    int             teleportTime;
    bool            isTeleport;
    bool            isDeath;
private:
    void initData();
    
    void loadTexture(int index);
   
    void updataStatus(float dt);
    
    void showBossPoseidonBullet(CCNode *pNode);
    void showAttackEffect();
    void setAttackAfterValue();
    void removeBulletEffect(CCNode *pNode);
    void setBulletNum();
    void setTeleportMove();
    void setTeleportMoveAfter(CCNode *pNode);
    void removeBossPosidon(CCNode *pNode);
public:
    void updata();
    void showBoss(CCObject *target,GMEnemy *enemy,CCPoint point,float scaleValue);
    void setPoseidonLife();
    bool checkBossCollision(float collisionW,CCPoint collisionP,float scale1,float scale2);
    void setHurtEffect();
    CCPoint getBossPoseidonPoint();
    float getShellAffectRates();
    void setBossLife(float hurt);
    
    void pauseActions(bool pause);
};
#endif /* defined(__FishX__GMBossPoseidon__) */
