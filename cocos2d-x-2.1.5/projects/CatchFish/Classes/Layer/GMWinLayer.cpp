//
//  GMWinLayer.cpp
//  FishX
//
//  Created by peng on 12-12-25.
//
//

#include "GMWinLayer.h"
#include "GMCardLayer.h"
#include "../Config/GMHeaderConfig.h"
#include "GMMainLayer.h"
#include "../PublicModels/ZPDialogLayer.h"
#include "../PublicModels/GMBillingLayer.h"
#include "../PublicModels/ZPJNIHelper.h"

//#pragma mark - GMLoseLayer


CCScene* GMWinLayer::scene()
{
    CCScene *scene = CCScene::create();
    GMWinLayer *layer = GMWinLayer::create();
    scene->addChild(layer);
    return scene;
}

GMWinLayer::GMWinLayer()
{
    
}

// on "init" you need to initialize your instance
bool GMWinLayer::init()
{    
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    GMPublicMethod::sharedPublicMethod()->setGameStatus(Win_Status);
//    GMPublicMethod::sharedPublicMethod()->setGameStatus1(Win_Status);
    
    GMAudioPlay::sharedAudioPlay()->stopMyAllEffects();
    GMAudioPlay::sharedAudioPlay()->stopBGMusic();
    
    GMAudioPlay::sharedAudioPlay()->playOtherEffect(Audio_Win,false);
    
//    CCRemoveUnusedSpriteFrames();
    CCRemoveUnusedAllSpriteFrames();
    ZPLog("win测试1");
    this->setTouchEnabled(true);
    
//    int bgIndex = GMPublicMethod::sharedPublicMethod()->getCheckpointsIndex();
    char bgName[20] = {0};
    sprintf(bgName,"iPhone/bg_%d.jpg",1);
    CCSprite *background = CCSprite::create(bgName);
	background->setPosition(ccp(WINSIZE_W/2, WINSIZE_H/2));
    if (Get_W(Get_Rect(background)) != WINSIZE_W) {
        SetScale(background);
    }
    this->addChild(background,0);
   
    CCAddSpriteFramesWithFile(Win_plist);
    winBatchNode = CCSpriteBatchNode::create(Win_png);
    this->addChild(winBatchNode);
    
    CCAddSpriteFramesWithFile(hitfish_plist);
    hitFishBatchNode = CCSpriteBatchNode::create(hitfish_png);
    this->addChild(hitFishBatchNode);
    
    CCAddSpriteFramesWithFile(wineffect_plist);
    CCSpriteBatchNode *wineffetBatchNode = CCSpriteBatchNode::create(wineffect_png);
    this->addChild(wineffetBatchNode);
    
    isOpenVideo = true;
    ZPLog("win测试5");
    winLayer = CCLayerColor::create(ccc4(0, 0, 0, 125));
    winLayer->setContentSize(CCSizeMake(S_WINSIZE_W, S_WINSIZE_H));
    winLayer->setAnchorPoint(ccp(0, 0));
    this->addChild(winLayer,1);
    SetScale(winLayer);
    
    currentLevel = GMAccessData::sharedAccessData()->getCurrentLevel();
    
    int tempIndex1 = currentLevel/10;
    int tempIndex2 = currentLevel%10;
    if (tempIndex2 == 5) {
        GMAccessData::sharedAccessData()->saveOpenCheckpoints(currentLevel,1);
        GMAccessData::sharedAccessData()->saveOpenCheckpoints(tempIndex1*10+11,1);
        int tempCheckpoints = GMAccessData::sharedAccessData()->getCurrentCheckpoints();
        if(tempCheckpoints < tempIndex1+1)
            GMAccessData::sharedAccessData()->saveCurrentCheckpoints(tempIndex1+1);
    }
    else {
        GMAccessData::sharedAccessData()->saveOpenCheckpoints(currentLevel+1,1);
    }
//    if (currentLevel == 15) {
//        GMAccessData::saveOpenCheckpoints(currentLevel,1);
//        GMAccessData::saveOpenCheckpoints(21,1);
//    }
//    else if (currentLevel == 25) {
//        GMAccessData::saveOpenCheckpoints(currentLevel,1);
//        GMAccessData::saveOpenCheckpoints(31,1);
//    }
//    else {
//        GMAccessData::saveOpenCheckpoints(currentLevel+1,1);
//    }
    scrollView = NULL;
    ZPLog("win测试4");
    initElement();

    winLayer->setPosition( ccp( 0, 0) );
    
    isShowDialogLayer = false;
    ZPLog("win测试2");
	this->setKeypadEnabled(true);
    isloadT = true;
    return true;
}


