//
//  CountBullet.h
//  FishX
//
//  Created by peng on 13-5-27.
//
//

#ifndef __FishX__CountBullet__
#define __FishX__CountBullet__

#include <iostream>
#include "cocos2d.h"

class CountBullet : public cocos2d::CCObject {
public:
    CountBullet();
    ~CountBullet();
    
    CC_SYNTHESIZE(int, m_gBulletTag, BulletTag);
    CC_SYNTHESIZE(int, m_gFishNum, FishNum);
};

#endif /* defined(__FishX__CountBullet__) */
