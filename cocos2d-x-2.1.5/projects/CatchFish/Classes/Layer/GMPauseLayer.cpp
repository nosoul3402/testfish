//
//  GMPauseLayer.cpp
//  FishX
//
//  Created by peng on 12-12-24.
//
//

#include "GMPauseLayer.h"
#include "GMCardLayer.h"
#include "GMIntroLayer.h"
#include "GMMainLayer.h"
#include "../Config/GMHeaderConfig.h"
#include "../PublicModels/ZPJNIHelper.h"


//#pragma mark - GMLoseLayer

CCScene* GMPauseLayer::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    GMPauseLayer *layer = GMPauseLayer::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

GMPauseLayer::GMPauseLayer()
{
    
}

// on "init" you need to initialize your instance
bool GMPauseLayer::init()
{
    if ( !CCLayerColor::init() )
    {
        return false;
    }
    
    CCAddSpriteFramesWithFile(pause_plist);
    pauseBatchNode = CCSpriteBatchNode::create(pause_png);
    this->addChild(pauseBatchNode);
    
    this->setColor(ccc3(0, 0, 0));
    this->setOpacity(220);
    
    exitLayer = NULL;
    initElement();
    isOpenVideo = true;
    isShowHelp = false;
    return true;
}

void GMPauseLayer::initElement()
{
    CCSprite *bg1 = CCSprite::create("pause/purse01.png");
    bg1->setPosition(ccp(WINSIZE_W/2, WINSIZE_H/2));
    CCRect bgRect = Get_Rect(bg1);
    SetScale2(bg1,Scale_X);
    this->addChild(bg1);
    
   GameMode pauseGameMode = GMPublicMethod::sharedPublicMethod()->getGameMode();
    
    CCArray *array = CCArray::create();
    //选择关卡
    CCSprite *normalSprite6 = NULL;
    CCSprite* selectedSprite7 = NULL;
    CCMenuItem *item1 = NULL;
    if (pauseGameMode == Boot_Mode) {
        normalSprite6 = CCSprite::createWithSpriteFrameName("purse07.png");
        item1 = CCMenuItemSprite::create(normalSprite6, NULL, this, menu_selector(GMPauseLayer::chooseCard));
        item1->setEnabled(false);
    }
    else {
        normalSprite6 = CCSprite::createWithSpriteFrameName("purse06.png");
        selectedSprite7 = CCSprite::createWithSpriteFrameName("purse07.png");
        item1 = CCMenuItemSprite::create(normalSprite6, selectedSprite7, this, menu_selector(GMPauseLayer::chooseCard));
    }
    item1->setPosition(ccp(WINSIZE_W/2, WINSIZE_H/2));
    array->addObject(item1);
    //继续
    CCSprite *normalSprite4 = CCSprite::createWithSpriteFrameName("purse04.png");
    CCSprite* selectedSprite5 = CCSprite::createWithSpriteFrameName("purse05.png");
    CCMenuItem *item2 = CCMenuItemSprite::create(normalSprite4, selectedSprite5, this, menu_selector(GMPauseLayer::continueTheGame));
    array->addObject(item2);
    
    GMBillingModel billingModel= GMPublicMethod::sharedPublicMethod()->getBillingModel();
   
    
    if(billingModel==B_91_IOS || billingModel == B_91_Android){
        CCSprite *normalSprite3 = CCSprite::create("pause/purse03.png");
        CCSprite *selectedSprite3 = CCSprite::create("pause/purse04.png");
        item3 = CCMenuItemSprite::create(normalSprite3, selectedSprite3, this, menu_selector(GMPauseLayer::enterFeedback));
    }
    else {
        CCSprite *normalSprite3 = NULL;
        //开启/关闭 声音
        int closeStatus = GMPublicMethod::sharedPublicMethod()->getAudioStatus();//GMAccessData::getAudioStatus();
        if (closeStatus==2) {
            normalSprite3 = CCSprite::createWithSpriteFrameName("purse03.png");
        }
        else if (closeStatus == 1)  {
            normalSprite3 = CCSprite::createWithSpriteFrameName("purse02.png");
        }
        item3 = CCMenuItemSprite::create(normalSprite3, NULL, this, menu_selector(GMPauseLayer::videoAction));
    }
    item3->retain();
    array->addObject(item3);
    //游戏帮助
    CCSprite *normalSprite8 = CCSprite::createWithSpriteFrameName("purse08.png");
    CCSprite* selectedSprite9 = CCSprite::createWithSpriteFrameName("purse09.png");
    CCMenuItem *item4 = CCMenuItemSprite::create(normalSprite8, selectedSprite9, this, menu_selector(GMPauseLayer::helpAction));
    array->addObject(item4);
    //重新开始
    CCSprite *normalSprite12 = CCSprite::createWithSpriteFrameName("purse12.png");
    CCSprite* selectedSprite13 = CCSprite::createWithSpriteFrameName("purse13.png");
    CCMenuItem *item5 = CCMenuItemSprite::create(normalSprite12, selectedSprite13, this, menu_selector(GMPauseLayer::againAction));
    array->addObject(item5);
    //返回
    CCSprite *normalSprite10 = CCSprite::createWithSpriteFrameName("purse10.png");
    CCSprite* selectedSprite11 = CCSprite::createWithSpriteFrameName("purse11.png");
    CCMenuItem *item6 = CCMenuItemSprite::create(normalSprite10, selectedSprite11, this, menu_selector(GMPauseLayer::backAction));
    array->addObject(item6);
    
    menu = CCMenu::createWithArray(array);
    menu->setPosition(CCPointZero);
    bg1->addChild(menu);
    
/////////////////////////////////////////////////////////////////
    //重新布置位置
    int i=0;
    CCPoint point = ccp(Get_W(bgRect)/2+10,Get_H(bgRect)/2);
    ZPLog("%f",point.x)
    CCObject *child;
    float tempW = 164;
    float tempH = 60;
    CCARRAY_FOREACH(menu->getChildren(),child){
        CCMenuItem*temp = (CCMenuItem*)child;
        CCPoint dstPoint = temp->getPosition();
        int x = i%2;
        int y = i/2;
        CCPoint point1;
        if (y==0) {
            point1 = ccp(point.x+(x*2-1)*(tempW/2+20),point.y+(1-y)*(tempH+5));
        }
        else if (y==1){
            point1 = ccp(point.x+(x*2-1)*(tempW/2+20),point.y-10);
        }
        else if (y==2){
            point1 = ccp(point.x+(x*2-1)*(tempW/2+20),point.y+(1-y)*(tempH+25));
        }
        temp->setPosition( point1 );
//        SetScale2(temp,Scale2);
        i++;
    }
/////////////////////////////////////////////////////////////////
    
    
}

