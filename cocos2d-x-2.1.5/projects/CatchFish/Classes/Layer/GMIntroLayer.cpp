//
//  GMIntroLayer.cpp
//  FishX
//
//  Created by peng on 12-12-21.
//
//

#include "GMIntroLayer.h"
#include "GMHelpLayer.h"
#include "GMCardLayer.h"
#include "GMMainLayer.h"
#include "GMWinLayer.h"
#include "GMLoseLayer.h"
#include "GMElementLayer.h"
#include "GMPauseLayer.h"
#include "../Config/GMHeaderConfig.h"
#include "GMAchievementLayer.h"
#include "../PublicModels/GMAudioPlay.h"
#include "GMCartoonLayer.h"

#include "../PublicModels/ZPDialogLayer.h"
#include "../PublicModels/ZPJNIHelper.h"
#include "../PublicModels/GMBillingLayer.h"

//#include "GMBillingLayer.h"

//USING_NS_CC_EXT;

//#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
//#include <jni.h>
//#include "platform/android/jni/JniHelper.h"
//#include <android/log.h>
////#define CLASS_NAME1 "com/cocos2dGamedo/fish/JniInterface"
//#endif

#define MenuTag    120

using namespace cocos2d;


CCScene* GMIntroLayer::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    GMIntroLayer *layer = GMIntroLayer::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GMIntroLayer::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    billingModel = GMPublicMethod::sharedPublicMethod()->getBillingModel();
	//GMPublicMethod::sharedPublicMethod()->setGameStatus1(None_Status);
    //GMAudioPlay::sharedAudioPlay()->playBGMusic(Audio_Home);

//    CCRemoveUnusedSpriteFrames();
    CCRemoveUnusedAllSpriteFrames();
    
    CCAddSpriteFramesAndTextureFile(homepage_plist,homepage_png);
    //    CCAddSpriteFramesWithFile(homepage_plist);
    //    homeBatchNode = CCSpriteBatchNode::create(homepage_png);
    //    this->addChild(homeBatchNode);
    CCAddSpriteFramesAndTextureFile(homepage_plist1,homepage_png1);
    
	homeLayer = CCLayer::create();
    homeLayer->setContentSize(CCSizeMake(S_WINSIZE_W, S_WINSIZE_H));
    homeLayer->setAnchorPoint(ccp(0, 0));
    //    SetScale(homeLayer);
    SetScale2(homeLayer,Scale_X);
    homeLayer->setPosition(ccp((WINSIZE_W-S_WINSIZE_W*Scale_X)/2, 0));
    this->addChild(homeLayer,2, 123123);
    
    //    CCAddSpriteFramesWithFile(homepage_plist1);
    //    homepageNode = CCSpriteBatchNode::create(homepage_png1);
    //    this->addChild(homepageNode,2);
    
    background = CCSprite::create("home/homepage008.jpg");
    background->setPosition(ccp(WINSIZE_W/2, WINSIZE_H/2));
    SetScale(background);
    this->addChild(background);

    CCSprite *sprint1 = CCSprite::createWithSpriteFrameName("homepage007.png");
    sprint1->setPosition(ccp(Get_W( Get_Box(sprint1) )/2, Get_H( Get_Box(sprint1) )/2));
    homeLayer->addChild(sprint1);
    
    CCSprite *effect = CCSprite::create("home/homepage050.png");
    effect->setAnchorPoint(ccp(0,1));
    CCArray *temp = CCArray::create();
    char strName[40] = {0};
    for (int j = 50; j <= 59; j++) {
        sprintf(strName,"home/homepage%03d.png",j);
        CCSpriteFrame *spriteFrame = CCSpriteFrame::create(strName, Get_Rect(effect));
        temp->addObject(spriteFrame);
    }
    CCAnimation *m_pAnimation = CCAnimation::createWithSpriteFrames(temp,0.1);
    CCAnimate *animate = CCAnimate::create(m_pAnimation);
    CCRepeatForever *repeateF1 = CCRepeatForever::create(animate);
    effect->runAction(repeateF1);
    effect->setPosition(ccp(0, WINSIZE_H));
    this->addChild(effect,3);
    SetScale(effect);
    //捕鱼标题
    CCSprite *sprint2 = NULL;
    if(billingModel == B_91){
        sprint2 = CCSprite::create("home/homepage1001.png");
        sprint2->setPosition(ccp(WINSIZE_W-20*Scale_Y,WINSIZE_H-10*Scale_Y));
        SetScale2(sprint2, Scale_Y);
    }
    else if(billingModel == B_91_IOS){
        sprint2 = CCSprite::create("home/homepage1002.png");
        SetScale2(sprint2, Scale_X);
        sprint2->setPosition(ccp(WINSIZE_W-20*Scale_X,WINSIZE_H-10*Scale_X));
    }
    else if(billingModel == B_YiDong || billingModel == B_Unicom_Android){
        sprint2 = CCSprite::create("home/homepage001.png");
        sprint2->setPosition(ccp(WINSIZE_W-20*Scale_Y,WINSIZE_H-10*Scale_Y));
        SetScale2(sprint2, Scale_Y);
    }
    else if(billingModel == B_Telecom){
        sprint2 = CCSprite::create("home/homepage001.png");
        sprint2->setPosition(ccp(WINSIZE_W-20*Scale_Y,WINSIZE_H-10*Scale_Y));
        SetScale2(sprint2, Scale_Y);
    }
    else{
        sprint2 = CCSprite::create("home/homepage1002.png");
//        sprint2 = CCSprite::createWithSpriteFrameName("homepage001.png");
//        sprint2 = CCSprite::create("homepage1002.png");
//        sprint2 = CCSprite::createWithSpriteFrameName("homepage001.png");
        SetScale2(sprint2, Scale_Y);
        sprint2->setPosition(ccp(WINSIZE_W-20*Scale_Y,WINSIZE_H-10*Scale_Y));
    }
    sprint2->setAnchorPoint(ccp(1, 1));
    this->addChild(sprint2);
    
    menuSprite = CCSprite::createWithSpriteFrameName("homepage012.jpg");
    GMPublicMethod::setRepeatAnimation(menuSprite, 12, 17, "homepage", "jpg",0.1,true);
    menuSprite->setPosition(ccp(S_WINSIZE_W/2, S_WINSIZE_H/2-16.5));
    homeLayer->addChild(menuSprite);
    
    int tempM = GMAccessData::sharedAccessData()->getTotalMoneyStatus();
    if (tempM==0) {
        ZPLog("第一次获取子弹 %d",tempM);
        GMAccessData::sharedAccessData()->initValue();
    }
    
    //long time = GMPublicMethod::getTime();
   
    struct tm * tm;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)  
	//win32平台
	time_t timep;
	time(&timep);
	tm = localtime(&timep);
#else 
	//android、ios平台
	struct cc_timeval now; 
	CCTime::gettimeofdayCocos2d(&now, NULL);
	tm = localtime(&now.tv_sec);
#endif  
    
	int day1 = tm->tm_mday;
    long time2 = GMAccessData::sharedAccessData()->getToday();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)  
	//win32平台
	time(&timep);
	tm = localtime(&timep);
#else 
	//android、ios平台
	tm = localtime(&time2);
