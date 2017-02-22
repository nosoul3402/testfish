//
//  PublicCPP..h
//  FishX
//
//  Created by peng on 13-6-6.
//
//

#ifndef __FishX__PublicCPP___
#define __FishX__PublicCPP___

#include "cocos2d.h"
using namespace cocos2d;

class PublicCPP:public cocos2d::CCObject
{
public:
    static int getCarrier();
    static bool getVersion();
//    static bool getMobileBilling();
    
    static void setInit91SDK();
    
//    static void set91MobileBilling(int index);
    
    
    static void showForum(int index);
    //91意见反馈
    static void enterFeedback();
    static void show91NdPause();
    static bool getLoginedStatus();
    /*
     *  支付 
     *  1=特殊道具（200），2=购买金币（200），
     *  3=购买金币（400），4=购买金币（900），
     *  5=购买武器（200），
     */
    static void paymentAll(int index);
    static void payment91MobileNet(int index,const char*phone ,const char*veriCode);
    static void messageBox();
    
    // 判断是否支付成功
    static void setPaymentSuccess(int success);
    static int getPaymentSuccess();
    static int  getBillingIndex();
    
    static void addPicker();
    static const char* getPhoneNum();
    static int getVerificationCodeStatus();
    static int getMobileStatus();
    static bool getloginSuccess();
#pragma mark - 检测漏单
    static void checkedRecord();
    static void removeRecord(int index);
    
    static void setNdToolBar(bool show);
public:
    static PublicCPP* sharedSpriteCPP();
    void myInit();
    virtual ~PublicCPP();
    
private:
    static PublicCPP* m_pPublicCPP;
};
#endif /* defined(__FishX__PublicCPP___) */
