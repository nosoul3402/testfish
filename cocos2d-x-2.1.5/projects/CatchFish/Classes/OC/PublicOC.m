//
//  PublicOC.m
//  FishX
//
//  Created by peng on 13-6-6.
//
//

#import "PublicOC.h"
//#import <NdComPlatform/NdComPlatform.h>
#import "Order.h"
#import "DemoComFunc.h"

#define MainScreen_W            (([[UIScreen mainScreen] applicationFrame]).size.width)
#define MainScreen_H            (([[UIScreen mainScreen] applicationFrame]).size.height)

#define OredeKey    @"cooOrderSerial_KEY"   

static NSString * const kCooOrder = @"cooOrderSerial_KEY";

extern NSString* CTSIMSupportCopyMobileSubscriberIdentity();

extern NSString *CTSettingCopyMyPhoneNumber();


@interface PublicOC (){
//    GameBilling *billing;
    //    PublicOC *sharedPublicOC;
    int paymentStatus;//默认0，1成功支付，2支付失败
    int billingIndex;
    
    NSMutableArray *shopArray;
    
    UIView *tempView;
    ABPeoplePickerNavigationController *picker;
    NSString    *phoneNum;
    
    int         mobileStatus;// 0 ：默认；1：获取好友手机号；2获取失败
    int         verificationCodeStatus;// 0 ：默认；1：获取验证码；2获取失败
    
    UIAlertView *loadingView;
    bool         loginSuccess;
}

@end

static PublicOC *sharedPublicOC = nil;

@implementation PublicOC

//获取手机号
+(NSString *)myNumber{
    return CTSettingCopyMyPhoneNumber();
}
/*
 *  0=@"Unknown",
 *  1=@"China Mobile"(中国移动),2=@"China Unicom"(中国联通)
 *  3=@"China Telecom"(中国电信),4=@"China Tietong"(中国铁通)
 */
+ (int)getCarrier{
    NSString *imsi = (NSString*)CTSIMSupportCopyMobileSubscriberIdentity(nil);
    if([imsi isEqualToString:@""])
        return 0;
    NSLog(@"%@",imsi);
    if (imsi == nil || [imsi isEqualToString:@"SIM Not Inserted"] ) {
        return 0;
    }
    else {
        if ([[imsi substringWithRange:NSMakeRange(0, 3)] isEqualToString:@"460"]) {
            NSInteger MNC = [[imsi substringWithRange:NSMakeRange(3, 2)] intValue];
            switch (MNC) {
                case 00:
                case 02:
                case 07:
                    return 1;
                    break;
                case 01:
                case 06:
                    return 2;
                    break;
                case 03:
                case 05:
                    return 3;
                    break;
                case 20:
                    return 4;
                    break;
                default:
                    break;
            }
        }
    }
    return 0;
}

/*
 *  为 true 调用   91 的SDK
 *  为 false 调用 移动 的sdk
 */
+ (bool)getVersion{
    float v = [[[UIDevice currentDevice] systemVersion] floatValue];
    if(v<6.0)
        return false;
    else
        return true;
    return false;
}


//+ (bool)getMobileBilling{
////    bool temp = [PublicOC getVersion];
//    int temp1 = [PublicOC getCarrier];
////    if(temp1==1 && temp == true){//移动卡同时ios系统在6.0以上
//    if(temp1==1){
//        return true;
//    }
//    return false;
//}
#pragma mark -

+ (PublicOC *)defaultPublicOC{
    @synchronized(self) {
        if(sharedPublicOC == nil) {
            sharedPublicOC =[[[self class] alloc] init]; //   assignment   not   done   here
//            [sharedPublicOC initCmccBilling];
            [sharedPublicOC init91Sdk];
        }
    }
//    return sharedCLDelegate;
//    if(sharedPublicOC)
//    {
//        sharedPublicOC = [[PublicOC alloc] init];
//        
//    }
    return sharedPublicOC ;
}

