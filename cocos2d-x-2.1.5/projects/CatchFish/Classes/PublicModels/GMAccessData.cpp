//
//  GMAccessData.cpp
//  FishX
//
//  Created by peng on 13-1-14.
//
//

#include "GMAccessData.h"
#include "DataBase64Himi.h"

GMAccessData* GMAccessData::m_spAccessData = 0;


GMAccessData* GMAccessData::sharedAccessData()
{
    if (! m_spAccessData)
    {
        m_spAccessData = new GMAccessData();
    }
    
    return m_spAccessData;
}

GMAccessData::GMAccessData()
{
    
}

void GMAccessData::initValue(){
    saveOpenCannonLeve(1);
    setTotalMoneyStatus(1);
    saveTotalMoneyNum(2000);
    saveSkillBloodNum(2);
    saveSkillPaysNum(2);
    saveGiftStatus(1);
    saveGiftCountdown(15);
}

void GMAccessData::cleanData(){
    saveOpenCannonLeve(0);
    setTotalMoneyStatus(1);
    saveTotalMoneyNum(2000);
    saveSkillBloodNum(0);
    saveSkillPaysNum(0);
    saveGiftStatus(1);
    saveGiftCountdown(60);

}

//#pragma mark - 保存游戏数据

static char keyName[40] = {0};
static char buffer[32];
#define Money_Key           "Money_Key"
#define MoneyStatus_Key     "MoneyStatus_Key"
#define CL_Key              "CurrentLevel"


void writeDataForFile(const char *key ,int status)
{
    sprintf(buffer, "%s",key);
    char tempString[20] = {0};
    sprintf(tempString, "%d",status);
    std::string sValue = tempString;
    std::string sKey = himiSaveData(reinterpret_cast<const unsigned char*>(sValue.c_str()), sValue.length());
    CCUserDefault::sharedUserDefault()->setStringForKey(buffer, sKey);
    CCUserDefault::sharedUserDefault()->flush();
}

int readDataForFile(const char *key)
{
    sprintf(buffer, "%s",key);
    std::string s = CCUserDefault::sharedUserDefault()->getStringForKey(buffer);
    std::string parseKey = himiParseData(s);
    return atoi(parseKey.c_str());
}

//保存游戏数据
void GMAccessData::saveTotalMoneyNum(int moneyNum)
{
    sprintf(buffer,"%d",moneyNum);
    CCUserDefault::sharedUserDefault()->setIntegerForKey(Money_Key, moneyNum);
    CCUserDefault::sharedUserDefault()->flush();//这里一定要提交写入哦，否则不会记录到xml中，下次启动游戏你就获取不到value了。
}

int GMAccessData::getTotalMoneyNum()
{
    return CCUserDefault::sharedUserDefault()->getIntegerForKey(Money_Key);
}

void GMAccessData::setTotalMoneyStatus(int nTotalMoney)
{
    CCUserDefault::sharedUserDefault()->setIntegerForKey(MoneyStatus_Key, nTotalMoney);
    CCUserDefault::sharedUserDefault()->flush();
}

int  GMAccessData::getTotalMoneyStatus(){
    return CCUserDefault::sharedUserDefault()->getIntegerForKey(MoneyStatus_Key);
}

/*
 *  保存每一关的分数
 */
void GMAccessData::saveEachLevelScore(int level,int score)
{
    sprintf(keyName,"Level_%d",level);
    CCUserDefault::sharedUserDefault()->setIntegerForKey(keyName, score);
    CCUserDefault::sharedUserDefault()->flush();//这里一定要提交写入哦，否则不会记录到xml中，下次启动游戏你就获取不到value了。
}

int GMAccessData::getEachLevelScore(int level)
{
    sprintf(keyName,"Level_%d",level);
    return CCUserDefault::sharedUserDefault()->getIntegerForKey(keyName);
}

/*
 *  保存每一关的星的等级
 */
