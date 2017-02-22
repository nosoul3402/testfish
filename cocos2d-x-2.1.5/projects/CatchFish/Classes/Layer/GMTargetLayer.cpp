//
//  GMTargetLayer.cpp
//  FishX
//
//  Created by peng on 13-3-10.
//
//

#include "GMTargetLayer.h"
#include "../Config/GMHeaderConfig.h"
#include "SimpleAudioEngine.h"
#include "../PublicModels/UIRollNum.h"
#include "GMGameLayer.h"
#include "GMMainLayer.h"
#include "GMIntroLayer.h"
#include "GMCardLayer.h"

using namespace CocosDenshion;

CCScene* GMTargetLayer::scene()
{
    CCScene *scene = CCScene::create();
    GMTargetLayer *layer = GMTargetLayer::create();
    scene->addChild(layer);
    return scene;
}

GMTargetLayer::GMTargetLayer()
{}

GMTargetLayer::~GMTargetLayer()
{
    CCRemoveTextureForKey(hitfish_png);
    CCRemoveSpriteFrameByName(hitfish_plist);
    
    CCRemoveSpriteFrameByName(gamegoal_plist);
    CCRemoveTextureForKey(gamegoal_png);
    
    CCRemoveTextureForKey(gamegoal1_plist);
    CCRemoveTextureForKey(gamegoal1_png);

	GMPublicMethod::sharedPublicMethod()->targetLayer = NULL;
    this->cleanup();
    ZPLog("~GMTargetLayer");
}

// on "init" you need to initialize your instance
bool GMTargetLayer::init()
{
    if ( !CCLayerColor::init() )
    {
        return false;
    }
    this->setTouchEnabled(true);
    this->setOpacity(178.5);
    
    m_nCurPage = 0;
    scrollView = NULL;
	GMPublicMethod::sharedPublicMethod()->targetLayer = this;
    return true;
}


/*
 *  index == 3//无尽模式结束界面
 *  index1 无尽模式 阶段索引
 */