void GMWinLayer::keyBackClicked(){}
void GMWinLayer::keyboardHook(int keyCode, int keyEvent){
	if (keyCode == kTypeEnterClicked && keyEvent == kTypeEventKeyDown) {
		this->nextGame(NULL);
	}
}

//800 x 480
void GMWinLayer::initElement()
{
    bg2 = CCSprite::create("win/win001.png");
    bg2->setPosition(ccp(WINSIZE_W/2, WINSIZE_H/2));
    SetScale2(bg2, Scale_Y);
    this->addChild(bg2,2);
    
    CCSprite *winSprite = CCSprite::create("game/winarrow009.png");
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
    winSprite->setPosition(ccp(100, 243));
    bg2->addChild(winSprite);
    
    CCSprite *tipSprite = CCSprite::createWithSpriteFrameName("winarrow011.png");
    tipSprite->setPosition(ccp(100+Get_W( Get_Box(winSprite) )/2, 165));
    bg2->addChild(tipSprite,5);
    
    tempW = Get_W( Get_Rect(bg2) );
    tempH = Get_H( Get_Rect(bg2) );
    
    showScore(bg2);
    
    CCSprite *titleS = NULL;
    if(currentLevel!=45)
        titleS = CCSprite::create("win/win021.png");
    else
        titleS = CCSprite::create("win/win022.png");
    titleS->setAnchorPoint(ccp(0.5,1));
    titleS->setPosition(ccp(tempW/2,tempH-25));
    bg2->addChild(titleS);
    
    
    CCSprite *ligth = CCSprite::createWithSpriteFrameName("wineffect001.png");
    CCArray *temp = CCArray::create();
    char strName[30] = {0};
    for (int j = 1; j <= 4; j++) {
       sprintf(strName,"wineffect%03d.png",j);
        CCSpriteFrame *spriteFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(strName);
        temp->addObject(spriteFrame);
    }
    CCAnimation *m_pAnimation = CCAnimation::createWithSpriteFrames(temp,0.1);
    CCAnimate *animate = CCAnimate::create(m_pAnimation);
    CCRepeatForever *repeateF = CCRepeatForever::create(animate);
    CCFiniteTimeAction *sequence = CCSequence::create(repeateF,NULL);
    ligth->runAction(sequence);
    SetScale2(ligth, Scale_Y);
    CCRect ligthRect = ligth->boundingBox();
    ligth->setPosition(ccp(WINSIZE_W/2, WINSIZE_H-ligthRect.size.height/2));
    this->addChild(ligth,1);
    
    
    int starNum  = GMPublicMethod::getStarNum();//GMAccessData::getEachLevelStar(currentLevel);
    for (int i = 0; i < 3; i++) {
        CCSprite *start = NULL;
        if (i < starNum) {
            start = CCSprite::createWithSpriteFrameName("wineffect010.png");
        }
        else {
            start = CCSprite::createWithSpriteFrameName("lose000.png");
        }
        CCRect startRect = Get_Box(start);
        start->setPosition(ccp(tempW/2+(i*88-10), tempH/2+88-10 ));
        bg2->addChild(start,3,10000+i);
    }
    
    CCSprite *win09 = CCSprite::createWithSpriteFrameName("win009.png");
    CCSprite *win10 = CCSprite::createWithSpriteFrameName("win010.png");
    CCMenuItem *win009 = CCMenuItemSprite::create(win09, win10, this, menu_selector(GMWinLayer::chooseCard));
    SetScale2(win009, Scale_X);
    win009->setAnchorPoint(ccp(0,0));
    win009->setPosition(ccp(10,10));
    
    CCMenuItem *win011 = NULL;
    if (currentLevel != 45) {
        CCSprite *win11 = CCSprite::createWithSpriteFrameName("win011.png");
        CCSprite *win12 = CCSprite::createWithSpriteFrameName("win012.png");
        win011 = CCMenuItemSprite::create(win11, win12, this, menu_selector(GMWinLayer::nextGame));
        SetScale2(win011, Scale_X);
        win011->setAnchorPoint(ccp(1,0));
		win011->setPosition(ccp(WINSIZE_W - 10, 10));
		CCScaleTo* scaleTo1 = CCScaleTo::create(0.5, 1.3*Scale_X);
		CCScaleTo* scaleTo2 = CCScaleTo::create(0.5, 1.0*Scale_X);
		CCSequence* seq = CCSequence::create(scaleTo1, scaleTo2, NULL);
		CCRepeatForever* rep = CCRepeatForever::create(seq);
		win011->runAction(rep);
    }
    
    CCMenu *mainMenu = CCMenu::create(win009,win011,NULL);
    CCRect rect16 = Get_Box(win009);
    mainMenu->setPosition(CCPointZero);
    this->addChild(mainMenu,MENU_Layer);
    

    CCSprite *winarrow007 = CCSprite::createWithSpriteFrameName("winarrow007.png");
    CCMenuItem *arrow1 = CCMenuItemSprite::create(winarrow007, winarrow007, this, menu_selector(GMWinLayer::arrowAction1));

    CCSprite *winarrow008 = CCSprite::createWithSpriteFrameName("winarrow008.png");
    CCMenuItem *arrow2 = CCMenuItemSprite::create(winarrow008, winarrow008, this, menu_selector(GMWinLayer::arrowAction2));

    CCMenu *arrowMenu = CCMenu::create(arrow1,arrow2,NULL);
    CCRect arrowR = Get_Box(arrow1);
    arrowMenu->setPosition(ccp(tempW/2, tempH/5+10));
    bg2->addChild(arrowMenu,MENU_Layer);
    arrowMenu->alignItemsHorizontallyWithPadding(tempW-40);
    
    float tempw = tempW-100*Scale_X;
    if(tempw<0){
        tempw = tempW;
    }
    float temph = tempH-200*Scale_X;
    if (temph<0) {
        temph = tempH;
    }
    
    scrollRect = CCRect(bg2->getPosition().x-(tempW-100*Scale_X)/2,bg2->getPosition().y-tempH/2,tempw,temph);
        
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    this->scheduleOnce(schedule_selector(GMWinLayer::initScrollView), 0.1);
//#endif
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    initScrollView();
#endif
    
}

