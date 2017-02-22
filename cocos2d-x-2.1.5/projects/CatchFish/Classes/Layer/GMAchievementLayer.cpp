//
//  GMAchievementLayer.cpp
//  FishX
//
//  Created by peng on 13-2-26.
//  成就
//

#include "SimpleAudioEngine.h"
#include "GMAchievementLayer.h"
#include "../Config/GMHeaderConfig.h"
#include "../Models/GMAchievement.h"
#include "../PublicModels/UIRollNum.h"

using namespace CocosDenshion;

CCScene* GMAchievementLayer::scene()
{
    CCScene *scene = CCScene::create();
    GMAchievementLayer *layer = GMAchievementLayer::create();
    scene->addChild(layer);
    return scene;
}

GMAchievementLayer::GMAchievementLayer()
{
    
}

GMAchievementLayer::~GMAchievementLayer()
{
    scrollView = NULL;
    background = NULL;
    CCRemoveSpriteFrameByName(achievement_plist);
    CCRemoveTextureForKey(achievement_png);
    
    CCRemoveSpriteFramesAndTextureForKey(achievement2_plist,achievement2_png);
    CCRemoveSpriteFramesAndTextureForKey(achievement3_plist,achievement3_png);
    
    achievementArray->removeAllObjects();
    achievementArray->release();
    achievementArray = NULL;
    
    achievementArray1->removeAllObjects();
    achievementArray1->release();
    achievementArray1 = NULL;
    
    this->cleanup();
    ZPLog("~GMAchievementLayer");
}

// on "init" you need to initialize your instance
bool GMAchievementLayer::init()
{
    if ( !CCLayerColor::init() )
    {
        return false;
    }
    setBgColor( ccc3(0, 0, 0) ,125);
    
    this->setTouchEnabled(true);
    background = CCSprite::create("game/achievement001.png");
    CCRect rect = background->getTextureRect();
    bg_w = rect.size.width;
    bg_h = rect.size.height;
	background->setPosition(ccp(WINSIZE_W/2, WINSIZE_H/2));
    SetScale2(background,Scale_X);
    this->addChild(background,0,111);
    
    m_nCurPage = 0;
    
    scrollRect = CCRect(50*Scale_X ,200*Scale_X,WINSIZE_W-50*Scale_X,WINSIZE_H-200*Scale_X);
    
    achievementArray = new CCArray();
    GMPublicMethod::getAchievementPrompFromFile(APromptList_plist,achievementArray);
    
    achievementArray1 = new CCArray();
    initElement();
    
    return true;
}

