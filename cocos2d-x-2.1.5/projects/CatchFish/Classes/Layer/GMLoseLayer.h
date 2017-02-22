//
//  GMLoseLayer.h
//  FishX
//
//  Created by peng on 12-12-26.
//
//

#ifndef __FishX__GMLoseLayer__
#define __FishX__GMLoseLayer__

#include <iostream>
//#include "cocos2d.h"
#include "../Config/GMFashionConfig.h"
#include "cocos-ext.h"

//USING_NS_CC;
USING_NS_CC_EXT;

class GMLoseLayer : public CCLayer
{
private:
    CCSpriteBatchNode   *loseBatchNode;
    CCSpriteBatchNode   *hitFishBatchNode;
    bool            isOpenVideo;
    void initElement();
    
    CCLayerColor         *loseLayer;
    
    void chooseCard(CCObject *pSender);
    void againGame(CCObject *pSender);
    
    void continueTheGame();
    void pauseAction();
    void videoAction();
    
    void addCrowAnimation();
    void removeCrow(CCNode *pNode);
    
    void showScore(CCSprite* pChild);
    void arrowAtion(CCObject *pSender);
    void arrowAtion1(CCObject *pSender);
	void keyBackClicked();
	void keyboardHook(int keyCode, int keyEvent);
    void showStartPrompt();
    CCSprite *bg2;
    CCRect          scrollRect;
public:
    virtual bool init();
    GMLoseLayer();
    ~GMLoseLayer();
    static CCScene* scene();
    
    CCMenu *menu;
    bool m_bTouchedMenu;
    
    CREATE_FUNC(GMLoseLayer);
    
private:
    CCScrollView    *scrollView;
    float           tempx1,tempx2;
    int             m_nCurPage;
    int             m_nTotalPage;
    float           moveW;
    int             currentLevel;
    
    void setPage(bool plus);
    void registerWithTouchDispatcher();
    void adjustScrollView(int arrow);
    void addStarEffect(CCNode *pNode);
    
    virtual bool ccTouchBegan(CCTouch *pTouch,CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch,CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch,CCEvent *pEvent);
    virtual void ccTouchCancelled(CCTouch *pTouch,CCEvent *pEvent);
};

#endif /* defined(__FishX__GMLoseLayer__) */
