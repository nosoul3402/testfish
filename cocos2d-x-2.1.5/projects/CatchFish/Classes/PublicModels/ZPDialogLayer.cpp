//
//  ZPDialogLayer.cpp
//  FishX
//
//  Created by peng on 13-4-19.
//
//

#include "ZPDialogLayer.h"
#include "../Config/GMHeaderConfig.h"
#include "UIRollNum.h"

ZPDialogLayer::ZPDialogLayer():tempColor(NULL),bgSprite(NULL)
{
}

ZPDialogLayer::~ZPDialogLayer()
{
}

bool ZPDialogLayer::init()
{
    bool bRet = false;
    
    do {
        CC_BREAK_IF(!CCLayerColor::initWithColor(ccc4(0, 0, 0, 123)));
        
        this->initDialog();
        
        bRet = true;
    } while (0);
    
    return bRet;
}

void ZPDialogLayer::initDialog()
{
    m_pMenu = NULL;
    bgSprite = NULL;
    bgSprite1 = NULL;
}

//#pragma mark - 
void ZPDialogLayer::initView(const char *pszFileName,const char *pszSpriteFrameName)
{
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    if (pszFileName) {
        bgSprite = CCSprite::create(pszFileName);
    }
    else {
        bgSprite = CCSprite::createWithSpriteFrameName(pszSpriteFrameName);
    }
    if(bgSprite){
        bgSprite->setPosition(ccp(winSize.width/2,winSize.height/2));
        SetScale2(bgSprite, Scale_X);
        this->addChild(bgSprite);
    }
}

void ZPDialogLayer::initView2()
{
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
//    bgSprite = CCSprite::createWithSpriteFrameName("guide015.png");
//    bgSprite->setPosition(ccp(winSize.width/2,winSize.height/2));
//    SetScale2(bgSprite, Scale_X);
//    this->addChild(bgSprite);
    initView(NULL,"guide015.png");
    bgSprite->setAnchorPoint(ccp(1, 1));
    bgSprite->setPosition(ccp(winSize.width-(150)*Scale_X,winSize.height-20*Scale_X));
    
    CCSprite *sprite = CCSprite::create("game/guide004.png");
    sprite->setAnchorPoint(ccp(0, 0));
    sprite->setPosition(ccp(bgSprite->getContentSize().width, bgSprite->getContentSize().height/2));
    bgSprite->addChild(sprite);
    
    CCSprite *mainmenu021000 = CCSprite::createWithSpriteFrameName("mainmenu021000.png");
    mainmenu021000->setAnchorPoint(ccp(1,0.5));
    SetScale2(mainmenu021000,Scale_X);
    mainmenu021000->setPosition(ccp(winSize.width-10,winSize.height-63/2*Scale_X));
    this->addChild(mainmenu021000);
    
    CCSprite *cupSprite = CCSprite::createWithSpriteFrameName("mainmenu021002.png");
    cupSprite->setAnchorPoint(ccp(0,0));
    cupSprite->setPosition(ccp(0,0));
    mainmenu021000->addChild(cupSprite,2);
    
    UIRollNum *m_pScoreNum = UIRollNum::create();
    m_pScoreNum->setEffect("game/mainmenu007.png",6,19,20,NumStyleNormal0);
    m_pScoreNum->setNumber(000000);
    m_pScoreNum->setPosition(ccp(Get_W(Get_Rect(mainmenu021000))+5,Get_H(Get_Rect(mainmenu021000))/2+5));
    mainmenu021000->addChild(m_pScoreNum,MENU_NUM_Layer);
}


void ZPDialogLayer::initView1()
{
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();

    initView(NULL,"guide015.png");
//    bgSprite = CCSprite::createWithSpriteFrameName("guide015.png");
//    bgSprite->setPosition(ccp(winSize.width/2,winSize.height/2));
//    SetScale2(bgSprite, Scale_X);
//    this->addChild(bgSprite);
    bgSprite->setAnchorPoint(ccp(1, 1));
    bgSprite->setPosition(ccp(winSize.width/2-(54/2)*Scale_X,winSize.height-20*Scale_X));
    
    CCSprite *sprite = CCSprite::create("game/guide004.png");
    sprite->setAnchorPoint(ccp(0, 0.5));
    sprite->setPosition(ccp(bgSprite->getContentSize().width, bgSprite->getContentSize().height/2));
    bgSprite->addChild(sprite);

    CCSprite *normalSprite1 = CCSprite::createWithSpriteFrameName("mainmenu0025.png");;
    CCSprite* selectedSprite1 = CCSprite::createWithSpriteFrameName("mainmenu0026.png");
    CCMenuItemSprite *magnificat = CCMenuItemSprite::create(normalSprite1, selectedSprite1, pSelectorTarget,selector2);
    magnificat->setPosition(ccp(WINSIZE_W/2,(winSize.height-63/2*Scale_X)+1));
    magnificat->setScale(Scale_X);
    
    CCSprite *xSprinte = CCSprite::createWithSpriteFrameName("mainmenu027.png");
    xSprinte->setPosition(ccp(18,64/2));
    magnificat->addChild(xSprinte,1,1);
    
    int temp1 = GMPublicMethod::getChooseMagnificationModel();
    UIRollNum *m_pMagnificat = UIRollNum::create();
    m_pMagnificat->setEffect("game/number10.png",2,16,20,NumStyleNormal0);
    m_pMagnificat->setNumber(temp1);
    m_pMagnificat->setPosition(ccp(58, 64/2));
    magnificat->addChild(m_pMagnificat,MENU_NUM_Layer);

    m_pMenu = CCMenu::create(magnificat,NULL);
    m_pMenu->setPosition(CCPointZero);
    this->addChild(m_pMenu);
}


