//
//  ZPJNIHelper.h
//  FishX
//
//  Created by peng on 13-4-26.
//
//

#ifndef __FishX__ZPJNIHelper__
#define __FishX__ZPJNIHelper__

#include <iostream>

#include "cocos2d.h"

USING_NS_CC;

class ZPJNIHelper: public CCObject
{
private:
    static ZPJNIHelper* m_pJNIHelper;
    void initValue();
private:
    bool _isStopVideo;
   
    bool init();
public:
    ZPJNIHelper();
    virtual ~ZPJNIHelper(void);
    
    static ZPJNIHelper* sharedJNIHelper();
    void purgeSharedPublicMethod();
    
//    void startThreads();
//    void updateThreads(float dt);
    
    void playCartoonVideo();
    
    bool getScreensaverStatus();
    
    void setVideoStatus();
    
    
    static int getOperators();//获取运营商的索引
    static void sendSMSBillingPoint(int index);
    static int  getSendSMSBillingPointStatus();
    static void setSMSBillingPointStatus();
    static int getBillingIndex();

//#pragma mark - 移动计划
    static bool getMusicEnabled();
    static void setYiDongBilling(int index);
    static void setExitGame();
    static void moreGames();
    static int  getExitStatus();
    static void setExitStatus();
//#pragma mark - 91 andriod
    static void setShowBBS();
    static void showSocial();
    static void isExitGame();
    static void setAllPay(int index);
    static void setPauseView();
    static void showEnterFeedback();
};

#endif /* defined(__FishX__ZPJNIHelper__) */



