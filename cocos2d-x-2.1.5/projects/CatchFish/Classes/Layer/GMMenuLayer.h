//
//  GMMenuLayer.h
//  FishX
//
//  Created by peng on 13-1-4.
//
//

#ifndef __FishX__GMMenuLayer__
#define __FishX__GMMenuLayer__

#include <iostream>
//#include "cocos2d.h"
#include "../Config/GMFashionConfig.h"
#include "../Models/GMBullet.h"
#include "../PublicModels/UIRollNum.h"
//USING_NS_CC;

class GMMenuLayer : public cocos2d::CCLayer
{
public:
    virtual bool init();

	GMMenuLayer();
    virtual ~GMMenuLayer(void);
    static CCScene* scene();
    CREATE_FUNC(GMMenuLayer);
    
    float       mPercentage;
    
    int         m_pTimeG;//关卡时间
    int         m_pTimeM;//送金币时间
    int         m_pTotalScre;
    int         m_pScre;
    int         m_pTotalMoney;
    int         m_pMoney;
    
    float       oldAngerValue;
	float       newAngerValue;
	CCMenuItemSprite    *skill1;
	CCMenuItemSprite    *skill2;
    
    void setMinusAndPlusEnabled(bool enabled);
private:
    CCSpriteBatchNode   *menuBatchNode;
    CCSpriteBatchNode   *cannonSheet;
//    CCSpriteBatchNode   *junengSheet;
    GMBullet            *cannon;
    CCSprite            *effect;
    CCSprite            *effect6;
    CCSprite            *junengEffect;
    
    UIRollNum           *m_pScoreNum;
    UIRollNum           *m_pScoreNum1;
    
    UIRollNum           *m_pTimeGNum;
    UIRollNum           *m_pTimeMNum;
    UIRollNum           *m_pTotalMoneyNum;
    UIRollNum           *m_pMagnificat;
    
    UIRollNum           *skillRollNum1;
    UIRollNum           *skillRollNum2;
    
    CCLayer             *taskLayer;
    CCLayer             *batterLayer;
    
    CCSprite            *toTheTiming;//倒计时精灵
//    UIRollNum           *m_pTaskTime1;
//    UIRollNum           *m_pTaskTime2;
    CCSprite            *changeboomEffect;
    
    int                 taskNum;
    
    char                cannonName[30];
    
    bool                isEffectOpacity;
    int                 effectOpacity;
    
    int                 batterNum;//连击次数
    int                 batterCount;
    int                 battercount1;
    bool                isAnger;//是否怒气值满了
    CCPoint             cannonPoint;
    CCPoint             effectPoint;
    CCPoint             junengPoint;
    
    int                 m_LifeValue;//生命值
    
    CCMenuItem          *pauseItem;
    
    CCMenuItemSprite    *plusItem;
    CCMenuItemSprite    *minusItem;
    int                  moneyNum;
private:
    void initValue();
    void loadData();
    void loadData1();
    void initElement();
    void pauseAction(CCObject *pSender);

    void smallerAction(CCObject *pSender);//变小
    void largerAction(CCObject *pSender);//变大
    
    void initCannon();
    
    void scaleAfter();
    void setEffect();
    void setFadeTo(CCSprite *sprite);    
    void moveCannonDown();
    void moveCannonUp();
    
    void moveNumProgress();
    void remvoeBatterEffect();
    void showTaskAnimation(CCNode *pNode);
    
    void setAngerAnimation(CCSprite *sprite,const char *name);
    
    void bugEnergyAction(CCObject *object);
    
    void shootLaser();
    
    static const int juneng[];
    static const int juneng1[];
    CCSprite            *bloodb;
    
    /*
     *  目标分数
     */
    CCSprite        *cupSprite;
    float           curScore;
    CCProgressTimer *targetScoreProTimer;
    bool            isFulfill;//是否完成
    void showTargetScore();
    void setAgainJunengEffect(CCNode *pNode);
    
    bool                isShootAgain;
    
    float               TopTempW;
    float               transformAngle;
    
//#pragma mark 倍率按钮
//    void setMagnificationModel();
    void removeLiuguang(CCNode *pNode);
    
    void addSkill();
    void usedSkill1(CCObject *object);
    void usedSkill2(CCObject *object);
    void showSkillNum();
public:
    int                 cannonIndex;
    bool                isLaser;
    bool                isShootLaser;//激光炮台移上来后在发射
    int                 laserIndex;
    bool                isShowTaskBox;
    
    CCObject             *delegateGame;
    
    void loadingData(int index);
    /*
     *  倒计时
     */
    void showCountdown(int index);
    
    void showLaser(bool laser);
    
    void changeCannon(int index);
    
    GMBullet* getCannon();
    float getCannonRotation();
    float getCannonPointX();
    void setCannonRotation(float angle);
    void setFadeOut();
    void setEffectOpacity();
    
    void setCheckpointsTimeValue(int time);
    void setAngerValue(int value);
    bool getAnger() { return  isAnger;}
    void setAnger();
    void setLifeValue(int value);
    int  getLifeValue(){return m_LifeValue;}
    
    void setTotalMoneyNum(int num);
    void setEnergyTime(int time);
    
    void addBatterEffect(int num);
    
    void showTaskScaleAnimation();
    void removeTaskAnimation();
    void showTaskBox(int strangeId,int taskTotalNum);
    void setTaskTime(int time);
    void setTaskNum(int num);
    void setTaskTip(bool win);
    void removeTaskBox();
    
    void setSKillNum1(int num1);
    void setSKillNum2(int num2);
//    void addSkill(CCObject* target, SEL_MenuHandler selector1,SEL_MenuHandler selector2);
    void setSkill1Enabled(bool enabled);
    void setSkill2Enabled(bool enabled);
    void commonConnon(int index);
    
    
//#pragma mark - 倒计时动画
    void setCountdownAnimation();
    void setStopCountdownAnimation();
    void showOverView();
    
    void showBloodb();
    
    void setAllMenuEnabled(bool value);
    
    /*
     *  目标分数
     */
    void setTargetScore(int score);
    void showTargetProTimer(int score,bool clean,int leve);
    void showCurrentScore(int score);
    
    /*
     *  设置是否再次发射子弹
     */
    void setShootAgain(bool sa) {isShootAgain = sa;}
    bool getShootAgain() { return isShootAgain;}
    
    float getTransformAngle() {return transformAngle;}
    
//#pragma mark 倍率按钮
    void setMagnificationModel(CCObject *pSender);
    void setMagnificationModel1(int index);
protected:
    
    CCProgressTimer *loadingCt1;
    CCProgressTimer *loadingCt2;
    
};


#endif /* defined(__FishX__GMMenuLayer__) */
