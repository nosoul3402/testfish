//
//  GMTask.h
//  FishX
//
//  Created by peng on 13-1-10.
//
//

#ifndef __FishX__GMTask__
#define __FishX__GMTask__

#include <iostream>
#include "cocos2d.h"

class GMTask : public cocos2d::CCObject
{
public:
    GMTask();
    virtual ~GMTask(void);
    // preprocessor macro for "static create()" constructor ( node() deprecated )
//    CREATE_FUNC(GMTask);
    
public:
    int                 _id;//序列号
    int                 _strange_id;//怪物id 对已enemy 的 id (任务目标ID)
    int                 _num;//任务目标数量
    int                 _time;//任务时间
    int                 _rewards;//任务奖励
public:
    void setValue(cocos2d::CCDictionary *dictionary);//设置属性
};

#endif /* defined(__FishX__GMTask__) */