void GMAchievementLayer::initElement()
{
    CCAddSpriteFramesWithFile(achievement_plist);
    CCSpriteBatchNode *achievementBatchNode = CCSpriteBatchNode::create(achievement_png);
    this->addChild(achievementBatchNode);
    
    CCAddSpriteFramesWithFile(achievement2_plist);
    CCSpriteBatchNode *achievementBatchNode2 = CCSpriteBatchNode::create(achievement2_png);
    this->addChild(achievementBatchNode2);
    
    CCAddSpriteFramesWithFile(achievement3_plist);
    CCSpriteBatchNode *achievementBatchNode3 = CCSpriteBatchNode::create(achievement3_png);
    this->addChild(achievementBatchNode3);
    
    CCSprite *close = CCSprite::createWithSpriteFrameName("achievement002b.png");
    CCSprite *close1 = CCSprite::createWithSpriteFrameName("achievement002.png");
    CCRect rect = Get_Rect(close);
    CCMenuItem *closeItem = CCMenuItemSprite::create(close, close1, this, menu_selector(GMAchievementLayer::backAction));
    CCMenu *closeMenu = CCMenu::create(closeItem,NULL);
    closeMenu->setPosition( ccp( bg_w-56+Get_W(rect)/2, bg_h-94+Get_H(rect)/2 ));
    background->addChild(closeMenu,MENU_Layer);
    int tempCount = achievementArray->count();
   
    for (int i = 0; i < tempCount; i++) {
        GMAchievement *ach = (GMAchievement*)achievementArray->objectAtIndex(i);
        int status = GMAccessData::sharedAccessData()->getEachAchievementStatus(ach->_id);
        if (status == 1) {
            ach->_status = 1;
            achievementArray1->insertObject(ach,0);
        }
        else {
            achievementArray1->addObject(ach);
        }
    }
    
    CCLayerColor *layer = CCLayerColor::create(ccc4(0, 0, 0, 0));
    
    m_nTotalPage = tempCount/4+(tempCount%4 > 0 ? 1 : 0);
    		//设置滚动区域的大小
    char cellName[30] = {0};
    
    for (int i = 0; i < tempCount; i++) {
        CCSprite *achievementBg = CCSprite::createWithSpriteFrameName("achievement003.png");
        achievementBg->setAnchorPoint(ccp(0, 0));
        achievementBg->setPosition(ccp(0+i*(168+3), 0));
        float tempW = Get_W(Get_Box(achievementBg));
        float tempH = Get_H(Get_Box(achievementBg));
        layer->addChild(achievementBg);
        GMAchievement *ach = (GMAchievement*)achievementArray1->objectAtIndex(i);

        sprintf(cellName, "achievementzi%03d.png",ach->_id-1);
        CCSprite *title = CCSprite::createWithSpriteFrameName(cellName);
        title->setPosition(ccp( tempW/2-5, tempH-35));
        achievementBg->addChild(title);

        sprintf(cellName, "%s",ach->_note);
        CCLabelTTF *labelt = CCLabelTTF::create(cellName,"Marker Felt",20,CCSize(tempW-30, 86), kCCTextAlignmentCenter);
        labelt->setVerticalAlignment(kCCVerticalTextAlignmentCenter);
        labelt->setAnchorPoint(ccp(0.5, 0));
        labelt->setPosition( ccp( tempW/2 -5, tempH/2-90 ));
        labelt->setColor(ccc3(183, 69, 0));
        achievementBg->addChild(labelt);
        
        sprintf(cellName, "achievementtu%03d.png",ach->_id-1);
        CCSprite *picIconSprite = CCSprite::createWithSpriteFrameName(cellName);
        picIconSprite->setPosition(ccp( tempW/2-5, tempH/2+20));
        achievementBg->addChild(picIconSprite);
        
        int num = GMPublicMethod::getScoreNum(ach->_energe);
        UIRollNum *tempNum = UIRollNum::create();
        tempNum->setEffect1("game/achievement009.png",num,23,23,NumStyleNormal0);
        tempNum->setNumber(ach->_energe);
        tempNum->setPosition( ccp( tempW/2, 45) );
        achievementBg->addChild(tempNum);
        
        CCSprite *eSprite = CCSprite::createWithSpriteFrameName("achievement012.png");
        eSprite->setAnchorPoint(ccp(0.5,0));
        eSprite->setPosition(ccp(tempW/2, 11));
        eSprite->setScale(0.8);
        achievementBg->addChild(eSprite);
        
        if (ach->_status == 0) {
            CCSprite *bgSprite = CCSprite::createWithSpriteFrameName("achievement013.png");
            bgSprite->setAnchorPoint(ccp(0,0));
            bgSprite->setPosition(ccp(0, 0));
            achievementBg->addChild(bgSprite);
        }
    }
//    layer->setContentSize(CCSizeMake(710*m_nTotalPage, 248));
    moveW = 4*(168+3);
    layer->setContentSize(CCSizeMake(moveW*m_nTotalPage, 258));
    
    scrollView = CCScrollView::create();// 位置不是居中的
    scrollView->setPosition(CCPointZero);
    scrollView->setContentOffset(CCPointZero);
    scrollView->setViewSize(CCSizeMake((bg_w-120)*Scale_X, 258*Scale_X));
    scrollView->setContentSize(CCSizeMake(moveW*m_nTotalPage, 258*Scale_Y));		//设置显示区域的大小
    scrollView->setContainer(layer);                            //设置需要滚动的内容
    scrollView->setTouchEnabled(false);                         //因为要自己实现触摸消息，所以这里设为false
    scrollView->setDelegate(this);
    scrollView->setDirection(kCCScrollViewDirectionHorizontal);  //设置滚动的方向，有三种可以选择
    scrollView->setPosition(ccp(60, 90));
    background->addChild(scrollView,4);
    
    for (int  i = 0; i < m_nTotalPage; i++) {
        CCSprite *sprite = NULL;
        if (i == m_nCurPage) {
            sprite = CCSprite::createWithSpriteFrameName("achievement004.png");
        }
        else {
            sprite = CCSprite::createWithSpriteFrameName("achievement005.png");
        }
        sprite->setAnchorPoint(ccp(0, 0.5));
        float tempW = Get_W(Get_Box(sprite))+10;
//        sprite->setPosition( ccp(bg_w/2+(i-1)*Get_W(Get_Box(sprite))*2, 60) );
        sprite->setPosition( ccp((bg_w-tempW*m_nTotalPage)/2+i*tempW, 65) );
        background->addChild(sprite,1,10000+i);
        
    }
}