void GMAccessData::saveEachLevelStar(int level,int star)
{
    sprintf(keyName,"EachLevelStar_%d",level);
    CCUserDefault::sharedUserDefault()->setIntegerForKey(keyName, star);
    CCUserDefault::sharedUserDefault()->flush();//这里一定要提交写入哦，否则不会记录到xml中，下次启动游戏你就获取不到value了。
}

int GMAccessData::getEachLevelStar(int level)
{
    sprintf(keyName,"EachLevelStar_%d",level);
    return CCUserDefault::sharedUserDefault()->getIntegerForKey(keyName);
}

/*
 *  目前完的游戏关卡
 */
void GMAccessData::saveCurrentLevel(int level)
{
    CCUserDefault::sharedUserDefault()->setIntegerForKey(CL_Key, level);
    CCUserDefault::sharedUserDefault()->flush();
}

int GMAccessData::getCurrentLevel()
{
    return CCUserDefault::sharedUserDefault()->getIntegerForKey(CL_Key);
}

/*
 *  目前开启的游戏关卡
 */
void GMAccessData::saveOpenCheckpoints(int cp1,int cp2)
{
    sprintf(keyName,"Checkpoints_%d",cp1);
    CCUserDefault::sharedUserDefault()->setIntegerForKey(keyName, cp2);
    CCUserDefault::sharedUserDefault()->flush();
}

int GMAccessData::getOpenCheckpoints(int cp1)
{
    sprintf(keyName,"Checkpoints_%d",cp1);
    return CCUserDefault::sharedUserDefault()->getIntegerForKey(keyName);
}

/*
 *  获取声音是否关闭
 *  closeAudio = 1：已关闭，2已开启
 */
void GMAccessData::saveAudioStatus(int closeAudio)
{
    sprintf(keyName,"CloseAudio");
    CCUserDefault::sharedUserDefault()->setIntegerForKey(keyName, closeAudio);
    CCUserDefault::sharedUserDefault()->flush();
}

int GMAccessData::getAudioStatus()
{
    sprintf(keyName,"CloseAudio");
    return CCUserDefault::sharedUserDefault()->getIntegerForKey(keyName);
}

/*
 *  是否第一次进入游戏
 *
 */
void GMAccessData::saveBootModeStatus(int sValue){
    writeDataForFile("BootModeStatus", sValue);
}

int GMAccessData::getBootModeStatus(){
    return readDataForFile("BootModeStatus");
}
/*
 *  成就能量状态
 */
void GMAccessData::saveEnergePromptStatus(std::string sValue)
{
    sprintf(buffer, "%s", "EnergePromp");
//    CCLog("----------存储");
//    CCLog("存储之前数据  value: %s  ",sValue.c_str() );
    std::string sKey = himiSaveData(reinterpret_cast<const unsigned char*>(sValue.c_str()), sValue.length());
//    CCLog("存储加密后的数据 value: %s  ",sKey.c_str());
    CCUserDefault::sharedUserDefault()->setStringForKey(buffer, sKey);
    CCUserDefault::sharedUserDefault()->flush();
}

int GMAccessData::getEnergePromptStatus()
{
//    CCLog("----------读取");
    sprintf(buffer, "%s", "EnergePromp");
    std::string s = CCUserDefault::sharedUserDefault()->getStringForKey(buffer);
//    CCLog("解密前的数据: %s  ",s.c_str());
    std::string parseKey = himiParseData(s);
//    CCLog("解密后的数据: %s  ",parseKey.c_str());
    return atoi(parseKey.c_str());
}
/*
 *  漩涡状态
 */
void GMAccessData::saveSwirlAmount(int amount){
    writeDataForFile("SwirlNum",amount);
}

int GMAccessData::getSwirlAmount(){
    return readDataForFile("SwirlNum");
}

/*
 *  成就每个的状态
 */
void GMAccessData::saveEachAchievementStatus(int index,int status){
    sprintf(buffer, "AchievementStatus_%d", index);
    writeDataForFile(buffer, status);
}