void GMTargetLayer::initElement(int index,int index1)
{
    CCAddSpriteFramesWithFile(gamegoal_plist);
    CCSpriteBatchNode *achievementBatchNode = CCSpriteBatchNode::create(gamegoal_png);
    this->addChild(achievementBatchNode);
    
    CCAddSpriteFramesWithFile(hitfish_plist);
    CCSpriteBatchNode *hitFishBatchNode = CCSpriteBatchNode::create(hitfish_png);
    this->addChild(hitFishBatchNode);
    
    bgSprite = CCSprite::create("game/gamegoal000.png");
    bgSprite->setAnchorPoint(ccp(0.5,0.7));
    SetScale2(bgSprite, Scale_Y);
    bgSprite->setPosition(ccp(WINSIZE_W/2, WINSIZE_H/2));
    this->addChild(bgSprite);
    
    bgRect = Get_Rect(bgSprite);
    CCSprite *gamegoal002 = CCSprite::createWithSpriteFrameName("gamegoal002.png");
    GMPublicMethod::setRepeatAnimation(gamegoal002, 2, 3, "gamegoal", "png", 0.2,true);
    gamegoal002->setAnchorPoint(ccp(0.5, 0));
    gamegoal002->setPosition(ccp(Get_W(bgRect)/2+15, Get_H(bgRect)));
    bgSprite->addChild(gamegoal002);

    m_nIndex = index1;

    if (index == 0 || index == 1) {
        CCSprite *gamegoal001 = CCSprite::createWithSpriteFrameName("gamegoal001.png");
        gamegoal001->setAnchorPoint(ccp(0.5, 0));
        gamegoal001->setPosition(ccp(Get_W(bgRect)/2, Get_H(bgRect)));
        bgSprite->addChild(gamegoal001);
    }
    if (index == 0) {
        CCSprite *gamegoal008 = CCSprite::createWithSpriteFrameName("gamegoal008.png");
        gamegoal008->setAnchorPoint(ccp(0.5, 0.5));
        gamegoal008->setPosition(ccp(Get_W(bgRect)/2, Get_H(bgRect)/2+12));
        bgSprite->addChild(gamegoal008);

        CCSprite *normalSprite = CCSprite::createWithSpriteFrameName("winarrow007.png");
        arrow1 = CCMenuItemSprite::create(normalSprite, NULL, this, menu_selector(GMTargetLayer::arrowAtion1));
        arrow1->setTag(1);
        arrow1->setAnchorPoint(ccp(1,0));
        arrow1->setPosition(ccp(15,50));
        CCSprite *normalSprite2 = CCSprite::createWithSpriteFrameName("winarrow008.png");
        arrow2 = CCMenuItemSprite::create(normalSprite2, NULL, this, menu_selector(GMTargetLayer::arrowAtion2));
        arrow2->setTag(2);
        arrow2->setAnchorPoint(ccp(0,0));
        arrow2->setPosition(ccp(Get_W(bgRect)-15,50));
    }
    else if (index == 1) {
        gamegoal011 = CCSprite::createWithSpriteFrameName("gamegoal011.png");
        gamegoal011->setAnchorPoint(ccp(0.5, 0.5));
        gamegoal011->setPosition(ccp(Get_W(bgRect)/2, Get_H(bgRect)/2+12));
        bgSprite->addChild(gamegoal011);
    }
    else if(index == 2){
        char tmepName[30] = {0};
        sprintf(tmepName, "mubiao%03d.png",index1);
        CCSprite *mubiao001 = CCSprite::createWithSpriteFrameName(tmepName);
        mubiao001->setAnchorPoint(ccp(0, 0));
        mubiao001->setPosition(ccp(10, Get_H(bgRect)));
        bgSprite->addChild(mubiao001);
        
        CCSprite *mubiao006 = CCSprite::createWithSpriteFrameName("mubiao006.png");
        mubiao006->setAnchorPoint(ccp(1, 0));
        mubiao006->setPosition(ccp(Get_W(bgRect)-10, Get_H(bgRect)));
        bgSprite->addChild(mubiao006);
        
        CCSprite *mubiao007 = CCSprite::createWithSpriteFrameName("mubiao007.png");
        mubiao007->setAnchorPoint(ccp(0, 0.5));
        mubiao007->setPosition(ccp(35, Get_H(bgRect)/2+5));
        bgSprite->addChild(mubiao007);
    }
    else if(index == 3)//无尽模式结束界面
    {
        CCAddSpriteFramesWithFile(gamegoal1_plist);
        CCSpriteBatchNode *achievementBatchNode1 = CCSpriteBatchNode::create(gamegoal1_png);
        this->addChild(achievementBatchNode1);
        
        CCSprite *win001 = CCSprite::create("game/gongxi1.png");
        win001->setAnchorPoint(ccp(0.5, 0));
        win001->setPosition(ccp(Get_W(bgRect)/2, Get_H(bgRect)));
        bgSprite->addChild(win001);
        
        CCSprite *win006 = CCSprite::createWithSpriteFrameName("win006.png");
        win006->setAnchorPoint(ccp(0.5, 1));
        win006->setPosition(ccp(Get_W(bgRect)/2, Get_H(bgRect)-15));
        bgSprite->addChild(win006);
       
        CCSprite *win007 = CCSprite::createWithSpriteFrameName("win007.png");
        win007->setAnchorPoint(ccp(0.5, 1));
        win007->setPosition(ccp(Get_W(bgRect)/2, Get_H(bgRect)-55));
        bgSprite->addChild(win007);
        
        CCSprite *win009 = CCSprite::createWithSpriteFrameName("win009.png");
        win009->setAnchorPoint(ccp(0, 1));
        win009->setPosition(ccp(Get_W(bgRect)/2-10, Get_H(bgRect)-60));
        bgSprite->addChild(win009);
        
        CCSprite *win010 = CCSprite::createWithSpriteFrameName("win010.png");
        win010->setAnchorPoint(ccp(0, 0));
        win010->setPosition(ccp(60, 40));
        bgSprite->addChild(win010);
      
    }
    
    CCMenuItemSprite *OKItem = NULL;
    CCMenuItemSprite *win002 = NULL;
    CCMenuItemSprite *win004 = NULL;
    
    if (index != 3) {
        CCSprite *normalSprite3 = CCSprite::createWithSpriteFrameName("gamegoal004.png");
        CCSprite *selectedImage3 = CCSprite::createWithSpriteFrameName("gamegoal005.png");
        
        OKItem = CCMenuItemSprite::create(normalSprite3, selectedImage3, this, menu_selector(GMTargetLayer::goAtion));
        OKItem->setTag(3);
        OKItem->setAnchorPoint(ccp(0.5,0.5));
        OKItem->setPosition(ccp(Get_W(bgRect)/2,10));
    }
    else {
        CCSprite *normalSprite3 = CCSprite::createWithSpriteFrameName("win2002.png");
        CCSprite *selectedImage3 = CCSprite::createWithSpriteFrameName("win2003.png");
        
        win002 = CCMenuItemSprite::create(normalSprite3, selectedImage3, this, menu_selector(GMTargetLayer::againAction));
        win002->setTag(3);
        win002->setAnchorPoint(ccp(0,0.5));
        win002->setPosition(ccp(-1,10));
        
        CCSprite *normalSprite4 = CCSprite::createWithSpriteFrameName("win2004.png");
        CCSprite *selectedImage4 = CCSprite::createWithSpriteFrameName("win2005.png");
        
        win004 = CCMenuItemSprite::create(normalSprite4, selectedImage4, this, menu_selector(GMTargetLayer::backHomeAtion));
        win004->setTag(3);
        win004->setAnchorPoint(ccp(1,0.5));
        win004->setPosition(ccp(Get_W(bgRect)+1,10));
    }
    
    CCMenu *mainMenu = NULL;
    if (index == 0) {
        mainMenu = CCMenu::create(arrow1,arrow2,OKItem,NULL);
    }
    else if (index == 1 || index == 2){
        mainMenu = CCMenu::create(OKItem,NULL);
    }
    else if(index == 3){
        mainMenu = CCMenu::create(win002,win004,NULL);
    }
    if (mainMenu) {
        mainMenu->setPosition(CCPointZero);
        bgSprite->addChild(mainMenu,MENU_Layer);
    }
}

