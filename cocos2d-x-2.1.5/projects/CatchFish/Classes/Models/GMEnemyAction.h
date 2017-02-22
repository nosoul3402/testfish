//
//  GMEnemyAction.h
//  FishX
//
//  Created by peng on 13-1-7.
//
//

#ifndef __FishX__GMEnemyAction__
#define __FishX__GMEnemyAction__

#include <iostream>

#include "../Config/GMFashionConfig.h"
#include "GMEnemy.h"

#define animation_tag1          100
#define move_tag1               200
#define speed_tag1              300

class GMEnemyAction : public GMEnemy
{
public:
    virtual bool init();
    // preprocessor macro for "static create()" constructor ( node() deprecated )
    CREATE_FUNC(GMEnemyAction);
    ~GMEnemyAction();
    GMEnemyAction(void);
private:
    int             countNum;
    int             curveNum;
    CCArray         *pointArray;
//    ccColor3B       color3b;
    float           rotationAngle;
    CCPoint         _moveV;
    int             _direction;
    int             _row;//
    ccBezier        randCurveBezier;
//    static const int _animationFrames[][3];
protected:
    int             _countAttackTime;		//记录攻击时间
private:
    ccBezier        ccbezier[10];
    ccBezier getBezier(CCPoint p1,CCPoint p2,CCPoint p3);
    
    CCObject        *_delegate;
public:
    
    ccDirection     direction;
    bool            isRotationAndMove;
    
    int             _checkTime;//检测移除时间
public:
    
    void setInitTheseProperties(CCObject *target, GMEnemy *enemy,float sacle);
    void setDelegate(CCObject *target) { _delegate = target;}
    /*
     *  初始
     */
    static GMEnemyAction* createEnemyName(const char *name);
    static GMEnemyAction* createEnemyFrameName(const char *name);
    static GMEnemyAction* createEnemyFrame(cocos2d::CCSpriteFrame *frame);
    
    void setInitValue();
    
    void setRandEnemyValue(CCObject *target, GMEnemy *enemy,float sacle);
    void setCurveValue(CCObject *target,GMEnemy *enemy,CCPoint point,CCArray*array ,int direction, int row, float delay,float sacle);
    /*
     *  设置游动动画和死亡动画，以及选择角度
     */
    void setEnemyAnimation(bool cache,const char *name);
//    void setDeathAnimation(bool cache,const char *name);
    void setDeathAnimation();
	void enemyDeathAfterNoPara();
    void enemyDeathAfter(CCNode *pNode);
    void setAttackAnimation(const char *name,CCObject* target, SEL_CallFuncN selector);

    /*
     *  添加固定路线
     */
    void setBezier(CCArray*array ,int direction, int row,float delay);
//    void setBezier(CCArray*array);
    
//    void addMoveAtion();
    void addCurveMoveAtion(float dt);
    
//    void moveWithParabola(CCSprite* mSprite ,ccBezier ccb);
//    void addMoveLineAtion();
//    void moveWithLine(ccBezier ccb);
    void fireFrom(CCPoint ptFrom,CCPoint ptTo);
    
    float getAngle(CCPoint p1,CCPoint p2);
//    float getAngle1(CCPoint p1,CCPoint p2);
    
//#pragma mark - 随机鱼阵
    
//    void setRandCurvePoint(ccBezier bezier,int row,float delay);
    void setRandCurvePoint(GMEnemy *enemy,CCObject *target,ccBezier bezier,int row,float delay,float sacle);
    void setRandCurveMove(float dt);
    /*
     *  随机移动
     */
    void randDirection();
//    void randEnemyMove();

//    void unscheduleRandFashion();
//    void randOtherEnemyMove();
//    void enemyMove1();
    void stopMoveAction();
    void randRotationMove();
    
    void randRotationAngle();
//    void toMoveBetweenTwoPoints();
    /*
     *  设置攻击角度
     */
    void setAttackAngle();
    /*
     *  冰冻后继续移动
     */
    void continueMoveAction();
    /*
     *  攻击后继续移动
     */
    void continueMoveAction1();
    
    /*
     *  设置加速
     */
    void setAccelerate();
    /*
     *  旋转技能
     */
//    void setRotationAndMove();
    void setRotationAndMove(CCObject* target, SEL_CallFuncN selector);
    void setBossRestoreLife(CCPoint point,CCObject* target, SEL_CallFuncN selector);
//    void updateLagrange();
    
    void stopCurveAtion();
    void pauseCurveAtion();
    void resumeCurveAtion();
    
    /*
     *  设置获取攻击的时间
     */
    void setAttackTime(int t);
    int  getAttackTime() { return _countAttackTime;}
    /*
     *  检查碰撞
     *  collisionW collisionP 碰撞物的宽与位置 scale 缩放系数
     */
    bool checkCollision(float collisionW,CCPoint collisionP,float scale1,float scale2);
    /*
     *  检测是否移到屏幕外
     */
    void checkIsRemove();
    /*
     *  检测某些fish 不让移到屏幕外
     */
    void setUnRemoveTheScreen();
    
private:
    int         movex;
    int         movey;
    bool        isCheckRandEnemy;
    CCAction    *curveAction;
//    CCActionInterval    *randSequence;
    CCSpeed             *enemySpeed;
    bool                isSpeed;
    void initValue();
    /*
     *  name : a(游动)、b(死亡)、c(攻击)
     *  index : 0、1、2  动作帧数索引
     *  repeat : 为 true 时重复播放动作
     */
    void setAnimation(const char *name,int index,float time,bool repeat,CCObject* target, SEL_CallFuncN selector);
    
    void removeObject(CCSprite* mSprite);
    
//    void removeCurveEnemy();
    /*
     *  设置加速
     */
    void setSpeedOfRecovery(float dt);
    
};


#endif /* defined(__FishX__GMEnemyAction__) */
