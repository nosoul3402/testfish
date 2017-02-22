//
//  GMAccessData.h
//  FishX
//
//  Created by peng on 13-1-14.
//
//

#ifndef __FishX__GMAccessData__
#define __FishX__GMAccessData__

#include <iostream>
//#include "GMStrange.h"
#include "cocos2d.h"

USING_NS_CC;

class GMAccessData // : public CCObject
{
public:
    GMAccessData();
    virtual ~GMAccessData(void);

private:
//    int             fishKind;//当前关卡鱼的种类    
//    CCDictionary    *hitDictionary;
//    int             checkpoints;
public:
    /*
     *  当前大关的所以
     */
//    void setCheckpointsIndex(int index) { checkpoints = index; }
//    int  getCheckpointsIndex() { return checkpoints; }
    
public:
    static GMAccessData* sharedAccessData();
    void purgeSharedAccessData();
    
    void initValue();
    void cleanData();
    
    //
    void saveTotalMoneyNum(int moneyNum);
    int  getTotalMoneyNum();
    void setTotalMoneyStatus(int nTotalMoney);
    int  getTotalMoneyStatus();
    /*
     *  每一个大关都是10、20、30开始
     *  大关里的小关按（11、12、13、14、15）（21、22、23、24、25）等来计算
     */
    void saveEachLevelScore(int level,int score);
    int  getEachLevelScore(int level);
    /*
     *  保存每一关的星的等级
     */
    void saveEachLevelStar(int level,int star);
    int  getEachLevelStar(int level);
    /*
     *  目前完的游戏关卡（小关）
     */
    void saveCurrentLevel(int level);
    int  getCurrentLevel();
    /*
     *  目前开启的游戏关卡
     *  cp1 : 关卡 tag
     *  cp2 : 0 或 1
     */
    void saveOpenCheckpoints(int cp1,int cp2);
    int getOpenCheckpoints(int cp1);
    
    /*
     *  获取声音是否关闭
     *  closeAudio = 1：关闭，2开启
     */
    void saveAudioStatus(int closeAudio);
    int getAudioStatus();
    
    /*
     *  是否第一次进入游戏
     *  
     */
    void saveBootModeStatus(int sValue);
    int  getBootModeStatus();
    
    /*
     *  成就能量状态
     */
    void saveEnergePromptStatus(std::string sValue);
    int  getEnergePromptStatus();
    /*
     *  Swirl 漩涡的数量
     */
    void saveSwirlAmount(int amount);
    int  getSwirlAmount();
    
    /*
     *  成就每个的状态
     */
//    static void saveEachAchievementStatus(int index,std::string sValue);
    void saveEachAchievementStatus(int index,int status);
    int  getEachAchievementStatus(int index);
    /*
     *  获取送金币时间
     */
    void saveGoldCoinsTime(long time);
    long getGoldCoinsTime();
    /*
     *  保存获取赔率模式
     */
    void saveMagnificationModel(int index);
    int  getMagnificationModel();
    /*
     *  保存获取当前的赔率模式
     */
    void saveCurrentMagnificationModel(int index);
    int  getCurrentMagnificationModel();
    
    /*
     *  怒气值
     */
    void saveAngerValue(int index);
    int  getAngerValue();
    
    /*
     *  引导关被boss 打死
     *  status 1 -> 在引导关被boss 打死
     */
    void saveRoleDeathStatus(int status);
    int  getRoleDeathStatus();
    
    /*
     * Endless_Mode 是否开启
     */
    void saveEndlessModeStatus(int status);
    int  getEndlessModeStatus();
    
    /*
     *  正版验证没过，无尽模式只能完一次
     */
    void saveEndlessModeNum(int status);
    int  getEndlessModeNum();
    /*
     * 第一关，进入游戏任务目标出现后点确定 只有第一次
     */
    void saveTaskTipsStatus(int status);
    int  getTaskTipsStatus();
    /*
     * 第一关，进入游戏任务目标出现后点确定 只有第一次
     */
    void saveOpenCannonLeve(int status);
    int  getOpenCannonLeve();
    /*
     *  连击提示，只提示一次
     */
    void savePromptBatterStatus(int status);
    int  getPromptBatterStatus();
    /*
     *  连击提示，只提示一次
     */
    void savePromptLaserStatus(int status);
    int  getPromptLaserStatus();
    /*
     *  是否暂停
     */
    void savePauseStatus(int status);
    int  getPauseStatus();
    
    /*
     *  保存当前选择的大关值
     */ 
    void saveCurrentCheckpoints(int value);
    int  getCurrentCheckpoints();
    /*
     *  保存是否正版验证过
     */
    void saveGenuineValidationStatus(int value);
    int  getGenuineValidationStatus();
    
    /*
     *  技能数目
     */
    void saveSkillBloodNum(int value);
    int  getSkillBloodNum();
    void saveSkillPaysNum(int value);
    int  getSkillPaysNum();
    /*
     *  Gift 礼品时间
     */
    void saveGiftStatus(int value);
    int  getGiftStatus();
    void saveGiftCountdown(int value);
    int  getGiftCountdown();
    
    void saveToday(long time);
    long getToday();
    
    void removeData();
private:
    static GMAccessData* m_spAccessData;
    
};



#endif /* defined(__FishX__GMAccessData__) */
