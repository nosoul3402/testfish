//
//  PublicCPP..cpp
//  FishX
//
//  Created by peng on 13-6-6.
//
//

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include "PublicOC.h"
#import "AppController.h"
#endif

#include "PublicCPP.h"


PublicCPP* PublicCPP::m_pPublicCPP = 0;

PublicCPP* PublicCPP::sharedSpriteCPP()
{
    if (! m_pPublicCPP)
    {
        m_pPublicCPP = new PublicCPP();
//        m_pPublicCPP->initValue();
    }
    return m_pPublicCPP;
}

int PublicCPP::getCarrier()
{
    return [PublicOC getCarrier];
}

bool PublicCPP::getVersion()
{
    return [PublicOC getVersion];
}

//bool PublicCPP::getMobileBilling()
//{
//    return [PublicOC getMobileBilling];
//}


//void PublicCPP::set91MobileBilling(int index){
////    [[PublicOC defaultPublicOC] initCmccBilling];
//    [[PublicOC defaultPublicOC] sendCmccBilling:index];
//}

void PublicCPP::setInit91SDK(){
    [PublicOC defaultPublicOC];
}

void PublicCPP::showForum(int index)
{
    if(index == 1)
        [[PublicOC defaultPublicOC] show1813Forum];
    else if(index == 2)
        [[PublicOC defaultPublicOC] show91Forum];
}
//意见反馈
void PublicCPP::enterFeedback()
{
    [[PublicOC defaultPublicOC] enterFeedback];
}
void PublicCPP::show91NdPause()
{
    [[PublicOC defaultPublicOC] show91NdPause];
}

bool PublicCPP::getLoginedStatus(){
    return [[PublicOC defaultPublicOC] isLogined];
}
//支付
void PublicCPP::paymentAll(int index)
{
    [[PublicOC defaultPublicOC] paymentAll:index];
}

void PublicCPP::payment91MobileNet(int index,const char*phone ,const char*veriCode)
{
    [[PublicOC defaultPublicOC] sendCmccBilling:index phone:phone veriCode:veriCode];
}

void PublicCPP::messageBox(){
    [[PublicOC defaultPublicOC] messageBox];
}

// 判断是否支付成功
void PublicCPP::setPaymentSuccess(int success){
    return [[PublicOC defaultPublicOC] setPaymentSuccess:success];
}

int PublicCPP::getPaymentSuccess(){
    return [[PublicOC defaultPublicOC] getPaymentSuccess];
}

int PublicCPP::getBillingIndex(){
    return [[PublicOC defaultPublicOC] getBillingIndex];
}

void PublicCPP::addPicker(){
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    AppController *appController = ((AppController*)[[UIApplication sharedApplication] delegate]);
    UIView *view = [appController getView];
    [[PublicOC defaultPublicOC] addPicker:view];
#endif
}


const char* PublicCPP::getPhoneNum(){
    return [[[PublicOC defaultPublicOC] getPhoneNum] UTF8String];
}

int PublicCPP::getVerificationCodeStatus(){
    return [[PublicOC defaultPublicOC] getVerificationCodeStatus];
}

int PublicCPP::getMobileStatus(){
    return [[PublicOC defaultPublicOC] getMobileStatus];
}

bool PublicCPP::getloginSuccess(){
    return [[PublicOC defaultPublicOC] getloginSuccess];
}
#pragma mark - 检测漏单
void PublicCPP::checkedRecord(){
    [[PublicOC defaultPublicOC] checkedRecord];
}

void PublicCPP::removeRecord(int index){
    [[PublicOC defaultPublicOC] removeRecord:nil index:index];
}

void PublicCPP::setNdToolBar(bool show){
    if(show){
        [[PublicOC defaultPublicOC] setNdShowToolBar];
    }
    else {
        [[PublicOC defaultPublicOC] setNdHideToolBar];
    }
}

PublicCPP::~PublicCPP(){
    
}