void GMWinLayer::initScrollView(float dt)
{
    //    CCLayerColor *layer = CCLayerColor::create(ccc4(0, 0, 0, 125));
    CCLayer *layer = CCLayer::create();	//创建一个层，作为滚动的内容
    float tempWW = 0.0f;
    float tempHH = 0.0f;
    char strName2[30] = {0};
    //    char page[30] = {0};
    m_nCurPage = 0;
    int num1 = GMPublicMethod::sharedPublicMethod()->getHitNum();
    m_nTotalPage = num1/5 + (num1%5>0 ? 1:0);
    for (int i = 0;i < num1;i++){
        CCSprite *sprite = CCSprite::createWithSpriteFrameName("win005.png");
        sprite->setAnchorPoint(ccp(0, 0));
        tempWW = Get_W(Get_Box(sprite));
        tempHH = Get_H(Get_Box(sprite));
        sprite->setPosition(ccp(0+i*(tempWW+5),0));
        layer->addChild(sprite);
        
        //        sprintf(page, "%d",i+1);
        //        CCLabelTTF *labelt = CCLabelTTF::create(page, "Arial Rounded MT Bold", 44);
        //        labelt->setPosition( ccp( tempWW /2 , tempHH/2 ));
        //        labelt->setColor(ccBLACK);
        //        sprite->addChild(labelt);
        
        GMStrange *strange = GMPublicMethod::sharedPublicMethod()->getHitStrange(i);
        sprintf(strName2,"winyu%03d.png",strange->_strange_id);
        CCSprite *hitFish = CCSprite::createWithSpriteFrameName(strName2);
        hitFish->setPosition(ccp(tempWW/2,tempHH/2));
        sprite->addChild(hitFish);
        
        int num = GMPublicMethod::getScoreNum(strange->_countNum);
        UIRollNum *tempNum = UIRollNum::create();
        tempNum->setEffect("win/win006.png",num,18,18,NumStyleNormal0);
        tempNum->setNumber(strange->_countNum);
        tempNum->setPosition( ccp( 0+num*18, 21/2) );
        sprite->addChild(tempNum,MENU_NUM_Layer);
    }
    
    ZPLog("win测试3");
    moveW = (tempWW+5)*5*m_nTotalPage;
    //    layer->setAnchorPoint(CCPointZero);
    //    layer->setPosition(CCPointZero);
    scrollView = CCScrollView::create();// 位置不是居中的
    scrollView->setPosition(CCPointZero);
    scrollView->setContentOffset(CCPointZero);
    layer->setContentSize(CCSizeMake(moveW, tempHH*Scale_Y));		//设置滚动区域的大小
    scrollView->setViewSize(CCSizeMake((tempW-80)*Scale_Y, tempHH*Scale_Y));
    scrollView->setContentSize(CCSizeMake(moveW, 320));		//设置显示区域的大小
    scrollView->setContainer(layer);                            //设置需要滚动的内容
    scrollView->setTouchEnabled(true);                         //因为要自己实现触摸消息，所以这里设为false
    //    scrollView->setDelegate(this);
    scrollView->setDirection(kCCScrollViewDirectionHorizontal);  //设置滚动的方向，有三种可以选择
    scrollView->setPosition(ccp(42.5, 65));
    //    scrollView->setBackgroundColor(ccRED);
    bg2->addChild(scrollView,4);
    
    this->scheduleOnce(schedule_selector(GMWinLayer::showStartPrompt), 0.5);
    
    if (currentLevel%10 == 5){
        
//        int temp1 = currentLevel/10;
//        int temp2 = GMAccessData::getMagnificationModel();
//        temp1++;
//        if(temp1>temp2)
//            GMAccessData::saveMagnificationModel(temp1);
        
        this->scheduleOnce(schedule_selector(GMWinLayer::showAchievementPrompt), 0.5);
    }
}
/*
 *  过大关的成就
 */