#endif

    int day2 = tm->tm_mday;
    int giftStatus = GMAccessData::sharedAccessData()->getGiftStatus();
    ZPLog("时间 %d==%d  giftStatus = %d",day1,day2,giftStatus);
    ZPLog("时间2 %ld == %ld",time,time2);
    
	//GMAccessData::sharedAccessData()->saveGenuineValidationStatus(2);
    
    if(day1 != day2){
        GMAccessData::sharedAccessData()->saveToday(GMPublicMethod::getTime());
        if(giftStatus == 4){
            GMAccessData::sharedAccessData()->saveGiftStatus(1);
            GMAccessData::sharedAccessData()->saveGiftCountdown(15);
        }
    }
//    GMAccessData::sharedAccessData()->saveGiftStatus(2);
//    GMAccessData::saveTotalMoneyNum(0);
//    GMAccessData::saveOpenCannonLeve(2);
    GMPublicMethod::getGoldCoinsTime();
    exitLayer = NULL;
    loadTime = 0;
    isShowDialogLayer = false;
    _isShowOpenVideo = false;
    _isClick = false;
    _isShowYiDong = false;
    isAgain = false;
    
    this->schedule(schedule_selector(GMIntroLayer::uploadDate), 0.0001);
    
    if(billingModel == B_TengXunBilling || billingModel == B_Telecom){
        showQQLogoDialogLayer(1);
    }
    else if(billingModel == B_91_IOS){
//#if (JNIHELPER_INDEX == JNIHELPER_91_IOS)
//        ZPLog("运营商 %d",PublicCPP::getCarrier());
////        showMoreItem();
//        if(GMPublicMethod::sharedPublicMethod()->getShowLogo() == false){
//            GMPublicMethod::sharedPublicMethod()->setShowLogo(true);
//            this->schedule(schedule_selector(GMIntroLayer::checkedRecord));
//        }
//#endif
    }
    else if(billingModel == B_YiDong){
    }
    else if(billingModel==B_91_Android){
//        showMoreItem();
    }
    else if(billingModel == B_Unicom_Android){
        ZPLog("测试1");
        showQQLogoDialogLayer(0);
        ZPLog("测试222");
    }
    else {
        showOpenMusicDialogLayer();
    }
    isLoadT = true;
    
#if (JNIHELPER_INDEX == JNIHELPER_YiDong || JNIHELPER_INDEX == JNIHELPER_91_Android)
    int mStatus = GMPublicMethod::sharedPublicMethod()->getAudioStatus();
    ZPLog("<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>");
    ZPLog("mStatus %d",mStatus);
    ZPLog("<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>");
    if(mStatus==0)
        this->schedule(schedule_selector(GMIntroLayer::checkMusicAction));
    else
        GMAudioPlay::sharedAudioPlay()->playBGMusic(Audio_Home);
#endif

	GMPublicMethod::sharedPublicMethod()->tempLayer = this;

	char str[256];
	sprintf(str, "the platform is %d", CC_TARGET_PLATFORM);
	CCLabelTTF *lable = CCLabelTTF::create(str, "", 40);
	lable->setPositionX(400);
	lable->setPositionY(200);

	this->addChild(lable, 9999, 999012);

	this->choosedMenu = 0;
    return true;
}


void GMIntroLayer::keyboardHook(int keyCode, int keyEvent) {


	GMIntroLayer* layer = this;
	if (layer == NULL) return;
	CCLabelTTF* label1 = (CCLabelTTF*)layer->getChildByTag(999012);
	char str[50];
	sprintf(str, "%s, %d,%d,", "key event is ", keyCode, keyEvent);
	//CCLog(str);
	label1->setString(str);
	switch (keyEvent) {
	case kTypeEventKeyUp:
		if (keyCode == kTypeEnterClicked) {
			if (layer->choosedMenu == 0) {
				layer->showAllMenu(NULL);
			}
			else {
				CCMenu* menu = (CCMenu*)(layer->homeLayer->getChildByTag(MenuTag));
				CCObject* child;
				if (menu != NULL) {
					CCARRAY_FOREACH(menu->getChildren(), child){
						CCMenuItem *mit = (CCMenuItem*)child;
						if (mit->getTag() == layer->choosedMenu) {
							switch (layer->choosedMenu) {
							case 1:
								layer->startGame(mit);
								break;
							case 2:
								layer->startEndlessMode(mit);
								break;
							case 3:
								layer->achievementLayer(mit);
								break;
							case 4:
								layer->helpGame(mit);
								break;
							}
						}
					}
				}
			}
			return;
		}
		else if (keyCode == kTypeDownArrowClicked) {
			layer->choosedMenu += 1;
			if (choosedMenu > 4) choosedMenu = 4;
			else {
				CCMenu* menu = (CCMenu*)(layer->homeLayer->getChildByTag(MenuTag));
				CCObject* child;
				if (menu != NULL) {
					CCARRAY_FOREACH(menu->getChildren(), child){
						CCMenuItem *mit = (CCMenuItem*)child;
						if (mit->getTag() == layer->choosedMenu) {
							mit->setScale(1.3f);
						}
						else if (mit->getTag() == choosedMenu - 1) {
							mit->setScale(1.0f);
						}
					}
				}
			}
		}
		else if (keyCode == kTypeUpArrowClicked) {
			layer->choosedMenu -= 1;
			if (choosedMenu < 1) choosedMenu = 1;
			else {
				CCMenu* menu = (CCMenu*)(layer->homeLayer->getChildByTag(MenuTag));
				CCObject* child;
				if (menu != NULL) {
					CCARRAY_FOREACH(menu->getChildren(), child){
						CCMenuItem *mit = (CCMenuItem*)child;
						if (mit->getTag() == layer->choosedMenu) {
							mit->setScale(1.3f);
						}
						else if (mit->getTag() == choosedMenu + 1) {
							mit->setScale(1.0f);
						}
					}
				}

			}
		}
	}
}


//#pragma mark -分批加载
void GMIntroLayer::uploadDate(float t){
    loadTime++;
    loadHomeData(loadTime);
}

