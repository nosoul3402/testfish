//
//  GMCartoonLayer.h
//  FishX
//
//  Created by peng on 13-3-6.
//
//

#ifndef __FishX__GMCartoonLayer__
#define __FishX__GMCartoonLayer__

#include <iostream>
#include "../Config/GMFashionConfig.h"
#include "cocos-ext.h"

USING_NS_CC_EXT;

class GMCartoonLayer : public CCLayer
{
public:
    virtual bool init();
    static cocos2d::CCScene* scene();
    CREATE_FUNC(GMCartoonLayer);

	GMCartoonLayer();
    virtual ~GMCartoonLayer(void);
    
private:
    void initElement1();
    void cartoon1Move();
    void removeScrollView1();
    
    void initElement2();
    
    void initElement3();
    void cartoon3Move();
    void showCartoon3Word();
    void startMove3();
    
    void initElement4();
    void cartoon4Move();
    void startMove4();
    void removeScrollView3();
    
    void update(float time);
    CCSprite        *sprite1;
    CCRect          rect1;
    
    static const char     *cartoonPrompt[5];
    CCLabelTTF *_labelt;
    void setLabel(const char *string);
    
    void tiaoguoAction(CCObject *object);
private:
    CCScrollView    *scrollView1;
    CCLayer         *cclayer2;
    CCScrollView    *scrollView3;
    CCSprite        *sprite3;
    
    CCScrollView    *scrollView4;
    CCPoint         adjustPos;
    bool            isScroll1;
    int             countTime1;
    int             countTime3;
    int             countTime4;
    
    CCSprite        *sprite4;
    CCSprite        *cartoon2001;
    CCSprite        *cartoon3007;
    int             isScroll2;
//    bool            isScroll3;
    int             isScroll3;// 3个状态 0 // 1// 2
    int             isScroll4;
    
    CCParticleSystem *rainParticle;
};
#endif /* defined(__FishX__GMCartoonLayer__) */
