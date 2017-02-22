//
//  GMBoss1Action.h
//  FishX
//
//  Created by peng on 13-2-4.
//
//

/*
 *  生命值86%~100%：4个蛇头顺着吐子弹。
 *  生命值到达85%，掉一个蛇头，释放一次石化。
 *  生命值71%~85%：3个蛇头顺着吐子弹。
 *  生命值达到70%：掉一个蛇头，释放一次石化。
 *  生命值56%~70%：2个蛇头顺着吐子弹。
 *  生命值达到55%：掉一个蛇头，释放一次石化。
 *  生命值41%~55%：1个蛇头顺着吐子弹。
 *  生命值达到40%：掉一个蛇头（全部掉完了），释放一次石化。
 *  生命值0%~40%：BOSS每隔10S放一次石化，紧接着连续放2个子弹。
 */

#ifndef __FishX__GMBoss1Action__
#define __FishX__GMBoss1Action__

#include <iostream>
#include "GMEnemy.h"
#include "../Config/GMFashionConfig.h"

class GMBoss1Action : public GMEnemy
{
public:
    virtual bool init();
    CREATE_FUNC(GMBoss1Action);
    ~GMBoss1Action();
    
private:
    void initBatchNode();
    void initBoss();
private:
    CCSprite    *boss01000;
    CCSprite    *boss06001;//左手
    CCSprite    *boss07001;//右手
    bool        isDeath;
protected:

public:
    int         _tag;
    int         _index;
    bool        _isSkill1;//释放一次石化
    
    CCArray     *snakeHeadsArray;
    int         _attackTime;
    CCNode      *delegate;
    void checkLife();
    void continueAnimation(int tag);
    int         _mouthAttackNum;
    
    void setBossHurtEffect();
    /*
     *  眼睛动画
     */
    void addEyeAnimation();
    /*
     *  口吐子弹动画
     */
    void addMouthAnimation();
    /*
     *  调用子弹攻击
     */
    void shootBossBullet();
    
    void setDeathStatus(bool death) {isDeath = death;}
    bool getDeathStatus() { return isDeath; }
    
private:
    CCPoint     point[6];
    CCSprite    *eyeSprite;
    CCSprite    *mouthSprite;
    
    CCRect      rect;
    int         countHead;
    void shootBulletBefore();
    void showButtleEffect(CCNode *pNode);
    void shootBullet(CCNode *pNode);
    
    void removeSnakeheads();
    bool checkSnakeheads(int tag);
    /*
     *  口吐子弹动画
     */
    void shootMouthBulletEffect(CCNode *pNode);
    void shootMouthBullet(CCNode *pNode);
    
    /*
     *  石化动作
     */
    void petrifactionAnimation();
    void petrifactionEffect();
public:
    
    
};


#endif /* defined(__FishX__GMBoss1Action__) */