//#pragma mark -
void GMTargetLayer::showBossIcon(int bossId)
{
    char strName2[20] = {0};
    sprintf(strName2,"winyu%03d.png",bossId);
    CCSprite *hitFish = CCSprite::createWithSpriteFrameName(strName2);
    hitFish->setAnchorPoint(ccp(0.5, 0));
    hitFish->setPosition(ccp(251/2,10));
    gamegoal011->addChild(hitFish);
}


void GMTargetLayer::showAllValue()
{
//    结果=(玩家失败时间/900-阶段时间*2)~ (玩家失败时间/900+阶段时间*2)浮动
    int temp = ((GMGameLayer*)_delegate)->getCountTotalTime();
    ZPLog("总时间 %d",temp);
    int tempRate = 0;
    float temp1 = temp/900.0f-(m_nIndex-1)*0.02f;
    float temp2 = temp/900.0f+(m_nIndex-1)*0.02f;
    if (temp!=0){
        int temp3 = temp1*100;
        int temp4 = temp2*100;
        int temp5 = temp4-temp3;
        tempRate = (rand()%temp5)+temp3;
        if(temp3 < 1 ){
            tempRate = 1;
        }
        if (temp4>=99) {
            tempRate = 99;
        }
    }
    
    int num = GMPublicMethod::getScoreNum(tempRate);
    
    UIRollNum *score = UIRollNum::create();
    score->setEffect1("game/win008.png",num,26,26,NumStyleNormal0);
    score->setNumber( tempRate );
    score->setPosition(ccp(Get_W(bgRect)/2-26-10, Get_H(bgRect)-70));
    bgSprite->addChild(score,11111);
    score->setScale(2);
//    CCScaleTo *scaleTo1 = CCScaleTo::create(0.5, 1.5);
    CCScaleTo *scaleTo2 = CCScaleTo::create(0.5, 1);
    CCFiniteTimeAction *sequence = CCSequence::create(scaleTo2,NULL);
    score->runAction(sequence);
    
    int tempNum = GMPublicMethod::sharedPublicMethod()->getConsumptionEnergy();
    num = GMPublicMethod::getScoreNum(tempNum);
    UIRollNum *score1 = UIRollNum::create();
    score1->setEffect("win/win002.png",num,22,21,NumStyleNormal0);
    score1->setNumber( tempNum );
    score1->setPosition(ccp(Get_W(bgRect)/2+num*22, 98));
    bgSprite->addChild(score1,11111);
    
    tempNum = GMPublicMethod::sharedPublicMethod()->getGainEnergy();
    num = GMPublicMethod::getScoreNum(tempNum);
    UIRollNum *score2 = UIRollNum::create();
    score2->setEffect("win/win003.png",num,22,21,NumStyleNormal0);
    score2->setNumber( tempNum );
    score2->setPosition(ccp(Get_W(bgRect)/2+num*22, 60) );
    bgSprite->addChild(score2,11112);
}