void GMAchievementLayer::setCurPageMark(int mark)
{
    for (int  i = 0; i < m_nTotalPage; i++) {
        CCSprite *sprite = (CCSprite*)background->getChildByTag(10000+i);
        CCSpriteFrame *spriteFrame = NULL;
        if (i == m_nCurPage) {
            spriteFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("achievement004.png");
        }
        else {
            spriteFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("achievement005.png");
        }
        sprite->setDisplayFrame(spriteFrame);
    }
}

void GMAchievementLayer::backAction(CCObject *pSender)
{
    GMAudioPlay::sharedAudioPlay()->playButtonEffect();
    
    this->setTouchEnabled(false);
    setBgColor( ccc3(0, 0, 0) ,0);
    this->removeAllChildrenWithCleanup(true);
}

void GMAchievementLayer::adjustScrollView(int arrow)
{
    // 关闭CCScrollView中的自调整
    ZPLog("arrow %d",arrow);
    
    scrollView->unscheduleAllSelectors();
    // 调整位置
    CCPoint adjustPos = ccp((-moveW)*arrow,0);
//    CCLOG("adjustPos (%f,%f)",adjustPos.x,adjustPos.y);
    // 调整位置
    scrollView->setContentOffsetInDuration(adjustPos, 0.5);
}

void GMAchievementLayer::scrollViewDidScroll(CCScrollView* view)
{
    
}

void GMAchievementLayer::scrollViewDidZoom(CCScrollView* view)
{
    
}

bool GMAchievementLayer::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
//    m_bTouchedMenu =
    CCPoint endPoint = CCDirector::sharedDirector()->convertToGL(pTouch->getLocationInView());
    ZPLog("(%f,%f),(%f,%f)",scrollRect.origin.x,scrollRect.origin.y,scrollRect.size.width,scrollRect.size.height);
    if(GMPublicMethod::checkRectContainsPoint(scrollRect, endPoint)){
        tempx1 = endPoint.x;
        scrollView->ccTouchBegan(pTouch, pEvent);
    }
//    tempx1 = scrollView->getContentOffset().x;
    
    return true;
}

void GMAchievementLayer::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
//    if (m_bTouchedMenu)
    {
        
    }
//     scrollView->ccTouchMoved(pTouch, pEvent);
}

void GMAchievementLayer::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
    scrollView->ccTouchEnded(pTouch, pEvent);

    CCPoint endPoint = CCDirector::sharedDirector()->convertToGL(pTouch->getLocationInView());
//    if(GMPublicMethod::checkRectContainsPoint(scrollRect, endPoint))
    {
        tempx2 = endPoint.x;
         CCLOG(" 起始点：%f <==> 结束点 %f)",tempx1,tempx2);
        
        if(tempx2 > tempx1){
            m_nCurPage--;
            if (m_nCurPage<=0) {
                m_nCurPage = 0;
            }
        }
        else if(tempx2 < tempx1){
            m_nCurPage++;
            if (m_nCurPage >= m_nTotalPage-1) {
                m_nCurPage = m_nTotalPage-1;
            }
            
        }
        adjustScrollView(m_nCurPage);
        setCurPageMark(m_nCurPage);
    }
}

void GMAchievementLayer::ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent)
{

}