void ZPDialogLayer::initPromptLaser(CCObject *targer,const char *string,SEL_CallFuncN sel)
{
    initView(NULL,"guide015.png");
    CCSprite *sprite = CCSprite::create("game/guide004.png");
    sprite->setAnchorPoint(ccp(0, 0));
    sprite->setPosition(ccp(bgSprite->getContentSize().width, bgSprite->getContentSize().height/2+30*Scale_X));
    bgSprite->addChild(sprite);
    
    setSelectorTarget(targer);
    setSELCallFun(sel);
    
    setLabel(string);
    bgSprite->setPosition(ccp(WINSIZE_W/2-100*Scale_X, WINSIZE_H/2+100*Scale_X));
    addMenu("guide009.png", "guide010.png",true);
}

void ZPDialogLayer::addPromptTexture(const char *pszFileName)
{
    CCSprite *tempSprite = CCSprite::create(pszFileName);
    tempSprite->setPosition(ccp(getBGSprite().width/2,getBGSprite().height/2));
    bgSprite->addChild(tempSprite);
}


void ZPDialogLayer::initSoundView()
{
    bgSprite = CCSprite::create("home/homepage008.jpg");
    bgSprite->setPosition(ccp(WINSIZE_W/2,WINSIZE_H/2));
    SetScale(bgSprite);
    this->addChild(bgSprite);
    
    CCSprite *sprite = CCSprite::create("game/sound001.png");
    sprite->setPosition(ccp(WINSIZE_W/2,WINSIZE_H/2));
    SetScale2(sprite,Scale_X);
    this->addChild(sprite);
    
    CCSprite *normalSprite1 = CCSprite::create("game/sound003.png");;
    CCSprite* selectedSprite1 = CCSprite::create("game/sound005.png");
    CCMenuItemSprite *magnificat = CCMenuItemSprite::create(normalSprite1, selectedSprite1, pSelectorTarget,selector2);
    magnificat->setPosition(ccp(53*Scale_X,57/2*Scale_X));
    magnificat->setScale(Scale_X);

    CCSprite *normalSprite2 = CCSprite::create("game/sound002.png");;
    CCSprite* selectedSprite2 = CCSprite::create("game/sound004.png");
    CCMenuItemSprite *magnificat2 = CCMenuItemSprite::create(normalSprite2, selectedSprite2, pSelectorTarget,selector3);
    magnificat2->setPosition(ccp(WINSIZE_W-53*Scale_X,57/2*Scale_X));
    magnificat2->setScale(Scale_X);
    
    m_pMenu = CCMenu::create(magnificat,magnificat2,NULL);
    m_pMenu->setPosition(CCPointZero);
    this->addChild(m_pMenu);
}