int  GMAccessData::getEachAchievementStatus(int index){
    sprintf(buffer, "AchievementStatus_%d", index);
    return readDataForFile(buffer);
}

/*
 *  获取送金币时间
 */
void GMAccessData::saveGoldCoinsTime(long time){
    sprintf(buffer, "%ld",time);
    std::string sValue = buffer;
    std::string sKey = himiSaveData(reinterpret_cast<const unsigned char*>(sValue.c_str()), sValue.length());
    CCUserDefault::sharedUserDefault()->setStringForKey("GoldCoinsTime", sKey);
    CCUserDefault::sharedUserDefault()->flush();
}

long GMAccessData::getGoldCoinsTime(){
    sprintf(buffer, "GoldCoinsTime");
    std::string s = CCUserDefault::sharedUserDefault()->getStringForKey(buffer);
    std::string parseKey = himiParseData(s);
    return atol(parseKey.c_str());
}

/*
 *  保存获取赔率模式
 */
void GMAccessData::saveMagnificationModel(int index)
{
    sprintf(buffer, "%d",index);
    std::string sValue = buffer;
    std::string sKey = himiSaveData(reinterpret_cast<const unsigned char*>(sValue.c_str()), sValue.length());
    CCUserDefault::sharedUserDefault()->setStringForKey("MagnificationModel", sKey);
    CCUserDefault::sharedUserDefault()->flush();
}

int GMAccessData::getMagnificationModel()
{
    sprintf(buffer, "MagnificationModel");
    std::string s = CCUserDefault::sharedUserDefault()->getStringForKey(buffer);
    std::string parseKey = himiParseData(s);
    return atoi(parseKey.c_str());
}
/*
 *  保存获取当前的赔率模式
 */
void GMAccessData::saveCurrentMagnificationModel(int index)
{
    sprintf(buffer, "%d",index);
    std::string sValue = buffer;
    std::string sKey = himiSaveData(reinterpret_cast<const unsigned char*>(sValue.c_str()), sValue.length());
    CCUserDefault::sharedUserDefault()->setStringForKey("CurrentMagnificationModel", sKey);
    CCUserDefault::sharedUserDefault()->flush();
}

int GMAccessData::getCurrentMagnificationModel()
{
    sprintf(buffer, "CurrentMagnificationModel");
    std::string s = CCUserDefault::sharedUserDefault()->getStringForKey(buffer);
    std::string parseKey = himiParseData(s);
    return atoi(parseKey.c_str());
}

/*
 *  怒气值
 */
void GMAccessData::saveAngerValue(int index){
    int temp1 = GMAccessData::getCurrentMagnificationModel();
    sprintf(buffer, "AngerValue_%d",temp1);
    writeDataForFile(buffer,index);
}

int GMAccessData::getAngerValue()
{
    int temp1 = GMAccessData::getCurrentMagnificationModel();
    sprintf(buffer, "AngerValue_%d",temp1);
    return readDataForFile(buffer);
}
/*
 *  引导关被boss 打死
 *  status 1 -> 在引导关被boss 打死
 */
void GMAccessData::saveRoleDeathStatus(int status){
    writeDataForFile("RoleDeathStatus",status);
}

int GMAccessData::getRoleDeathStatus(){
    return readDataForFile("RoleDeathStatus");
}

/*
 * Endless_Mode 是否开启
 */
void GMAccessData::saveEndlessModeStatus(int status)
{
    writeDataForFile("OpenEndlessModeStatus",status);
}

int GMAccessData::getEndlessModeStatus(){
    return readDataForFile("OpenEndlessModeStatus");
}

void GMAccessData::saveEndlessModeNum(int status){
    writeDataForFile("EndlessModeNum",status);
}

int GMAccessData::getEndlessModeNum(){
    return readDataForFile("EndlessModeNum");
}

/*
 * 第一关，进入游戏任务目标出现后点确定 只有第一次
 */
void GMAccessData::saveTaskTipsStatus(int status)
{
    writeDataForFile("TaskTipsStatus",status);
}

