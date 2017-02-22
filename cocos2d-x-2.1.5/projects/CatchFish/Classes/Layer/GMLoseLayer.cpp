//
//  GMLoseLayer.cpp
//  FishX
//
//  Created by peng on 12-12-26.
//
//

#include "GMLoseLayer.h"
#include "GMCardLayer.h"
#include "../PublicModels/UIRollNum.h"
#include "GMMainLayer.h"
#include "../Config/GMHeaderConfig.h"
//#include "GMStrange.h"

CCScene* GMLoseLayer::scene()
{
    CCScene *scene = CCScene::create();
    GMLoseLayer *layer = GMLoseLayer::create();
    scene->addChild(layer);
    return scene;
}

GMLoseLayer::GMLoseLayer()
{
    
}

// on "init" you need to initialize your instance
bool GMLoseLayer::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    GMPublicMethod::sharedPublicMethod()->setGameStatus(Lose_Status);
//    GMPublicMethod::sharedPublicMethod()->setGameStatus1(Lose_Status);
    
    GMAudioPlay::sharedAudioPlay()->stopMyAllEffects();
    GMAudioPlay::sharedAudioPlay()->stopBGMusic();
    
    GMAudioPlay::sharedAudioPlay()->playOtherEffect(Audio_Lose,false);
    
//    CCRemoveUnusedSpriteFrames();
    CCRemoveUnusedAllSpriteFrames();
    
    this->setTouchEnabled(true);
    
    currentLevel = GMAccessData::sharedAccessData()->getCurrentLevel();
    
//    int bgIndex = GMPublicMethod::sharedPublicMethod()->getCheckpointsIndex();
    char bgName[20] = {0};
    sprintf(bgName,"iPhone/bg_%d.jpg",1);
    CCSprite *background = CCSprite::create(bgName);
	background->setPosition(ccp(WINSIZE_W/2, WINSIZE_H/2));
    if (Get_W(Get_Rect(background)) != WINSIZE_W) {
        SetScale(background);
    }
    this->addChild(background,0);
    
    CCAddSpriteFramesWithFile(Lose_plist);
    loseBatchNode = CCSpriteBatchNode::create(Lose_png);
    this->addChild(loseBatchNode);
    
    CCAddSpriteFramesWithFile(hitfish_plist);
    hitFishBatchNode = CCSpriteBatchNode::create(hitfish_png);
    this->addChild(hitFishBatchNode);
    
    CCAddSpriteFramesWithFile(wineffect_plist);
    CCSpriteBatchNode *wineffetBatchNode = CCSpriteBatchNode::create(wineffect_png);
    this->addChild(wineffetBatchNode);
    
    isOpenVideo = true;
    
    loseLayer = CCLayerColor::create(ccc4(0, 0, 0, 125));
    loseLayer->setContentSize(CCSizeMake(S_WINSIZE_W, S_WINSIZE_H));
    loseLayer->setAnchorPoint(ccp(0, 0));
    this->addChild(loseLayer,1);
    SetScale(loseLayer);
    loseLayer->setPosition( ccp( 0, 0) );
    
    initElement();
    scrollView = NULL;
    addCrowAnimation();


	this->setKeypadEnabled(true);
    return true;
}

void GMLoseLayer::keyBackClicked() {

}

