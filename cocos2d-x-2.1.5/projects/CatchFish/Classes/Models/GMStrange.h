//
//  GMStrange.h
//  FishX
//
//  Created by peng on 13-1-10.
//  关卡随机刷怪数据
//

#ifndef __FishX__GMStrange__
#define __FishX__GMStrange__

#include <iostream>
#include "cocos2d.h"

class GMStrange : public cocos2d::CCObject
{
public:
    GMStrange();
    virtual ~GMStrange(void);
    // preprocessor macro for "static create()" constructor ( node() deprecated )
//    CREATE_FUNC(GMStrange);
    
public:
    int                 _id;//序列号
    int                 _strange_id;//怪物id 对已enemy 的 id
    float               _rate;//出现概率
    int                 _limit_num;//极限数量
    int                 _interval_range1;//区间范围
    int                 _interval_range2;
    
    int                 _countNum;
    //固定刷怪属性
    int                 _type;//刷怪类型，如果为2，则为鱼阵，1为单条的鱼
    int                 _fishArray_id;//鱼阵id
    int                 _time;//刷怪出的时间
    int                 _obrit_id;//曲线id
    int                 _direction;//鱼出现的方向  0：左边  1：右边
public:
    void setValue(cocos2d::CCDictionary *dictionary);//设置属性
    //固定刷怪属性
    void setValue1(cocos2d::CCDictionary *dictionary);//设置属性
};

#endif /* defined(__FishX__GMStrange__) */











