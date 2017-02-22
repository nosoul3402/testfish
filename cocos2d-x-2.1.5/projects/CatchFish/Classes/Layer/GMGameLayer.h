//
//  GMGameLayer.h
//  FishX
//
//  Created by peng on 12-12-24.
//
//

#ifndef __FishX__GMGameLayer__
#define __FishX__GMGameLayer__

#include <iostream>
//#include "cocos2d.h"
#include "../Config/GMFashionConfig.h"
#include "../Models/GMBullet.h"
#include "GMMenuLayer.h"
#include "GMElementLayer.h"
#include "../Models/GMCheckpointsList.h"
#include "../Models/GMEnemyAction.h"
#include "../Models/GMTask.h"
#include "GMBootModeLayer.h"
#include "GMWheelLayer.h"
#include "../Models/GMGoods.h"
#include "GMTargetLayer.h"
#include "GMPauseLayer.h"
#include "GMAchievementPrompt.h"
#include "../Models/GMNet.h"

#define RandFishNum  50
//USING_NS_CC;

class GMGameLayer : public cocos2d::CCLayer
{
public:
    virtual bool init();
    GMGameLayer(void);
    virtual ~GMGameLayer(void);
    static cocos2d::CCScene* scene();
    
    void chooseCardLaye();
    CREATE_FUNC(GMGameLayer);
    void loadData(int status);    
public:
    GameMode            gameMode;
    GMBillingModel      billingModel;
	GMCheckpointsList   *checkpointsList;
	GMMenuLayer         *menuLayer;
	int arrowDir;
	int fireOn;
	bool shootting;
	int fireTimeCount;
	int choosedSkill;
	int arrowTurnSpeed;
	int fireDelay;
	CCPoint touchLocation;
    int     getCountTotalTime() {return countTotalTime;}
private:
    CCLayerColor        *ripple3DLayer;
    CCNode              *node;
    CCSprite            *tempSprite;
    CCLayer             *fishLayer;
    GMElementLayer      *elementLayer;
    GMElementLayer      *skillElementLayer;
    GMBootModeLayer     *bootModeLayer;
    GMWheelLayer        *wheelLayer;
    GMTargetLayer       *targetLayer;
    GMAchievementPrompt *achievementPrompt;
    GMPauseLayer        *pauseLayer;
    
    CCSpriteBatchNode   *fishBatchNode1;
    CCSpriteBatchNode   *attackfishBatchNode1;
    
    CCSpriteBatchNode   *bulletSheet;
    CCSpriteBatchNode   *laserSheet;
    CCSpriteBatchNode   *netBatchNode;
    CCSpriteBatchNode   *fishBulletBatchNode;
    CCLayer             *fishBulletLayer;
    CCLayer             *bossLayer;
    GMBullet            *m_pLaserBullet;
    CCPoint             tempVector;
    
//    GMCardList          *cardList;
    GMTask              *task;
    
    CCArray             *allEnemyArray;
    CCArray             *allBulletArray;
    CCArray             *allNetArray;
    CCArray             *allEnemyBulletArray;
    
    bool                _isLaser;//

    GMGoods             *goods;
    
    GMSkill             critSkill;//暴击
    int                 countCritTime;//暴击持续时间
    int                 oldCount;
    int                 countPaysScore;//记录秒杀技能的总分数
//    bool                isWheel;//任务轮是否显示
    
    float               brushSTimes;//刷怪时间
    float               countbrushSTimes;
    int                 checkBatterTimes;//检测连击时间

    float               scaleValue;//鱼、能量的缩放
    int                 startBrushSTime;
private:
    int                 mPercentage;
    int                 laserTimes;
    int                 taskShowTime;
    int                 countTotalTime;//顺时针计时
    int                 countTime;//顺时针计时
    int                 countCardTime;//关卡时间
    
    int                 taskHitNum;
    char                bulletName[30];
    bool                isAgainTransform;

    int                 totalNum;//刷怪数
    int                 countNum;//记录已经加了多少条鱼
    
    int                 countAllFishTag;//标记每条鱼的tag
    int                 countFishBulletTag;//标记每条鱼子弹的tag
    int                 countShootBulletTag;//标记每条鱼子弹的tag
    
    int                 strangeNum;
    int                 countStrangeNum[RandFishNum][2];//记录怪物的数据 [][0] 为怪物id,[][1]为加载怪物数目
    int                 countHitNum;
    bool                isCheckBatter;//是否连击
    