void GMPauseLayer::chooseCard(CCObject *pSender)
{
    GMAudioPlay::sharedAudioPlay()->playButtonEffect();
    GMAudioPlay::sharedAudioPlay()->stopBGMusic();
    continueTheGame(NULL);
    
    ((GMGameLayer*)delegateGame)->cleanup();
    ((GMGameLayer*)delegateGame)->unscheduleGame();
    
    CCScene *pScene = CCTransitionFade::create(0.0, GMCardLayer::scene(), ccWHITE);
    CCDirector::sharedDirector()->replaceScene(pScene);
//    tempGameLayer-> chooseCardLaye();
}

void GMPauseLayer::removeTouchDelegate()
{
    CCDirector::sharedDirector()->resume();
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
    this->removeAllChildrenWithCleanup(true);
}

void GMPauseLayer::continueTheGame(CCObject *pSender){
    
    GMAudioPlay::sharedAudioPlay()->playButtonEffect();
    
    removeTouchDelegate();
    
    this->setColor(ccc3(0, 0, 0));
    this->setOpacity(0);
    
    GMGameLayer *temp = (GMGameLayer*)delegateGame;
    temp->continueGame();
//    CC_SAFE_DELETE(this);
}

void GMPauseLayer::enterFeedback(CCObject *pSender){
#if (JNIHELPER_INDEX == JNIHELPER_91_IOS)
    //PublicCPP::enterFeedback();
#endif
    
#if (JNIHELPER_INDEX == JNIHELPER_91_Android)
    ZPJNIHelper::showEnterFeedback();
#endif
    
    
}

