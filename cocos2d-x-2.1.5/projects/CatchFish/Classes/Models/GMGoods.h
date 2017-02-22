//
//  GMGoods.h
//  FishX
//
//  Created by peng on 13-3-1.
//
//

#ifndef __FishX__GMGoods__
#define __FishX__GMGoods__

#include <iostream>
#include "cocos2d.h"

using namespace cocos2d;

class GMGoods : public CCObject
{
public:
    GMGoods();
    virtual ~GMGoods(void);
    
    void setValue(CCDictionary *dictionary);
public:
    int         _id;//
    const char* _name;
    int         _type;
    float       _rate;
    float       _angle;
    int         _energe;
};

#endif /* defined(__FishX__GMGoods__) */