void GMIntroLayer::loadHomeData(int time)
{
    switch (time) {
        case 1:{
             GMAudioPlay::sharedAudioPlay();
            showMusic();
        }   break;
        case 2:{
            CCParticleSystem *explodePar = CCParticleSystemQuad::create(Particles2);
            //    explodePar->setAutoRemoveOnFinish(true);
            explodePar->setPosition(ccp(S_WINSIZE_W/2, -25)); //setPosition(point);
            homeLayer->addChild(explodePar, 3, 100);
            explodePar->setScale(2);
            
            int temp = GMAccessData::sharedAccessData()->getMagnificationModel();
            ZPLog("测试::%d",temp);
            if(temp <= 0){
                GMAccessData::sharedAccessData()->saveMagnificationModel(1);
                GMAccessData::sharedAccessData()->saveCurrentMagnificationModel(1);
            }
        }   break;
        case 4:{
            tipSprite = CCSprite::createWithSpriteFrameName("homepage011.png");
            tipSprite->setPosition(ccp(S_WINSIZE_W/2-3, S_WINSIZE_H/2-20));
            homeLayer->addChild(tipSprite,2);
            tipSprite->setScale(0);
            CCScaleTo *scale1 = CCScaleTo::create(0.5, 0.7);
            CCScaleTo *scale2 = CCScaleTo::create(0.5, 1);
            CCActionInterval *sequence = (CCActionInterval*)CCSequence::create(scale1,scale2,NULL);
            CCRepeatForever *repeateF = CCRepeatForever::create(sequence);
            tipSprite->runAction(repeateF);

            CCSprite *normalSprite = CCSprite::createWithSpriteFrameName("homepage018.png");
            CCMenuItem *menuItem = CCMenuItemSprite::create(normalSprite, normalSprite, this, menu_selector(GMIntroLayer::showAllMenu));
            mainMenu1 = CCMenu::create(menuItem,NULL);
            mainMenu1->setPosition(ccp(S_WINSIZE_W/2, S_WINSIZE_H/2-16.5));
            homeLayer->addChild(mainMenu1,3);

            fish = CCSprite::createWithSpriteFrameName("homeyu001.png");
            GMPublicMethod::setRepeatAnimation(fish, 1, 8, "homeyu", "png", 0.1,true);
            fish->setPosition(ccp(S_WINSIZE_W/2+145, 95));
            background->addChild(fish,1);
            
            CCMoveTo *moveTo1 = CCMoveTo::create(0.3, ccp(S_WINSIZE_W/2+145, 150));
            CCMoveTo *moveTo2 = CCMoveTo::create(0.3, ccp(S_WINSIZE_W/2+145, 95));
            CCActionInterval *sequence1 = (CCActionInterval*)CCSequence::create(moveTo1,moveTo1,moveTo2,NULL);
            CCRepeatForever *repeateF2 = CCRepeatForever::create(sequence1);
            
            fish->runAction(repeateF2);
            //
            CCSprite *fishBox = CCSprite::createWithSpriteFrameName("homeyu000.png");
            fishBox->setPosition(ccp(S_WINSIZE_W/2+154, 99));
            background->addChild(fishBox,1);
            
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
            CCAddSpriteFramesAndTextureFile(gamegoal_plist,gamegoal_png);
#endif
			this->setKeypadEnabled(true);
            
            this->unschedule(schedule_selector(GMIntroLayer::uploadDate));
        }   break;
        default:
            break;
    }
    
    ZPLog("测试 GMIntroLayer::loadHomeData");
}

void GMIntroLayer::checkedRecord(){
    if(billingModel == B_91_IOS){
//#if (JNIHELPER_INDEX == JNIHELPER_91_IOS)
//        if(PublicCPP::getloginSuccess()){
//            this->unschedule(schedule_selector(GMIntroLayer::checkedRecord));
//            PublicCPP::checkedRecord();
//            this->schedule(schedule_selector(GMIntroLayer::check91BillingPoint));
//        }
//#endif
    }
}

void GMIntroLayer::showMusic()
{
    /*
     *  关闭音乐按钮
     */
    int closeStatus = GMPublicMethod::sharedPublicMethod()->getAudioStatus();//GMAccessData::getAudioStatus();
    CCSprite *homepage040 = NULL;
    CCSprite *homepage041 = NULL;
    closeMusicItem = NULL;
    CCMenuItemSprite *quitItem = NULL;
    CCMenuItemSprite *moreItem = NULL;
    if (billingModel == B_YiDong || billingModel == B_91_Android) {
        
        GMPublicMethod::sharedPublicMethod()->setGameStatus(Home_Status);
        
        homepage040 = CCSprite::create("homepage060.png");
        homepage041 = CCSprite::create("homepage061.png");
        closeMusicItem = CCMenuItemSprite::create(homepage040, homepage041, this, menu_selector(GMIntroLayer::setMusicAtion));
        
        homepage040 = CCSprite::create("homepage062.png");
        homepage041 = CCSprite::create("homepage063.png");
        quitItem = CCMenuItemSprite::create(homepage040, homepage041, this, menu_selector(GMIntroLayer::setQuitAction));
        SetScale2(quitItem, Scale_X);
        quitItem->setAnchorPoint(ccp(0, 0));
        quitItem->setPosition(ccp(10*Scale_X,10*Scale_X));
        
        homepage040 = CCSprite::create("homepage064.png");
        homepage041 = CCSprite::create("homepage065.png");
        moreItem = CCMenuItemSprite::create(homepage040, homepage041, this, menu_selector(GMIntroLayer::setMoreAction));
        SetScale2(moreItem, Scale_X);
        moreItem->setAnchorPoint(ccp(0, 0));
        moreItem->setPosition(ccp(10*Scale_X,68*Scale_X));
        
    }
    else {
        if ( ((billingModel == B_91_IOS || billingModel == B_91_Android) && (closeStatus == 2 || closeStatus==0 ) ) ||
            ((billingModel !=B_91_IOS && billingModel != B_91_Android) && closeStatus == 2 ) ) {
            //    if (closeStatus == 2 || closeStatus==0) {
            homepage040 = CCSprite::createWithSpriteFrameName("homepage040.png");
            GMAudioPlay::sharedAudioPlay()->playBGMusic(Audio_Home);
        }
        else if(closeStatus == 1){
            homepage040 = CCSprite::createWithSpriteFrameName("homepage041.png");
        }
        closeMusicItem = CCMenuItemSprite::create(homepage040, homepage041, this, menu_selector(GMIntroLayer::closeMusicAtion));
    }
    if(closeMusicItem){
        SetScale2(closeMusicItem, Scale_X);
        closeMusicItem->setAnchorPoint(ccp(0, 1));
        closeMusicItem->setPosition(ccp(10,WINSIZE_H-10));
        
        CCMenu *closeMusicMenu = CCMenu::create(closeMusicItem,quitItem,moreItem,NULL);
        closeMusicMenu->setPosition(CCPointZero);
        this->addChild(closeMusicMenu,3,MenuTag);
    }
}

//#pragma mark -
void GMIntroLayer::setMusicAtion(CCObject *pSender){
    GMAudioPlay::sharedAudioPlay()->playButtonEffect();
    showOpenMusicDialogLayer();
}

//#pragma mark - 移动退出游戏
void GMIntroLayer::setQuitAction(CCObject *pSender){
    GMAudioPlay::sharedAudioPlay()->playButtonEffect();
    setGameOver();
    
#if (JNIHELPER_INDEX == JNIHELPER_YiDong)
    this->unschedule(schedule_selector(GMIntroLayer::checkYiDongExitStatus));
    this->schedule(schedule_selector(GMIntroLayer::checkYiDongExitStatus));
    ZPJNIHelper::setExitGame();
#endif
}

void GMIntroLayer::setGameOver(){
#if (JNIHELPER_INDEX == JNIHELPER_91_Android)
    if(isAgain==false){
        isAgain = true;
        ZPLog("setGameOversetGameOversetGameOversetGameOver");
        ZPJNIHelper::isExitGame();
        this->scheduleOnce(schedule_selector(GMIntroLayer::setGameOverStaus), 1);
    }
#endif
}

void GMIntroLayer::setGameOverStaus(float dt){
    isAgain = false;
}

void GMIntroLayer::setMoreAction(CCObject *pSender){
//    GMPublicMethod::sharedPublicMethod()->setGameStatus(Home_Status);
    
    GMAudioPlay::sharedAudioPlay()->playButtonEffect();
    ZPJNIHelper::moreGames();
}