- (void)loading{
    loadingView = [[UIAlertView alloc] initWithTitle:@"发送消息中……"
													message:nil
												   delegate:nil
										  cancelButtonTitle:nil
										  otherButtonTitles:nil, nil];
	[loadingView show];
//	[loadingView release];
    
//    UIActivityIndicatorView *m_pActivity = [[UIActivityIndicatorView alloc] initWithActivityIndicatorStyle:UIActivityIndicatorViewStyleWhite];
//    [loadingView addSubview:m_pActivity];
//    [m_pActivity startAnimating];
//    m_pActivity.frame = CGRectMake(0, 0, 20, 20);
//    [m_pActivity release];
}

//- (void)initCmccBilling{
////    if(billing)
//    {
////        billing = [[GameBilling alloc] init];
////        billing = [GameBilling initializeGameBilling];
////        [billing setDelegate:self];
////        [billing initWithChargePath:[[NSBundle mainBundle] pathForResource:@"Charge" ofType:@"xml"] ConsumeCodePath:[[NSBundle mainBundle] pathForResource:@"ConsumeCodeInfo" ofType:@"xml"]];
//        
//        paymentStatus = 0;
//        mobileStatus = 0;
//        verificationCodeStatus = 0;
//    }
//}

//- (void)sendCmccBilling:(int)index{
//    billingIndex = index;
//    bool isRepeated = true;
//    if(index == 6)
//        index = 3;
////    if(index == 5){
////        isRepeated = false;
////    }
//    NSString *indexS = [NSString stringWithFormat:@"00%d",index-1];
//    bool temp = [PublicOC getVersion];
////    if (temp)
//    {
////        NSString *num = [PublicOC myNumber];
////        [billing doBillingWithBillingIndex:indexS isRepeated:isRepeated phoneNum:num veriCode:nil];
////        [billing doBillingWithUIAndBillingIndex:indexS isRepeated:isRepeated useSms:false];
//    }
////    else{
////        [billing doBillingWithBillingIndex:indexS isRepeated:isRepeated phoneNum:nil veriCode:nil];
////    }
//}

//
//- (void)sendCmccBilling:(int)index phone:(const char*)phone veriCode:(const char*)veriCode{
//    billingIndex = index;
//    
//    if(index == 6)
//        index = 3;
//    [self loading];
//    
//    bool isRepeated = true;
//    if(index == 5){
//        isRepeated = false;
//    }
//    NSString *indexS = [NSString stringWithFormat:@"00%d",index-1];
//    NSString *phoneS = nil;
//    NSString *veriCodeS = nil;
//    if(phone){
//        phoneS = [NSString stringWithUTF8String:phone];
//        phoneS = [phoneS stringByReplacingOccurrencesOfString:@"-" withString:@"%20"];
//    }
//    if(veriCode)
//        veriCodeS = [NSString stringWithUTF8String:veriCode];
//    
//    NSLog(@"手机号 = %@, 验证码 = %@",phoneS,veriCodeS);
//    
////    bool temp = [PublicOC getVersion];
////    if (temp)
//    {
//        if(!phoneS){
//            phoneS = [PublicOC myNumber];
//        }
////        [billing doBillingWithBillingIndex:indexS isRepeated:isRepeated phoneNum:phoneS veriCode:veriCodeS];
//    }
////    else{
////        [billing doBillingWithBillingIndex:indexS isRepeated:isRepeated phoneNum:nil veriCode:nil];
////    }
//}



//- (void)onBillingResult:(BillingResultType)resultCode billingIndex:(NSString *)index message:(NSString *)message{
//    
//    [loadingView dismissWithClickedButtonIndex:0 animated:true];
//    [loadingView release];
//    loadingView = nil;
//    
//    BOOL result =  (resultCode == BillingResultSucceed);
//    NSLog(@"billing=%@ %@ %@",result?@"yes":@"no", index, message);
//    if(result){
//        paymentStatus = 1;
////        string = @"计费成功";
//    }
//    else {
//        paymentStatus = 2;
////        string = @"计费失败";
//    }
//    [DemoComFunc messageBox:[NSString stringWithFormat:@"计费点%@,%@",index,message]];
//}