void GMLoseLayer::keyboardHook(int keyCode, int keyEvent){
	if (keyCode == kTypeEnterClicked)
	{
		this->againGame(NULL);
	}
}
//800 x 480
void GMLoseLayer::initElement()
{
    bg2 = CCSprite::create("lose/lose001.png");
    bg2->setPosition(ccp(WINSIZE_W/2, WINSIZE_H/2));
    SetScale2(bg2, Scale_Y);
    this->addChild(bg2,2);
    
    float tempW = Get_W( Get_Rect(bg2) );
    float tempH = Get_H( Get_Rect(bg2) );
    
    showScore(bg2);
    
    CCSprite *win9 = CCSprite::createWithSpriteFrameName("win009.png");
    CCSprite *win10 = CCSprite::createWithSpriteFrameName("win010.png");
    int n = GMAccessData::sharedAccessData()->getBootModeStatus();
    CCMenuItem *win009 = NULL;
    if (n==0) {
        win009 = CCMenuItemSprite::create(win10, win9, this, menu_selector(GMLoseLayer::chooseCard));
        win009->setEnabled(false);
    }
    else {
        win009 = CCMenuItemSprite::create(win9, win10, this, menu_selector(GMLoseLayer::chooseCard));
    }
    win009->setAnchorPoint(ccp(0,0));
    win009->setPosition(ccp(10,10));
    SetScale2(win009, Scale_X);
    
    CCSprite *win011_0 = CCSprite::createWithSpriteFrameName("lose007.png");
    CCSprite *win011_1 = CCSprite::createWithSpriteFrameName("lose008.png");
    CCMenuItem *win011 = CCMenuItemSprite::create(win011_0, win011_1, this, menu_selector(GMLoseLayer::againGame));
    win011->setAnchorPoint(ccp(1,0));
    win011->setPosition(ccp(WINSIZE_W-10,10));
    SetScale2(win011, Scale_X);
	CCScaleTo* scaleTo1 = CCScaleTo::create(0.5, 1.3*Scale_X);
	CCScaleTo* scaleTo2 = CCScaleTo::create(0.5, 1.0*Scale_X);
	CCSequence* seq = CCSequence::create(scaleTo1, scaleTo2, NULL);
	CCRepeatForever* rep = CCRepeatForever::create(seq);
	win011->runAction(rep);
    
    CCMenu *mainMenu = CCMenu::create(win009,win011,NULL);
    mainMenu->setPosition(CCPointZero);
    this->addChild(mainMenu,MENU_Layer);
    
    int starNum = 0;//GMPublicMethod::getStarNum();//GMAccessData::getEachLevelStar(currentLevel);
    for (int i = 0; i < 3; i++) {
        CCSprite *start = NULL;
        CCRect startRect;
        if (i < starNum) {
            start = CCSprite::createWithSpriteFrameName("wineffect010.png");
        }
        else {
            start = CCSprite::createWithSpriteFrameName("lose000.png");
        }
        startRect = Get_Box(start);
        start->setPosition(ccp(tempW/2+i*(88-10), tempH/2+88-10 ));
        bg2->addChild(start,3,10000+i);
    }
    
    //左右箭头按钮
    CCSprite *arrow1_0 = CCSprite::createWithSpriteFrameName("winarrow007.png");
    CCMenuItem *arrow1 = CCMenuItemSprite::create(arrow1_0, arrow1_0, this, menu_selector(GMLoseLayer::arrowAtion));
    CCSprite *arrow1_1 = CCSprite::createWithSpriteFrameName("winarrow008.png");
    CCMenuItem *arrow2 = CCMenuItemSprite::create(arrow1_1, arrow1_1, this, menu_selector(GMLoseLayer::arrowAtion1));
    CCMenu *arrowMenu = CCMenu::create(arrow1,arrow2,NULL);
    CCRect arrowR = Get_Box(arrow1);
    arrowMenu->setPosition(ccp(tempW/2, tempH/5+10));
    bg2->addChild(arrowMenu,MENU_Layer);
    arrowMenu->alignItemsHorizontallyWithPadding(tempW-40);
    //
    CCSprite *lose22 = CCSprite::createWithSpriteFrameName("lose022.png");
    GMPublicMethod::setRepeatAnimation(lose22, 22, 23, "lose", "png", 0.1,true);
    lose22->setPosition(ccp(100, 233));
    bg2->addChild(lose22,6);
    
    CCSprite *lose009 = CCSprite::createWithSpriteFrameName("lose009.png");
    lose009->setPosition(ccp(180, 180));
    bg2->addChild(lose009,6);
    
//    CCLayerColor *layer = CCLayerColor::create(ccc4(0, 0, 0, 125));
    CCLayer *layer = CCLayer::create();	//创建一个层，作为滚动的内容
    float tempWW = 0.0f;
    float tempHH = 0.0f;
    char strName[40] = {0};
    
    m_nCurPage = 0;
    int num1 = GMPublicMethod::sharedPublicMethod()->getHitNum();
    m_nTotalPage = num1/5 + (num1%5>0 ? 1:0);
    for (int i = 0;i < num1;i++){
        CCSprite *sprite = CCSprite::createWithSpriteFrameName("lose005.png");
        sprite->setAnchorPoint(ccp(0, 0));
        tempWW = Get_W(Get_Box(sprite));
        tempHH = Get_H(Get_Box(sprite));
        sprite->setPosition(ccp(0+i*(tempWW+5),0));
        layer->addChild(sprite);
        
        GMStrange *strange = GMPublicMethod::sharedPublicMethod()->getHitStrange(i);
        if (strange->_strange_id != 0) {
            sprintf(strName,"winyu%03d.png",strange->_strange_id);
            CCSprite *hitFish = CCSprite::createWithSpriteFrameName(strName);
            hitFish->setPosition(ccp(tempWW/2,tempHH/2));
            sprite->addChild(hitFish);
        }
                
        int num = GMPublicMethod::getScoreNum(strange->_countNum);
        UIRollNum *tempNum = UIRollNum::create();
        tempNum->setEffect("lose/lose006.png",num,19,18,NumStyleNormal0);
        tempNum->setNumber(strange->_countNum);
        tempNum->setPosition( ccp( 0+num*19, 21/2) );
        sprite->addChild(tempNum,MENU_NUM_Layer);
        
    }

    moveW = (tempWW+5)*5*m_nTotalPage;
    ZPLog("测试测试 ：： (%f,%f)",moveW,tempHH*Scale_Y);
    layer->setContentSize(CCSizeMake(moveW, tempHH*Scale_Y));
    ZPLog("测试测试2 ：： (%f,%f)",(tempW-80)*Scale_Y, tempHH*Scale_Y);
    
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
    bg2->addChild(scrollView,MENU_Layer);
    
    float temph = tempH-200*Scale_X;
    if (temph<0) {
        temph = tempH;
    }
    scrollRect = CCRect(bg2->getPosition().x-(tempW-100*Scale_X)/2,bg2->getPosition().y-tempH/2,tempW-100*Scale_X,temph);
   
    ZPLog("测试测试3 ：： (%f,%f)",scrollRect.size.width, scrollRect.size.height);
//    this->scheduleOnce(schedule_selector(GMLoseLayer::showStartPrompt), 0.5);
}