void GMWinLayer::showAchievementPrompt(float t)
{
    int tempIndex = currentLevel/10+1;
    int status = GMAccessData::sharedAccessData()->getEachAchievementStatus(tempIndex);
    if (status == 0) {
        achievementPrompt = GMAchievementPrompt::create();
        this->addChild(achievementPrompt,APrompt_Layer);
        
        achievementPrompt->showGMCheckpointsPrompt(tempIndex);
        
        this->scheduleOnce(schedule_selector(GMWinLayer::removeAchievementPrompt), 2);
    } 
}

void GMWinLayer::removeAchievementPrompt(float t)
{
    this->removeChild(achievementPrompt, true);
}

void GMWinLayer::showStartPrompt(float dt){
    int starNum = GMPublicMethod::getStarNum();
    for (int i = 0; i < 3; i++) {
        if (i < starNum) {
            CCSprite *start = (CCSprite*)bg2->getChildByTag(10000+i);
            GMPublicMethod::setSpriteAnimation(start, 10, 15, "wineffect",0.2f,this,callfuncN_selector(GMWinLayer::addStarEffect));
        }
    }
}
/*
 *
 */
void GMWinLayer::addStarEffect(CCNode *pNode)
{
	CCSprite *sprite = (CCSprite*)pNode; 
    CCSprite *winEffect = CCSprite::createWithSpriteFrameName("wineffect016.png");
    GMPublicMethod::setRepeatAnimation(winEffect, 16, 19, "wineffect", "png",0.1,true);
    winEffect->setAnchorPoint(ccp(0, 0));
    sprite->addChild(winEffect);
}
// 
void GMWinLayer::showScore(CCSprite* pChild)
{
//    float tempW = Get_W( Get_Rect(pChild) );
//    float tempH = Get_H( Get_Rect(pChild) );
    score1 = UIRollNum::create();
    int tempNum = GMPublicMethod::sharedPublicMethod()->getConsumptionEnergy();
    int num = GMPublicMethod::getScoreNum(tempNum);
    score1->setEffect("win/win002.png",num,22,21,NumStyleNormal0);
    score1->setNumber( tempNum );
    score1->setPosition(ccp(tempW/2+85+num*NUM_WIDTH, tempH/2+5));
    pChild->addChild(score1,11111);
    
    tempNum = GMPublicMethod::sharedPublicMethod()->getGainEnergy();
    num = GMPublicMethod::getScoreNum(tempNum);
    score2 = UIRollNum::create();
    score2->setEffect("win/win003.png",num,22,21,NumStyleNormal0);
    score2->setNumber( tempNum );
    score2->setPosition(ccp(tempW/2+85+num*NUM_WIDTH, tempH/2-35));
    pChild->addChild(score2,11112);
}