+ (void)messageBox:(NSString*)stringTip
{
	UIAlertView *alert = [[UIAlertView alloc] initWithTitle:stringTip
													message:nil
												   delegate:nil
										  cancelButtonTitle:nil
										  otherButtonTitles:@"确定", nil];
	[alert show];
	[alert release];
}

#pragma mark - 计费接口
- (void)paymentAll:(int)index{
    billingIndex = index;
//    bool temp = [PublicOC getVersion];
    paymentStatus = 0;
//    int temp1 = [PublicOC getCarrier];
    
//    if(temp1==1){
//        [self sendCmccBilling:index];
//    }
//    else
//        if(temp1!=1){
        if([self isLogined]){
            [self payment];
        }
        else {
            [[NdComPlatform defaultPlatform] NdLoginEx:0];
            paymentStatus = 3;
        }
//    }
//    else {
//        paymentStatus = 2;
//    }
}

- (void)messageBox{
    bool temp = [PublicOC getVersion];
    int temp1 = [PublicOC getCarrier];
    
    if(temp1==1){
    }
    else if(temp && temp1!=1){
        [DemoComFunc messageBox:[NSString stringWithFormat:@"取消支付或支付失败"]];
    }
    else {
        [DemoComFunc messageBox:[NSString stringWithFormat:@"无法支付"]];
    }

}
#pragma mark - 91 sdk

- (void)init91Sdk{
    loginSuccess = false;
    NdInitConfigure *cfg = [[[NdInitConfigure alloc] init] autorelease];
	cfg.appid = [[DemoComFunc appIdForDemo] intValue];
	cfg.appKey = [DemoComFunc appKeyForDemo];
    
    NSLog(@"appid=%d ,appKey=%@",cfg.appid,cfg.appKey);
    
	[[NdComPlatform defaultPlatform] NdInit:cfg];
    
    [[NdComPlatform defaultPlatform] NdSetScreenOrientation:[DemoComFunc orientationFor91SDK]];
	//设置是否自动旋转
	[[NdComPlatform defaultPlatform] NdSetAutoRotation:[DemoComFunc is91SDKAutoRotateMode]];
    //设定为调试模式的支付功能和升级功能,参数为预留,默认为零。
//    [[NdComPlatform defaultPlatform] NdSetDebugMode:0];

//  调用检测更新的接口
//    int nRes = [[NdComPlatform defaultPlatform] NdAppVersionUpdate:0 delegate:self];
//    if(nRes){
//        
//    }
    
    shopArray = [[NSMutableArray alloc] init];
    
    [shopArray addObject:[NSArray arrayWithObjects:@"2",@"2",@"1",@"特殊道具",@"购买超级道具",@"特殊道具", nil]];
    [shopArray addObject:[NSArray arrayWithObjects:@"2",@"2",@"1",@"购买能量",@"购买5000能量",@"购买能量", nil]];
    [shopArray addObject:[NSArray arrayWithObjects:@"4",@"4",@"1",@"购买能量",@"购买13000能量",@"购买能量", nil]];//4
    [shopArray addObject:[NSArray arrayWithObjects:@"9",@"9",@"1",@"购买能量",@"购买40000能量",@"购买能量", nil]];//9
    [shopArray addObject:[NSArray arrayWithObjects:@"2",@"2",@"1",@"特殊武器",@"购买超级武器",@"特殊武器", nil]];
    [shopArray addObject:[NSArray arrayWithObjects:@"4",@"4",@"1",@"开启关卡",@"开启关卡",@"开启关卡", nil]];
    
    
    
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(SNSInitResult:) name:(NSString *)kNdCPInitDidFinishNotification object:nil];
    
    
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(SNSLoginResult:) name:(NSString *)kNdCPLoginNotification object:nil];
    
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(NdInitDidFinishNotification:) name:(NSString *)kNdCPInitDidFinishNotification object:nil];
//    
//    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(SNSleavePlatform:) name:(NSString *)kNdCPLeavePlatformNotification object:nil];
}


