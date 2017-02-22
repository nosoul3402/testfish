//
//  UINumber.h
//  FishX
//
//  Created by peng on 12-12-27.
//
//

#ifndef __FishX__UINumber__
#define __FishX__UINumber__


#define NUM_WIDTH  22
#define NUM_HEIGHT 21

#define SCORE_SPACE_W 35.5
#define SCORE_SPACE_H 45

typedef enum{
    NumStyleNormal0,
    NumStyleNormal,
    NumStyleSameTime,
}NumStyle;

#include <iostream>
#include "cocos2d.h"

USING_NS_CC;

class UINumber : public cocos2d::CCSprite
{
public:
    virtual bool init();
    // preprocessor macro for "static create()" constructor ( node() deprecated )
    CREATE_FUNC(UINumber);
    
    NumStyle    m_style;            //滚动样式
    int         m_num;              //显示的数字
//    int         m_nPosCur;          //当前的位置
//    int         m_nPosEnd;          //结束的位置
    float         m_nPosCur;          //当前的位置
    float         m_nPosEnd;          //结束的位置
    float         m_nMoveLen;         //每次移动的位置
    CCTexture2D *m_texture;         //数字的texture
    
    void setTyle(NumStyle style);
    void setNumber(int num);
    void setTexture(const char *name,float w ,float h);
    void setTextureFromSpriteFrame(const char *name,float w ,float h);
private:
    float       textW,textH;
//    void setTextureIndex(int x);
    void setTextureIndex(float x);
    void setDisplayFrame(CCSpriteFrame *frame);
    void onRollUP(float dt);
    void onRollDown(float dt);
};
#endif /* defined(__FishX__UINumber__) */