    int                 m_nTotalMoney;
    
    int                 m_nCurrentScore;
    
    int                 taskTimes;//任务时间
    int                 taskOverTimes;//任务时间
    
    int                 bulletGrade;//炮弹等级
    int                 energyTime;
    //记录冰冻时间
    bool                isFrozen;
    int                 countFrozenTime;

    CCLayer             *netParticleLayer;
    CCArray             *curvePointArray;
    CCArray             *fishArrayData;
    
//    bool isStartBrushStrange;
    int  laserTotalNum;
    bool isHitIDFish15;//是否击中15
    CCPoint fish15Point;
    
    bool           isAndroidBack;//
    
    CCSpriteBatchNode *wheelBatchNode;
    int                 _isExistboss;//当前关是否存在boss
    int                 currentLevel;//当前关卡索引
    int                 m_nEndlessModeDataIndex;//无尽模式文件索引
    int                 m_nMagnification;//倍率系统
    
    int                 countSmallStarNum;//记录当前屏幕小海星的个数
    int                 giftTime;
    
    CCArray             *m_pShootBullet;
    
    int                 countSkillTime[2];//技能cd 状态
    
    int                 billingIndex;
    bool                _isShowYiDong;//是否已经显示移动的计费界面
    bool                _billing91Again;//无尽模式失败后的91付费
public:
	//static void keyboardHook(UINT message, WPARAM wParam, LPARAM lParam);
//#pragma mark - 更换炮台
    void changeCannon(int index);
    
    void removeNet(int num ,GMNet *net);
    void setMinusAndPlusEnabled(int index);
    void plusAction();//加大
    void minusAction();//减小
    void pauseAction();
    bool getPauseStatus();
    void continueGame();
    void removeWheelView(CCNode *pNode);
    void removePayskillEffect();
    void removeBloodEffect();
    void usedSkill1(CCObject *object);
    void usedSkill2(CCObject *object);
    void shootBossBullet();
    void showEnergeDialog();
    void setGiftAtion();
    void againAction();
    void bugEnergyAction();
    
    
    void petrifactionEffect();
    void nextAction(int index);
    void startGame();
    void rewaradPayskillEffect();
    void achievementEnerge(int score,CCPoint point);

    void unscheduleGame();
    
    void enemyDeath(GMEnemyAction* enemyAction);
    void removeEnemyFromBatchNode (CCNode *pNode);
    /*
     *  引导模式出现雅典娜
     */
    void showBootModeFIshID16();
    /*
     *  移除子弹
     */
    void removeBullet(GMBullet*bullet);
    void automaticallyRemovedBullet(CCNode *pNode);
    void removeFishBullet(GMBullet *bullet);
    void removeCollisionFishBullet(GMBullet *bullet);
    /*
     *  施放技能
     */
    bool getBootModeCastSkill();
    void setCastSkill(int goodsId);
    
    void setOctopusShootBullet(CCPoint point ,float rotation);
    /*
     *  暂停
     */
    void pauseAllAction(bool pause);
    /*
     *  召唤海星星
     */
    void setCallTwoStarFish(int num);
    void setRestoreLife();
    void setRestoreLifeValue(float value);
    void removeStarfishKing();
//    ccBezier getRandCurveBezier();
    
    
//#pragma mark - GMBossPoseidon
    void showBossPoseidonBullet(CCPoint point,float rotation);
    
    void removeBossPoseidon();
    
    void setFishBullet(float rotation,CCPoint point,int _id);
    
    void setAndroidBack(bool isBack) {isAndroidBack = isBack;}
    
    CCPoint getFish15Point() {return fish15Point;}
    
    float getScaleValue() {return scaleValue;}
    
    void setFirstBootMode();
//#pragma mark -  计费
	void removeBilling(int index, bool _isClickClose, int type);
	void checkBillingPoint(float dt);
private:
    void initValue();
    void initElement();
    
    void checkAllBullet();
    void logicProcessing(GMEnemyAction *enemyAction);

    void update(float t);
    void brushStrange(float ct);
    void checkUpadte(float t);
    void updateCheckNetAndFish(float t);
    
    void initFishFrames();
//    void addEnemy(int _id);
    void addEnemy(int _id, EnemyRouteStatus status,CCPoint point);

//    void addFishArray(GMStrange *strange);
    void addFishArray(GMStrange *strange ,EnemyRouteStatus status);
    void setRandCurve(GMStrange *strange);
    