void GMTargetLayer::showScoreAndTime(int score,int time)
{
    int num = GMPublicMethod::getScoreNum(score);
    UIRollNum *tempNum = UIRollNum::create();
    tempNum->setEffect("game/number11.png",num,25,33,NumStyleNormal0);
    tempNum->setNumber(score);
    tempNum->setPosition( ccp(Get_W(bgRect)/2+25*num, Get_H(bgRect)/2+35) );
    bgSprite->addChild(tempNum);
    
    CCSprite *gamegoal006 = CCSprite::create("game/energe.png");
    gamegoal006->setAnchorPoint(ccp(0, 0.5));
    gamegoal006->setScale(1.5);
    gamegoal006->setPosition(ccp(Get_W(bgRect)/2+25*num, Get_H(bgRect)/2+35));
    bgSprite->addChild(gamegoal006);
    //
    num = GMPublicMethod::getScoreNum(time);
    UIRollNum *tempNum2 = UIRollNum::create();
    tempNum2->setEffect("game/number11.png",num,25,33,NumStyleNormal0);
    tempNum2->setNumber(time);
    tempNum2->setPosition( ccp(Get_W(bgRect)/2+25*num, Get_H(bgRect)/2-20) );
    bgSprite->addChild(tempNum2);
    
    CCSprite *mubiao008 = CCSprite::createWithSpriteFrameName("mubiao008.png");
    mubiao008->setAnchorPoint(ccp(0, 0.5));
    mubiao008->setPosition(ccp(Get_W(bgRect)/2+25/2+25*num, Get_H(bgRect)/2-20));
    bgSprite->addChild(mubiao008);
    
}

