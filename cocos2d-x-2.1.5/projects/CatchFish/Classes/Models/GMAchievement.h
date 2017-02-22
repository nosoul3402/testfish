//
//  GMAchievement.h
//  FishX
//
//  Created by peng on 13-3-12.
//
//

#ifndef __FishX__GMAchievement__
#define __FishX__GMAchievement__

#include <iostream>
#include "cocos2d.h"
using namespace cocos2d;

class GMAchievement : public CCObject
{
public:
    GMAchievement();
    virtual ~GMAchievement(void);
    
    void setValue(CCDictionary *dictionary);
public:
    int         _id;//
    char        _name[30];
    int         _energe;//获得的能量
    char        _note[30];
    
    int         _status;
};


#endif /* defined(__FishX__GMAchievement__) */
