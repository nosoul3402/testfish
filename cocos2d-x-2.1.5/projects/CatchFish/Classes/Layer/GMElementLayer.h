//
//  GMElementLayer.h
//  FishX
//
//  Created by peng on 13-1-9.
//
//

#ifndef __FishX__GMElementLayer__
#define __FishX__GMElementLayer__

#include <iostream>
#include "../Config/GMFashionConfig.h"
#include "../PublicModels/UIRollNum.h"
//USING_NS_CC;

class GMElementLayer : public cocos2d::CCLayer
{
public:
    virtual bool init();
    virtual ~GMElementLayer(void);
    static CCScene* scene();
    CREATE_FUNC(GMElementLayer);
private:
    void initElement();
public:
    
    void loadingData(int index);
    
    void addEnergeBlink(CCPoint point,float scale);
//    void addEnerge(CCPoint point);
    void moveEnerge(CCSprite *sprite);
    void addParticles(const char *name,CCPoint point);
    void showParticles(const char *name,CCPoint point);

    void showNumber(int value, CCPoint point);
    
    //
    void showBloodEffect(float scale);
    void showPayskillEffect();
    void showPayTittle(float move);
    
    void showIceEffect();
    void iceMoveAction();
    
    //
    void showWater(CCPoint point);
    /*
     *  鱼的的子弹爆炸效果
     */
    void initFishBulletExplosionEffect();
    void bulletExplosionAnimation(int _id,CCPoint point,float scale);
    /*
     *  boss 的子弹爆炸效果
     */
    void initBoss1BulletExplosionEffect();
    void boss1ExplosionAnimation(int _id,CCPoint point);
    /*
     *  打中特殊鱼的奖励 Reward
     */
    void showRewardEffect(int score);
    void countRewaradTime();
    /*
     *  暴击
     */
    void showBaoJiEffect();
    void showBaoJiEffect1();
    void baoJiTitleMove();
    void setbaojiRotation(float rotate);
    void removeBaoji019Sprite();
    
    /*
     *  显示任务提升2
     */
    void showTaskPrompt2(int score);
    void removeTaskPrompt2();
    /*
     *  "你真牛" 大到鱼显示 还是 技能漩涡 显示
     */
    void  setPaysStats(int status) {paysStatus = status;}
    int   getPaysStats() {return paysStatus;}
    
    
    void setDelegate(CCObject *target) { delegateGame = target; }
    
    /*
     *  倒计时
     */
    void showOverView();
    CCSprite *getOverSprite();
    void removeOverSprite();
private:
    
    CCObject             *delegateGame;
    
    /*
     *  水波纹层
     */
    CCSpriteBatchNode *waterBatchNode;
    /*
     *  "你真牛" 大到鱼显示 还是 技能漩涡 显示
     */
    int         paysStatus;
    /*
     *  任务提升2
     */
    CCSprite *taskPrompt2;
    
    void removePayskillEffect(CCNode *pNode);
    /*
     *  鱼的的子弹爆炸效果
     */
    void removeExplosion(CCNode *pNode);
    
    /*
     *  boss1 的血条
     */
    
    CCLayer     *bossbloodLayer;
    CCProgressTimer *bossbloodProgress;
    
    /*
     *  boss1 的石化
     */
    CCSpriteBatchNode *petrifactionBatchNode;
    
    /*
     *  boss1 的石化
     */
    CCSprite *payTittle;
//#pragma mark - 礼盒
    CCLayer *giftLayer;
    CCSprite *gift;
    UIRollNum *minRollNum;
    UIRollNum *secRollNum;
    CCMenuItem *giftmenuItem;
    bool    isShowA;
    void setGiftAtion(CCObject *pSender);
    void setAnimation();
    
    void removeBloodEffect(CCNode *pNode);
//#pragma mark - public
public:
    /*
     *  boss1 的血条
     */
    void initBossbloodFile();
    void showBoosBlood();
    void setBossBloodValue(float value);
    void removeBossBlood();
    /*
     *  boss1 的石化
     */
    void initPetrifactionFile();
    void showPetrifactionEffect();
    void showPetrifactionEffect2();
    void removePetrifactionEffect2(CCNode *pNode);
    void setPetrifaction(bool p) { isPetrifaction = p; }
    bool getPetrifaction() { return isPetrifaction;}
    
    int  countPetrifactionTime;
//#pragma mark - 闪红
    void setRedlightningEffect();
    void removeRedlightningEffect(CCNode *pNode);
    /*
     *  换爆弹的提示
     */
    void changeShowNumeber(int num);
    
//#pragma mark -  ------  等到的技能
    void setOtheSkill(int goodId);
    void setCountSillTime();
    void setClickOtheSkill();
    void removeOtherSkill();
    
//#pragma mark - 礼盒
    void addGift();
    void setGiftTime(int time);
    void setGiftValue();
private:
//#pragma mark - 
    void scaleEffect(CCNode *pNode);
   
    void removeParticles(CCNode *pNode);
    void removeNumber(CCNode *pNode);
    //
    void initSpriteFrames();
    void removeSprite(CCSprite *sprite);
    void removeSprite1(CCNode *pNode);
    
    void removeEffect(CCNode *pNodescaleEffect);
    
    //
    void initWater();
    
    int     countIceTime;
    bool    isIcetopMove;
    
    /*
     *  打中特殊鱼的奖励 Reward
     */
    bool  isShowReward;
    int   showRewardTime;
    void removeRewarad();
    
    /*
     *  暴击
     */
    CCSpriteBatchNode *baoJiBatchNode;
    void initBaoJi();
    void removeBaoJiEffect(CCNode *pNode);
//    void removeBaoJiEffect1(CCSprite *object);
    
    /*
     *  换爆弹的提示
     */
    CCSprite    *numberSprite;
    
    bool isPetrifaction;
    
    void initNumberFile();
    void removeNumber1(CCNode *pNode);

private:
    CCMenu              *otherSkill;
    bool                isShow;
    int                 countSkillTime;
    void setOtheSkillEffect(CCObject *pSender);
protected:

    
};

#endif /* defined(__FishX__GMElementLayer__) */
