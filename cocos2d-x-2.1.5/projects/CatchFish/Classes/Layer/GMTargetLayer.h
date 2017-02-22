//
//  GMTargetLayer.h
//  FishX
//
//  Created by peng on 13-3-10.
//
//

#ifndef __FishX__GMTargetLayer__
#define __FishX__GMTargetLayer__

#include <iostream>
#include "../Config/GMFashionConfig.h"
#include "cocos-ext.h"

USING_NS_CC_EXT;

class GMTargetLayer : public CCLayerColor
{
    
public:
    virtual bool init();
    GMTargetLayer();
    ~GMTargetLayer();
	static CCScene* scene();
    CREATE_FUNC(GMTargetLayer);
    
public:
    CCNode          *_delegate;
    
    /*
     *  index == 3//无尽模式结束界面
     *  index1 无尽模式 阶段索引
     */
    void initElement(int index,int index1);
    void showBossIcon(int bossId);
    void showFishKind(int score,CCArray*array);
    void showScoreAndTime(int score,int time);
	void showAllValue();
	void goAtion(CCObject *pSender);
private:
    CCScrollView    *scrollView;
    CCSprite        *background;
    CCSprite        *gamegoal011;
    float           bg_w,bg_h;
    CCPoint         m_touchPoint;
    float           tempx1,tempx2;
    //    int
    int             m_nCurPage;
    int             m_nTotalPage;
    int             m_nIndex;
    
    CCRect          scrollRect;
    CCSprite        *bgSprite;
    CCRect          bgRect;
    CCMenuItemSprite *arrow1;
    CCMenuItemSprite *arrow2;
    
    CCArray         *tempArray;
    
    
    void arrowAtion1(CCObject *pSender);
    void arrowAtion2(CCObject *pSender);
    
    void againAction(CCObject *pSender);
    void backHomeAtion(CCObject *pSender);
    void backAction();
    void adjustScrollView(int arrow);
    void setPage(bool plus);
    virtual void registerWithTouchDispatcher();
    
    virtual bool ccTouchBegan (CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved (CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded (CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);
};
#endif /* defined(__FishX__GMTargetLayer__) */
