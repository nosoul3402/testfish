//
//  GMFishBullet.h
//  FishX
//
//  Created by peng on 13-3-1.
//
//

#ifndef __FishX__GMFishBullet__
#define __FishX__GMFishBullet__

#include <iostream>
#include "cocos2d.h"

using namespace cocos2d;

class GMFishBullet : public CCObject
{
public:
    GMFishBullet();
    virtual ~GMFishBullet(void);
    
    void setValue(CCDictionary *dictionary);
public:
    int         _id;//
    float       _speed;
    int         _hurt_Value;//伤害值
    int         _angle_Value;//爆后获得的能量
    int         _life_Value;//生命值
    float       _rates_Value;//炮弹影响率
};
#endif /* defined(__FishX__GMFishBullet__) */