void GMIntroLayer::closeMusicAtion(CCObject *pSender)
{
    CCSprite *normalSprite3 = NULL;
    int tempInde = 0;
    int closeStatus = GMPublicMethod::sharedPublicMethod()->getAudioStatus();//GMAccessData::getAudioStatus();
    ZPLog("<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>");
    ZPLog("closeStatus %d",closeStatus);
    ZPLog("<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>");
    if (closeStatus == 2 || closeStatus==0) {//关闭
        tempInde = 1;
//        normalSprite3 = CCSprite::createWithSpriteFrameName("homepage041.png");
//        GMAccessData::saveAudioStatus(1);
        GMPublicMethod::sharedPublicMethod()->setAudioStatus(1);
        GMAudioPlay::sharedAudioPlay()->setCloseStatus();
        GMAudioPlay::sharedAudioPlay()->stopBGMusic();
    }
    else if (closeStatus == 1) {//开启
        tempInde = 0;
//        normalSprite3 = CCSprite::createWithSpriteFrameName("homepage040.png");
//        GMAccessData::saveAudioStatus(2);
        GMPublicMethod::sharedPublicMethod()->setAudioStatus(2);
        GMAudioPlay::sharedAudioPlay()->setCloseStatus();
        GMAudioPlay::sharedAudioPlay()->playBGMusic(Audio_Home);
        
        GMPublicMethod::sharedPublicMethod()->setGameStatus(Home_Status);
    }

    if(billingModel == B_YiDong || billingModel == B_91_Android){
         
    }
    else {
        char musiName[30] ={0};
        sprintf(musiName, "homepage04%d.png",tempInde);
        normalSprite3 = CCSprite::createWithSpriteFrameName(musiName);
        closeMusicItem->setNormalImage(normalSprite3);
    }
  
    _isShowOpenVideo = false;
   
    ZPJNIHelper::sharedJNIHelper()->setVideoStatus();

}

void GMIntroLayer::showAllMenu(CCObject *pSender)
{
    _isClick = true;
    
    GMAudioPlay::sharedAudioPlay()->playAttackEffect(Audio_attack1);
    
    homeLayer->removeChild(menuSprite, true);
    homeLayer->removeChild(mainMenu1, true);
    homeLayer->removeChild(tipSprite, true);
    
    moveSprite = CCSprite::createWithSpriteFrameName("homepage021.png");
    GMPublicMethod::setSpriteAnimation(moveSprite, 21, 34, "homepage", this,callfuncN_selector(GMIntroLayer::overAnimation));
    moveSprite->setAnchorPoint(ccp(0, 0.5));
    moveSprite->setPosition(ccp(S_WINSIZE_W/2-80, S_WINSIZE_H/2-5));
    homeLayer->addChild(moveSprite,4);
    
    this->schedule(schedule_selector(GMIntroLayer::updateData), 0.05);
    
    countTime = 0;
}

void GMIntroLayer::overAnimation(CCNode *pNode)
{
    homeLayer->removeChild(moveSprite, true); 
}

void GMIntroLayer::updateData(float time)
{
    countTime++;
    if (countTime == 13) {
        this->unschedule(schedule_selector(GMIntroLayer::updateData));
        CCSprite *normalSprite1 = CCSprite::createWithSpriteFrameName("homepage002.png");
        CCProgressTimer *loadingMenu= CCProgressTimer::create(normalSprite1);
        //    SetScale1(loadingCt1);
        loadingMenu->setPosition(ccp(S_WINSIZE_W - Get_W(Get_Box(normalSprite1))/2-25,(S_WINSIZE_H)/2-15));
        loadingMenu->setType(kCCProgressTimerTypeBar);
        loadingMenu->setMidpoint(ccp(0.5, 0.5));
        loadingMenu->setBarChangeRate(ccp(0, 1));
        homeLayer->addChild(loadingMenu);
        
        loadingMenu->setPercentage(0);
        CCProgressTo* to = CCProgressTo::create(0.5,100);
//        CCActionInterval *action = CCRepeatForever::create(to);
        CCCallFuncN *callFun = CCCallFuncN::create(this, callfuncN_selector(GMIntroLayer::moveMenu));
        CCFiniteTimeAction *sequence = CCSequence::create(to,callFun,NULL);
        loadingMenu->runAction(sequence);
    }
}

void GMIntroLayer::moveMenu(CCNode *object)
{
    _isClick = false;
    CCProgressTimer *loadingMenu = (CCProgressTimer*)object;
    homeLayer->removeChild(loadingMenu, true);
    
    CCSprite *normalSprite1 = CCSprite::createWithSpriteFrameName("homepage002.png");
    CCSprite *selectedSprite1 = CCSprite::createWithSpriteFrameName("homepage002b.png");
    menuW = Get_W(Get_Box(normalSprite1));
    CCMenuItem *menuItem1 = CCMenuItemSprite::create(normalSprite1, selectedSprite1, this, menu_selector(GMIntroLayer::startGame));
    menuItem1->setTag(1);
    menuItem1->setPosition(ccp(S_WINSIZE_W - menuW/2-25,(S_WINSIZE_H)/2-15));
    
    CCSprite *normalSprite2 = CCSprite::createWithSpriteFrameName("homepage003.png");
    CCSprite *selectedSprite2 = CCSprite::createWithSpriteFrameName("homepage003b.png");
    CCMenuItem *menuItem2 = CCMenuItemSprite::create(normalSprite2, selectedSprite2, this, menu_selector(GMIntroLayer::startEndlessMode));
    menuItem2->setTag(2);
    menuItem2->setPosition(ccp(S_WINSIZE_W - menuW/2-25,(S_WINSIZE_H)/2-15));
    
    CCSprite *normalSprite3 = CCSprite::createWithSpriteFrameName("homepage004.png");
    CCSprite *selectedSprite3 = CCSprite::createWithSpriteFrameName("homepage004b.png");
    CCMenuItem *menuItem3 = CCMenuItemSprite::create(normalSprite3, selectedSprite3, this, menu_selector(GMIntroLayer::achievementLayer));
    menuItem3->setTag(3);
    menuItem3->setPosition(ccp(S_WINSIZE_W - menuW/2-25,(S_WINSIZE_H)/2-15));
    
    CCSprite *normalSprite4 = CCSprite::createWithSpriteFrameName("homepage005.png");
    CCSprite *selectedSprite4 = CCSprite::createWithSpriteFrameName("homepage005b.png");
    CCMenuItem *menuItem4 = CCMenuItemSprite::create(normalSprite4, selectedSprite4, this, menu_selector(GMIntroLayer::helpGame));
    menuItem4->setTag(4);
    menuItem4->setPosition(ccp(S_WINSIZE_W - menuW/2-25,(S_WINSIZE_H)/2-15));
    
    CCMenu *mainMenu = CCMenu::create(menuItem4,menuItem3,menuItem2,menuItem1,NULL);
//    mainMenu->setPosition(ccp(S_WINSIZE_W - Get_W(Get_Box(normalSprite1))/2-40, Get_H(Get_Box(normalSprite1))*3-10));
    mainMenu->setPosition(CCPointZero);

    homeLayer->addChild(mainMenu,3,MenuTag);
//    mainMenu->alignItemsVerticallyWithPadding(15);
    
    CCPoint point = ccp(S_WINSIZE_W - menuW/2-25,(S_WINSIZE_H)/2+40);
    CCMoveTo *moveTo1 = CCMoveTo::create(0.2, point);
	CCScaleTo *scaleTo1 = CCScaleTo::create(0.1, 1.2);
	CCSequence * seq1 = CCSequence::create(moveTo1, scaleTo1, NULL);
	this->choosedMenu = 1;
	menuItem1->runAction(seq1);
    
    point = ccp(S_WINSIZE_W - menuW/2-25,(S_WINSIZE_H)/2-35);
    CCMoveTo *moveTo2 = CCMoveTo::create(0.2, point);
    menuItem2->runAction(moveTo2);
    
    point = ccp(S_WINSIZE_W - menuW/2-25,(S_WINSIZE_H)/2-105);
    CCMoveTo *moveTo3 = CCMoveTo::create(0.2, point);
    menuItem3->runAction(moveTo3);
    
    point = ccp(S_WINSIZE_W - menuW/2-25,(S_WINSIZE_H)/2-175);
    CCMoveTo *moveTo4 = CCMoveTo::create(0.2, point);
//    CCCallFunc *callFunc = CCCallFunc::create(this, callfunc_selector(GMIntroLayer::moveTo));
//    CCAction *action = CCSequence::create(moveTo4,callFunc,NULL);

    menuItem4->runAction(moveTo4);
}

