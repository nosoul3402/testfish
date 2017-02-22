//
//  GMCheckpoints.h
//  FishX
//
//  Created by peng on 13-1-10.
//  关卡
//

#ifndef __FishX__GMCheckpoints__
#define __FishX__GMCheckpoints__

#include <iostream>
#include "cocos2d.h"

class GMCheckpoints : public cocos2d::CCObject
{
public:
    GMCheckpoints();
    virtual ~GMCheckpoints(void);
    // preprocessor macro for "static create()" constructor ( node() deprecated )
//    CREATE_FUNC(GMCheckpoints);
    
public:
    int                 _id;//关卡id
    int                 _time;//关卡时间
    int                 _trigger_task_time;//触发任务时间
    int                 _task_id;//任务id
    int                 _target_score;//目标分数
    int                 _evaluation_score;//评价分数
    int                 _brush_strange_start_time;//随机刷怪开始时间
    int                 _brush_strange_end_time;//随机刷怪结束时间
    int                 _brush_strange_num;//刷怪数
    int                 _isExistboss;//是否存在boss
    
public:
    void setValue(cocos2d::CCDictionary *dictionary);//设置属性
};
#endif /* defined(__FishX__GMCheckpoints__) */
