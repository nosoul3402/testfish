//
//  GMAchievementPrompt.h
//  FishX
//
//  Created by peng on 13-3-12.
//
//

#ifndef __FishX__GMAchievementPrompt__
#define __FishX__GMAchievementPrompt__

#include <iostream>
#include "../Config/GMFashionConfig.h"

typedef struct _AchievementView {
    CCSprite    *_bg;
    int         _countShowTime;
    bool        _isShow;
    int         _energe;
    
} AchievementView;

class GMAchievementPrompt : public CCLayer
{
    
public:
    virtual bool init();
    GMAchievementPrompt();
    ~GMAchievementPrompt();
    static CCScene* scene();
    
    CREATE_FUNC(GMAchievementPrompt);
    CCNode      *_delegate;
private:
    CCSpriteBatchNode *achievementBatchNode;
    CCArray     *achievementArray;
    int     eStatus;
//    int     countShowTime;
    int     countPayNum;
    bool    isShow;
    
//    CCSprite *bg[3];
    
    AchievementView view[3];
    int         showNum;//view上已经展示的数目
private:
    void initElement();
    void showAchievement(int index);
    void removeAchievementPromptView();
public:
    void showGMCheckpointsPrompt(int index);
    void showEnergePrompt(int curEnerge);
    void showSwirlPrompt();
    /*
     *  一炮击中n条鱼的 提示
     */
    void showhitFishPrompt(int num);
    /*
     *  显示成就界面持续时间
     */
    void showAchievementPromptViewTime();
};

#endif /* defined(__FishX__GMAchievementPrompt__) */
