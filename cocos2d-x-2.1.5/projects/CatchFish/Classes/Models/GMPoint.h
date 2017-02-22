//
//  GMPoint.h
//  FishX
//
//  Created by peng on 13-1-23.
//
//

#ifndef __FishX__GMPoint__
#define __FishX__GMPoint__

#include <iostream>
#include "cocos2d.h"

using namespace cocos2d;

class GMPoint : public CCObject
{
public:
    GMPoint();
    virtual ~GMPoint(void);
    
public:
    int         _id;//
    int         _start;//是否是起始点
    int         _curveNum;
    CCPoint     _point;
    
//    int         _t_row;//总行数
//    int         _t_columns;//总列数
//    int         _e_row;//每一个的 行 号
//    int         _e_columns;//每一个的 列 号
    float       _time;//没格多长时间开始移动移动
    
    int         _row;
    int         _columns;
    
};

#endif /* defined(__FishX__GMPoint__) */