void GMPauseLayer::videoAction(CCObject *pSender)
{
    GMAudioPlay::sharedAudioPlay()->playButtonEffect();

    CCSprite *normalSprite3 = NULL;
    int closeStatus = GMPublicMethod::sharedPublicMethod()->getAudioStatus();//GMAccessData::getAudioStatus();
    if (closeStatus == 2 || closeStatus == 0) {
        normalSprite3 = CCSprite::createWithSpriteFrameName("purse02.png");
//        GMAccessData::saveAudioStatus(1);
        GMPublicMethod::sharedPublicMethod()->setAudioStatus(1);
    }
    else if (closeStatus == 1) {
        normalSprite3 = CCSprite::createWithSpriteFrameName("purse03.png");
//        GMAccessData::saveAudioStatus(2);
        GMPublicMethod::sharedPublicMethod()->setAudioStatus(2);
    }
    item3->setNormalImage(normalSprite3);
    
    GMAudioPlay::sharedAudioPlay()->setCloseStatus();
    GMAudioPlay::sharedAudioPlay()->playBGMusic(Audio_Gmae1);
    
//    ZPJNIHelper::setVideoStatus();
    ZPJNIHelper::sharedJNIHelper()->setVideoStatus();
}


void GMPauseLayer::helpAction(CCObject *pSender)
{
    GMAudioPlay::sharedAudioPlay()->playButtonEffect();
//    GMAudioPlay::sharedAudioPlay()->stopBGMusic();
    
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
    
//    CCScene *pScene = CCTransitionFade::create(0.0, GMHelpLayer::scene(), ccWHITE);
//    CCDirector::sharedDirector()->replaceScene(pScene);
    
    helpLayer = GMHelpLayer::create();
    this->addChild(helpLayer,20);
    helpLayer->_delegate = this;
    
    isShowHelp = true;
}

void GMPauseLayer::closeHelpAction()
{
    isShowHelp = false;
    
    helpLayer->removeHelpTouchDelegate();
    this->removeChild(helpLayer, true);
    helpLayer = NULL;
    
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, kCCMenuHandlerPriority - 1, true);
    
}


void GMPauseLayer::againAction(CCObject *pSender)
{
    GMAudioPlay::sharedAudioPlay()->stopBGMusic();
    GMAudioPlay::sharedAudioPlay()->stopMyAllEffects();
    GMAudioPlay::sharedAudioPlay()->playButtonEffect();
    
    continueTheGame(NULL);
    ((GMGameLayer*)delegateGame)->cleanup();
    ((GMGameLayer*)delegateGame)->unscheduleGame();
    CCScene *pScene = CCTransitionFade::create(0.0, GMMainLayer::scene(), ccWHITE);
    CCDirector::sharedDirector()->replaceScene(pScene);
}

void GMPauseLayer::backAction(CCObject *pSender)
{
    //CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID &&
    GMAudioPlay::sharedAudioPlay()->playButtonEffect();
#if(JNIHELPER_INDEX == JNIHELPER_YiDong)
    setExitLayer();
#endif
    
#if (JNIHELPER_INDEX != JNIHELPER_YiDong)
    confirmAtion(NULL);
#endif
    
}

//#pragma mark - 返回首页二级菜单

