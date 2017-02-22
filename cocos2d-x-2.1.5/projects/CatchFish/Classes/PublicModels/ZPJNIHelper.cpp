//
//  ZPJNIHelper.cpp
//  FishX
//
//  Created by peng on 13-4-26.
//
//

#include "ZPJNIHelper.h"
#include "GMPublicMethod.h"
#include "../Config/GMHeaderConfig.h"


#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include <jni.h>
#include "platform/android/jni/JniHelper.h"
#include <android/log.h>
#define CLASS_NAME "com/dsw/fish/JniInterface"
#endif

#if (JNIHELPER_INDEX == JNIHELPER_NUKNOW)
#define CLASS_NAME "com/cocos2dGamedo/fish/JniInterface"
#endif

#if (JNIHELPER_INDEX == JNIHELPER_TengXun)
#define CLASS_NAME "com/gomedo/YFish/JniInterface"
#endif

#if (JNIHELPER_INDEX == JNIHELPER_91)
#define CLASS_NAME "com/gamedo/fish91/JniInterface"
#endif
//com.Gamedo.FishYiDong;
#if (JNIHELPER_INDEX == JNIHELPER_YiDong)
#define CLASS_NAME "com/Gamedo/FishYiDong/JniInterface"
#endif

#if (JNIHELPER_INDEX == JNIHELPER_Telecom)
#define CLASS_NAME "com/fish/telecom/JniInterface"
#endif

#if (JNIHELPER_INDEX == JNIHELPER_91_Android)
#define CLASS_NAME "com/gamedo/fish91/JniInterface"
#endif

#if (JNIHELPER_INDEX == JNIHELPER_Unicom_Android)
#define CLASS_NAME "com/GameDoUnicom/fish/JniInterface"
#endif


ZPJNIHelper* ZPJNIHelper::m_pJNIHelper = 0;

ZPJNIHelper* ZPJNIHelper::sharedJNIHelper()
{
    if (! m_pJNIHelper)
    {
        m_pJNIHelper = new ZPJNIHelper();
        m_pJNIHelper->initValue();
    }
    return m_pJNIHelper;
}

ZPJNIHelper::ZPJNIHelper()
{
    
}

void ZPJNIHelper::initValue()
{
    _isStopVideo = false;
}

void ZPJNIHelper::purgeSharedPublicMethod()
{
    CC_SAFE_DELETE(m_pJNIHelper);
    m_pJNIHelper = NULL;
}

ZPJNIHelper::~ZPJNIHelper()
{
    
}

//#pragma mark -

void ZPJNIHelper::playCartoonVideo()
{
	return ;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID && JNIHELPER_INDEX != JNIHELPER_Telecom)
    ZPLog("playCartoonVideo CLASS_NAME :: %s",CLASS_NAME);
    GameMode mode = GMPublicMethod::sharedPublicMethod()->getGameMode();
    if (mode == Boot_Mode) {
        GMPublicMethod::sharedPublicMethod()->setAndroidPlayVideo(true);
        JniMethodInfo t;
        if(JniHelper::getStaticMethodInfo(t, CLASS_NAME, "onPlayVideo", "()V")){
            t.env->CallStaticVoidMethod(t.classID, t.methodID);
        }
    }
#endif
}

bool ZPJNIHelper::getScreensaverStatus()
{
	return false;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    ZPLog("getScreensaverStatus CLASS_NAME :: %s",CLASS_NAME);
    JniMethodInfo mInfo;
//    int status = GMPublicMethod::sharedPublicMethod()->getAudioStatus();
//    bool b = JniHelper::getStaticMethodInfo(mInfo, CLASS_NAME, "setVideoStatus", "(I)V");
//    if(b){
//        mInfo.env->CallStaticVoidMethod(mInfo.classID, mInfo.methodID,status);
//    }
//    else {
//        ZPLog("JniHelper::getMethodInfo error...");
//    }
    jboolean  status = false;
    bool b = JniHelper::getStaticMethodInfo(mInfo, CLASS_NAME, "getScreensaverStatus", "()Z");
    if(b){
        status = mInfo.env->CallStaticBooleanMethod(mInfo.classID, mInfo.methodID);
    }
    
    if(status == true){
        if(_isStopVideo == false){
            _isStopVideo = true;
        }
        return true;
    }
    else {
        return false;
    }
#endif
    return false;
}

void ZPJNIHelper::setVideoStatus(){
    
	return ;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    ZPLog("setVideoStatus CLASS_NAME :: %s",CLASS_NAME);
    int status = GMPublicMethod::sharedPublicMethod()->getAudioStatus();
    JniMethodInfo mInfo;
    bool bb = JniHelper::getStaticMethodInfo(mInfo, CLASS_NAME, "setVideoStatus", "(I)V");
    
    if (bb) {
        mInfo.env->CallStaticVoidMethod(mInfo.classID, mInfo.methodID,status);
    }
    ZPLog("setVideoStatus CLASS_NAME :: %s",CLASS_NAME);
#endif
}

