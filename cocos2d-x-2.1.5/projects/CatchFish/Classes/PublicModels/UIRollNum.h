//
//  UIRollNum.h
//  FishX
//
//  Created by peng on 12-12-27.
//
//

#ifndef __FishX__UIRollNum__
#define __FishX__UIRollNum__

#include <iostream>
#include "cocos2d.h"
#include "UINumber.h"

USING_NS_CC;

class UIRollNum : public cocos2d::CCSprite
{
public:
    virtual bool init();

    // preprocessor macro for "static create()" constructor ( node() deprecated )
    CREATE_FUNC(UIRollNum);
    ~UIRollNum();
    int             m_nNumber;              //显示的数字
    int             m_maxCol;               //最大显示位数
    CCArray         *numArray;               //存放每个数字的数组
    CCPoint         m_point;                //坐标
    bool            zeroFill;               //是否开启0填充
    NumStyle        style;                  //滚动样式
    
    
    int  getNumber();
    void setEffect(const char *name,int col,float w, float h, NumStyle nstyle);
    void setNumber(int num);
    void rebuildEffect();
    void clearEffect(const char *name ,float w,float h);
    //居中
    void setEffect1(const char *name,int col,float w, float h, NumStyle nstyle);
    void clearEffect1(const char *name ,float w,float h);
   
    void setEffectSpriteFrame(const char *name,int col,float w, float h, NumStyle nstyle);
    void clearEffectSpriteFrame(const char *name ,float w,float h);
    
private:
    
    
};
#endif /* defined(__FishX__UIRollNum__) */
