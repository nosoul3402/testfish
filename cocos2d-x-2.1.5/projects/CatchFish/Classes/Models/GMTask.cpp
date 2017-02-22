//
//  GMTask.cpp
//  FishX
//
//  Created by peng on 13-1-10.
//
//

#include "GMTask.h"
#include "cocos2d.h"

USING_NS_CC;


GMTask::GMTask()
{
    
}

void GMTask::setValue(CCDictionary *dictionary)
{
    _id = ((CCString*)dictionary->valueForKey("id"))->intValue();
    _strange_id = ((CCString*)dictionary->valueForKey("strange_id"))->intValue();
    _num = ((CCString*)dictionary->valueForKey("num"))->intValue();
    _time = ((CCString*)dictionary->valueForKey("time"))->intValue();
    _rewards = ((CCString*)dictionary->valueForKey("rewards"))->intValue();
}

GMTask::~GMTask()
{
    
}


