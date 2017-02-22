//
//  FishXAppDelegate.cpp
//  FishX
//
//  Created by peng on 12-12-21.
//  Copyright __MyCompanyName__ 2012年. All rights reserved.
//

#include "AppDelegate.h"
#include "cocos2d.h"
#include "Layer/GMIntroLayer.h"
#include "Config/GMHeaderConfig.h"
#include "SimpleAudioEngine.h"
#include "PublicModels/GMAudioPlay.h"
#include "Layer/GMGameLayer.h"
#include "PublicModels/GMPublicMethod.h"
#include "PublicModels/ZPJNIHelper.h"

//com.Gamedo.Fish91
USING_NS_CC;
using namespace CocosDenshion;
//#pragma mark - retina
/*
 *  用来设置 retina display
 */
typedef struct tagResource
{
    cocos2d::CCSize size;
    char directory[100];
}Resource;

static Resource smallResource  =  { cocos2d::CCSizeMake(480, 320),   "iPhone" };
static Resource resPhoneRetina =  { cocos2d::CCSizeMake(960, 640),   "iPhoneRetina"};
static Resource iPhone5Resource =  { cocos2d::CCSizeMake(568, 320),  "iPhone5"};
static Resource iPhone5Retina =  { cocos2d::CCSizeMake(1136, 640),   "iPhone5Retina"};
static Resource mediumResource =  { cocos2d::CCSizeMake(1024, 768),  "iPhoneRetina"   }; //"ipad"
static Resource largeResource  =  { cocos2d::CCSizeMake(2048, 1536), "iPhoneRetina" }; //"ipadhd"

static cocos2d::CCSize designResolutionSize = cocos2d::CCSizeMake(480, 320);



AppDelegate::AppDelegate()
{

}

AppDelegate::~AppDelegate()
{
    GMPublicMethod::sharedPublicMethod()->purgeSharedPublicMethod();
    ZPJNIHelper::sharedJNIHelper()->purgeSharedPublicMethod();
}

