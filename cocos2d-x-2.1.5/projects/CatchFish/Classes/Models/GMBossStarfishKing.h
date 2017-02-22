//
//  GMBossStarfishKing.h
//  FishX
//
//  Created by peng on 13-4-16.
//
//

/*
 * 技能召唤：每隔10秒召唤2只小海星。
 * 技能吞噬：每隔20秒判断一下存在多少海星，每只回复5%生命。
 每10秒召唤一次，第30秒吸收。
 */

#ifndef __FishX__GMBossStarfishKing__
#define __FishX__GMBossStarfishKing__

#include <iostream>
#include "GMEnemyAction.h"
#include "../Config/GMHeaderConfig.h"


class GMBossStarfishKing : public GMEnemyAction
{
public:
//    virtual bool init();
//    CREATE_FUNC(GMBossStarfishKing);
    GMBossStarfishKing();
    ~GMBossStarfishKing();
    
private:
    CCObject        *_delegate;
    bool            m_bIsMove;
    int             m_nReverse;
    int             m_nCountTime;
    int             m_nCountNum;
    int             m_nCountTime2;//回生命值
    int             m_nDTime;

private:
    void initElement();
    void setCallTwoStarFish(CCNode *pNode);
    void setIncomeStarFish(CCNode *pNode);
    void setshootStarFishBullet(CCNode *pNode);
    
    void removeEffect(CCNode *pNode);
    
    void removeDeathEffect(CCNode *pNode);
public:
    void initStarfishKing(CCObject *target,GMEnemy *enemy);
    
    void setStarfishKingMove();
    void setRunTime(int num);
    
    void setRestoreLifeEffect(int num);
    void setStarfishKingLifeValue(float value);
    void setDeathEffcet();
    

};

#endif /* defined(__FishX__GMBossStarfishKing__) */