int GMAccessData::getTaskTipsStatus(){
    return readDataForFile("TaskTipsStatus");
}

/*
 * 第一关，进入游戏任务目标出现后点确定 只有第一次
 */
void GMAccessData::saveOpenCannonLeve(int status)
{
    writeDataForFile("OpenCannonLeve",status);
}

int GMAccessData::getOpenCannonLeve()
{
    return readDataForFile("OpenCannonLeve");
}
/*
 *  连击提示，只提示一次
 */
void GMAccessData::savePromptBatterStatus(int status){
    writeDataForFile("PromptBatter",status);
}
int  GMAccessData::getPromptBatterStatus(){
    return readDataForFile("PromptBatter");
}
/*
 *  连击提示，只提示一次
 */
void GMAccessData::savePromptLaserStatus(int status)
{
    writeDataForFile("PromptLaser",status);
}

int  GMAccessData::getPromptLaserStatus()
{
    return readDataForFile("PromptLaser");
}
/*
 *  是否暂停
 */
void GMAccessData::savePauseStatus(int status)
{
    writeDataForFile("PauseStatus",status);
}

int  GMAccessData::getPauseStatus()
{
    return readDataForFile("PauseStatus");
}

/*
 *  保存当前选择的大关值
 */
void GMAccessData::saveCurrentCheckpoints(int value){
    writeDataForFile("CurrentCheckpoints",value);
}
int  GMAccessData::getCurrentCheckpoints(){
    return readDataForFile("CurrentCheckpoints");
}
/*
 *  保存是否正版验证过
 */
void GMAccessData::saveGenuineValidationStatus(int value){
    writeDataForFile("GenuineValidation",value);
}
int  GMAccessData::getGenuineValidationStatus(){
    return readDataForFile("GenuineValidation");
}
/*
 *  技能数目
 */
void GMAccessData::saveSkillBloodNum(int value){
    writeDataForFile("SkillBloodNum",value);
}
int  GMAccessData::getSkillBloodNum(){
    return readDataForFile("SkillBloodNum");
}
void GMAccessData::saveSkillPaysNum(int value){
    writeDataForFile("SkillPaysNum",value);
}
int  GMAccessData::getSkillPaysNum(){
    return readDataForFile("SkillPaysNum");
}

//#pragma mark - gift 

void GMAccessData::saveGiftStatus(int value){
    writeDataForFile("GiftStatus",value);
}

int  GMAccessData::getGiftStatus(){
    return readDataForFile("GiftStatus");
}

void GMAccessData::saveGiftCountdown(int value){
    if(value<0)
        value = 0;
    writeDataForFile("GiftCountdown",value);
}

int  GMAccessData::getGiftCountdown(){
    return readDataForFile("GiftCountdown");
}

void GMAccessData::saveToday(long time){
    sprintf(buffer, "%ld",time);
    std::string sValue = buffer;
    std::string sKey = himiSaveData(reinterpret_cast<const unsigned char*>(sValue.c_str()), sValue.length());
    CCUserDefault::sharedUserDefault()->setStringForKey("Today", sKey);
    CCUserDefault::sharedUserDefault()->flush();
}

long GMAccessData::getToday(){
    sprintf(buffer, "Today");
    std::string s = CCUserDefault::sharedUserDefault()->getStringForKey(buffer);
    std::string parseKey = himiParseData(s);
    return atol(parseKey.c_str());
}

//#pragma mark - 清空数据
void GMAccessData::removeData(){
    //销毁CCUserdefault
    CCUserDefault::purgeSharedUserDefault();
    //清除临时文件
    remove(CCUserDefault::getXMLFilePath().c_str());

}

//#pragma mark-

void GMAccessData::purgeSharedAccessData()
{
    CC_SAFE_DELETE(m_spAccessData);
    m_spAccessData = NULL;
}

GMAccessData::~GMAccessData()
{
//    if (hitArray) {
//        hitArray->release();
//        hitArray = NULL;
//    }

    m_spAccessData = NULL;
}