//获取运营商的索引
int ZPJNIHelper::getOperators(){

	return 0;
    int operatorsIndex = 0;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    ZPLog("getOperators CLASS_NAME :: %s",CLASS_NAME);
    JniMethodInfo mInfo;
    jint temp = 0;
    bool bb = JniHelper::getStaticMethodInfo(mInfo, CLASS_NAME, "getOperators", "()I");
    if (bb) {
        temp = mInfo.env->CallStaticIntMethod(mInfo.classID, mInfo.methodID);
    }
    operatorsIndex = temp;
#endif
    return operatorsIndex;
}


//#pragma mark -
void ZPJNIHelper::sendSMSBillingPoint(int index){

	return;
//    && (JNIHELPER_INDEX==JNIHELPER_TengXun || JNIHELPER_INDEX==JNIHELPER_Telecom)
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    ZPLog("sendSMSBillingPoint CLASS_NAME :: %s",CLASS_NAME);
    JniMethodInfo mInfo;
    bool bb = JniHelper::getStaticMethodInfo(mInfo, CLASS_NAME, "sendSMSBillingPoint", "(I)V");
    if (bb) {
        mInfo.env->CallStaticVoidMethod(mInfo.classID, mInfo.methodID,index);
    }
#endif
}

int ZPJNIHelper::getSendSMSBillingPointStatus(){

	return 0;
    int status = 0;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    ZPLog("getSendSMSBillingPointStatus CLASS_NAME :: %s",CLASS_NAME);
    jint  status1;
    JniMethodInfo mInfo;
    bool bb = JniHelper::getStaticMethodInfo(mInfo, CLASS_NAME, "getSendSMSBillingPointStatus", "()I");
    if (bb) {
       status1 = mInfo.env->CallStaticIntMethod(mInfo.classID, mInfo.methodID);
    }
    status = (int)status1;
    ZPLog("status1 %d",status);
#endif
    return status;
}

void ZPJNIHelper::setSMSBillingPointStatus(){

	return;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    ZPLog("setSMSBillingPointStatus CLASS_NAME :: %s",CLASS_NAME);
    JniMethodInfo mInfo;
    bool bb = JniHelper::getStaticMethodInfo(mInfo, CLASS_NAME, "setSMSBillingPointStatus", "()V");
    if (bb) {
        mInfo.env->CallStaticVoidMethod(mInfo.classID, mInfo.methodID);
    }
#endif
}

int ZPJNIHelper::getBillingIndex(){

	return 0;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    ZPLog("getBillingIndex CLASS_NAME :: %s",CLASS_NAME);
    JniMethodInfo mInfo;
    bool bb = JniHelper::getStaticMethodInfo(mInfo, CLASS_NAME, "getBillingIndex", "()I");
    if (bb) {
        return mInfo.env->CallStaticIntMethod(mInfo.classID, mInfo.methodID);
    }
#endif
    return 0;
}


//#pragma mark - 移动计划

bool ZPJNIHelper::getMusicEnabled(){

	return false;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    ZPLog("getMusicEnabled CLASS_NAME :: %s",CLASS_NAME);
    JniMethodInfo mInfo;
    bool bb = JniHelper::getStaticMethodInfo(mInfo, CLASS_NAME, "getMusicEnabled", "()Z");
    if (bb) {
        return (bool)mInfo.env->CallStaticBooleanMethod(mInfo.classID, mInfo.methodID);
    }
#endif
    return false;
}

void ZPJNIHelper::setYiDongBilling(int index){

	return ;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID && JNIHELPER_INDEX == JNIHELPER_YiDong)
    ZPLog("setYiDongBilling CLASS_NAME :: %s",CLASS_NAME);
    JniMethodInfo mInfo;
    bool bb = JniHelper::getStaticMethodInfo(mInfo, CLASS_NAME, "setYiDongBilling", "(I)V");
    if (bb) {
         mInfo.env->CallStaticVoidMethod(mInfo.classID, mInfo.methodID,index);
    }
#endif
}

void ZPJNIHelper::setExitGame(){

	return ;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID && (JNIHELPER_INDEX == JNIHELPER_YiDong || JNIHELPER_INDEX == JNIHELPER_91_Android))
    ZPLog("setExitGame CLASS_NAME :: %s",CLASS_NAME);
    JniMethodInfo mInfo;
    bool bb = JniHelper::getStaticMethodInfo(mInfo, CLASS_NAME, "exitGame", "()V");
    if (bb) {
        mInfo.env->CallStaticVoidMethod(mInfo.classID, mInfo.methodID);
    }
#endif
}

void ZPJNIHelper::moreGames(){

	return ;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID && (JNIHELPER_INDEX == JNIHELPER_YiDong || JNIHELPER_INDEX == JNIHELPER_91_Android))
    ZPLog("moreGames CLASS_NAME :: %s",CLASS_NAME);
    JniMethodInfo mInfo;
    bool bb = JniHelper::getStaticMethodInfo(mInfo, CLASS_NAME, "moreGames", "()V");
    if (bb) {
        mInfo.env->CallStaticVoidMethod(mInfo.classID, mInfo.methodID);
    }
#endif
}

