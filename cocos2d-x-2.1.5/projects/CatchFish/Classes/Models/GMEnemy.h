//
//  GMEnemy.h
//  FishX
//
//  Created by peng on 12-12-21.
//
//

#ifndef __FishX__GMEnemy__
#define __FishX__GMEnemy__

#include <iostream>
//#include "cocos2d.h"
#include "../Config/GMFashionConfig.h"

//#include "GMBezier.h"

//void ArrowDirection::draw()
//{
//    if (mDrawBezier)
//    {
//        CCPoint control1 = ccpAdd(mBezierStartPoint, mBezierConfig.controlPoint_1);
//        CCPoint control2 = ccpAdd(mBezierStartPoint, mBezierConfig.controlPoint_2);
//        CCPoint end = ccpAdd(mBezierStartPoint, mBezierConfig.endPosition);
//        
//        // 画控制点
//        ccDrawLine(mBezierStartPoint, control1);
//        ccDrawLine(control2, end);
//        
//        // 画贝塞尔曲线
//        ccDrawCubicBezier(mBezierStartPoint, mBezierConfig.controlPoint_1, mBezierConfig.controlPoint_2, mBezierConfig.endPosition, 100);
//    }
//}

typedef enum {
    S_NONE  = 1,//无
    S_Move,//移动状态
    S_Death,//死亡状态
    S_Attack,//攻击状态
    S_Stop,//停止状态
} EnemyStatus;

typedef enum {
    R_NONE  = 1,//无
    R_Rand,//随机刷
    R_Curve_Formation,//固定曲线阵型
    R_Curve_Single,//固定曲线单个
    R_RandCurve,//随机曲线
    R_NotMoveOut,//随机 无法游出去
} EnemyRouteStatus;

class GMEnemy : public cocos2d::CCSprite
{
public:
    virtual bool init();
    virtual ~GMEnemy(void);
    // preprocessor macro for "static create()" constructor ( node() deprecated )
    CREATE_FUNC(GMEnemy);
  
public:
    int         _id;//类型
    const char  *_name;//名称
    int         _type;//怪物类型(1固定、2倍率、3BOSS)
    int         _numerical;//数值
    float       _life;//生命
    float       _burst_rate;//暴击概率
    int         _bulletId;//对应子弹id
    float       _bullet_firing_frequency;//子弹发射频率
    float       _shells_affect_rates;//炮弹影响率
    float       _limit_burst_rate;//极限爆率
    int         _speed;//速度
    int         _time;//间隔时间
    int         _angle;//浮动角度
    int         _accelerate;//加速概率
    
    int         _countTime;//记录时间 选择
    CCPoint     _tempPoint;
    CCPoint     _newPoint;
public:

    CCPoint     _startPoint;
    CCPoint     _oldPoint;
    
    bool        _isCatch;//

    int         _deathStatus;//鱼的死亡状态，自然死亡 1 被攻击死亡 2
    
    float       _oldAngle;
    bool        _isShootBullet;
    float       _countLife;//记录当前的生命
    bool        _unRemoveTheScreen;//不能移除屏幕
    EnemyStatus   _enemyStatus;
    /*
     *  设置鱼的路线
     */
    CC_SYNTHESIZE(EnemyRouteStatus, _routeStatus, RouteStatus);
//    void setRouteStatus(EnemyRouteStatus status) {_routeStatus = status;}
//    EnemyRouteStatus getRouteStatus() { return _routeStatus; }
private:
    bool        _isFrozen;//释放冰冻
//    EnemyRouteStatus    _routeStatus;
public:
    static GMEnemy* createEnemyName(const char *name);
    static GMEnemy* createEnemyFrameName(const char *name);
    static GMEnemy* createEnemyFrame(cocos2d::CCSpriteFrame *frame);
    void setValue(CCDictionary *dictionary);
    void setValue(GMEnemy*enemy);
    /*
     *  设置碰撞效果
     */
    void setHurtEffect();
    /*
     *  释放冰冻
     */
    void setFrozen(bool frozen) { _isFrozen = frozen;}
    bool getFrozen() { return _isFrozen;}
    
    void setEnemyTag(int tag);
//    void setEnemyAnimation(bool cache,const char *name);
//    void setDeathAnimation(bool cache,const char *name);

};
#endif /* defined(__FishX__GMEnemy__) */
