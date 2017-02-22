//
//  GMPublicMethod.h
//  FishX
//
//  Created by peng on 13-1-15.
//
//

#ifndef __FishX__GMPublicMethod__
#define __FishX__GMPublicMethod__

#include <iostream>
#include "../Config/GMEnum.h"
#include "cocos2d.h"
#include "../Models/GMStrange.h"

USING_NS_CC;

class GMPublicMethod // : public CCObject
{
public:
    GMPublicMethod();
    virtual ~GMPublicMethod(void);

	CCObject*		tempLayer;
	CCObject*		menuLayer;
	CCObject*		introLayer;
	CCObject*		mainLayer;
	CCObject*		cardLayer;
	CCObject*		targetLayer;
private:
    GMSkill         skillType;//技能
    float           zoomRatio;//缩放比率
    GameMode        gameMode;
    GameStatus      gameStatus;//优先状态
//    GameStatus      gameStatus1;//优先状态
    MoveStatus      moveStatus;//
    CCArray         *hitArray;//存放击中鱼的数目
    CCObject        *gameLayer;
//    BillingModel    m_gBillingModel;//计费模式
    
    int             consumption_of_energy;//消耗能量
    int             gain_energy;//获得能量
    //    int             currentScore;//等分
    int             evaluationScore;//评价分数
    
    int             m_nCheckpointsIndex;
    bool            isOpenMusic;//是否开启音效
    bool            isAndroidPlayVideo;//安卓是否播放视频
    int             _AudioStatus;

protected:
    std::string *m_pPhoneNumber;
    CCLabelTTF  *tipLabelTTF;
    CCSprite    *tipSpriteBg;
public:
    
    CC_SYNTHESIZE(bool,_isShowLogo,ShowLogo);//只显示一次
    CC_SYNTHESIZE(int, billingIndex, BillingIndex);//91移动计费索引
    
    CC_SYNTHESIZE(bool,_isShow91Pause,Show91Pause);//只显示一次
    
    void setPhoneNumber(const char *text);
    const char* getPhoneNumber();
//    CC_SYNTHESIZE(const char*, phoneNumber, PhoneNumber);//手机号
//
//    CC_SYNTHESIZE(CCString*,number,Number);//手机号
    
    void setCheckpointsIndex(int index) { m_nCheckpointsIndex = index;}
    int  getCheckpointsIndex() { return m_nCheckpointsIndex; }
    /*
     *  获得能量
     */
    void cleanEnergy();
    void setGainEnergy(int ge) {gain_energy = ge;};
    int  getGainEnergy() {return gain_energy;}
    
    void setConsumptionEnergy(int ce);
    int  getConsumptionEnergy() { return consumption_of_energy;}
    
    //    int getCurrentScore() {return currentScore;}
    void setEvaluationScore(int score);
    int  getEvaluationScore() {return evaluationScore;}
    
    /*
     *  设置或获取当前释放的技能
     */
    void setSkillType(GMSkill type) {skillType = type;}
    GMSkill getSkillType() { return skillType; }
    
    /*
     *  设置或获取当前游戏模式
     */
    void setGameMode(GameMode mode) {gameMode = mode;}
    GameMode getGameMode() { return gameMode; }
    
    /*
     *  
     */
    void setGameStatus(GameStatus status) {gameStatus = status;}
    GameStatus getGameStatus() { return gameStatus; }
    
    /*
     *  当前游戏是否暂停
     */
    void setMoveStatus(MoveStatus status) { moveStatus = status; }
    MoveStatus getMoveStatus() {return moveStatus;}
    /*
     *  控制是否弹出暂停界面
     */
//    void setGameStatus1(GameStatus status) {gameStatus1 = status;}
//    GameStatus getGameStatus1() { return gameStatus1; }
    /*
     *
     */
    void setGameObject(CCObject *tager) {gameLayer = tager;}
    CCObject* getGameObject() { return gameLayer; }
    /*
     *  是否开启音效
     */
    void setOpenMusic(bool isShow) {isOpenMusic = isShow;}
    bool getOpenMusic() {return isOpenMusic;}
    /*
     *  安卓是否播放视频
     */
    void setAndroidPlayVideo(bool play) { isAndroidPlayVideo = play;};
    bool getAndroidPlayVideo() {return isAndroidPlayVideo;}
    