void GMIntroLayer::moveTo()
{
    CCMenu *temp = (CCMenu*)homeLayer->getChildByTag(MenuTag);
    
    CCObject *child;
    CCARRAY_FOREACH(temp->getChildren(),child){
        CCMenuItem *menuItem = (CCMenuItem*)child;
        if ( index < 4 &&menuItem->getTag() == 3) {
            index = 3;
            CCPoint point = ccp(S_WINSIZE_W - menuW/2-25,WINSIZE_H/2-10);
            CCMoveTo *moveTo3 = CCMoveTo::create(1, point);
            menuItem->runAction(moveTo3);
        }
        else if (menuItem->getTag() == 4) {
            index ++;
            CCPoint point;
            CCMoveTo *moveTo = NULL;
            CCCallFunc *callFunc = NULL;
            if (index == 4) {
                point = ccp(S_WINSIZE_W - menuW/2-25,WINSIZE_H/2-10);
                moveTo = CCMoveTo::create(0.5, point);
                callFunc = CCCallFunc::create(this, callfunc_selector(GMIntroLayer::moveTo));
            }
            else {
                point = ccp(S_WINSIZE_W - menuW/2-25,WINSIZE_H/2-70);
                moveTo = CCMoveTo::create(0.5, point);
            }
            CCAction *action = CCSequence::create(moveTo,callFunc,NULL);
            menuItem->runAction(action);
        }
    }
}

void GMIntroLayer::startGame(CCObject *pSender)
{
    _isClick = true;
    GMAudioPlay::sharedAudioPlay()->playButtonEffect();
    this->cleanup();
//    GMAccessData::saveBootModeStatus(1);
    int n = GMAccessData::sharedAccessData()->getBootModeStatus();
    
    GMPublicMethod::sharedPublicMethod()->setShow91Pause(false);
    
	n = 1;
    if (n==0) {
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID && JNIHELPER_INDEX != JNIHELPER_Telecom)
        GMAudioPlay::sharedAudioPlay()->stopBGMusic();
        GMPublicMethod::sharedPublicMethod()->setGameMode(Boot_Mode);
        CCScene *pScene = CCTransitionFade::create(0.0, GMMainLayer::scene(), ccWHITE);
        CCDirector::sharedDirector()->replaceScene(pScene);
//#endif
        
//#if ((JNIHELPER_INDEX == JNIHELPER_Telecom || JNIHELPER_INDEX == JNIHELPER_91_IOS) && JNIHELPER_INDEX!=JNIHELPER_91_Android)
//        GMPublicMethod::sharedPublicMethod()->setGameMode(Boot_Mode);
//        GMPublicMethod::sharedPublicMethod()->setGameStatus(None_Status);
//        CCScene *pScene = CCTransitionFade::create(0.0, GMCartoonLayer::scene(), ccWHITE);
////        CCScene *pScene = CCTransitionFade::create(0.0, GMMainLayer::scene(), ccWHITE);
//        CCDirector::sharedDirector()->replaceScene(pScene);
//#endif
    }
    else {
        GMPublicMethod::sharedPublicMethod()->setGameMode(Story_Mode);
        
        CCScene *pScene = CCTransitionFade::create(0.0, GMCardLayer::scene(), ccWHITE);
        CCDirector::sharedDirector()->replaceScene(pScene);
    }
}

void GMIntroLayer::startEndlessMode(CCObject *pSender)
{
    GMAudioPlay::sharedAudioPlay()->playButtonEffect();
    GMPublicMethod::sharedPublicMethod()->setShow91Pause(false);
    int b = GMAccessData::sharedAccessData()->getBootModeStatus();
    if((billingModel == B_TengXunBilling || billingModel== B_91_IOS || billingModel== B_91_Android ||
        billingModel == B_Unicom_Android)&& b == 0){//腾讯版本不用跳到引导关
        b = 1;
    }
    if (b ==0 ){
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID && JNIHELPER_INDEX != JNIHELPER_Telecom)
        GMAudioPlay::sharedAudioPlay()->stopBGMusic();
        
        GMPublicMethod::sharedPublicMethod()->setGameMode(Boot_Mode);
        CCScene *pScene = CCTransitionFade::create(0.0, GMMainLayer::scene(), ccWHITE);
        CCDirector::sharedDirector()->replaceScene(pScene);
#endif
        
#if (JNIHELPER_INDEX == JNIHELPER_Telecom)
        showDialogLayer();
#endif
    }
    else {
        int n = GMAccessData::sharedAccessData()->getEndlessModeStatus();
        CCScene *pScene = NULL;
        if (n==0) {
            int satatus = GMAccessData::sharedAccessData()->getGenuineValidationStatus();
            if((billingModel == B_YiDong || (billingModel == B_Telecom))&& satatus != 2){
                addBilling(1,1);
            }
            else{
                showDialogLayer();
            }
        }
        else {
//            if (billingModel == B_91_IOS) {
//                GMPublicMethod::sharedPublicMethod()->setGameMode(Endless_Mode);
//                pScene = CCTransitionFade::create(0.0, GMMainLayer::scene(), ccWHITE);
//                CCDirector::sharedDirector()->replaceScene(pScene);
//            }
//            else
            {
                int num = GMAccessData::sharedAccessData()->getEndlessModeNum();
                int satatus = GMAccessData::sharedAccessData()->getGenuineValidationStatus();
                if((billingModel == B_YiDong || billingModel == B_Telecom || billingModel == B_91_IOS || billingModel == B_91_Android) && satatus != 2){
                    addBilling(1,1);
                }
                else {
                    ZPLog("satatus %d",satatus);
                    if (billingModel!=B_Free && satatus != 2 && num == 1){
                        addBilling(1,1);
                    }
                    else if( satatus == 2 || num == 0){
                        GMPublicMethod::sharedPublicMethod()->setGameMode(Endless_Mode);
                        pScene = CCTransitionFade::create(0.0, GMMainLayer::scene(), ccWHITE);
                        CCDirector::sharedDirector()->replaceScene(pScene);
                    }
                }
            }
        }
    }
}

void GMIntroLayer::helpGame(CCObject *pSender)
{
    GMAudioPlay::sharedAudioPlay()->playButtonEffect();
//    
    GMHelpLayer *helpLayer = GMHelpLayer::create();
    this->addChild(helpLayer,20);
    helpLayer->_delegate = NULL;
    
}

void GMIntroLayer::cardGame(){
    CCScene *pScene = CCTransitionFade::create(0.0, GMCardLayer::scene(), ccWHITE);
    CCDirector::sharedDirector()->replaceScene(pScene);
}

void GMIntroLayer::winGame(){
    CCScene *pScene = CCTransitionFade::create(1.0, GMWinLayer::scene(), ccWHITE);
    CCDirector::sharedDirector()->replaceScene(pScene);
}

void GMIntroLayer::loseGame(){
    CCScene *pScene = CCTransitionFade::create(0.0, GMLoseLayer::scene(), ccWHITE);
    CCDirector::sharedDirector()->replaceScene(pScene);
}