- (bool)isLogined{
	return [[NdComPlatform defaultPlatform] isLogined];
}

- (void)SNSInitResult:(NSNotification *)notify
{
    [self setNdShowToolBar];
}

- (void)setNdShowToolBar
{
    [[NdComPlatform defaultPlatform] NdShowToolBar:NdToolBarAtBottomLeft];
}

- (void)setNdHideToolBar{
    [[NdComPlatform defaultPlatform]  NdHideToolBar];
}
//展示 1813 论坛
- (void)show1813Forum{
    bool temp = [self isLogined];
    if(!temp)
        [[NdComPlatform defaultPlatform] NdLoginEx:0];
    else
        [self enterBBS];
}
//展示 91 论坛
- (void)show91Forum{
    bool temp = [self isLogined];
    if(!temp)
        [[NdComPlatform defaultPlatform] NdLoginEx:0];
    else
        [self enterPlatform];
}

//社区
- (void)enterPlatform
{
	[[NdComPlatform defaultPlatform] NdEnterPlatform:0];
}

//论坛
- (void)enterBBS
{
	[[NdComPlatform defaultPlatform] NdEnterAppBBS:0];
}

//意见反馈
- (void)enterFeedback
{
    bool temp = [self isLogined];
    if(!temp)
        [[NdComPlatform defaultPlatform] NdLoginEx:0];
    else
        [[NdComPlatform defaultPlatform] NdUserFeedBack];
}

- (void)show91NdPause{
    [[NdComPlatform defaultPlatform] NdPause];
}

- (bool)getloginSuccess{
    return loginSuccess;
}

#pragma mark - 虚拟商店
// 虚拟商店
- (void)initVirtualShop{
    
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(NdBuyCommodityResult:) name:(NSString *)kNdCPBuyResultNotification object:nil];
    
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(SNSLeaveComplatformUI:) name:(NSString *)kNdCPLeavePlatformNotification object:nil];
    
    //进入虚拟商店，显示所有类别，所有计费类型的商品
//    int nFeeType = ND_VG_FEE_TYPE_POSSESS | ND_VG_FEE_TYPE_SUBSCRIBE | ND_VG_FEE_TYPE_CONSUME;
//    [[NdComPlatform defaultPlatform] NdEnterVirtualShop:nil feeType:nFeeType];
//    [[NdComPlatform defaultPlatform] NdProductlsPayed];
}

- (void)SNSLeaveComplatformUI:(NSNotification*)notify {
    [[NSNotificationCenter defaultCenter] removeObserver:self name:kNdCPBuyResultNotification object:nil];
    [[NSNotificationCenter defaultCenter] removeObserver:self name:kNdCPLeavePlatformNotification object:nil];
    // TODO:
}

#pragma mark -
//支付
- (void)payment{
    [self initVirtualShop];
    
    CFUUIDRef theUUID = CFUUIDCreate(NULL);
	CFStringRef guid = CFUUIDCreateString(NULL, theUUID);
	CFRelease(theUUID);
	NSString *uuidString = [((NSString *)guid) stringByReplacingOccurrencesOfString:@"-" withString:@""];
	CFRelease(guid);
    
   
    int tempIndex = 0;
//    if(billingIndex == 6)
//        tempIndex = 5;//
//    else
        tempIndex = billingIndex-1;
    NSArray *tempArray = [shopArray objectAtIndex:tempIndex];
    NdBuyInfo *buyInfo = [[NdBuyInfo new] autorelease];
	buyInfo.cooOrderSerial = [uuidString lowercaseString];
    buyInfo.productPrice = [[tempArray objectAtIndex:0] floatValue];
    buyInfo.productOrignalPrice = [[tempArray objectAtIndex:1] floatValue];
    buyInfo.productCount = [[tempArray objectAtIndex:2] intValue];
    buyInfo.productId = [tempArray objectAtIndex:3];
    buyInfo.productName = [tempArray objectAtIndex:4];
    buyInfo.payDescription = [tempArray objectAtIndex:5];
	
//    int res = [[NdComPlatform defaultPlatform] NdUniPayAsyn:buyInfo];
    int res = [[NdComPlatform defaultPlatform] NdUniPay:buyInfo];
    if(res < 0){
        [[NdComPlatform defaultPlatform] NdLoginEx:0];
    }
    else{
        [self addRecord:buyInfo.cooOrderSerial];
    }
//    [[NdComPlatform defaultPlatform] NdUniPayForCoin:[uuidString lowercaseString] needPayCoins:0 payDescription:@"支付描述内容(iOS)"];
}