void GMPauseLayer::setExitLayer(){
    
    if (exitLayer==NULL) {
        
        CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
        
        exitLayer = GMNoTouchLayer::create();
        exitLayer->setContentSize(CCSize(WINSIZE_W,WINSIZE_H));
        this->addChild(exitLayer,29);
        
        CCSprite *exitBG = CCSprite::create("game/gamegoal000.png");
        SetScale2(exitBG, Scale_X);
        exitBG->setPosition(ccp(WINSIZE_W/2, WINSIZE_H/2));
        exitLayer->addChild(exitBG);
        
        float tempW = Get_W(Get_Rect(exitBG));
        float tempH = Get_H(Get_Rect(exitBG));
        CCSprite *title = CCSprite::create("exit002.png");
        title->setPosition(ccp(tempW/2, tempH/2 + Get_H(Get_Rect(title))/2));
        exitBG->addChild(title);
        
        CCSprite *normalSpriteOK = CCSprite::create("exit003.png");
        CCSprite *selectedSpriteOK = CCSprite::create("exit004.png");
        CCMenuItem *menuItem1 = CCMenuItemSprite::create(normalSpriteOK, selectedSpriteOK, this, menu_selector(GMPauseLayer::confirmAtion));
        menuItem1->setTag(1);
        menuItem1->setAnchorPoint(ccp(0,0));
        menuItem1->setPosition(ccp(20,20));
        
        CCSprite *normalSprite1 = CCSprite::create("exit005.png");
        CCSprite *selectedSprite1 = CCSprite::create("exit006.png");
        CCMenuItem *cancel = CCMenuItemSprite::create(normalSprite1, selectedSprite1, this, menu_selector(GMPauseLayer::cancelAtion));
        cancel->setTag(2);
        cancel->setAnchorPoint(ccp(1,0));
        cancel->setPosition(ccp(tempW-20,20));
        
        CCMenu *mainMenu = CCMenu::create(menuItem1,cancel,NULL);
        mainMenu->setPosition(CCPointZero);
        exitBG->addChild(mainMenu);
    }    
//    _isShowOpenVideo = true;

}

void GMPauseLayer::confirmAtion(CCObject *object){
    
    ZPLog("confirmAtion");
    
    if(exitLayer){
        exitLayer->removeTouchDelegate();
        this->removeChild(exitLayer, true);
        exitLayer = NULL;
    }
    
    GMAudioPlay::sharedAudioPlay()->stopBGMusic();
    continueTheGame(NULL);
    
    ((GMGameLayer*)delegateGame)->cleanup();
    ((GMGameLayer*)delegateGame)->unscheduleGame();
    
    CCScene *pScene = CCTransitionFade::create(0.0, GMIntroLayer::scene(), ccWHITE);
    CCDirector::sharedDirector()->replaceScene(pScene);
}

void GMPauseLayer::cancelAtion(CCObject *object){
    
    if(exitLayer){
        exitLayer->removeTouchDelegate();
        this->removeChild(exitLayer, true);
        exitLayer = NULL;
    }
}

//#pragma mark -

GMPauseLayer::~GMPauseLayer()
{
    this->setColor(ccc3(0, 0, 0));
    this->setOpacity(0);
    item3->release();
    
    CCRemoveSpriteFrameByName(pause_plist);
    
    CCRemoveTextureForKey(pause_png);
    this->removeChild(pauseBatchNode, true);

    this->cleanup();
    ZPLog("~GMPauseLayer");
}

//#pragma mark - 重构

void GMPauseLayer::onEnter()
{
    CCLayer::onEnter();
//    CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate(this, kCCMenuHandlerPriority - 1, true);
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, kCCMenuHandlerPriority - 1, true);
}

void GMPauseLayer::onExit()
{
    CCLayer::onExit();
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
}

bool GMPauseLayer::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    m_bTouchedMenu = menu->ccTouchBegan(pTouch, pEvent);
    
    return true;
}

void GMPauseLayer::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    if (m_bTouchedMenu) {
        menu->ccTouchMoved(pTouch, pEvent);
    }
}

void GMPauseLayer::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    if (m_bTouchedMenu) {
        menu->ccTouchEnded(pTouch, pEvent);
        m_bTouchedMenu = false;
    }
}

void GMPauseLayer::ccTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    if (m_bTouchedMenu) {
        menu->ccTouchEnded(pTouch, pEvent);
        m_bTouchedMenu = false;
    }
}