void GMTargetLayer::showFishKind(int score,CCArray*array)
{
    int num = GMPublicMethod::getScoreNum(score);
    UIRollNum *tempNum = UIRollNum::create();
    tempNum->setEffect("game/number11.png",num,25,33,NumStyleNormal0);
    tempNum->setNumber(score);
    tempNum->setPosition( ccp(Get_W(bgRect)/2+20, Get_H(bgRect)-33 ) );
    bgSprite->addChild(tempNum);
   
    if (array) {
        tempArray = CCArray::create();
        int kind = array->count();
        for (int i = 0; i < kind; i++) {
            GMStrange *strange = (GMStrange*)array->objectAtIndex(i);
            if (strange->_strange_id != 0) {
                tempArray->addObject(strange);
            }
        }
        kind = tempArray->count();
        
        CCLayer *layer = CCLayer::create();	//CCLayerColor::create(ccc4(0, 0, 0, 125)); 创建一个层，作为滚动的内容
        float tempWW = 0;
        float tempHH = 0;
        char strName2[30] = {0};
        //    char page[30] = {0};
        m_nCurPage = 0;
        m_nTotalPage = kind/4 + (kind%4>0 ? 1:0);
        for (int i = 0;i < kind;i++){
            CCSprite *sprite = CCSprite::createWithSpriteFrameName("win005.png");
            sprite->setAnchorPoint(ccp(0, 0));
            tempWW = Get_W(Get_Box(sprite));
            tempHH = Get_H(Get_Box(sprite));
            sprite->setPosition(ccp(0+i*(tempWW+5),0));
            layer->addChild(sprite);
            
            GMStrange *strange = (GMStrange*)tempArray->objectAtIndex(i);
            sprintf(strName2,"winyu%03d.png",strange->_strange_id);
            CCSprite *hitFish = CCSprite::createWithSpriteFrameName(strName2);
            hitFish->setPosition(ccp(tempWW/2,tempHH/2));
            sprite->addChild(hitFish);
            
            CCSprite *eSprite = CCSprite::createWithSpriteFrameName("gamegoal006.png");
            eSprite->setAnchorPoint(ccp(1, 0));
            eSprite->setPosition(ccp(tempWW-5, 10));
            sprite->addChild(eSprite);

            GMEnemy *enemy =  ((GMGameLayer*)_delegate)->checkpointsList->getEnemy(strange->_strange_id-1);
            int num = GMPublicMethod::getScoreNum(enemy->_numerical);
            UIRollNum *tempNum = UIRollNum::create();
            tempNum->setEffect("win/win006.png",num,18,18,NumStyleNormal0);
            tempNum->setNumber(enemy->_numerical);
            tempNum->setPosition( ccp( 0+3*18, 18) );
            sprite->addChild(tempNum,MENU_NUM_Layer);
            
        }
        if (m_nTotalPage == 1) {
            CCSprite *normalSprite = CCSprite::createWithSpriteFrameName("winarrow007b.png");
            arrow1->setNormalImage(normalSprite);
            normalSprite = CCSprite::createWithSpriteFrameName("winarrow008b.png");
            arrow2->setNormalImage(normalSprite);
        }
        else {
            CCSprite *normalSprite = CCSprite::createWithSpriteFrameName("winarrow007b.png");
            arrow1->setNormalImage(normalSprite);
        }
        float moveW = (tempWW+5)*4*m_nTotalPage;
        
        scrollView = CCScrollView::create();// 位置不是居中的
        scrollView->setPosition(CCPointZero);
        scrollView->setContentOffset(CCPointZero);
        layer->setContentSize(CCSizeMake(moveW, tempHH));		//设置滚动区域的大小
        scrollView->setViewSize(CCSizeMake((Get_W(bgRect)-45)*Scale_Y, tempHH*Scale_Y));
        scrollView->setContentSize(CCSizeMake(moveW, 320));		//设置显示区域的大小
        scrollView->setContainer(layer);                            //设置需要滚动的内容
        scrollView->setTouchEnabled(false);                         //因为要自己实现触摸消息，所以这里设为false
        scrollView->setDirection(kCCScrollViewDirectionHorizontal);  //设置滚动的方向，有三种可以选择
        scrollView->setPosition(ccp(23, 43));
        bgSprite->addChild(scrollView,4);
    
        scrollRect = CCRect(bgSprite->getPosition().x-Get_W(bgRect)/2,bgSprite->getPosition().y-Get_H(bgRect)/2,Get_W(bgRect),Get_H(bgRect));
    }
}

//#pragma mark -
//#pragma mark ation
void GMTargetLayer::arrowAtion1(CCObject *pSender)
{
    GMAudioPlay::sharedAudioPlay()->playButtonEffect();
    setPage(false);
}

void GMTargetLayer::arrowAtion2(CCObject *pSender){
    GMAudioPlay::sharedAudioPlay()->playButtonEffect();
    setPage(true);
}