- (void)okPressed:(int)nTag{
    paymentStatus = 2;
}

//- (void)NdCPLeavePlatformNotification:(NSNotification*)notify{
//    paymentStatus = 2;
//}

#pragma mark - NSNotification
- (void)NdInitDidFinishNotification:(NSNotification*)notify{
    loginSuccess = true;
}

- (void)NdBuyCommodityResult:(NSNotification*)notify{
    NSDictionary *dic = [notify userInfo];
    NdBuyInfo* buyInfo = (NdBuyInfo*)[dic objectForKey:@"buyInfo"];
    BOOL bSuccess = [[dic objectForKey:@"result"] boolValue];
    NSString* str = bSuccess ? @"Yes" : @"NO";
    if (!bSuccess) {
        NSString* strError = nil;
        int nErrorCode = [[dic objectForKey:@"error"] intValue];
        switch (nErrorCode) {
            case ND_COM_PLATFORM_ERROR_USER_CANCEL:
                strError = @"用户取消操作";
                break;
            case ND_COM_PLATFORM_ERROR_NETWORK_FAIL:
                strError = @"网络连接错误";
                break;
            case ND_COM_PLATFORM_ERROR_SERVER_RETURN_ERROR:
                strError = @"服务器端处理失败";
                break;
            case ND_COM_PLATFORM_ERROR_ORDER_SERIAL_SUBMITTED: //!!!: 异步支付，用户进入充值界面
                strError = @"支付订单已提交";
                break;
            default:
                strError = @"购买过程发生错误";
                break;
        }
        str = [str stringByAppendingFormat:@"\n%@", strError];
        paymentStatus = 2;
    }
    else {
        NSLog(@"NdBuyCommodityResult: %@", str);
        paymentStatus = 1;
    }
    [self removeRecord:buyInfo.cooOrderSerial index:0];
    //本次购买的请求参数
    str = [str stringByAppendingFormat:@"\n<productId = %@, productCount = %d, cooOrderSerial = %@>",
           buyInfo.productId, buyInfo.productCount, buyInfo.cooOrderSerial];
    NSLog(@"NdUiPayAsynResult: %@", str);
}