void GMLoseLayer::showStartPrompt(){
    int starNum = GMPublicMethod::getStarNum();
    for (int i = 0; i < 3; i++) {
        if (i < starNum) {
            CCSprite *start = (CCSprite*)bg2->getChildByTag(10000+i);
            if (start) {
                GMPublicMethod::setSpriteAnimation(start, 10, 15, "wineffect",0.2,this,callfuncN_selector(GMLoseLayer::addStarEffect));
            }
        }
    }
}

void GMLoseLayer::addStarEffect(CCNode *pNode)
{
	CCSprite *sprite = (CCSprite*)pNode;
    CCSprite *winEffect = CCSprite::createWithSpriteFrameName("wineffect016.png");
    GMPublicMethod::setRepeatAnimation(winEffect, 16, 19, "wineffect", "png",0.1,true);
    winEffect->setAnchorPoint(ccp(0, 0));
    sprite->addChild(winEffect);
}

void GMLoseLayer::addCrowAnimation()
{
    //乌鸦
    CCSprite *crow = CCSprite::createWithSpriteFrameName("lose010.png");
//    CCArray *temp = CCArray::create();
//    char crowName[20] = {0};
//    for (int j = 10; j <= 13; j++) {
//        sprintf(crowName,"lose%03d.png",j);
//        CCSpriteFrame *spriteFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(crowName);
//        temp->addObject(spriteFrame);
//    }
//    CCAnimation *m_pAnimation = CCAnimation::createWithSpriteFrames(temp,0.1);
//    CCAnimate *animate = CCAnimate::create(m_pAnimation);
//    CCRepeatForever *repeateF = CCRepeatForever::create(animate);
//    CCFiniteTimeAction *sequence = CCSequence::create(repeateF,NULL);
//    crow->runAction(sequence);
    GMPublicMethod::setRepeatAnimation(crow, 10, 13, "lose", "png", 0.1,true);
    this->addChild(crow,6);
    
    crow->setPosition(ccp(WINSIZE_W+Get_W(Get_Box(crow)), WINSIZE_H*3/4));
    
    CCMoveTo *moveTo = CCMoveTo::create(6, ccp(-Get_W(Get_Box(crow)), WINSIZE_H*3/4) );
    CCCallFuncN *callFuncN = CCCallFuncN::create(this, callfuncN_selector(GMLoseLayer::removeCrow));
    CCFiniteTimeAction *sequence1 = CCSequence::create(moveTo,callFuncN,NULL);
    crow->runAction(sequence1);

    GMAudioPlay::sharedAudioPlay()->playOtherEffect(Audio_Crow,false);
}