void GMIntroLayer::achievementLayer(CCObject *pSender)
{
    GMAudioPlay::sharedAudioPlay()->playButtonEffect();
    GMAchievementLayer*achievemen = GMAchievementLayer::create();
//    achievementLayer->setBgColor( ccc3(0, 0, 0) ,125);
    this->addChild(achievemen,20);
}

void GMIntroLayer::pauseLayerGame(){
    CCScene *pScene = CCTransitionFade::create(0.0, GMPauseLayer::scene(), ccWHITE);
    CCDirector::sharedDirector()->replaceScene(pScene);
}

//#pragma mark - 91SDK
void GMIntroLayer::showMoreItem(){
  
    CCSprite *normalSprite = CCSprite::create("game/homepage042.png");
    CCSprite *selectedSprite = CCSprite::create("game/homepage043.png");
  
    CCMenuItemSprite *homepage042 = CCMenuItemSprite::create(normalSprite, selectedSprite, this, menu_selector(GMIntroLayer::set91SdkAction));
    SetScale2(homepage042, Scale_X);
    homepage042->setTag(1);
    homepage042->setAnchorPoint(ccp(0, 1));
    homepage042->setPosition(ccp(110*Scale_X,WINSIZE_H-10));
    
    CCSprite *normalSprite1 = CCSprite::create("game/homepage044.png");
    CCSprite *selectedSprite1 = CCSprite::create("game/homepage045.png");
    
    CCMenuItemSprite *homepage044 = CCMenuItemSprite::create(normalSprite1, selectedSprite1, this, menu_selector(GMIntroLayer::set91SdkAction));
    SetScale2(homepage044, Scale_X);
    homepage044->setTag(2);
    homepage044->setAnchorPoint(ccp(0, 1));
    homepage044->setPosition(ccp(210*Scale_X,WINSIZE_H-10));
    
    CCMenu *menu91 = CCMenu::create(homepage042,homepage044,NULL);
    menu91->setPosition(CCPointZero);
    this->addChild(menu91,3,MenuTag);
}

void GMIntroLayer::set91SdkAction(CCObject *pSender){

	CCMenuItemSprite *item = (CCMenuItemSprite *)pSender;
#if (JNIHELPER_INDEX == JNIHELPER_91_IOS)
    if(item->getTag() == 1){
       // PublicCPP::showForum(1);
    }
    else {
        //PublicCPP::showForum(2);
    }
#endif
    
#if (JNIHELPER_INDEX == JNIHELPER_91_Android)
    ZPLog("set91SdkAction");
    GMPublicMethod::sharedPublicMethod()->setShow91Pause(false);

    if(item->getTag() == 1){
        ZPJNIHelper::setShowBBS();
    }
    else {
        ZPJNIHelper::showSocial();
    } 
#endif
}

//#pragma mark - Dialog


void GMIntroLayer::showQQLogoDialogLayer(int type){
    if(GMPublicMethod::sharedPublicMethod()->getShowLogo() == false){
        ZPDialogLayer *dialogLayer = ZPDialogLayer::create();
        dialogLayer->initQQLogoView(type);
        this->addChild(dialogLayer,100,1001);
        float tempD = 3.0;
        if(type==1)
            tempD = 6;
        this->scheduleOnce(schedule_selector(GMIntroLayer::removeQQLogoLayer), tempD);
        GMPublicMethod::sharedPublicMethod()->setShowLogo(true);
    }
}

void GMIntroLayer::removeQQLogoLayer(float dt){
    ZPDialogLayer *dialogLayer = (ZPDialogLayer*)this->getChildByTag(1001);
    if(dialogLayer){
        this->removeChild(dialogLayer,true);
        dialogLayer = NULL;
        
        showOpenMusicDialogLayer();
    }
}

void GMIntroLayer::showOpenMusicDialogLayer()
{
    if(GMPublicMethod::sharedPublicMethod()->getOpenMusic()==false){
        ZPDialogLayer *dialogLayer = ZPDialogLayer::create();
        dialogLayer->setSelectorTarget(this);
        dialogLayer->setSELMenuHandler(menu_selector(GMIntroLayer::openMusic));
        dialogLayer->setSELMenuHandler3(menu_selector(GMIntroLayer::closeMusic));
        dialogLayer->initSoundView();
        this->addChild(dialogLayer,100,1000);
        if(billingModel == B_YiDong || billingModel==B_91_Android){}
        else {
            GMPublicMethod::sharedPublicMethod()->setOpenMusic(true);
        }
        _isShowOpenVideo = true;
    }
    else {
         GMPublicMethod::sharedPublicMethod()->setGameStatus(Home_Status);
    }
}

void GMIntroLayer::openMusic(CCObject *pSender)
{
    ZPDialogLayer *dialogLayer = (ZPDialogLayer*)this->getChildByTag(1000);
    if (dialogLayer) {
        this->removeChild(dialogLayer, true);
    }
//    GMAccessData::saveAudioStatus(1);
    GMPublicMethod::sharedPublicMethod()->setAudioStatus(1);
//    GMAudioPlay::sharedAudioPlay()->setCloseStatus();
//    GMAudioPlay::sharedAudioPlay()->playBGMusic(Audio_Home);
    
    closeMusicAtion(NULL);
//    showMusic();
    
//    FILE  *fp = fopen(CCUserDefault::sharedUserDefault()->getXMLFilePath().c_str(), "r");
//    bool bRet = false;
//    if (fp){
//        bRet = true;
//        clearerr(fp);
//        CCUserDefault::purgeSharedUserDefault();
//    }
}
void GMIntroLayer::closeMusic(CCObject *pSender)
{
    ZPDialogLayer *dialogLayer = (ZPDialogLayer*)this->getChildByTag(1000);
    if (dialogLayer) {
        this->removeChild(dialogLayer, true);
    }
//    GMAccessData::saveAudioStatus(2);
    GMPublicMethod::sharedPublicMethod()->setAudioStatus(2);
//    GMAudioPlay::sharedAudioPlay()->setCloseStatus();
//    GMAudioPlay::sharedAudioPlay()->playBGMusic(Audio_Home);
    closeMusicAtion(NULL);
//    showMusic();
}

void GMIntroLayer::showDialogLayer()
{
    if(isShowDialogLayer  == false){
        ZPDialogLayer *dialogLayer = ZPDialogLayer::create();
        dialogLayer->initView("game/gamegoal000.png", NULL);
        dialogLayer->addPromptTexture("game/gamegoal016.png");
        dialogLayer->setSelectorTarget(this);
        dialogLayer->setSELCallFun(callfuncN_selector(GMIntroLayer::removeDialogLayer));
        dialogLayer->setAnimation(true,1.5);
        this->addChild(dialogLayer,10);
        isShowDialogLayer = true;
    }
}

void GMIntroLayer::removeDialogLayer(CCNode *dialog)
{
    ZPDialogLayer *dialogLayer = (ZPDialogLayer*)dialog;
    this->removeChild(dialogLayer, true);
    isShowDialogLayer = false;
}