//登录
- (void)SNSLoginResult:(NSNotification *)notify
{
	NSDictionary *dict = [notify userInfo];
	BOOL success = [[dict objectForKey:@"result"] boolValue];
	NdGuestAccountStatus* guestStatus = (NdGuestAccountStatus*)[dict objectForKey:@"NdGuestAccountStatus"];
	
	//登录成功后处理
	if([[NdComPlatform defaultPlatform] isLogined] && success) {
		
		//也可以通过[[NdComPlatform defaultPlatform] getCurrentLoginState]判断是否游客登录状态
		if (guestStatus) {
			NSString* strUin = [[NdComPlatform defaultPlatform] loginUin];
			NSString* strTip = nil;
			if ([guestStatus isGuestLogined]) {
				strTip = [NSString stringWithFormat:@"游客账号登录成功,\n uin = %@", strUin];
			}
			else if ([guestStatus isGuestRegistered]) {
				strTip = [NSString stringWithFormat:@"游客成功注册为普通账号,\n uin = %@", strUin];
			}
			
			if ([strTip length] > 0) {
//				[DemoComFunc messageBox: strTip];
			}
		}
		else {
			// 普通账号登录成功!
//            paymentStatus = 0;
		}
//		[self updateView];
//		[self dismissModalViewControllerAnimated:YES];
	}
	//登录失败处理和相应提示
	else {
		int error = [[dict objectForKey:@"error"] intValue];
		NSString* strTip = [NSString stringWithFormat:@"登录失败, error=%d", error];
		switch (error) {
			case ND_COM_PLATFORM_ERROR_USER_CANCEL://用户取消登录
				if (([[NdComPlatform defaultPlatform] getCurrentLoginState] == ND_LOGIN_STATE_GUEST_LOGIN)) {
					strTip =  @"当前仍处于游客登录状态";
				}
				else {
					strTip = @"用户未登录";
				}
				break;
			case ND_COM_PLATFORM_ERROR_APP_KEY_INVALID://appId未授权接入, 或appKey 无效
				strTip = @"登录失败, 请检查appId/appKey";
				break;
			case ND_COM_PLATFORM_ERROR_CLIENT_APP_ID_INVALID://无效的应用ID
				strTip = @"登录失败, 无效的应用ID";
				break;
			case ND_COM_PLATFORM_ERROR_HAS_ASSOCIATE_91:
				strTip = @"有关联的91账号，不能以游客方式登录";
				break;
			default:
				break;
		}
		[DemoComFunc messageBox:strTip];
        
//         paymentStatus = 2;
	}
   
}

- (void)SNSleavePlatform:(NSNotification *)notify{
    [[NSNotificationCenter defaultCenter] removeObserver:self name:kNdCPBuyResultNotification object:nil];
    
//    NSArray *recordArray = [self getUnCheckedRecord];
//    for (NSString *cooOrderSerial in recordArray) {
//        [[NdComPlatform defaultPlatform] NdCheckPaySuccess : cooOrderSerial delegate : self];
//    }
}


//- (void)appVersionUpdateDidFinish:(ND_APP_UPDATE_RESULT)updateResult
//{
//    NSString *title = nil;
//    switch (updateResult) {
//        case ND_APP_UPDATE_NO_NEW_VERSION:
//            title = @"无可用更新";
//            break;
//        case ND_APP_UPDATE_FORCE_UPDATE_CANCEL_BY_USER:
//            title = @"下载强制更新被取消";
//            break;
//        case ND_APP_UPDATE_NORMAL_UPDATE_CANCEL_BY_USER:
//            title = @"下载普通更新被取消";
//            break;
//        case ND_APP_UPDATE_NEW_VERSION_DOWNLOAD_FAIL:
//            title = @"下载更新版本失败";
//            break;
//        case ND_APP_UPDATE_CHECK_NEW_VERSION_FAIL:
//            title = @"检测新版本信息失败";
//            break;
//        default:
//        break;
//    }
//    NSLog(@"update result:%d %@", updateResult,title);
//    if (updateResult == ND_APP_UPDATE_NO_NEW_VERSION)
//    {
//    }
//    else{
//            
//    }
//}
/**
 @brief NdUploadChannelId的回调
 @param error 错误码，如果error为0，则代表API执行成功，否则失败。错误码涵义请查看NdComPlatformError文件
 */
- (void)uploadChannelIdDidFinish:(int)error{
    
}
#pragma mark -

- (int)getPaymentSuccess{
    return paymentStatus;
}

- (void)setPaymentSuccess:(int)success{
    paymentStatus = success;
}

- (int)getBillingIndex{
    return billingIndex;
}