void GMWinLayer::setScore(int s1 ,int s2)
{
    score1->setNumber(s1);
    score2->setNumber(s2);
}

// action 
void GMWinLayer::arrowAction1(CCObject *pSender)
{
    GMAudioPlay::sharedAudioPlay()->playButtonEffect();
    setPage(false);
}

void GMWinLayer::arrowAction2(CCObject *pSender)
{
    GMAudioPlay::sharedAudioPlay()->playButtonEffect();
    setPage(true);
}

void GMWinLayer::chooseCard(CCObject *pSender)
{
    CCDirector::sharedDirector()->resume();
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
    this->removeAllChildrenWithCleanup(true);
    
    this->cleanup();
    
    GMAudioPlay::sharedAudioPlay()->playButtonEffect();
    
    CCScene *pScene = CCTransitionFade::create(0.0, GMCardLayer::scene(), ccWHITE);
    CCDirector::sharedDirector()->replaceScene(pScene);
    //    tempGameLayer-> chooseCardLaye();
}

void GMWinLayer::nextGame(CCObject *pSender)
{
    GMBillingModel tmpBilling = GMPublicMethod::sharedPublicMethod()->getBillingModel();
    if(tmpBilling != B_Free){
//        if(tmpBilling!=B_91_IOS)
        {
            int satatus =  GMAccessData::sharedAccessData()->getGenuineValidationStatus();
            if (currentLevel == GoToEndless && satatus != 2){
                addBilling(1,0);
                return;
            }
        }
    }
    
    this->cleanup();
    
    GMAudioPlay::sharedAudioPlay()->playButtonEffect();
    
    CCDirector::sharedDirector()->resume();
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
    this->removeAllChildrenWithCleanup(true);
    
    int tempIndex1 = currentLevel/10;
    int tempIndex2 = currentLevel%10;
    if (tempIndex2 == 5) {
        GMAccessData::sharedAccessData()->saveCurrentLevel(tempIndex1*10+11);
        GMPublicMethod::sharedPublicMethod()->setCheckpointsIndex(tempIndex1+1);
    }
    else {
        GMAccessData::sharedAccessData()->saveCurrentLevel(currentLevel+1);
    }
    
//    if (currentLevel == 15) {
//        GMAccessData::saveCurrentLevel(21);
//    }
//    else {
//        GMAccessData::saveCurrentLevel(currentLevel+1);
//    }

    CCScene *pScene = CCTransitionFade::create(0.0, GMMainLayer::scene(), ccWHITE);
    CCDirector::sharedDirector()->replaceScene(pScene);
}