//#pragma mark - 
void GMIntroLayer::addchangeboom(){
    if(isLoadT){
        CCAddSpriteFramesAndTextureFile(changeboom_plist,changeboom_png);
        isLoadT = false;
    }
}
//#pragma mark -  计费
//1 为正版验证，2为购买能量，3为购买技能，4为购买武器
void GMIntroLayer::addBilling(int index,int index2){
    
    if(billingModel == B_YiDong){
        if(!_isShowYiDong)
            showYidongSdkView(index);
    }
    else if(billingModel == B_Telecom){
        if(!_isShowYiDong)
            showTelecomSMSView(index);
    }
    else if(billingModel == B_91_Android && index == 1){
        ZPJNIHelper::setAllPay(6);
        this->schedule(schedule_selector(GMIntroLayer::check91BillingPoint));
    }
    else {
        //#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        GMBillingLayer *billingLayer = GMBillingLayer::create();
        billingLayer->setDelegate(this);
        billingLayer->setIndex(index);
        billingLayer->setStartBliling(false);
        billingLayer->setClassType(4);
        switch (index) {
            case 1:{
                if(billingModel == B_YiDong){
                    addchangeboom();
                    billingLayer->showGenuineValidationTips();
                }
                else if(billingModel == B_91_IOS){
#if (JNIHELPER_INDEX == JNIHELPER_91_IOS)
//                    if(PublicCPP::getMobileBilling()){
//                        GMPublicMethod::sharedPublicMethod()->setBillingIndex(6);
//                        billingLayer->show91MobileView();
//                    }
//                    else
                    {
                        addchangeboom();
                        billingLayer->showGenuineValidationTips();
                    }
#endif
                }
                else {
//                    addchangeboom();
//                    billingLayer->showGenuineValidationTips();
//                    腾讯的暂时注释2次确认
                    billingLayer->showSecondaryConfirmationTips(0);
                }
            }   break;
    //        case 2:{
    //            billingLayer->showThePurchaseOfEnergy(1,1);
    //        }   break;
            case 6:{
    //            billingLayer->showSecondaryConfirmationTips(0);
                addchangeboom();
                billingLayer->setStartBliling(true);
                billingLayer->showGenuineValidationTips();
            }   break;
            case 8:{
                billingLayer->show91MobileView2();
            }   break;
            default:
                break;
        }
        this->addChild(billingLayer,2222,Billing_tag);
    //#endif
    }
}

//#pragma mark - 电信计费相关的方法
void GMIntroLayer::showTelecomSMSView(int _index){
    switch (_index) {
        case 1:{
            _isShowYiDong = true;
            ZPJNIHelper::sendSMSBillingPoint(1);
            this->schedule(schedule_selector(GMIntroLayer::checkBillingPoint));
        } break;
            
        default:
            break;
    }
}

//#pragma mark - 移动 网乐

void GMIntroLayer::checkMusicAction(float dt){
    
    ZPLog("checkMusicAction");
    ZPLog("checkMusicAction");
    
    if(ZPJNIHelper::getMusicEnabled()){
        GMPublicMethod::sharedPublicMethod()->setAudioStatus(1);
    }
    else {
        GMPublicMethod::sharedPublicMethod()->setAudioStatus(2);
    }
    
    closeMusicAtion(NULL);

    this->unschedule(schedule_selector(GMIntroLayer::checkMusicAction));
}

void GMIntroLayer::showYidongSdkView(int index){
    switch (index) {
        case 1:{
            _isShowYiDong = true;
            ZPJNIHelper::setYiDongBilling(1);
            this->schedule(schedule_selector(GMIntroLayer::checkBillingPoint));
        } break;
            
        default:
            break;
    }
}

void GMIntroLayer::removeBilling(int index,bool _isClickClose){
#if (JNIHELPER_INDEX == JNIHELPER_91_IOS)
    if( _isClickClose /*|| PublicCPP::getMobileBilling()*/)
#endif
    {
        GMBillingLayer *tempBillingLayer = (GMBillingLayer*)this->getChildByTag(Billing_tag);
        this->removeChild(tempBillingLayer, true);
    }
    
    if(_isClickClose==false){
        switch (index) {
            case 1:{
                if(_isClickClose==false){
                    if(billingModel == B_YiDong){
                        ZPJNIHelper::setYiDongBilling(1);
                        this->schedule(schedule_selector(GMIntroLayer::checkBillingPoint));
                    }
                    else if (billingModel == B_91_IOS) {
#if (JNIHELPER_INDEX == JNIHELPER_91_IOS)
//                        if(PublicCPP::getMobileBilling()){
//                            addBilling(8,0);
//                        }
//                        else
                        {
                            //PublicCPP::paymentAll(6);
                            this->schedule(schedule_selector(GMIntroLayer::check91BillingPoint));
                        }
#endif
                    }
                    else if(billingModel == B_Unicom_Android && index == 1){
                        ZPJNIHelper::sendSMSBillingPoint(1);
                        this->schedule(schedule_selector(GMIntroLayer::checkBillingPoint));
                    }
                    else {
//                       腾讯的暂时注释2次确认
//                        if(billingModel == B_TengXunBilling){
//                            ZPJNIHelper::sendSMSBillingPoint(1);
//                            this->schedule(schedule_selector(GMIntroLayer::checkBillingPoint));
//                        }
                        GMAccessData::sharedAccessData()->saveGenuineValidationStatus(1);
                        addBilling(6,0);
                    }
                }
            }   break;
            case 6:{
                if(_isClickClose==false){
                    if(billingModel == B_TengXunBilling){
                        ZPJNIHelper::sendSMSBillingPoint(1);
                        this->schedule(schedule_selector(GMIntroLayer::checkBillingPoint));
                    }
                }
            }   break;
            case 8:{
                this->schedule(schedule_selector(GMIntroLayer::check91BillingPoint));
            }   break;
            default:
                break;
        }
    }
}

void GMIntroLayer::checkBillingPoint(float dt){
    int status = ZPJNIHelper::getSendSMSBillingPointStatus();
    ZPLog("GMIntroLayer getSendSMSBillingPointStatus %d",status);
    if(status != 0){
        if(status == 1){
            int index = ZPJNIHelper::getBillingIndex();
            if(index == 1){
                GMAccessData::sharedAccessData()->saveGenuineValidationStatus(2);
                int money = GMAccessData::sharedAccessData()->getTotalMoneyNum();
                money += 5000;
                GMAccessData::sharedAccessData()->saveTotalMoneyNum(money);
                
                int num = GMAccessData::sharedAccessData()->getSkillBloodNum();
                num = num+5;
                GMAccessData::sharedAccessData()->saveSkillBloodNum(num);
                ZPLog("GMIntroLayer 正版验证计费  计费索引 1");
            }
        }
        
        _isShowYiDong = false;
        
        ZPJNIHelper::setSMSBillingPointStatus(); //将状态付值为0 (腾讯 移动 通用方法)
        this->unschedule(schedule_selector(GMIntroLayer::checkBillingPoint));
    }
}

//检测移动退出状态
void GMIntroLayer::checkYiDongExitStatus(float t){
    
    int status = ZPJNIHelper::getExitStatus();
    ZPLog("checkYiDongExitStatus %d",status);
    if(status != 0){
        if(status == 2){
            CCDirector::sharedDirector()->end();
            exit(0);
        }
        ZPJNIHelper::setExitStatus();
        this->unschedule(schedule_selector(GMIntroLayer::checkYiDongExitStatus));
    }
}

void GMIntroLayer::saveMoney(int money){
    int tempM = GMAccessData::sharedAccessData()->getTotalMoneyNum();
    tempM+=money;
    GMAccessData::sharedAccessData()->saveTotalMoneyNum(tempM);
}
void GMIntroLayer::setAllSkillNum(){
    int num = GMAccessData::sharedAccessData()->getSkillBloodNum();
    num += 5;
    GMAccessData::sharedAccessData()->saveSkillBloodNum(num);
    num = GMAccessData::sharedAccessData()->getSkillPaysNum();
    num += 5;
    GMAccessData::sharedAccessData()->saveSkillPaysNum(num);
}