+ (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation {
    return [DemoComFunc shouldAutorotateToInterfaceOrientation:interfaceOrientation];
}

+ (void)attemptDealloc
{
    if ([sharedPublicOC retainCount] != 1)
        return;
    
    [sharedPublicOC release];
    sharedPublicOC = nil;
}

#pragma mark - 漏单处理
- (void)addRecord:(NSString*)cooOrderSerial{
    NSMutableArray *tempArray = [self getUnCheckedRecord];
//    [tempArray removeAllObjects];
    [tempArray retain];
    if(!tempArray)
        tempArray = [[NSMutableArray alloc] init];

    Order *order = [[Order alloc] init];
    order._cooOrderSerial = cooOrderSerial;
    order._billingIndex = [NSString stringWithFormat:@"%d",billingIndex];
    [tempArray addObject:order];
    [order release];
    
    [self setSaveRecord:tempArray];
    [tempArray release];
}


- (void)removeRecord:(NSString*)cooOrderSerial index:(int)index{
    NSMutableArray *tempArray =  [self getUnCheckedRecord];
    NSLog(@"count == %d ",tempArray.count);
    if(tempArray){
        for (int i = 0; tempArray.count; i++) {
            Order * order = [tempArray objectAtIndex:i];
            if(cooOrderSerial==nil && order._billingIndex.intValue == index){
                [tempArray removeObject:order];
            }
            else if([order._cooOrderSerial isEqualToString:cooOrderSerial]){
                [tempArray removeObject:order];
            }
        }
    }
    NSLog(@"count == %d ",tempArray.count);
    [self setSaveRecord:tempArray];
}

- (void)setSaveRecord:(NSMutableArray*)array{
    NSData*encodedSingleObj = [NSKeyedArchiver archivedDataWithRootObject:array];
    [[NSUserDefaults standardUserDefaults] setObject:encodedSingleObj forKey:kCooOrder];
    [[NSUserDefaults standardUserDefaults] synchronize];
}

- (NSMutableArray*)getUnCheckedRecord{
    NSData *data = [[NSUserDefaults standardUserDefaults] objectForKey:OredeKey];
    NSMutableArray *tempArray = (NSMutableArray*)[NSKeyedUnarchiver unarchiveObjectWithData:data];
    return tempArray;
}

- (void)checkedRecord{
    bool temp = [self isLogined];
    if(!temp)
        [[NdComPlatform defaultPlatform] NdLoginEx:0];
    
    NSArray *recordArray = [self getUnCheckedRecord];

    for (Order * order in recordArray) {
        [[NdComPlatform defaultPlatform] NdCheckPaySuccess:order._cooOrderSerial delegate:self];
    }
    if(recordArray.count==0){
        [self setPaymentSuccess:3];
    }
}

- (void)checkPaySuccessDidFinish:(int)error cooOrderSerial:(NSString*)cooOrderSerial bSuccess:(BOOL)bSuccess
{
    Order*tempOrder = nil;
    NSMutableArray *tempArray =  [self getUnCheckedRecord];
    for (Order * order in tempArray) {
        if ([order._cooOrderSerial isEqualToString:cooOrderSerial]) {
            tempOrder = order;
            break;
        }
    }
    
    if (bSuccess){
        billingIndex = tempOrder._billingIndex.intValue;
        [self setPaymentSuccess:1];
    }
    else{
        [self setPaymentSuccess:2];
    }
    
    [self removeRecord:cooOrderSerial index:0];
}

- (void)searchPayResultInfoDidFinish:(int)error bSuccess:(BOOL)bSuccess buyInfo:(NdBuyInfo*)buyInfo{
}

#pragma mark -
- (void)addPicker:(UIView*)view{
    tempView = view;
    if(!picker){
        picker = [[ABPeoplePickerNavigationController alloc] init];
        picker.peoplePickerDelegate = self;
        picker.view.frame = CGRectMake(0, 0,MainScreen_H, MainScreen_W);
//    picker.frame
    //picker.navigationBar.topItem.prompt = @"选择要添加到“个人收藏”的联系人";
        [picker setHidesBottomBarWhenPushed:YES];
//    [picker setNavigationBarHidden:YES animated:NO];
    //picker.displayedProperties = [NSArray arrayWithObject:[NSNumber numberWithInt:kABPersonPhoneProperty]];
    }
    [view addSubview:picker.view];
//    [view presentModalViewController:picker animated:YES];
//    [picker release];
//
}

//用户取消选择时调用
- (void)peoplePickerNavigationControllerDidCancel:(ABPeoplePickerNavigationController *)peoplePicker
{
    //[self dismissModalViewControllerAnimated:YES];
    
    mobileStatus = 2;
    
    [picker.view removeFromSuperview];
//    [self.view removeFromSuperview];
}
-(BOOL)peoplePickerNavigationController:(ABPeoplePickerNavigationController *)peoplePicker shouldContinueAfterSelectingPerson:(ABRecordRef)person
{
    NSLog(@"%@", (NSString*)ABRecordCopyCompositeName(person));
    
    //获取联系人电话
    ABMutableMultiValueRef phoneMulti = ABRecordCopyValue(person, kABPersonPhoneProperty);
    NSMutableArray *phones = [[NSMutableArray alloc] init];
    int i;
    for (i = 0; i < ABMultiValueGetCount(phoneMulti); i++){
        NSString *aPhone = [(NSString*)ABMultiValueCopyValueAtIndex(phoneMulti, i) autorelease];
        NSString *aLabel = [(NSString*)ABMultiValueCopyLabelAtIndex(phoneMulti, i) autorelease];
//        NSLog(@"PhoneLabel:%@ Phone#:%@",aLabel,aPhone);
        if([aLabel isEqualToString:@"_$!<Mobile>!$_"]){
            [phones addObject:aPhone];
        }
    }
    phoneNum = @"";
    if([phones count]>0){
        NSString *mobileNo = [phones objectAtIndex:0];
        phoneNum = mobileNo;
        NSLog(@"%@" ,mobileNo);
        mobileStatus = 1;
    }
    //获取联系人邮箱
//    ABMutableMultiValueRef emailMulti = ABRecordCopyValue(person, kABPersonEmailProperty);
//    NSMutableArray *emails = [[NSMutableArray alloc] init];
//    for (i = 0;i < ABMultiValueGetCount(emailMulti); i++)
//    {
//        NSString *emailAdress = [(NSString*)ABMultiValueCopyValueAtIndex(emailMulti, i) autorelease];
//        [emails addObject:emailAdress];
//    }
//    email.text=@"";
//    
//    if([emails count]>0){
//        NSString *emailFirst=[emails objectAtIndex:0];
//    　   email.text = emailFirst;
//        //NSLog(emailFirst);
//    }
    
//    [peoplePicker dismissModalViewControllerAnimated:YES];
    [picker.view removeFromSuperview];
    return NO;
}
-(BOOL)peoplePickerNavigationController:(ABPeoplePickerNavigationController *)peoplePicker shouldContinueAfterSelectingPerson:(ABRecordRef)person property:(ABPropertyID)property identifier:(ABMultiValueIdentifier)identifier
{
    
    return YES;
}
-(BOOL)personViewController:(ABPersonViewController *)personViewController shouldPerformDefaultActionForPerson:(ABRecordRef)person property:(ABPropertyID)property identifier:(ABMultiValueIdentifier)identifier{
    return YES;
}

-(void)newPersonViewController:(ABNewPersonViewController *)newPersonView didCompleteWithNewPerson:(ABRecordRef)person{
    if(person)
    {
        CFErrorRef error=NULL;
        ABAddressBookSave(newPersonView.addressBook, &error);
        //[newPersonView dismissModalViewControllerAnimated:YES];
    }
//    [self.view removeFromSuperview];
}

- (NSString*)getPhoneNum{
    NSString *tempP =[PublicOC myNumber];
    tempP = [tempP stringByReplacingOccurrencesOfString:@"+86" withString:@""];
    return tempP;
}

- (int)getMobileStatus{
    return mobileStatus;
}

- (int)getVerificationCodeStatus{
    return verificationCodeStatus;
}

- (void)dealloc{
    
//    [billing release];
   
    [shopArray release];
    [super dealloc];
}

@end
