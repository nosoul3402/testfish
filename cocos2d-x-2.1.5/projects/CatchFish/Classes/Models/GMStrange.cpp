//
//  GMStrange.cpp
//  FishX
//
//  Created by peng on 13-1-10.
//  关卡随机刷怪数据
//

#include "GMStrange.h"
#include "cocos2d.h"

USING_NS_CC;


GMStrange::GMStrange()
{
    _strange_id = 0;
    _countNum = 0;
}

void GMStrange::setValue(CCDictionary *dictionary)
{
    _id = ((CCString*)dictionary->valueForKey("id"))->intValue();
    _strange_id = ((CCString*)dictionary->valueForKey("strange_id"))->intValue();
    _rate = ((CCString*)dictionary->valueForKey("rate"))->floatValue();
    _limit_num = ((CCString*)dictionary->valueForKey("limit_num"))->intValue();
//    _interval_range1 = ((CCString*)dictionary->valueForKey("interval_range1"))->intValue();
//    _interval_range2 = ((CCString*)dictionary->valueForKey("interval_range2"))->intValue();
    _fishArray_id = ((CCString*)dictionary->valueForKey("fishArray_id"))->intValue();
    _interval_range1 = 0;
    _interval_range2 = 0;
}

void GMStrange::setValue1(CCDictionary *dictionary)
{
    _id = ((CCString*)dictionary->valueForKey("id"))->intValue();
    _type = ((CCString*)dictionary->valueForKey("type"))->intValue();
    _strange_id = ((CCString*)dictionary->valueForKey("strange_id"))->intValue();
    _fishArray_id = ((CCString*)dictionary->valueForKey("fishArray_id"))->intValue();
    _time = ((CCString*)dictionary->valueForKey("time"))->intValue();
    _obrit_id = ((CCString*)dictionary->valueForKey("obrit_id"))->intValue();
    _direction = ((CCString*)dictionary->valueForKey("direction"))->intValue();
}

GMStrange::~GMStrange()
{
    
}