void GMIntroLayer::check91BillingPoint(float dt){
    
    int tempStatus = 0;
    int tempInde = 0;
//#if (JNIHELPER_INDEX == JNIHELPER_91_IOS)
//    tempStatus = PublicCPP::getPaymentSuccess();
//    tempInde = PublicCPP::getBillingIndex();
//#endif
#if (JNIHELPER_INDEX == JNIHELPER_91_Android)
    tempStatus = ZPJNIHelper::getSendSMSBillingPointStatus();
    tempInde = ZPJNIHelper::getBillingIndex();
#endif
    
    ZPLog("PaymentSuccess = %d",tempStatus);
    ZPLog("tempInde = %d",tempInde);
    if(tempStatus != 0){

        if(tempStatus==1){
            if(tempInde == 1){//特殊道具（技能）
                setAllSkillNum();
            }
            else if(tempInde == 2){//购买能量 （5000）
                saveMoney(5000);
            }
            else if(tempInde == 3){//购买能量 （13000)
                saveMoney(13000);
            }
            else if(tempInde == 4){//购买能量 （40000）
                saveMoney(40000);
            }
            else if(tempInde == 5){//升级武器
                GMAccessData::sharedAccessData()->saveOpenCannonLeve(6);
            }
            else if(tempInde == 6){
                if(ZPJNIHelper::getOperators() == 1){
                    int tempM = GMAccessData::sharedAccessData()->getTotalMoneyNum();
                    tempM += 13000;
                    GMAccessData::sharedAccessData()->saveTotalMoneyNum(tempM);
                }
                
                GMAccessData::sharedAccessData()->saveGenuineValidationStatus(2);
            }
//#if (JNIHELPER_INDEX == JNIHELPER_91_IOS)
//            PublicCPP::removeRecord(tempInde);
//#endif
        }
        else if(tempStatus==2){
            if(tempInde == 6){
                GMAccessData::sharedAccessData()->saveGenuineValidationStatus(0);
            }
//#if (JNIHELPER_INDEX == JNIHELPER_91_IOS)
//            if(PublicCPP::getLoginedStatus())
//                PublicCPP::messageBox();
//#endif
        }
//#if (JNIHELPER_INDEX == JNIHELPER_91_IOS) 
//        PublicCPP::setPaymentSuccess(0);
//#endif
        this->unschedule(schedule_selector(GMIntroLayer::check91BillingPoint));
        
        GMBillingLayer *tempBillingLayer = (GMBillingLayer*)this->getChildByTag(Billing_tag);
        this->removeChild(tempBillingLayer, true);
    }

}

//#pragma mark - Android back action

void GMIntroLayer::keyBackClicked(){
    ZPLog("GMIntroLayer::keyBackClicked");
    if(_isShowOpenVideo || _isClick)
        return;
//    exitLayer = GMNoTouchLayer::create();
//    if (exitLayer) {
//        exitLayer->setContentSize(CCSize(WINSIZE_W,WINSIZE_H));
//        this->addChild(exitLayer,22);
//    }
    
    ZPLog("GMIntroLayer::keyBackClicked 3");
    
    if(billingModel == B_YiDong){
        this->unschedule(schedule_selector(GMIntroLayer::checkYiDongExitStatus));
        this->schedule(schedule_selector(GMIntroLayer::checkYiDongExitStatus));
        ZPJNIHelper::setExitGame();
    }
    else if(billingModel == B_91_Android){
        setGameOver();
    }
    else {
        exitLayer = GMNoTouchLayer::create();
        if (exitLayer) {
            exitLayer->setContentSize(CCSize(WINSIZE_W,WINSIZE_H));
            this->addChild(exitLayer,22);
        }
        
        CCSprite *exitBG = CCSprite::create("game/gamegoal000.png");
        SetScale2(exitBG, Scale_X);
        exitBG->setPosition(ccp(WINSIZE_W/2, WINSIZE_H/2));
        exitLayer->addChild(exitBG);
        
        float tempW = Get_W(Get_Rect(exitBG));
        float tempH = Get_H(Get_Rect(exitBG));
        CCSprite *title = CCSprite::createWithSpriteFrameName("exit002.png");
        title->setPosition(ccp(tempW/2, tempH/2 + Get_H(Get_Rect(title))/2));
        exitBG->addChild(title);
        
        CCSprite *normalSpriteOK = CCSprite::createWithSpriteFrameName("gamegoal004.png");
        CCSprite *selectedSpriteOK = CCSprite::createWithSpriteFrameName("gamegoal005.png");
        CCMenuItem *menuItem1 = CCMenuItemSprite::create(normalSpriteOK, selectedSpriteOK, this, menu_selector(GMIntroLayer::confirmAtion));
        menuItem1->setTag(1);
        menuItem1->setAnchorPoint(ccp(0,0));
        menuItem1->setPosition(ccp(20,20));
        
        CCSprite *normalSprite1 = CCSprite::createWithSpriteFrameName("exit005.png");
        CCSprite *selectedSprite1 = CCSprite::createWithSpriteFrameName("exit006.png");
        CCMenuItem *cancel = CCMenuItemSprite::create(normalSprite1, selectedSprite1, this, menu_selector(GMIntroLayer::cancelAtion));
        cancel->setTag(2);
        cancel->setAnchorPoint(ccp(1,0));
        cancel->setPosition(ccp(tempW-20,20));
        
        CCMenu *mainMenu = CCMenu::create(menuItem1,cancel,NULL);
        mainMenu->setPosition(CCPointZero);
        exitBG->addChild(mainMenu,3,MenuTag);
        _isShowOpenVideo = true;

    }

    ZPLog("GMIntroLayer::keyBackClicked  2");
}

void GMIntroLayer::confirmAtion(CCObject *pSender)
{
    CCDirector::sharedDirector()->end();
    //#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
    //#endif
    _isShowOpenVideo = false;
}

void GMIntroLayer::cancelAtion(CCObject *pSender)
{
    exitLayer->removeTouchDelegate();
    this->removeChild(exitLayer, true);
    exitLayer = NULL;
    
    _isShowOpenVideo = false;
}

GMIntroLayer::~GMIntroLayer()
{
//    this->unschedule(schedule_selector(GMIntroLayer::update));
    //this->unschedule(schedule_selector(GMIntroLayer::startGame));
    //this->unschedule(schedule_selector(GMIntroLayer::helpGame));
    //this->unschedule(schedule_selector(GMIntroLayer::cardGame));
    
//    CCRemoveSpriteFrameByName(homepage_plist);
//    CCRemoveSpriteFrameByName(homepage_plist1);
    CCRemoveSpriteFramesAndTextureForKey(homepage_plist,homepage_png);
//    CCRemoveTextureForKey(homepage_png);
//    CCRemoveTextureForKey(homepage_png1);
    CCRemoveSpriteFramesAndTextureForKey(homepage_plist1,homepage_png1);
//    this->removeChild(homeBatchNode, true);
//    this->removeChild(homepageNode, true);
   
    CCRemoveSpriteFramesAndTextureForKey(gamegoal_plist,gamegoal_png);
    CCRemoveSpriteFramesAndTextureForKey(changeboom_plist,changeboom_png);

	GMPublicMethod::sharedPublicMethod()->tempLayer = NULL;
    this->cleanup();
    
}