    void setAudioStatus(int closeAudio) {_AudioStatus = closeAudio;}
    int getAudioStatus() {return _AudioStatus;}
    /*
     * 设置获取计费模式
     */
    CC_SYNTHESIZE(GMBillingModel, m_gBillingModel, BillingModel);
    
    void showTipView(CCNode *node ,const char*text);
    void removeTipView(CCNode *node);
public:
    static GMPublicMethod* sharedPublicMethod();
    void   purgeSharedPublicMethod();
    
public:
    
    static const int _animationFrames[][3];
    static const int _bExplosion[];
    static const int _eExplosion[];
    /*
     *  获取某个值是几位位数
     */
    static int getScoreNum(int num);
    
    /*
     *  1星：评价分数≤得分≤120%评价分数
     *  2星：120%评价分数＜得分≤150%评价分数
     *  3星：150%评价分数＜得分
     */
    static int getStarNum();
    
    /*
     *  精灵动画帧
     */
    static void setSpriteAnimation(CCSprite *sprite,int s,int e,const char *name,CCObject *pSelectorTarget,SEL_CallFuncN selector);
    static void setSpriteAnimation(CCSprite *sprite,int s,int e,const char *name,float time,CCObject *pSelectorTarget,SEL_CallFuncN selector);
    /*
     *  循环精灵动画
     *  s 起始帧， e 结束帧
     */
    static void setRepeatAnimation(CCSprite *sprite,int s,int e,const char *name,const char *png,float time,bool isStop);
    
    /*
     *  设置获取缩放比率
     */
    static void setZoomRatio(float zoomRatio) { GMPublicMethod::sharedPublicMethod()->zoomRatio = zoomRatio; }
    static float getZoomRatio() { return GMPublicMethod::sharedPublicMethod()->zoomRatio; }
    /*
     *  计算两点间的角度
     */
    static double pointToAngle(CCPoint AOrigin, CCPoint APoint, double AEccentricity);
    
    /*
     *  点与矩形的碰撞检测
     */
    static bool checkRectContainsPoint(CCRect rect,CCPoint point);
    
    /*
     *  从 tiled map 获取曲线
     */
    static void getCurveDataFromTiledMap(CCArray *array );
    /*
     *  从 tiled map 获取鱼阵
     */
    static void getFishArrayDataFromTiledMap(CCArray *array );
    
    /*
     *  物品列表
     */
    static void readGoodsListFromFile(const char *fileName,CCArray *arrar);
    /*
     *  成就列表
     */
    static void getAchievementPrompFromFile(const char *fileName,CCArray *arrar);
    /*
     *  angle:当前鱼的角度
     *  r0:离中心点的距离（有正反）r1:鱼的半径（宽） r2:子弹的半径（宽） p1:鱼的位置  p2:子弹的位置
     */
    static bool getCollisionValue(float angle,int r0,float r1,float r2,CCPoint p1, CCPoint p2);
    
    /*
     *  获取送金币时间
     */
    static long getTime();
    static void getGoldCoinsTime();
    /*
     *  获取
     */
    static bool getChangeTime(int year,int mon,int day);
    /*
     *  获取随机曲线点
     */
    static ccBezier getRandCurveBezier();
//#pragma mark -
//#pragma mark 倍率模式
    /*
     *  index 为-1 和 1
     */
    static void setCurrentMagnificationModel(int index);
    static int getChooseMagnificationModel();
    static int getOpenMagnificationModel();
    static int getMagnificationModel(int index);
    //  怒气设定
    static int getChooseMagnificationModel1();
public:
    /*
     *  添加获取击中的鱼
     */
    void setHitValue(int strangeId);
    int  getHitNum();
    GMStrange* getHitStrange(int index);
    void cleanHitArray();
private:
    static GMPublicMethod* m_pPublicMethod;
    void initValue();
    
};

#endif /* defined(__FishX__GMPublicMethod__) */
