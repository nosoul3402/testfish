//
//  PublicOC.h
//  FishX
//
//  Created by peng on 13-6-6.
//
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
//#import "GameBilling.h"
#import <AddressBook/AddressBook.h>
#import <AddressBookUI/AddressBookUI.h>
#import <NdComPlatform/NdComPlatform.h>
#import <NdComPlatform/NdCPNotifications.h>
#import <NdComPlatform/NdComPlatformError.h>
#import <NdComPlatform/NdComPlatform+VirtualGoods.h>
#import <NdComPlatform/NdComPlatformAPIResponse+VirtualGoods.h>

@interface PublicOC : NSObject</*GameBillingDelegate,*/ABPersonViewControllerDelegate,ABPeoplePickerNavigationControllerDelegate,ABNewPersonViewControllerDelegate,NdComPlatformUIProtocol,NdComPlatformUIProtocol_PayAndRecharge>
{
}

+ (PublicOC *)defaultPublicOC;
+ (void)attemptDealloc;
/*
 *  0=@"Unknown",
 *  1=@"China Mobile"(中国移动),2=@"China Unicom"(中国联通)
 *  3=@"China Telecom"(中国电信),4=@"China Tietong"(中国铁通)
 */
+ (int)getCarrier;

/*
 *  为 true 调用   91 的SDK
 *  为 false 调用 移动 的sdk
 */
+ (bool)getVersion;

//+ (bool)getMobileBilling;

/*
 *  91移动计费
 */
//- (void)initCmccBilling;
//- (void)sendCmccBilling:(int)index;
//- (void)sendCmccBilling:(int)index  phone:(const char*)phone veriCode:(const char*)veriCode;

- (void)messageBox;

- (bool)isLogined;
- (bool)getloginSuccess;

//展示 91 论坛
- (void)show91Forum;
//展示 1813 论坛
- (void)show1813Forum;

//意见反馈
- (void)enterFeedback;


- (void)paymentAll:(int)index;

- (int)getPaymentSuccess;

- (void)setPaymentSuccess:(int)success;

- (int)getBillingIndex;


- (void)addPicker:(UIView*)view;
- (NSString*)getPhoneNum;
- (int)getMobileStatus;
- (int)getVerificationCodeStatus;
- (void)show91NdPause;

//检测订单
- (void)checkedRecord;
- (void)removeRecord:(NSString*)cooOrderSerial index:(int)index;

+ (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation;

- (void)setNdShowToolBar;
- (void)setNdHideToolBar;

@end