//#pragma mark - Dialog
void GMWinLayer::showDialogLayer()
{
    if(isShowDialogLayer  == false){
        ZPDialogLayer *dialogLayer = ZPDialogLayer::create();
        dialogLayer->initView("gamegoal000.png", NULL);
        dialogLayer->addPromptTexture("game/gamegoal015.png");
        dialogLayer->setSelectorTarget(this);
        dialogLayer->setSELCallFun(callfuncN_selector(GMWinLayer::removeDialogLayer));
        dialogLayer->setAnimation(true,1.5f);
        this->addChild(dialogLayer,10);
        isShowDialogLayer = true;
    }
}

void GMWinLayer::removeDialogLayer(CCNode *dialog)
{
    ZPDialogLayer *dialogLayer = (ZPDialogLayer*)dialog;
    this->removeChild(dialogLayer, true);
    isShowDialogLayer = false;
}

//#pragma mark -

void GMWinLayer::registerWithTouchDispatcher()
{
    //1.x
    //CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate(this, std::numeric_limits <int> ::min() , true);
    //2.x
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, kCCMenuHandlerPriority, true);
    //使用int最小值做最高优先级,并且吞掉事件true
    
    CCLayer::registerWithTouchDispatcher();
}

bool GMWinLayer::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    //    m_bTouchedMenu =
    CCPoint endPoint = CCDirector::sharedDirector()->convertToGL(pTouch->getLocationInView());
    
    if(GMPublicMethod::checkRectContainsPoint(scrollRect, endPoint)){
        tempx1 = endPoint.x;
        if (moveW>0 && scrollView) {
            scrollView->ccTouchBegan(pTouch, pEvent);
        }
    }
    return true;
}

void GMWinLayer::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    if (moveW>0 && scrollView)
    {
        scrollView->ccTouchMoved(pTouch, pEvent);
    }
    
}

void GMWinLayer::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
    if (moveW>0 && scrollView)
    {
        scrollView->ccTouchEnded(pTouch, pEvent);
        
        CCPoint endPoint = CCDirector::sharedDirector()->convertToGL(pTouch->getLocationInView());
        if(GMPublicMethod::checkRectContainsPoint(scrollRect, endPoint)){
            tempx2 = endPoint.x;
            if(tempx2 > tempx1){
                setPage(false);
            }
            else if(tempx2 < tempx1){
                setPage(true);
            }
        }
    }
}

void GMWinLayer::setPage(bool plus)
{
    if (plus) {
        m_nCurPage++;
        if (m_nCurPage >= m_nTotalPage-1) {
            m_nCurPage = m_nTotalPage-1;
        }
    }
    else {
        m_nCurPage--;
        if (m_nCurPage<=0) {
            m_nCurPage = 0;
        }
    }
    adjustScrollView(m_nCurPage);
}

void GMWinLayer::ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent)
{
    
}

void GMWinLayer::adjustScrollView(int arrow)
{
    // 关闭CCScrollView中的自调整
    scrollView->unscheduleAllSelectors();
    // 调整位置
    CCPoint adjustPos = ccp(-(moveW/m_nTotalPage)*arrow,0);
    // 调整位置
    scrollView->setContentOffsetInDuration(adjustPos, 0.5);
}

