//
//  GMEnum.h
//  FishX
//
//  Created by peng on 13-1-25.
//
//

#ifndef FishX_GMEnum_h
#define FishX_GMEnum_h

#include "cocos2d.h"
enum GMSkill{
    SKILL_NONE,
    SKILL_BLOOD,    //加血技能
    SKILL_PAYS,     //漩涡
    SKILL_ICE ,     //冰河世纪
    SKILL_Crit      //暴击
};

//typedef enum{
//    SKILL_NONE,
//    SKILL_BLOOD,    //加血技能
//    SKILL_PAYS,     //漩涡
//    SKILL_ICE      //冰河世纪
//}GMSkill;

typedef struct _ccBezier {
    //start positiom
    cocos2d::CCPoint _sp;
	//! end position of the bezier
	cocos2d::CCPoint _ep;
	//! Bezier control point 1
	cocos2d::CCPoint _p1;
	//! Bezier control point 2
	cocos2d::CCPoint _p2;
    // startAngle
    float _sa;
    // endAngle
    float _ea;
    // dirTime
    float _time;
    float _speed;
} ccBezier;

typedef enum {
    D_NONE = 0,
    D_LEFT,
    D_RIGHT,
    D_UP,
    D_DOWN,
} ccDirection;

typedef enum {
    T_NONE = 0,
    T_LINE = 10,
    T_RAND = 10000,
} ccType;

typedef enum {
    Home_Mode = 1,  //首页
    Story_Mode,     //剧情模式
    Endless_Mode,   //无尽模式
    Boot_Mode,      //引导模式
} GameMode;

typedef enum {
    None_Status = 0,
    Home_Status = 1,
    Checkpoints_Status,
    Target_Status,
    Game_Status,
    Boss_Status,
    Pause_Status,
    Win_Status,
    Lose_Status,
} GameStatus;

typedef enum {
    N_Status = 0,
    P_Status = 1,//移动
    M_Status,//
} MoveStatus;

/*
 *  计费模式
 */
typedef enum {
    B_Free = 0,//免费模式
    B_TengXunBilling = 1,//腾讯计费
    B_91 = 2,//91计费
    B_91_IOS = 3,//91计费
    B_YiDong = 4,//移动计划计费
    B_Telecom = 5,//电信计费
    B_91_Android = 6,//91 android
    B_Unicom_Android,//联通宽带
} GMBillingModel;

#endif
