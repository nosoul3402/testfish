//
//  LRActionInterval.h
//  FishX
//
//  Created by peng on 13-1-24.
//
//

#ifndef __FishX__LRActionInterval__
#define __FishX__LRActionInterval__

#include <iostream>
//#include "ccTypes.h"
#include "cocos2d.h"
#include "../../../cocos2dx/actions/CCActionInterval.h"			//包含系统延时类动作头文件

using namespace cocos2d; 
// 定义一个结构来包含确定椭圆的参数
typedef struct _lrTuoyuanConfig {
    //中心点坐标
    CCPoint centerPosition;
    //椭圆a长，三角斜边
    float aLength;
    //椭圆c长，三角底边
    float cLength;
} lrTuoyuanConfig;

class  LRTuoyuanBy : public CCActionInterval
{
public:
    //用“动作持续时间”和“椭圆控制参数”初始化动作
    bool initWithDuration(float t, const lrTuoyuanConfig& c);
    virtual void update(float time);//利用update函数来不断的设定坐标
public:
    //用“动作持续时间”和“椭圆控制参数”创建动作
    static LRTuoyuanBy *actionWithDuration(float t, const lrTuoyuanConfig& c);
    
protected:
    lrTuoyuanConfig m_sConfig;
    CCPoint m_startPosition;
    CCPoint s_startPosition;
};
#endif /* defined(__FishX__LRActionInterval__) */