    void initBullet();
    void addBullet(CCPoint shootVector);
    
    
    void addLaser();
    void removeLaser(CCNode *pNode);
    void showLaserReward(float dt);
    
    void addFishBullet(CCNode *pNode);
    void fishBulletMove(GMBullet *fBullet);
    void enenyBulletMove(GMBullet *fBullet);

    void fishBulletMoveAfter(CCNode *pNode);
    
    void addNet(CCPoint point,int tag);
   
    void firedBullets(CCPoint shootVector);
    void transformCannon(CCPoint location);
    void finishShoot();
    void spriteMoveFinished(CCObject *object);    
    //
    void randEnemy();

    void   setCurrentScore(int scroe);
    void   setTotalMoney(int money);
    float  getStageRate();//获取能量阶段概率
    
    float getRate(GMEnemyAction* enmey);
    bool randRates(float rate);

    //击中效果
    void hitEffect(GMEnemyAction* enemyAction);
//    bool getCollisionValue(float angle,int r0,float r1,float r2,CCPoint p1, CCPoint p2);
    //检测连击
    void checkBatter();
    void checkTaskFinshed(GMEnemyAction* enemyAction);
    //检测胜利还是失败
    void checkWinOrFail();
    /*
     *  检测固定刷怪
     */
    void checkFixedBrushStrange(int time);
    
    void showOver();
    //
    void initTiledMap();
    
    void draw();
//#pragma mark - boss  
    //boss
    void initBossLayer();
    void initBoss1();
    void removeBoss1();
    void cleanBoss1(CCNode *pNode);
    
    void initBossOctopus();
    void removeAllBoss(float dt);
    void setOctopusShootBulletAfter(CCNode *pNode);
    
    void initStarfishKing();

    void initBossPoseidon(float dt);
//#pragma mark - Weel  
    /*
     *  Weel
     */
    void showWheelView();
    void removeWheelRes();
//#pragma mark - 设置总能量和当前的分数  
    //设置总能量和当前的分数
	void setMoneyAndSocre(int value);
   
//#pragma mark - 暂停  
    /*
     *  暂停
     */
//    void pauseAllAction(bool pause);
    void setCurveEnemyAction(bool stop);
    void setBulletEnemyAction(bool stop);
    
    void goToCardLayeFormBootMOde(float dt);
    
    void winOverSaveData(bool isScore);
   
    float getStoryModeRatio();
    
    void setReadNewFileData(int index);
    
    void setRestoreLifeEffect(float dt);
    
    void removeSubBoss(CCNode *pNode);
//#pragma mark - win lose
    void skipWinLayer(float dt);
    void skipLoseLayer();
    void skipEndlessMode();
    void skipGMCardLayer();
//#pragma mark - 提示
    bool isShowDialogLayer;
    bool isShowDialogLayer2;
    bool isShowDialogLayer3;
    void showDialogLayer();
    bool showDialogLayer2();
    //  赔率开启提示
    bool showDialogLayer3();
    void removeDialogLayer3(CCObject *pSender);
    
    void removeDialog(CCNode *dialog);
    void removeDialogLayer(CCNode *dialog);
    
    void initDialogLayer(const char *string,SEL_CallFuncN sel);
    void initDialogLayer2(const char *string,SEL_CallFuncN sel);
    bool showPromptBatter();
    bool showPromptLaser();
    
    bool isShowPromptOpenCannon;
    bool showPromptOpenCannon();
    bool showOpenCannon();
    
    void removePromptOpenCannon(CCNode *dialog);
    void removePromptOpenCannon2(CCNode *dialog);
    
    void setSkillValue();
//#pragma mark -  计费
    void addBilling(int index,int index2);//1 为正版验证，2为购买能量，3为购买技能，4为购买武器
//#pragma mark - 91 计费回调方法
    void check91BillingPoint(float dt);
    void removeTipView(float dt);
//#pragma mark - 移动 网乐
    void showYidongSdkView(int index);
//#pragma mark - 电信计费相关的方法
    void showTelecomSMSView(int _index);
    
    void setAllSkillNum();
    void setUpgradeWeapons();
    
    virtual void keyBackClicked();//Android 返回键
	virtual void keyboardHook(int code, int event);//AndroidTV enter
protected:    
    void ccTouchesMoved(CCSet* touches, CCEvent* event);
    void ccTouchesEnded(CCSet* touches, CCEvent* event);
};

#endif /* defined(__FishX__GMGameLayer__) */
