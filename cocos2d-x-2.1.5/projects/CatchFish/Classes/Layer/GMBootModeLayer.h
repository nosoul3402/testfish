//
//  GMBootModeLayer.h
//  FishX
//
//  Created by peng on 13-2-28.
//
//

#ifndef __FishX__GMBootModeLayer__
#define __FishX__GMBootModeLayer__

#include "cocos2d.h"
#include "../Config/GMHeaderConfig.h"

USING_NS_CC;

typedef struct StoryStatus {
    int _storyIndex;			//剧情
    int _dialogueNum;			//对话
} _StoryStatus;

class GMBootModeLayer : public CCLayerColor
{
public:
    virtual bool init();
    virtual ~GMBootModeLayer(void);
    static CCScene* scene();
    
    CREATE_FUNC(GMBootModeLayer);

private:
//    std::string         *prompt[1];
    static const char                *prompt[27];
    CCSpriteBatchNode   *guideBatchNode;
    CCSprite            *guide001;
    CCSprite            *role1;
    CCSprite            *role2;
    CCLabelTTF          *labelt;
    int                 _page;

	//bool                isMoveTip;

    CCArray             *promptLanguage;
    CCObject            *_delegate;
    
    int                 _storyStatus;
    CCMenu              *specialMenu;
    
    _StoryStatus        m_nStoryStatus;
    
    void nextAction(CCObject *pSender);
    void sureAction(CCObject *pSender);
    void setInterceptionOfEvents();
    void removeInterceptionOfEvents();

    virtual bool ccTouchBegan (CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved (CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded (CCTouch *pTouch, CCEvent *pEvent);

    int                 promptIndex;
    bool                isShowDialogue;
    bool                isShow;
    bool                isShowDialogue2;

    CCSprite *minusItem;
    CCSprite *plusItem;
    CCSprite *roundSprite;
    bool                isClickSkill;
public:
    int                 _status;
	//bool                _whetherGray;
    
    
    int                 curTimes;//记录当前的时间
	//bool                _isPause;
    bool                isHitFishId15;
    
    void setOtherValue();
    
    void setDelegate(CCObject *target) {_delegate = target;}
    
    void setSynopsisBg();
    void setLabelInfo(int index);
    
    void setStoryStatus(int status) { _storyStatus = status;}
    int  getStoryStatus() {return _storyStatus;}
    bool getClickSkill() {return isClickSkill;}
    
    void showPromptBox();
    void removePrompView();

    void showBootModeStory(int countTime,int enemyCount);
   
    void showBossDeath();
    void showDialogueNum();
    
    bool getShow() { return isShow;}
};
#endif /* defined(__FishX__GMBootModeLayer__) */