bool AppDelegate::applicationDidFinishLaunching()
{


	float a1 = ccpAngle(ccp(50, 50), ccp(0, 0));
	float a2 = CC_RADIANS_TO_DEGREES(a1);
	float ar2 = CC_DEGREES_TO_RADIANS(a2);
	CCPoint ap2 = ccpRotateByAngle(ccp(0, 50), ccp(0, 0), ar2);
	float a3 = ccpAngle(ccp(-50, 50), ccp(0, 0));
	float a4 = CC_RADIANS_TO_DEGREES(a3);
    // initialize director
    CCDirector *pDirector = CCDirector::sharedDirector();
    CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();
    pDirector->setOpenGLView(pEGLView);
    CCDirector::sharedDirector()->setDepthTest(false);
////////////////////////////////////////////////////////////////////////
    Resource actualResource;
    CCSize frameSize = pEGLView->getFrameSize();
    ZPLog("w=%f;h=%f",frameSize.width,frameSize.height);
    // In this demo, we select resource according to the frame's height.
    // If the resource size is different from design resolution size, you need to set contentScaleFactor.
    // We use the ratio of resource's height to the height of design resolution,
    // this can make sure that the resource's height could fit for the height of design resolution.
    
//    pEGLView->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, kResolutionNoBorder);
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    // if the frame's height is larger than the height of medium resource size, select large resource.
    if (frameSize.height > mediumResource.size.height){
        actualResource = largeResource;
    }
    // if the frame's height is larger than the height of small resource size, select medium resource.
    else if (frameSize.height > resPhoneRetina.size.height) {
        actualResource = largeResource;
    }
    else if(frameSize.width == iPhone5Retina.size.width && frameSize.height== iPhone5Retina.size.height){
        actualResource = iPhone5Resource;//iPhone5Retina;
    }
    else if(frameSize.width == resPhoneRetina.size.width && frameSize.height== resPhoneRetina.size.height) {
        actualResource = smallResource;//resPhoneRetina;
    }
    else if(frameSize.width == smallResource.size.width && frameSize.height== smallResource.size.height) {
        actualResource = smallResource;//resPhoneRetina;
    }
    
    CCFileUtils::sharedFileUtils()->setResourceDirectory(actualResource.directory);
#endif
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
//    CCFileUtils::sharedFileUtils()->setResourceDirectory("../../Resource/");
#endif
    
    // Set the design resolution
    pEGLView->setDesignResolutionSize(actualResource.size.width, actualResource.size.height, kResolutionNoBorder);
//    IOSLog("11 w=%f;h=%f",actualResource.size.width,actualResource.size.height);
//    float scale = actualResource.size.height/designResolutionSize.height;
//    IOSLog("scale = %f",scale);
//    pDirector->setContentScaleFactor(scale);
////////////////////////////////////////////////////////////////////////
    // turn on display FPS
//    pDirector->setDisplayStats(true);
//    enableRetinaDisplay(true)
//    IOSLog("333 %f",pDirector->getContentScaleFactor());
    // set FPS. the default value is 1.0/60 if you don't call this
//    pDirector->setAnimationInterval(1.0 / 60);
   
    setBillingModel();

    // create a scene. it's an autorelease object
    CCScene *pScene = GMIntroLayer::scene();
    // run
    pDirector->runWithScene(pScene);
//    UIActivityIndicatorView
    
    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{

    // if you use SimpleAudioEngine, it must be paused
//    SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
//    SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
    
    GMAudioPlay::sharedAudioPlay()->stopBGMusic();
    SimpleAudioEngine::sharedEngine()->pauseAllEffects();
        
    GameStatus type = GMPublicMethod::sharedPublicMethod()->getGameStatus();
    int tempStatus = GMAccessData::sharedAccessData()->getPauseStatus();
    bool tempPlayVideo = GMPublicMethod::sharedPublicMethod()->getAndroidPlayVideo();
    ZPLog("Home建退出 %d",type);
    if (tempStatus == 0 && tempPlayVideo == false) {
        switch (type) {
            case Game_Status:
            case Boss_Status:
            {
                CCObject*tempObject = GMPublicMethod::sharedPublicMethod()->getGameObject();
                GMGameLayer *temp = (GMGameLayer*)tempObject;
                if (temp) {
                    temp->pauseAction();
                }
            }   break;
            default:
                break;
        }
    }

    CCDirector::sharedDirector()->stopAnimation();
    CCDirector::sharedDirector()->pause();
}


// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    CCDirector::sharedDirector()->startAnimation();
    CCDirector::sharedDirector()->resume();
    // if you use SimpleAudioEngine, it must resume here
    GameStatus type = GMPublicMethod::sharedPublicMethod()->getGameStatus();
    bool tempPlayVideo = GMPublicMethod::sharedPublicMethod()->getAndroidPlayVideo();
    
    ZPLog("Home再次进入 %d",type);
    if (tempPlayVideo == false){
        switch (type) {
            case Home_Status:{
                GMAudioPlay::sharedAudioPlay()->playBGMusic(Audio_Home);
            }   break;
            case Game_Status:
            case Target_Status:
            case Checkpoints_Status:
//            case Pause_Status:
            {
                GMAudioPlay::sharedAudioPlay()->playBGMusic(Audio_Gmae1);
                GMPublicMethod::getGoldCoinsTime();
            }   break;
            case Boss_Status:{
                GMAudioPlay::sharedAudioPlay()->playBGMusic(Audio_BG_Boss);
            }   break;
            default:
                break;
        }
    }
    
    GMPublicMethod::sharedPublicMethod()->setAndroidPlayVideo(false);
    SimpleAudioEngine::sharedEngine()->resumeAllEffects();
    
    if(ZPJNIHelper::sharedJNIHelper()->getScreensaverStatus()){
        ZPJNIHelper::sharedJNIHelper()->setVideoStatus();
    }
#if (JNIHELPER_INDEX == JNIHELPER_91_IOS)
    //PublicCPP::sharedSpriteCPP()->show91NdPause();
#endif
    
#if (JNIHELPER_INDEX == JNIHELPER_91_Android)
    
    if(GMPublicMethod::sharedPublicMethod()->getShow91Pause() == true){
        ZPLog("getShow91Pause");
        ZPJNIHelper::setPauseView();
    }
    
    GMPublicMethod::sharedPublicMethod()->setShow91Pause(true);
    
//    GameStatus type1 = GMPublicMethod::sharedPublicMethod()->getGameStatus();
//    ZPLog("type1type1type1type1type1type1 == %d",type1);
//    if(type1 ==  Game_Status || type1 == Boss_Status){
//        CCObject*tempObject = GMPublicMethod::sharedPublicMethod()->getGameObject();
//        GMGameLayer *temp = (GMGameLayer*)tempObject;
//        if (temp) {
//            ZPLog(" == %d",type1);
//        }
//    }
#endif
   
}

void AppDelegate::setBillingModel(){
    //    B_Free  B_TengXunBilling B_91
#if (JNIHELPER_INDEX == JNIHELPER_NUKNOW)
    GMPublicMethod::sharedPublicMethod()->setBillingModel(B_Free);
#endif
    
#if (JNIHELPER_INDEX == JNIHELPER_TengXun)
    GMPublicMethod::sharedPublicMethod()->setBillingModel(B_TengXunBilling);
#endif
    
#if (JNIHELPER_INDEX == JNIHELPER_91)
    GMPublicMethod::sharedPublicMethod()->setBillingModel(B_91);
#endif
    
#if (JNIHELPER_INDEX == JNIHELPER_91_IOS)
    GMPublicMethod::sharedPublicMethod()->setBillingModel(B_91_IOS);
#endif
    
#if (JNIHELPER_INDEX == JNIHELPER_YiDong)
    GMPublicMethod::sharedPublicMethod()->setBillingModel(B_YiDong);
#endif

#if (JNIHELPER_INDEX == JNIHELPER_Telecom)
    GMPublicMethod::sharedPublicMethod()->setBillingModel(B_Telecom);
#endif
   
#if (JNIHELPER_INDEX == JNIHELPER_91_Android)
    GMPublicMethod::sharedPublicMethod()->setBillingModel(B_91_Android);
#endif

#if (JNIHELPER_INDEX == JNIHELPER_Unicom_Android)
    GMPublicMethod::sharedPublicMethod()->setBillingModel(B_Unicom_Android);
#endif
    
}