void ZPDialogLayer::showPromptOpenCannon(int index)
{
    bgSprite = CCSprite::create("game/gamegoal000.png");
    bgSprite->setAnchorPoint(ccp(0.5,0.7));
    SetScale2(bgSprite, Scale_Y);
    bgSprite->setPosition(ccp(WINSIZE_W/2, WINSIZE_H/2));
    this->addChild(bgSprite);
    
    CCRect bgRect = Get_Rect(bgSprite);
    CCSprite *winSprite = CCSprite::create("game/winarrow009.png");
    winSprite->setAnchorPoint(ccp(0.5, 0));
    CCArray *temp1 = CCArray::create();
    char strName1[30] = {0};
    for (int j = 9; j <= 10; j++) {
        sprintf(strName1,"game/winarrow%03d.png",j);
        CCSpriteFrame *spriteFrame = CCSpriteFrame::create(strName1, CCRect(0,0,154,190));
        temp1->addObject(spriteFrame);
    }

    CCAnimation *m_pAnimation1 = CCAnimation::createWithSpriteFrames(temp1,0.1);
    CCAnimate *animate1 = CCAnimate::create(m_pAnimation1);
    CCRepeatForever *repeateF1 = CCRepeatForever::create(animate1);
    CCFiniteTimeAction *sequence1 = CCSequence::create(repeateF1,NULL);
    winSprite->runAction(sequence1);
    winSprite->setPosition(ccp(Get_W(bgRect)/2+15, Get_H(bgRect)));
    bgSprite->addChild(winSprite,1,1);

//    CCSprite *gamegoal002 = CCSprite::createWithSpriteFrameName("gamegoal002.png");
//    GMPublicMethod::setRepeatAnimation(gamegoal002, 2, 3, "gamegoal", "png", 0.2,true);
//    gamegoal002->setAnchorPoint(ccp(0.5, 0));
//    gamegoal002->setPosition(ccp(Get_W(bgRect)/2+15, Get_H(bgRect)));
//    bgSprite->addChild(gamegoal002);
    
    CCSprite *win001 = CCSprite::create("game/gongxi1.png");
    win001->setAnchorPoint(ccp(0.5, 0));
    win001->setPosition(ccp(Get_W(bgRect)/2, Get_H(bgRect)));
    bgSprite->addChild(win001);
    
    CCSprite *gongxi001 = CCSprite::create("game/gongxi001.png");
    gongxi001->setAnchorPoint(ccp(0.5, 0));
    gongxi001->setPosition(ccp(Get_W(bgRect)/2, Get_H(bgRect)-55));
    bgSprite->addChild(gongxi001);
    if (index > 6) {
        index = 6;
    }

    char cannonName[30] = {0};
    sprintf(cannonName, "game/gongxi00%d.png",index);
    CCSprite *cannon = CCSprite::create(cannonName);
    cannon->setAnchorPoint(ccp(0.5, 0));
    cannon->setPosition(ccp(206, Get_H(bgRect)-55));
    bgSprite->addChild(cannon);
    
    sprintf(cannonName, "mainmenu03%d.png",index);
    CCSprite *cannon1 = CCSprite::createWithSpriteFrameName(cannonName);
    cannon1->setAnchorPoint(ccp(0.5, 0));
    cannon1->setPosition(ccp(Get_W(bgRect)/2, 20));
    bgSprite->addChild(cannon1);
    cannon1->setScale(0.7);
    
    sprintf(cannonName, "mainmenu_effect03%d.png",index);
    CCSprite *cannon2 = CCSprite::createWithSpriteFrameName(cannonName);
    cannon2->setAnchorPoint(ccp(0.5, 0));
    cannon2->setPosition(ccp(Get_W(bgRect)/2, 20));
    bgSprite->addChild(cannon2);
    cannon2->setScale(0.7);
}

CCSprite *ZPDialogLayer::getSprite()
{
    return bgSprite;
}

CCSize ZPDialogLayer::getBGSprite()
{
    if(bgSprite) {
        return bgSprite->getContentSize();
    }
    return CCSizeZero;
}

void ZPDialogLayer::setLabel(const char *string)
{
    _labelt = CCLabelTTF::create(string, "Marker Felt", 20,CCSize(280, 100), kCCTextAlignmentCenter);
    _labelt->setVerticalAlignment(kCCVerticalTextAlignmentCenter);
    _labelt->setAnchorPoint(ccp(0, 0));
    _labelt->setPosition( ccp( 15 , 5 ));
    _labelt->setColor(ccc3(211,105,58));
    bgSprite->addChild(_labelt);
}

void ZPDialogLayer::setLabel2(const char *string)
{
    _labelt = CCLabelTTF::create(string, "Marker Felt", 30,CCSize(280, 100), kCCTextAlignmentCenter);
    _labelt->setVerticalAlignment(kCCVerticalTextAlignmentCenter);
    _labelt->setAnchorPoint(ccp(0, 0));
    _labelt->setPosition( ccp( (bgSprite->getContentSize().width-270)/2 , (bgSprite->getContentSize().height-80)/2 ));
    _labelt->setColor(ccc3(211,105,58));
    bgSprite->addChild(_labelt);
}

void ZPDialogLayer::addMenu(const char *normalName,const char *selectedName,bool isFrame)
{
    CCSprite *normalSprite = NULL;
    CCSprite *selectedSprite = NULL;
    if (isFrame) {
        normalSprite = CCSprite::createWithSpriteFrameName(normalName);
        selectedSprite = CCSprite::createWithSpriteFrameName(selectedName);
    }
    else {
        normalSprite = CCSprite::create(normalName);
        selectedSprite = CCSprite::create(selectedName);
    }
    
    CCMenuItem *item = CCMenuItemSprite::create(normalSprite, selectedSprite, this, menu_selector(ZPDialogLayer::removeDialogLayer));
    item->setPosition(ccp((getBGSprite().width)/2,0));
    m_pMenu = CCMenu::create(item,NULL);
    m_pMenu->setPosition(CCPointZero);
    bgSprite->addChild(m_pMenu);
}