int ZPJNIHelper::getExitStatus(){

	return 0;
    int status = 0;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID && JNIHELPER_INDEX == JNIHELPER_YiDong)
    ZPLog("getExitStatus CLASS_NAME :: %s",CLASS_NAME);
    JniMethodInfo mInfo;
    bool bb = JniHelper::getStaticMethodInfo(mInfo, CLASS_NAME, "getExitStatus", "()I");
    if (bb) {
        status = (int)mInfo.env->CallStaticIntMethod(mInfo.classID, mInfo.methodID);
    }
#endif
    return status;
}

void ZPJNIHelper::setExitStatus(){

	return ;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID && JNIHELPER_INDEX == JNIHELPER_YiDong)
    ZPLog("getExitStatus CLASS_NAME :: %s",CLASS_NAME);
    JniMethodInfo mInfo;
    bool bb = JniHelper::getStaticMethodInfo(mInfo, CLASS_NAME, "setExitStatus", "()V");
    if (bb) {
        mInfo.env->CallStaticVoidMethod(mInfo.classID, mInfo.methodID);
    }
#endif
}

//#pragma mark - 91 android 

void ZPJNIHelper::setShowBBS(){
	return ;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID && JNIHELPER_INDEX == JNIHELPER_91_Android)
    ZPLog("setShowBBS CLASS_NAME :: %s",CLASS_NAME);
    JniMethodInfo mInfo;
    bool bb = JniHelper::getStaticMethodInfo(mInfo, CLASS_NAME, "setShowBBS", "()V");
    if (bb) {
        mInfo.env->CallStaticVoidMethod(mInfo.classID, mInfo.methodID);
    }
#endif
}

void ZPJNIHelper::showSocial(){
	return ;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID && JNIHELPER_INDEX == JNIHELPER_91_Android)
    ZPLog("showSocial CLASS_NAME :: %s",CLASS_NAME);
    JniMethodInfo mInfo;
    bool bb = JniHelper::getStaticMethodInfo(mInfo, CLASS_NAME, "showSocial", "()V");
    if (bb) {
        mInfo.env->CallStaticVoidMethod(mInfo.classID, mInfo.methodID);
    }
#endif
}


void ZPJNIHelper::isExitGame(){
	return ;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID && JNIHELPER_INDEX == JNIHELPER_91_Android)
    ZPLog("setKeyCodeBack CLASS_NAME :: %s",CLASS_NAME);
    JniMethodInfo mInfo;
    bool bb = JniHelper::getStaticMethodInfo(mInfo, CLASS_NAME, "isExitGame", "()V");
    if (bb) {
        mInfo.env->CallStaticVoidMethod(mInfo.classID, mInfo.methodID);
    }
#endif
}

void ZPJNIHelper::setAllPay(int index){
	return ;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID && JNIHELPER_INDEX == JNIHELPER_91_Android)
    ZPLog("setAllPay CLASS_NAME :: %s",CLASS_NAME);
    JniMethodInfo mInfo;
    bool bb = JniHelper::getStaticMethodInfo(mInfo, CLASS_NAME, "setAllPay", "(I)V");
    if (bb) {
        mInfo.env->CallStaticVoidMethod(mInfo.classID, mInfo.methodID,index);
    }
#endif
}

void ZPJNIHelper::setPauseView(){
	return ;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID && JNIHELPER_INDEX == JNIHELPER_91_Android)
    ZPLog("setPauseView CLASS_NAME :: %s",CLASS_NAME);
    JniMethodInfo mInfo;
    bool bb = JniHelper::getStaticMethodInfo(mInfo, CLASS_NAME, "setPauseView", "()V");
    if (bb) {
        mInfo.env->CallStaticVoidMethod(mInfo.classID, mInfo.methodID);
    }
#endif
}

void ZPJNIHelper::showEnterFeedback(){
	return ;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID && JNIHELPER_INDEX == JNIHELPER_91_Android)
    ZPLog("showEnterFeedback CLASS_NAME :: %s",CLASS_NAME);
    JniMethodInfo mInfo;
    bool bb = JniHelper::getStaticMethodInfo(mInfo, CLASS_NAME, "showEnterFeedback", "()V");
    if (bb) {
        mInfo.env->CallStaticVoidMethod(mInfo.classID, mInfo.methodID);
    }
#endif
}


#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

#include <jni.h>

extern "C"
{
//    void Java_com_gamedo_fish91_Cocos2dXFishProject91_gameOver(JNIEnv* env, jobject firedragonpzy)
//    {
//        
//        ZPLog("Java_com_gamedo_fish91_Cocos2dXFishProject91_gameOver");
//        CCDirector::sharedDirector()->end();
//    }
//    
//    void Java_com_gamedo_fish91_Cocos2dXFishProject91_Leave91Platform(JNIEnv* env, jobject firedragonpzy)
//    {
//        ZPLog("Java_com_gamedo_fish91_Cocos2dXFishProject91_Leave91Platform");
////        GMPublicMethod::sharedPublicMethod()->setShow91Pause(true);
//    }
    
    
}

#endif