//#pragma mark -  计费
//1 为正版验证，2为购买能量，3为购买技能，4为购买武器
void GMWinLayer::addBilling(int index,int index2){
    GMBillingModel tmpBilling = GMPublicMethod::sharedPublicMethod()->getBillingModel();
    if(tmpBilling == B_91_Android && index == 1){
#if (JNIHELPER_INDEX == JNIHELPER_91_Android)
        ZPJNIHelper::setAllPay(6);
        this->schedule(schedule_selector(GMWinLayer::check91BillingPoint));
        return;
#endif
    }
    //#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    
    GMBillingLayer *billingLayer = GMBillingLayer::create();
    billingLayer->setDelegate(this);
    billingLayer->setStartBliling(false);
    billingLayer->setIndex(index);
    billingLayer->setClassType(3);
    switch (index) {
        case 1:{
            if(tmpBilling == B_91_IOS){
#if (JNIHELPER_INDEX == JNIHELPER_91_IOS)
//                if(PublicCPP::getMobileBilling()){
//                    GMPublicMethod::sharedPublicMethod()->setBillingIndex(6);
//                    billingLayer->show91MobileView();
//                }
//                else
                {
//                    PublicCPP::paymentAll(6);//
//                    this->schedule(schedule_selector(GMWinLayer::check91BillingPoint));
                    if(isloadT){
                        CCAddSpriteFramesAndTextureFile(changeboom_plist,changeboom_png);
                        isloadT = false;
                    }
                    billingLayer->setStartBliling(true);
                    billingLayer->showGenuineValidationTips();
                }
#endif
            }
            else if(tmpBilling == B_TengXunBilling || tmpBilling == B_Unicom_Android){
//            腾讯版本暂时注销儿子确认
                billingLayer->showSecondaryConfirmationTips(0);
            }
        }   break;
        case 6:{
            ZPLog("c测试   》》》》》》》 6");
            if(isloadT){
                CCAddSpriteFramesAndTextureFile(changeboom_plist,changeboom_png);
                isloadT = false;
            }
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

void GMWinLayer::removeBilling(int index,bool _isClickClose){
    
#if (JNIHELPER_INDEX == JNIHELPER_91_IOS)
    if( _isClickClose /*|| PublicCPP::getMobileBilling()*/)
#endif
    {
        GMBillingLayer *tempBillingLayer = (GMBillingLayer*)this->getChildByTag(Billing_tag);
        this->removeChild(tempBillingLayer, true);
    }
    
    GMBillingModel billingModel= GMPublicMethod::sharedPublicMethod()->getBillingModel();
    switch (index) {
        case 1:{
            if(_isClickClose==false){
                if(billingModel == B_91){
                    GMAccessData::sharedAccessData()->saveGenuineValidationStatus(2);
                    
                    int money = GMAccessData::sharedAccessData()->getTotalMoneyNum();
                    money += 5000;
                    GMAccessData::sharedAccessData()->saveTotalMoneyNum(money);
                    
                    int num = GMAccessData::sharedAccessData()->getSkillBloodNum();
                    num = num+5;
                    GMAccessData::sharedAccessData()->saveSkillBloodNum(num);
                }
                else if(billingModel==B_TengXunBilling){
                    ZPLog("c测试   》》》》》》》 8");
                    GMAccessData::sharedAccessData()->saveGenuineValidationStatus(1);
                    addBilling(6,0);
                }
                else if(billingModel == B_91_IOS){
#if (JNIHELPER_INDEX == JNIHELPER_91_IOS)
//                    if(PublicCPP::getMobileBilling()){
//                        addBilling(8,0);
//                    }
//                    else
                    {
                        this->schedule(schedule_selector(GMWinLayer::check91BillingPoint));
                    }
#endif
                }
                else if(billingModel == B_Unicom_Android){
                    ZPJNIHelper::sendSMSBillingPoint(1);
                    this->schedule(schedule_selector(GMWinLayer::checkBillingPoint));
                }

            }
        }   break;
        case 6:{
            if(_isClickClose==false){
                if(billingModel == B_TengXunBilling){
                    ZPLog("c测试   》》》》》》》 7");
                    ZPJNIHelper::sendSMSBillingPoint(1);
                    this->schedule(schedule_selector(GMWinLayer::checkBillingPoint));
                }
            }
        }   break;
        case 8:{
            if(_isClickClose==false){
                this->schedule(schedule_selector(GMWinLayer::check91BillingPoint));
            }
        }   break;
        default:
            break;
    }
}

void GMWinLayer::checkBillingPoint(float dt){
    int status = ZPJNIHelper::getSendSMSBillingPointStatus();
    ZPLog("GMWinLayer ::getSendSMSBillingPointStatus %d",status);
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
            ZPLog("正版验证计费  计费索引 1");
        }
        ZPJNIHelper::setSMSBillingPointStatus();//将状态付值为0 (腾讯 移动 通用方法)
        this->unschedule(schedule_selector(GMWinLayer::checkBillingPoint));
    }
    else if(status==2){
        ZPJNIHelper::setSMSBillingPointStatus();//将状态付值为0 (腾讯 移动 通用方法)
        this->unschedule(schedule_selector(GMWinLayer::checkBillingPoint));
    }
}


void GMWinLayer::check91BillingPoint(float dt){
    int tempStatus = 0;
    int tempInde = 0;

#if (JNIHELPER_INDEX == JNIHELPER_91_Android)
    tempStatus = ZPJNIHelper::getSendSMSBillingPointStatus();
    tempInde = ZPJNIHelper::getBillingIndex();
#endif
    if(tempStatus != 0){
        if(tempStatus==1){
            if(tempInde == 6){
                if(ZPJNIHelper::getOperators() == 1){
                    int tempM = GMAccessData::sharedAccessData()->getTotalMoneyNum();
                    tempM += 13000;
                    GMAccessData::sharedAccessData()->saveTotalMoneyNum(tempM);
                }

                GMAccessData::sharedAccessData()->saveGenuineValidationStatus(2);
            }

        }
        else if(tempStatus==2){
            if(tempInde == 6){
                GMAccessData::sharedAccessData()->saveGenuineValidationStatus(1);
            }
        }

        this->unschedule(schedule_selector(GMWinLayer::check91BillingPoint));
        
        GMBillingLayer *tempBillingLayer = (GMBillingLayer*)this->getChildByTag(Billing_tag);
        this->removeChild(tempBillingLayer, true);
    }
}

GMWinLayer::~GMWinLayer()
{
    this->removeChild(winLayer, true);
    winLayer = NULL;
    this->removeChild(winBatchNode, true);
    this->removeChild(hitFishBatchNode, true);
    CCRemoveSpriteFrameByName(Win_plist);
    CCRemoveTextureForKey(Win_png);
    CCRemoveSpriteFrameByName(hitfish_plist);
    CCRemoveTextureForKey(hitfish_png);
    CCRemoveSpriteFrameByName(wineffect_plist);
    CCRemoveTextureForKey(wineffect_png);
    
    CCRemoveSpriteFramesAndTextureForKey(changeboom_plist,changeboom_png);
    
    score1 = NULL;
    score2 = NULL;
    scrollView = NULL;
    this->cleanup();
    
    ZPLog("~GMWinLayer");
}

//#pragma mark - 重构

//void GMWinLayer::onEnter()
//{
//    CCLayer::onEnter();
//    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, kCCMenuHandlerPriority - 1, true);
//}
//
//void GMWinLayer::onExit()
//{
//    CCLayer::onExit();
//    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
//}
//
//bool GMWinLayer::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
//{
//    m_bTouchedMenu = menu->ccTouchBegan(pTouch, pEvent);
//    
//    return true;
//}
//
//void GMWinLayer::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
//{
//    if (m_bTouchedMenu) {
//        menu->ccTouchMoved(pTouch, pEvent);
//    }
//}
//
//void GMWinLayer::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
//{
//    if (m_bTouchedMenu) {
//        menu->ccTouchEnded(pTouch, pEvent);
//        m_bTouchedMenu = false;
//    }
//}
//
//void GMWinLayer::ccTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
//{
//    if (m_bTouchedMenu) {
//        menu->ccTouchEnded(pTouch, pEvent);
//        m_bTouchedMenu = false;
//    }
//}