//#pragma mark - 动画
void ZPDialogLayer::setAnimation(bool isRemoved,float delay)
{
    bgSprite->setScale(0);
    CCScaleTo *scaleTo1 = CCScaleTo::create(0.5, Scale_X);
    bgSprite->runAction(scaleTo1);
   
    if (isRemoved) {
        this->scheduleOnce(schedule_selector(ZPDialogLayer::setAnimation2), delay);
    }
}

void ZPDialogLayer::setAnimation2(float dt)
{
    CCScaleTo *scaleTo1 = CCScaleTo::create(0.5, 0);
    CCCallFunc *callFunc = CCCallFunc::create(this, callfunc_selector(ZPDialogLayer::removeDialogLayer1));
    CCFiniteTimeAction *sequence = CCSequence::create(scaleTo1,callFunc,NULL);
    bgSprite->runAction(sequence);

}

void ZPDialogLayer::removeDialogLayer(CCObject *pSender)
{
    this->removeAllChildrenWithCleanup(true);
    CCCallFuncN *callFunc = CCCallFuncN::create(pSelectorTarget, selector);
    CCFiniteTimeAction *sequence = CCSequence::create(callFunc,NULL);
    this->runAction(sequence);
}

void ZPDialogLayer::removeDialogLayer1()
{
	this->removeAllChildrenWithCleanup(true);
	CCCallFuncN *callFunc = CCCallFuncN::create(pSelectorTarget, selector);
	CCFiniteTimeAction *sequence = CCSequence::create(callFunc,NULL);
	this->runAction(sequence);
}

//#pragma mark - 腾讯的logo
void ZPDialogLayer::initQQLogoView(int type){
    this->setOpacity(255);
    this->setColor(ccc3(255, 255, 255));

    bgSprite1 = CCSprite::create("gamedo.png");
    bgSprite1->setPosition(ccp(WINSIZE_W/2, WINSIZE_H/2));
    SetScale(bgSprite1);
    this->addChild(bgSprite1,1);
    
    if(type == 1){
        tempColor = CCLayerColor::create(ccc4(255, 255, 255, 255));
        tempColor->setPosition(ccp(0,0));
        this->addChild(tempColor,2);
        
        bgSprite = CCSprite::create("480800.png");
        bgSprite->setPosition(ccp(WINSIZE_W/2, WINSIZE_H/2));
        SetScale(bgSprite);
        tempColor->addChild(bgSprite,2);
        this->scheduleOnce(schedule_selector(ZPDialogLayer::removeQQLogo), 2);
    }

}

void ZPDialogLayer::removeQQLogo(float dt){
    CCFadeOut *fadeOut = CCFadeOut::create(2);
    tempColor->runAction(fadeOut);
    if(bgSprite){
        CCFadeOut *fadeOut1 = CCFadeOut::create(2);
        bgSprite->runAction(fadeOut1);
    }
}

//#pragma mark -

void ZPDialogLayer::onEnter()
{
    CCLayerColor::onEnter();
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,kCCMenuHandlerPriority, true);
}

void ZPDialogLayer::onExit()
{
    CCLayerColor::onExit();
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
}

bool ZPDialogLayer::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    if (m_pMenu) {
        m_bTouchedMenu = m_pMenu->ccTouchBegan(pTouch, pEvent);
    }
    
    return true;
}

void ZPDialogLayer::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    if (m_bTouchedMenu && m_pMenu) {
        m_pMenu->ccTouchMoved(pTouch, pEvent);
    }
}

void ZPDialogLayer::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    if (m_bTouchedMenu && m_pMenu) {
        m_pMenu->ccTouchEnded(pTouch, pEvent);
        m_bTouchedMenu = false;
    }
}

void ZPDialogLayer::ccTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    if (m_bTouchedMenu && m_pMenu) {
        m_pMenu->ccTouchCancelled(pTouch, pEvent);
        m_bTouchedMenu = false;
    }
}

void ZPDialogLayer::okMenuItemCallback(cocos2d::CCObject *pSender)
{
    // 点击确定就退出（拷贝的原有方法）
    CCDirector::sharedDirector()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}

void ZPDialogLayer::cancelMenuItemCallback(cocos2d::CCObject *pSender)
{
    this->removeFromParentAndCleanup(false);
}