void GMTargetLayer::goAtion(CCObject *pSender)
{
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
//    this->removeAllChildrenWithCleanup(true);
    GMAudioPlay::sharedAudioPlay()->playButtonEffect();
   ((GMGameLayer*)_delegate)->startGame();
}

void GMTargetLayer::setPage(bool plus)
{
    CCSprite *normalSprite1 = NULL;
    CCSprite *normalSprite2 = NULL;
    if (plus) {
        m_nCurPage++;
        if (m_nCurPage >= m_nTotalPage-1) {
            m_nCurPage = m_nTotalPage-1;
            normalSprite1 = CCSprite::createWithSpriteFrameName("winarrow007.png");
            normalSprite2 = CCSprite::createWithSpriteFrameName("winarrow008b.png");
        }
        else  {
            normalSprite1 = CCSprite::createWithSpriteFrameName("winarrow007.png");
            normalSprite2 = CCSprite::createWithSpriteFrameName("winarrow008.png");
        }
    }
    else {
        m_nCurPage--;
        if (m_nCurPage<=0) {
            m_nCurPage = 0;
            normalSprite1 = CCSprite::createWithSpriteFrameName("winarrow007b.png");
            normalSprite2 = CCSprite::createWithSpriteFrameName("winarrow008.png");
        }
        else  {
            normalSprite1 = CCSprite::createWithSpriteFrameName("winarrow007.png");
            normalSprite2 = CCSprite::createWithSpriteFrameName("winarrow008.png");
        }
    }
    
    arrow1->setNormalImage(normalSprite1);
    arrow2->setNormalImage(normalSprite2);
    
    adjustScrollView(m_nCurPage);
}


void GMTargetLayer::againAction(CCObject *pSender)
{
   ((GMGameLayer*)_delegate)->againAction();
}

void GMTargetLayer::backHomeAtion(CCObject *pSender)
{
    CCScene *pScene = CCTransitionFade::create(0.0, GMCardLayer::scene(), ccWHITE);
    CCDirector::sharedDirector()->replaceScene(pScene);
}

void GMTargetLayer::backAction()
{
    GMAudioPlay::sharedAudioPlay()->playButtonEffect();
    
    this->setTouchEnabled(false);

    this->removeAllChildrenWithCleanup(true);
}

void GMTargetLayer::adjustScrollView(int arrow)
{
    // 关闭CCScrollView中的自调整
    if (scrollView) {
        scrollView->unscheduleAllSelectors();
        // 调整位置
        CCPoint adjustPos;
        
        adjustPos = ccp((-(Get_W(bgRect)-50))*arrow,0);
        
        // 调整位置
        scrollView->setContentOffsetInDuration(adjustPos, 0.5);
    }
}

void GMTargetLayer::registerWithTouchDispatcher()
{
    //1.x
    //CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate(this, std::numeric_limits <int> ::min() , true);
    //2.x
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, /*std::numeric_limits <int> ::min()*/kCCMenuHandlerPriority, true);
    //使用int最小值做最高优先级,并且吞掉事件true
    
//    CCLayer::registerWithTouchDispatcher();
}
bool GMTargetLayer::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    if (scrollView) {
        CCPoint endPoint = CCDirector::sharedDirector()->convertToGL(pTouch->getLocationInView());
        ZPLog("(%f,%f,%f,%f)",scrollRect.origin.x,scrollRect.origin.y,scrollRect.size.width,scrollRect.size.height);
        ZPLog("(%f,%f)",endPoint.x,endPoint.y);
        if(GMPublicMethod::checkRectContainsPoint(scrollRect, endPoint)){
            tempx1 = endPoint.x;
            scrollView->ccTouchBegan(pTouch, pEvent);
        }
    }
    return true;
}

void GMTargetLayer::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
//    if (scrollView) {
//        scrollView->ccTouchMoved(pTouch, pEvent);
//    }
}

void GMTargetLayer::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
    if (scrollView) {
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

void GMTargetLayer::ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent)
{
    
}