void GMLoseLayer::removeCrow(CCNode *pNode)
{
	CCSprite *sprite = (CCSprite*)pNode;
    this->removeChild(sprite, true);
}

void GMLoseLayer::showScore(CCSprite* pChild)
{
    float tempW = Get_W( Get_Rect(pChild) );
    float tempH = Get_H( Get_Rect(pChild) );
    int tempNum = GMPublicMethod::sharedPublicMethod()->getConsumptionEnergy();
    int num = GMPublicMethod::getScoreNum(tempNum);
    UIRollNum *score1 = UIRollNum::create();
    score1->setEffect("lose/lose002.png",num,211/10,21,NumStyleNormal0);
    score1->setNumber( tempNum );
    score1->setPosition(ccp(tempW/2+85+num*21, tempH/2+19));
    pChild->addChild(score1,11111);
    
    tempNum = GMPublicMethod::sharedPublicMethod()->getGainEnergy();
    num = GMPublicMethod::getScoreNum(tempNum);
    UIRollNum *score2 = UIRollNum::create();
    score2->setEffect("lose/lose003.png",num,211/10,21,NumStyleNormal0);
    score2->setNumber( tempNum );
    score2->setPosition(ccp(tempW/2+85+num*21, tempH/2-28));
    pChild->addChild(score2,11112);
}

void GMLoseLayer::arrowAtion(CCObject *pSender)
{
    GMAudioPlay::sharedAudioPlay()->playButtonEffect();
    setPage(false);
}

void GMLoseLayer::arrowAtion1(CCObject *pSender)
{
    GMAudioPlay::sharedAudioPlay()->playButtonEffect();
    setPage(true);
}

void GMLoseLayer::chooseCard(CCObject *pSender)
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

void GMLoseLayer::againGame(CCObject *pSender)
{
    GMPublicMethod::sharedPublicMethod()->setShow91Pause(false);
    
    GMAudioPlay::sharedAudioPlay()->playButtonEffect();
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
    this->removeAllChildrenWithCleanup(true);
    this->cleanup();
    
    CCScene *pScene = CCTransitionFade::create(0.0, GMMainLayer::scene(), ccWHITE);
    CCDirector::sharedDirector()->replaceScene(pScene);
}


void GMLoseLayer::registerWithTouchDispatcher()
{
    //1.x
    //CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate(this, std::numeric_limits <int> ::min() , true);
    //2.x
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, /*std::numeric_limits <int> ::min()*/kCCMenuHandlerPriority, true);
    //使用int最小值做最高优先级,并且吞掉事件true
    
    CCLayer::registerWithTouchDispatcher();
}

bool GMLoseLayer::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
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

void GMLoseLayer::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    if (moveW>0 && scrollView){
        scrollView->ccTouchMoved(pTouch, pEvent);
    }
    
}

void GMLoseLayer::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
    if (moveW>0 && scrollView){
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

void GMLoseLayer::setPage(bool plus)
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

void GMLoseLayer::ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent)
{
    
}

void GMLoseLayer::adjustScrollView(int arrow)
{
    // 关闭CCScrollView中的自调整
    if(scrollView){
        scrollView->unscheduleAllSelectors();
    // 调整位置
        CCPoint adjustPos = ccp(-(moveW/m_nTotalPage)*arrow,0);
    // 调整位置
        scrollView->setContentOffsetInDuration(adjustPos, 0.5);
    }
}

GMLoseLayer::~GMLoseLayer()
{
    this->removeChild(loseLayer, true);
    loseLayer = NULL;
    
    this->removeChild(loseBatchNode, true);
    loseBatchNode = NULL;

    this->removeChild(hitFishBatchNode, true);
    
    CCRemoveSpriteFrameByName(Lose_plist);
    CCRemoveTextureForKey(Lose_png);
    CCRemoveSpriteFrameByName(hitfish_plist);
    CCRemoveTextureForKey(hitfish_png);
    CCRemoveSpriteFrameByName(wineffect_plist);
    CCRemoveTextureForKey(wineffect_png);
    
//    GMAccessData::sharedAccessData()->purgeSharedAccessData();
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);

    scrollView = NULL;
    
    this->cleanup();
}



