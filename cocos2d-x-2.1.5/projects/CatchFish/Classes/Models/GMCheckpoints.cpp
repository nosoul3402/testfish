//
//  GMCheckpoints.cpp
//  FishX
//
//  Created by peng on 13-1-10.
//
//

#include "GMCheckpoints.h"

using namespace cocos2d;


GMCheckpoints::GMCheckpoints()
{
    
}

void GMCheckpoints::setValue(CCDictionary *dictionary)
{
    _id = ((CCString*)dictionary->valueForKey("id"))->intValue();
    _time = ((CCString*)dictionary->valueForKey("time"))->intValue();
    _trigger_task_time = ((CCString*)dictionary->valueForKey("trigger_task_time"))->intValue();
    _task_id = ((CCString*)dictionary->valueForKey("task_id"))->intValue();
    _target_score = ((CCString*)dictionary->valueForKey("target_score"))->intValue();
    _evaluation_score = ((CCString*)dictionary->valueForKey("evaluation_score"))->intValue();
    _brush_strange_start_time = ((CCString*)dictionary->valueForKey("brush_strange_start_time"))->intValue();
    _brush_strange_end_time = ((CCString*)dictionary->valueForKey("brush_strange_end_time"))->intValue();
    _brush_strange_num = ((CCString*)dictionary->valueForKey("brush_strange_num"))->intValue();
    _isExistboss = ((CCString*)dictionary->valueForKey("isExistboss"))->intValue();
}

GMCheckpoints::~GMCheckpoints()
{
    
}





