//
//  GMCardLayer.cpp
//  FishX
//
//  Created by peng on 12-12-24.
//
//

#include "GMCardLayer.h"
#include "GMIntroLayer.h"
#include "GMMainLayer.h"
#include "../Config/GMHeaderConfig.h"
#include "../PublicModels/ZPJNIHelper.h"
#include "../PublicModels/ZPDialogLayer.h"
#include "../PublicModels/GMBillingLayer.h"

using namespace cocos2d;

#define EL_W         (WINSIZE_W-90)
#define EL_H         (WINSIZE_H-75)

#define EL_Tag00     100
#define EL_Tag01     110
#define EL_Tag02     111

#define TOTAL_PAGE      4

CCScene* GMCardLayer::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    GMCardLayer *layer = GMCardLayer::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GMCardLayer::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
#if (JNIHELPER_INDEX == JNIHELPER_91_IOS)
    //PublicCPP::setNdToolBar(true);
#endif
    
//    renderTexture = CCRenderTexture::create(WINSIZE_W, WINSIZE_H);
//    renderTexture->begin();
//    this->visit();
//    renderTexture->end();
    
//    CCRemoveUnusedSpriteFrames();
    CCRemoveUnusedAllSpriteFrames();
    GMAudioPlay::sharedAudioPlay()->stopMyAllEffects();
    
    GMAudioPlay::sharedAudioPlay()->playBGMusic(Audio_Gmae1);
    
    GMPublicMethod::sharedPublicMethod()->setGameStatus(Checkpoints_Status);
    
    this->setContentSize(CCSize(WINSIZE_W, WINSIZE_H));
    
    billingModel= GMPublicMethod::sharedPublicMethod()->getBillingModel();
    
    CCSprite *background = CCSprite::create("Card/xuanzgk022bj.jpg");
	background->setPosition(ccp(WINSIZE_W/2, WINSIZE_H/2));
    SetScale(background);
    this->addChild(background,0);
    
    CCAddSpriteFramesWithFile(card_plist);
    cardBatchNode = CCSpriteBatchNode::create(card_png);
    this->addChild(cardBatchNode);
    
    CCAddSpriteFramesAndTextureFile(ui_checkpointsfish_plist,ui_checkpointsfish_png);
    
    checkpoints_tag = -1;
    initElement();
    this->setTouchEnabled(true);
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,kCCMenuHandlerPriority - 1, true);
    
    isShowDialogLayer = false;
	isSelectotherMenu   = false;
	isSelectCheckpoints = false;
    isLoadT = true;
    _isShowYiDong = false;
    return true;
}

void GMCardLayer::keyboardHook(int keyCode, int keyEvent) {
	if (keyEvent != kTypeEventKeyUp) return;
	if (keyCode == kTypeEnterClicked) {
		this->startAction(NULL);
	}
	else {
		int next = 0;
		if (keyCode == kTypeRightArrowClicked) {
			next = 1;
		}
		else if (keyCode == kTypeLeftArrowClicked) {
			next = -1;
		}
		if (next != 0) {

			GMCardLayer* layer = this;
			if (layer != NULL) {
				CCObject* levelMenuItem = layer->tempObj;
				CCMenuItemSprite* mit = (CCMenuItemSprite*)levelMenuItem;
				if (mit != NULL) {
					int nextTag = mit->getTag();
					int levelIndex = nextTag / 10;
					int cardIndex = nextTag % 10;
					cardIndex += next;
					char str[50];
					sprintf(str, "next level is %d, %d", levelIndex, cardIndex);
					CCLog(str);
					int turnPage = 0;
					if (cardIndex >= 5) {
						cardIndex = 1;
						levelIndex += 1;
						turnPage = 1;
					}
					if (cardIndex < 0) {
						cardIndex = 5;
						levelIndex -= 1;
						turnPage = -1;
					}

					if (levelIndex < 1 || levelIndex > TOTAL_PAGE) {
						return;
					}

					nextTag = levelIndex * 10 + cardIndex;


					CCNode* eachLevel = layer->m_pLayer->getChildByTag(EL_Tag00 + levelIndex);
					CCMenu* menu = (CCMenu*)eachLevel->getChildByTag(EL_Tag01);
					layer->tempObj = menu->getChildByTag(nextTag);
					if (turnPage != 0) {
						layer->setPage(turnPage == 1, false);
					}
					if (layer->tempObj != NULL) {
						layer->chooseLevel(layer->tempObj);
					}
					//m_pLayer->addChild(eachLevel, 1, EL_Tag00 + index);
					//eachLevel->addChild(menu, 1, EL_Tag01);
				}
			}
		}
	}
}

//#pragma mark - 
void GMCardLayer::intScorllView()
{
    m_pLayer = CCLayerColor::create(ccc4(0, 0, 0, 0));
    
    m_pLayer->setContentSize(CCSizeMake(EL_W*2, EL_H));
    
    m_pScrollView = CCScrollView::create();// 位置不是居中的
    m_pScrollView->setPosition(CCPointZero);
    m_pScrollView->setContentOffset(CCPointZero);
    		//设置滚动区域的大小
    m_pScrollView->setViewSize(CCSizeMake(EL_W, EL_H));
    m_pScrollView->setContentSize(CCSizeMake(EL_W*2, EL_H));		//设置显示区域的大小
    m_pScrollView->setContainer(m_pLayer);                            //设置需要滚动的内容
    m_pScrollView->setTouchEnabled(false);                         //因为要自己实现触摸消息，所以这里设为false
    //    scrollView->setDelegate(this);
    m_pScrollView->setDirection(kCCScrollViewDirectionHorizontal);  //设置滚动的方向，有三种可以选择
    m_pScrollView->setAnchorPoint(ccp(0.5, 0.5));
    m_pScrollView->setPosition(ccp((WINSIZE_W-EL_W)/2,(WINSIZE_H-EL_H)/2));
	//m_pScrollView->se
    this->addChild(m_pScrollView,4);
    
    checkpoints_index = 1;
    checkpoints_index = GMAccessData::sharedAccessData()->getCurrentCheckpoints();//GMPublicMethod::sharedPublicMethod()->getCheckpointsIndex();
    if(checkpoints_index>0){
        checkpoints_index --;
    }
//    if(checkpoints_index == 0)
//        checkpoints_index = 1;
    tempcheckpointsIndex = checkpoints_index;
    for (int i = 1; i <= TOTAL_PAGE; i++) {
        initEachLevel(i);
    }
//    
//    if(checkpoints_index!=1)
    setPage(true,false);

	chooseLevel(tempObj);
}


//#pragma mark - 

void GMCardLayer::showStart(int num,CCNode* pChild)
{
    for (int i = 0; i < 3; i ++) {
        CCSprite *start1 = NULL;
        if (i<num) {
            start1 = CCSprite::createWithSpriteFrameName("xuanzgk015.png");
        }
        else {
            start1 = CCSprite::createWithSpriteFrameName("xuanzgk016.png");
        }
        float w1 = Get_W( Get_Box(start1) );
        float w = Get_W( Get_Box(pChild) );
        float x = w/2+(i-1)*(w1);//w/2+35+(i-1)*(w1);
        start1->setPosition(ccp( x , Get_H( Get_Box(start1) )/2 ) );
        pChild->addChild(start1,1,i+Tag_Star1);
    }
}

void GMCardLayer::setRepeatScale(CCNode *node)
{
    CCScaleTo *scaleTo3 = CCScaleTo::create(0.5, Scale_X+0.2);
    CCScaleTo *scaleTo4 = CCScaleTo::create(0.5, Scale_X);
    CCActionInterval *sequence = (CCActionInterval*)CCSequence::create(scaleTo3,scaleTo4,NULL);
    CCRepeatForever *repeatForever = CCRepeatForever::create(sequence);
    node->runAction(repeatForever);
}

CCMenuItemSprite* GMCardLayer::addMenu(const char *normal,const char *selected,bool filpx,CCPoint point,SEL_MenuHandler selector,CCPoint anc){
    CCSprite *normalSprite1 = CCSprite::createWithSpriteFrameName(normal);
    if(filpx)
        normalSprite1->setFlipX(true);
    CCSprite *selectedSprite1 = CCSprite::createWithSpriteFrameName(selected);
    if(filpx)
        selectedSprite1->setFlipX(true);
    CCMenuItemSprite* tempItem = CCMenuItemSprite::create(normalSprite1, selectedSprite1, this, selector);
    SetScale2(tempItem, Scale_X);
    tempItem->setPosition( point );
    tempItem->setAnchorPoint( anc );
    return tempItem;
}

void GMCardLayer::initElement(){
    
    CCSprite *title1 = CCSprite::createWithSpriteFrameName("xuanzgk023.png");
    SetScale2(title1, Scale_X);
    title1->setPosition(ccp(WINSIZE_W/2, WINSIZE_H-Get_H(Get_Box(title1))/2-5));
    cardBatchNode->addChild(title1 ,1);
    
    checkpointTheme = CCSprite::createWithSpriteFrameName("checkpointTheme1.png");
    SetScale2(checkpointTheme, Scale_X);
    checkpointTheme->setPosition(ccp(WINSIZE_W/2, WINSIZE_H-Get_H(Get_Box(checkpointTheme))/2-22*Scale_X));
    cardBatchNode->addChild(checkpointTheme ,1);
    
    arrow1 = NULL;
//    CCSprite *normalSprite1 = CCSprite::createWithSpriteFrameName("xuanzgk011.png");
//    normalSprite1->setFlipX(true);
//    CCSprite *selectedSprite1 = CCSprite::createWithSpriteFrameName("xuanzgk011.png");
//    selectedSprite1->setFlipX(true);
//    arrow1 = CCMenuItemSprite::create(normalSprite1, selectedSprite1, this, menu_selector(GMCardLayer::arrowAtion1));
//    SetScale2(arrow1, Scale_X);
//    arrow1->setPosition(ccp(40*Scale_X, WINSIZE_H/2-20*Scale_X));
    CCPoint point = ccp(40*Scale_X, WINSIZE_H/2-20*Scale_X);
    arrow1 = addMenu("xuanzgk011.png","xuanzgk011.png",true,point,menu_selector(GMCardLayer::arrowAtion1),ccp(0.5,0.5));
    arrow2 = NULL;
//    CCSprite *normalSprite2 = CCSprite::createWithSpriteFrameName("xuanzgk010.png");
//    CCSprite *selectedSprite2 = CCSprite::createWithSpriteFrameName("xuanzgk011.png");
//    arrow2 = CCMenuItemSprite::create(normalSprite2, selectedSprite2, this, menu_selector(GMCardLayer::arrowAtion2));
//    SetScale2(arrow2, Scale_X);
//    arrow2->setPosition(ccp(WINSIZE_W-40*Scale_X, WINSIZE_H/2-20*Scale_X));
    point = ccp(WINSIZE_W-40*Scale_X, WINSIZE_H/2-20*Scale_X);
    arrow2 = addMenu("xuanzgk011.png","xuanzgk011.png",false,point,menu_selector(GMCardLayer::arrowAtion2),ccp(0.5,0.5));
    setRepeatScale(arrow2);
    /*
     *  下面的三个选择按钮
     */
//    CCSprite *xuanzgk005 = CCSprite::createWithSpriteFrameName("xuanzgk005.png");
//    CCSprite *xuanzgk006 = CCSprite::createWithSpriteFrameName("xuanzgk006.png");
//    CCMenuItemSprite *back1 = CCMenuItemSprite::create(xuanzgk005, xuanzgk006, this, menu_selector(GMCardLayer::backAction));
//    SetScale2(back1, Scale_X);
//    back1->setAnchorPoint(ccp(0,0));
//    back1->setPosition(ccp(10*Scale_X,5*Scale_X));
    point = ccp(10*Scale_X,5*Scale_X);
    CCMenuItemSprite *back1 = addMenu("xuanzgk005.png","xuanzgk006.png",false,point,menu_selector(GMCardLayer::backAction),ccp(0,0));
    
//    CCSprite *xuanzgk001 = CCSprite::createWithSpriteFrameName("xuanzgk001.png");
//    CCSprite *xuanzgk002 = CCSprite::createWithSpriteFrameName("xuanzgk002.png");
//    CCMenuItem *gold = CCMenuItemSprite::create(xuanzgk001, xuanzgk002, this, menu_selector(GMCardLayer::goleAction));
//    SetScale2(gold, Scale_X);
//    gold->setAnchorPoint(ccp(0.5,0));
//    gold->setPosition(ccp(WINSIZE_W/2,5*Scale_X));
    point = ccp(WINSIZE_W/2,5*Scale_X);
    CCMenuItemSprite *gold = addMenu("xuanzgk001.png","xuanzgk002.png",false,point,menu_selector(GMCardLayer::goleAction),ccp(0.5,0));
    
//    CCSprite *xuanzgk004 = CCSprite::createWithSpriteFrameName("xuanzgk004.png");
//    startMenu = CCMenuItemSprite::create(xuanzgk004, xuanzgk004, this, menu_selector(GMCardLayer::startAction));
//    SetScale2(startMenu, Scale_X);
//    startMenu->setEnabled(false);
//    startMenu->setAnchorPoint(ccp(1,0));
//    startMenu->setPosition(ccp(WINSIZE_W-10*Scale_X,5*Scale_X));
    point = ccp(WINSIZE_W-10*Scale_X,5*Scale_X);
    startMenu = addMenu("xuanzgk004.png","xuanzgk004.png",false,point,menu_selector(GMCardLayer::startAction),ccp(1,0));
    startMenu->setEnabled(false);
    
    otherMenu = CCMenu::create(arrow1,arrow2,back1,gold,startMenu,NULL);
    otherMenu->setPosition(CCPointZero);
    this->addChild(otherMenu,6);
    
    int num = GMAccessData::sharedAccessData()->getCurrentLevel();
    if (num==0) {
        GMAccessData::sharedAccessData()->saveCurrentLevel(11);
    }
    
    int Open = GMAccessData::sharedAccessData()->getOpenCheckpoints(11);
    if (Open == 0) {
        GMAccessData::sharedAccessData()->saveOpenCheckpoints(11,1);
    }
    tempW = 214;
    tempH = 174;
    
    intScorllView();
    
//     setPage(true);
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#endif
    this->setKeypadEnabled(true);
    
    this->scheduleOnce(schedule_selector(GMCardLayer::showMoney), 1);
}

void GMCardLayer::showMoney(float dt)
{
    CCSprite *showenergy = CCSprite::createWithSpriteFrameName("xuanzgk008.png");
    showenergy->setAnchorPoint(ccp(0,1));
    SetScale2(showenergy, Scale_X);
    CCRect rectE = Get_Rect(showenergy);
    showenergy->setPosition(ccp(30*Scale_X, WINSIZE_H-20*Scale_X));
    this->addChild(showenergy);
    
    int tempM = GMAccessData::sharedAccessData()->getTotalMoneyNum();
    moneyNum = GMPublicMethod::getScoreNum(tempM);
    m_pTotalEnergy = UIRollNum::create();
    m_pTotalEnergy->setEffect("game/mainmenuTask004a.png",moneyNum,19,20,NumStyleNormal0);
    m_pTotalEnergy->setNumber(tempM);
    m_pTotalEnergy->setPosition(ccp(Get_W(rectE)-30, Get_H(rectE)/2-2));
    showenergy->addChild(m_pTotalEnergy,MENU_NUM_Layer);
}

void GMCardLayer::setMoney(){
    int tempM = GMAccessData::sharedAccessData()->getTotalMoneyNum();
    int num2 = GMPublicMethod::getScoreNum(tempM);
    if (num2 > moneyNum) {
        moneyNum = num2;
        m_pTotalEnergy->setEffect("game/mainmenuTask004a.png",moneyNum,19,20,NumStyleNormal0);
    }
     m_pTotalEnergy->setNumber(tempM);
}

void GMCardLayer::initEachLevel(int index)
{
    level = 10*index;
    
    CCLayerColor *eachLevel = CCLayerColor::create();//ccc4(0, 0, 0, 125)
    eachLevel->setContentSize(CCSizeMake(EL_W, EL_H));
//    eachLevel->setAnchorPoint(ccp(0.5, 0.5));
//    eachLevel->setPosition(ccp((WINSIZE_W-EL_W)/2,(WINSIZE_H-EL_H)/2));
    eachLevel->setPosition(ccp(0+EL_W*(index-1), 0));
    m_pLayer->addChild(eachLevel,1,EL_Tag00+index);

    CCSprite *line = CCSprite::createWithSpriteFrameName("xuanzgk014.png");
    SetScale2(line, Scale_X);
    line->setPosition(ccp(EL_W*3/5+7+EL_W*(index-1), EL_H/2));
    m_pLayer->addChild(line,0);
    
    CCArray *array = CCArray::create();
    CCSprite *normalSprite[5];
    CCMenuItem *tempItem[5];
    for (int i = 0; i < 5; i++) {
        normalSprite[i] = CCSprite::createWithSpriteFrameName("xuanzgk013.png");
        tempItem[i] = CCMenuItemSprite::create(normalSprite[i], NULL, this, menu_selector(GMCardLayer::chooseLevel));
        int tempTag = level+(i+1);
        if(i==3)
            tempTag = level+(4+1);
        else if(i==4)
            tempTag = level+(3+1);
        tempItem[i]->setTag(tempTag);
        tempItem[i]->setEnabled(false);
        array->addObject(tempItem[i]);
        tempItem[i] = NULL;
        normalSprite[i] = NULL;
    }
    
    CCMenu *menu = CCMenu::createWithArray(array);
    menu->setPosition(CCPointZero);
    eachLevel->addChild(menu,1,EL_Tag01);
//    menu->setTouchEnabled(false);
    //上一个关的选择的关卡索引
    int num = GMAccessData::sharedAccessData()->getCurrentLevel();
    //开启的关卡

//    if(index==1)
//    {
//        for (int i = 1; i <= 5; i++) {
//            GMAccessData::sharedAccessData()->saveOpenCheckpoints(level+i,1);
//        }
//    }
    int i=0;
    char helpstr[30] = {0};
    CCObject *child;
    
    CCARRAY_FOREACH(menu->getChildren(),child){
        CCMenuItemSprite*temp = (CCMenuItemSprite*)child;
        int tempTag = temp->getTag();
        CCSprite *normalSprite = NULL;
        int tempSmallIndex = tempTag%10;
        if (tempSmallIndex != 5) {
            normalSprite = CCSprite::createWithSpriteFrameName("xuanzgk013.png");
        }
        else {
           normalSprite = CCSprite::createWithSpriteFrameName("xuanzgk062.png");
        }
        if (normalSprite)
            temp->setNormalImage(normalSprite);
        
        CCPoint dstPoint = temp->getPosition();
        int offsetx = 214/2*Scale_X; // 原图的 宽高 214x174
        int offsety = 174/2*Scale_X;
        int x = i % 3;
        int y = i/3;
        CCPoint point;
        if (x == 0 && y == 0) {
            offsetx = -offsetx*2;
            offsety = offsety;
        }
        else if (x == 1 && y == 0) {
            offsetx = 0;
            offsety = offsety;
        }
        else if (x == 2 && y == 0) {
            offsetx = offsetx*2;
            offsety = offsety;
        }
        else if (x == 0 && y == 1 ) {
            offsetx = -offsetx-10;
            offsety = -offsety*y;
        }
        else if (x == 1 && y == 1 ){
            offsetx = offsetx+10;
            offsety = -offsety*y;
        }
        temp->setPosition(ccp( EL_W/2 + offsetx, EL_H/2+offsety));
        
        if (tempSmallIndex != 5){
            //标题
            sprintf(helpstr,"xuanzgk_%03d.png",tempTag);
            CCSprite *title = CCSprite::createWithSpriteFrameName(helpstr);
            point = ccp((tempW)/2,tempH-Get_H(Get_Box(title))-12);
            title->setPosition(point);
            temp->addChild(title,1,Tag_Title);
        }

        //每关的是鱼的图标
		sprintf(helpstr,"checkpointsfish%03d.png",tempTag);
		CCSprite *sprite = CCSprite::createWithSpriteFrameName(helpstr);
		sprite->setPosition(ccp((tempW)/2,tempH/2));
		temp->addChild(sprite,1,Tag_Fish);
        
        int status = GMAccessData::sharedAccessData()->getOpenCheckpoints(temp->getTag());
        if (status == 1) {

            int starNum = GMAccessData::sharedAccessData()->getEachLevelStar(temp->getTag());
            temp->setEnabled(true);
            showStart(starNum,temp);
        }
        else if(status == 0){
            //未开启
            CCSprite *xBg = CCSprite::createWithSpriteFrameName("xuanzgk012.png");
            xBg->setAnchorPoint(ccp(0.5, 0.5));
            xBg->setPosition(ccp((tempW)/2,tempH/2-10));
            temp->addChild(xBg,2,Tag_xBg);
            //未开启
            CCSprite *coverBg = CCSprite::createWithSpriteFrameName("xuanzgk013c.png");
            coverBg->setAnchorPoint(ccp(0.5, 0.5));
            coverBg->setPosition(ccp((tempW)/2,tempH/2));
            temp->addChild(coverBg,1,Tag_Cover);
        }
        
        if (num == temp->getTag()) {
			this->tempObj = temp;
        }

        SetScale2(temp, Scale_X);
        i++;
    }
}

void GMCardLayer::chooseLevel(CCObject *object)
{
    CCMenuItem *tempItem = (CCMenuItem*)object;
    int tempTag = tempItem->getTag();
    if (checkpoints_index != tempTag/10) {
        return;
    }
    
    ZPLog("tag %d",checkpoints_tag);
    if (checkpoints_tag == tempTag) {
        return;
    }
    
    tempcheckpointsIndex = checkpoints_index;
     
    GMPublicMethod::sharedPublicMethod()->setGameMode(Story_Mode);
    
    GMAudioPlay::sharedAudioPlay()->playOtherEffect(Audio_Waves,false);
    
    if (startMenu->isEnabled() == false) {
        CCSprite *xuanzgk003 = CCSprite::createWithSpriteFrameName("xuanzgk003.png");
        CCSprite *xuanzgk004 = CCSprite::createWithSpriteFrameName("xuanzgk004.png");
        startMenu->setEnabled(true);
        startMenu->setNormalImage(xuanzgk003);
        startMenu->setSelectedImage(xuanzgk004);
    }
    
    checkpoints_tag = tempTag;
    
    CCObject *child;
    CCSprite *normalSprite = NULL;
    char helpstr[30] = {0};
    
    //this->unschedule(schedule_selector(GMCardLayer::removeWaves));
    for (int i = 1; i <= TOTAL_PAGE; i++) {
        CCLayer *eachLevel = (CCLayer*)m_pLayer->getChildByTag(EL_Tag00+i);
        CCMenu *menu = (CCMenu*)eachLevel->getChildByTag(EL_Tag01);
        CCARRAY_FOREACH(menu->getChildren(),child){
            CCMenuItemSprite*temp = (CCMenuItemSprite*)child;
            int tempTag = temp->getTag();
            CCSprite *title = NULL;
            if(tempTag%10 != 5)
                title = (CCSprite*)temp->getChildByTag(Tag_Title);
            CCSprite *socreTitle = (CCSprite*)temp->getChildByTag(Tag_SocreTitle);
            if (socreTitle) {
                socreTitle->stopAllActions();
                temp->removeChild(socreTitle, true);
            }
            UIRollNum *maxSocre = (UIRollNum*)temp->getChildByTag(Tag_MaxSocre);
            if (maxSocre) {
                maxSocre->stopAllActions();
                temp->removeChild(maxSocre, true);
            }
            if (checkpoints_tag == tempTag) {
                if(tempTag%10 != 5){
                    normalSprite = CCSprite::createWithSpriteFrameName("xuanzgk013b.png");
                }
                else {
                    normalSprite = CCSprite::createWithSpriteFrameName("xuanzgk061.png");
                }
                
                temp->setNormalImage(normalSprite);
                // 标题
                if (title) {
                    CCPoint point = ccp((tempW)/2,tempH-Get_H(Get_Box(title))-5);
                    title->setPosition(point);
                    CCScaleTo *scale1 = CCScaleTo::create(0.5, 0.7);
                    CCScaleTo *scale2 = CCScaleTo::create(0.5, 1);
                    CCActionInterval *sequence = (CCActionInterval*)CCSequence::create(scale1,scale2,NULL);
                    CCRepeatForever *repeateF = CCRepeatForever::create(sequence);
                    title->runAction(repeateF);
                }
                
                //移除关卡上的鱼的图标
                CCSprite *sprite = (CCSprite*)temp->getChildByTag(Tag_Fish);
                temp->removeChild(sprite, true);
                //选中关卡后出现场景的小图标
                sprintf(helpstr,"xuanzgk05%d.png",checkpoints_index-1);
                CCSprite *tempBG = CCSprite::createWithSpriteFrameName(helpstr);
                tempBG->setPosition( ccp(tempW/2,tempH/2) );
                temp->addChild(tempBG,1,Tag_Bg);
                //
                CCSprite *tempWaves = CCSprite::createWithSpriteFrameName("xuanzgk056.png");
                tempWaves->setPosition( ccp(tempW-50,tempH/2) );
                temp->addChild(tempWaves,2,Tag_Waves);
                GMPublicMethod::setRepeatAnimation(tempWaves, 56, 58, "xuanzgk", "png", 0.1,true);
                CCMoveTo *moveTo = CCMoveTo::create(1, ccp(76,tempH/2));
                CCCallFunc *callFun = CCCallFunc::create(this, callfunc_selector(GMCardLayer::removeWaves));
                CCActionInterval *sequence1 = (CCActionInterval*)CCSequence::create(moveTo,callFun,NULL);
                tempWaves->runAction(sequence1);
            }
            else {
                CCSprite *sprite = (CCSprite*)temp->getChildByTag(Tag_Fish);
                if (!sprite) {
                    sprintf(helpstr,"checkpointsfish%03d.png",tempTag);
                    CCSprite *sprite = CCSprite::createWithSpriteFrameName(helpstr);
                    sprite->setPosition(ccp((tempW)/2,tempH/2));
                    temp->addChild(sprite,1,Tag_Fish);
                }
                
                CCSprite *tempBG = (CCSprite*)temp->getChildByTag(Tag_Bg);
                if (tempBG) {
                    temp->removeChild(tempBG, true);
                }
                
                CCSprite *tempWaves =(CCSprite*)temp->getChildByTag(Tag_Waves);
                if (tempWaves) {
                    tempWaves->stopAllActions();
                    temp->removeChild(tempWaves, true);
                }
                
                if (title) {
                    CCPoint point = ccp((tempW)/2,tempH-Get_H(Get_Box(title))-12);
                    title->setPosition(point);
                    title->setScale(1);
                    title->stopAllActions();
                }
                if(tempTag%10 != 5){
                    normalSprite = CCSprite::createWithSpriteFrameName("xuanzgk013.png");
                }
                else {
                    normalSprite = CCSprite::createWithSpriteFrameName("xuanzgk062.png");
                }
                temp->setNormalImage(normalSprite);
            }
        }
    }

    GMPublicMethod::sharedPublicMethod()->setCheckpointsIndex(checkpoints_index);
    
    GMAccessData::sharedAccessData()->saveCurrentLevel(checkpoints_tag);
    
    ZPLog("chooseLevel %d",checkpoints_tag);
}

void GMCardLayer::removeWaves()
{
    CCObject *child;
    CCLayer *eachLevel = (CCLayer*)m_pLayer->getChildByTag(EL_Tag00 +tempcheckpointsIndex);
    CCMenu *menu = (CCMenu*)eachLevel->getChildByTag(EL_Tag01);
    CCARRAY_FOREACH(menu->getChildren(),child){
        CCMenuItemSprite*temp = (CCMenuItemSprite*)child;
        CCSprite *tempWaves = (CCSprite*)temp->getChildByTag(Tag_Waves);
        if (tempWaves) {
            temp->removeChild(tempWaves, true);
            //显示最高分
            CCSprite *socreT = CCSprite::createWithSpriteFrameName("xuanzgk054.png");
            socreT->setPosition(ccp(tempW/2,tempH/2+Get_H( Get_Box(socreT))/2 ));
            socreT->setScale(0);
            temp->addChild(socreT,3,Tag_SocreTitle);
            
            CCScaleTo*scaleTo1 = CCScaleTo::create(0.5, 1.5);
            CCScaleTo*scaleTo2 = CCScaleTo::create(0.5, 1);
            CCActionInterval *sequence1 = (CCActionInterval*)CCSequence::create(scaleTo1,scaleTo2,NULL);
            socreT->runAction(sequence1);
            
            int tempM = GMAccessData::sharedAccessData()->getEachLevelScore(checkpoints_tag);
            int num = GMPublicMethod::getScoreNum(tempM);
            UIRollNum *maxSocre = UIRollNum::create();
            maxSocre->setEffect1("Card/xuanzgk055.png",num,23,22,NumStyleNormal0);
            maxSocre->setNumber(tempM);
            maxSocre->setPosition(ccp( (tempW)/2, tempH/2-20 ));
            maxSocre->setScale(0);
            temp->addChild(maxSocre,3,Tag_MaxSocre);
            CCScaleTo*scaleTo11 = CCScaleTo::create(0.5, 1.5);
            CCScaleTo*scaleTo22 = CCScaleTo::create(0.5, 1);
            CCActionInterval *sequence2 = (CCActionInterval*)CCSequence::create(scaleTo11,scaleTo22,NULL);
            maxSocre->runAction(sequence2);
        }
    }
}


//#pragma mark -
//#pragma mark ation
void GMCardLayer::arrowAtion1(CCObject *pSender)
{
	CCMenuItemSprite *itemSprite = (CCMenuItemSprite *)pSender;
    GMAudioPlay::sharedAudioPlay()->playButtonEffect();
    setPage(false,true);
}

void GMCardLayer::arrowAtion2(CCObject *pSender){

	CCMenuItemSprite *itemSprite = (CCMenuItemSprite *)pSender;
    GMAudioPlay::sharedAudioPlay()->playButtonEffect();
    setPage(true,true);
}

void GMCardLayer::backAction(CCObject *pSender){
    this->cleanup();
    GMAudioPlay::sharedAudioPlay()->playButtonEffect();
    
    CCScene *pScene = CCTransitionFade::create(0.0, GMIntroLayer::scene(), ccWHITE);
    CCDirector::sharedDirector()->replaceScene(pScene);
}

void GMCardLayer::goleAction(CCObject *pSender)
{
    GMAudioPlay::sharedAudioPlay()->playOtherEffect(Audio_Button,false);
    switch (billingModel) {
        case B_Free:{
            if(isShowDialogLayer  == false){
                ZPDialogLayer *dialogLayer = ZPDialogLayer::create();
                dialogLayer->initView("game/gamegoal000.png", NULL);
                dialogLayer->addPromptTexture("game/gamegoal015.png");
                dialogLayer->setSelectorTarget(this);
                dialogLayer->setSELCallFun(callfuncN_selector(GMCardLayer::removeDialogLayer));
                dialogLayer->setAnimation(true,1.5);
                this->addChild(dialogLayer,10);
                isShowDialogLayer = true;
            }
        }   break;
        case B_TengXunBilling:
        case B_91:
        case B_91_IOS:
        case B_YiDong:
        case B_Telecom:
        case B_91_Android:
        case B_Unicom_Android:
        {
            addBilling(2,0);
        }   break;
        default:
            break;
    }
}

void GMCardLayer::removeDialogLayer(CCNode *dialog)
{
    ZPDialogLayer *dialogLayer = (ZPDialogLayer*)dialog;
    this->removeChild(dialogLayer, true);
    isShowDialogLayer = false;
}

void GMCardLayer::startAction(CCObject *pSender)
{
//    if(billingModel != B_Free){
////        if( billingModel != B_91_IOS)
//        {
//            int satatus =  GMAccessData::sharedAccessData()->getGenuineValidationStatus();
//            ZPLog("satatus  == %d",satatus);
//            if((billingModel==B_YiDong || billingModel==B_Telecom) && satatus != 2 ){
//                addBilling(1, 0);
//                return;
//            }
//            else if (satatus != 2 && checkpoints_tag > GoToEndless) {
//                addBilling(1, 0);
//                return;
//            }
//        }
//    }
    
    if (checkpoints_tag>0) {
        this->cleanup();
        
        GMPublicMethod::sharedPublicMethod()->setGameStatus(Target_Status);
        
        //this->unschedule(schedule_selector(GMCardLayer::removeWaves));
        GMAudioPlay::sharedAudioPlay()->playButtonEffect();
        
        CCScene *pScene = CCTransitionFade::create(0.0, GMMainLayer::scene(), ccWHITE);
        CCDirector::sharedDirector()->replaceScene(pScene);
    }
}

//#pragma mark - touch
void GMCardLayer::setPage(bool plus,bool isScroll)
{
    CCSprite *normalSprite1 = NULL;
    CCSprite *normalSprite2 = NULL;
    if (plus) {
        checkpoints_index++;
        if (checkpoints_index >= TOTAL_PAGE) {
            checkpoints_index = TOTAL_PAGE;
            normalSprite1 = CCSprite::createWithSpriteFrameName("xuanzgk010.png");
            normalSprite2 = CCSprite::createWithSpriteFrameName("xuanzgk011.png");
            setRepeatScale(arrow1);
            SetScale2(arrow2, Scale_X);
            arrow2->stopAllActions();
        }
        else  {
            normalSprite1 = CCSprite::createWithSpriteFrameName("xuanzgk010.png");
            normalSprite2 = CCSprite::createWithSpriteFrameName("xuanzgk010.png");
            if(checkpoints_index ==1){
                normalSprite1 = CCSprite::createWithSpriteFrameName("xuanzgk011.png");
            }
            else{
                setRepeatScale(arrow1);
            }
            setRepeatScale(arrow2);
            
        }
    }
    else {
        checkpoints_index--;
        if (checkpoints_index<=1) {
            checkpoints_index = 1;
            normalSprite1 = CCSprite::createWithSpriteFrameName("xuanzgk011.png");
            normalSprite2 = CCSprite::createWithSpriteFrameName("xuanzgk010.png");
            setRepeatScale(arrow2);
            SetScale2(arrow1, Scale_X);
            arrow1->stopAllActions();
        }
        else  {
            normalSprite1 = CCSprite::createWithSpriteFrameName("xuanzgk010.png");
            normalSprite2 = CCSprite::createWithSpriteFrameName("xuanzgk010.png");
            setRepeatScale(arrow2);
            setRepeatScale(arrow1);
        }
    }
    normalSprite1->setFlipX(true);
    arrow1->setNormalImage(normalSprite1);
    arrow2->setNormalImage(normalSprite2);
    
    ZPLog("checkpoints_index == %d",checkpoints_index);
    adjustScrollView(checkpoints_index,isScroll);

    if(checkpointTheme){
        char themeName[30] = {0};
        sprintf(themeName, "checkpointTheme%d.png",checkpoints_index);
        CCSpriteFrame *spriteFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(themeName);
        checkpointTheme->setDisplayFrame(spriteFrame);
    }
}

void GMCardLayer::adjustScrollView(int arrow,bool isScroll)
{
    arrow = arrow-1;
    // 关闭CCScrollView中的自调整
    m_pScrollView->unscheduleAllSelectors();
    // 调整位置
    CCPoint adjustPos = ccp((-EL_W)*arrow,0);
    // 调整位置
    float tempDt = 0.0f;
    if(isScroll)
        tempDt = 0.3f;
    m_pScrollView->setContentOffsetInDuration(adjustPos, tempDt);
}
//#pragma mark - touch

bool GMCardLayer::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    sPoint = CCDirector::sharedDirector()->convertToGL(pTouch->getLocationInView());
    tempx1 = sPoint.x;

    if(m_pScrollView){
        m_pScrollView->ccTouchBegan(pTouch,pEvent);
    }
    CCLayer *eachLevel = (CCLayer*)m_pLayer->getChildByTag(EL_Tag00+checkpoints_index);
    if (eachLevel) {
        CCMenu *menu = (CCMenu*)eachLevel->getChildByTag(EL_Tag01);
        menu->m_eState = kCCMenuStateWaiting;
        isSelectCheckpoints = menu->ccTouchBegan(pTouch, pEvent);
    }
    if(isSelectCheckpoints==false){
        otherMenu->m_eState = kCCMenuStateWaiting;
        isSelectotherMenu = otherMenu->ccTouchBegan(pTouch, pEvent);
    }
    return true;
}

void GMCardLayer::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    ePoint = CCDirector::sharedDirector()->convertToGL(pTouch->getLocationInView());
    float temp = ccpLength(ccpSub(sPoint,ePoint));
    if (isSelectCheckpoints && temp > 150) {
        CCLayer *eachLevel = (CCLayer*)m_pLayer->getChildByTag(EL_Tag00+checkpoints_index);
        if (eachLevel) {
            CCMenu *menu = (CCMenu*)eachLevel->getChildByTag(EL_Tag01);
            menu->ccTouchMoved(pTouch, pEvent);
        }
        isSelectCheckpoints = false;
    }
    
    if(m_pScrollView){
//        m_pScrollView->ccTouchMoved(pTouch,pEvent);
    }
    
    if(isSelectotherMenu && otherMenu && temp > 150){
        otherMenu->ccTouchMoved(pTouch, pEvent);
        isSelectCheckpoints = false;
    }
}

void GMCardLayer::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
    if(m_pScrollView){
//        m_pScrollView->ccTouchEnded(pTouch,pEvent);
    }
    ePoint = CCDirector::sharedDirector()->convertToGL(pTouch->getLocationInView());
    tempx2 = ePoint.x;
    
    //关卡按钮
    float temp = ccpLength(ccpSub(sPoint,ePoint));
    if (isSelectCheckpoints) {
        CCLayer *eachLevel = (CCLayer*)m_pLayer->getChildByTag(EL_Tag00+checkpoints_index);
        if (eachLevel) {
            CCMenu *menu = (CCMenu*)eachLevel->getChildByTag(EL_Tag01);
            menu->ccTouchEnded(pTouch, pEvent);
        }
        isSelectCheckpoints = false;
    }
    else {
		//dream 滑动屏幕
        if(tempx2 > tempx1 && temp > WINSIZE_W/4){
            setPage(false,true);
        }
        else if(tempx2 < tempx1 && temp > WINSIZE_W/4){
            setPage(true,true);
        }
    }
    
    if(isSelectotherMenu  && otherMenu/* && temp<100.0f*/){
        otherMenu->ccTouchEnded(pTouch, pEvent);
        isSelectotherMenu = false;
    }
}

void GMCardLayer::ccTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    if (isSelectCheckpoints) {
        CCLayer *eachLevel = (CCLayer*)m_pLayer->getChildByTag(EL_Tag00+checkpoints_index);
        if (eachLevel) {
            CCMenu *menu = (CCMenu*)eachLevel->getChildByTag(EL_Tag01);
            menu->ccTouchCancelled(pTouch, pEvent);
        }
        isSelectCheckpoints = false;
    }
    
    if(isSelectotherMenu){
        otherMenu->ccTouchCancelled(pTouch, pEvent);
        isSelectotherMenu = false;
    }
}

//void GMCardLayer::loadingBillingView(){
//    if(isLoadT){
//        CCAddSpriteFramesAndTextureFile(changeboom_plist,changeboom_png);
//        isLoadT = false;
//    }
//    
//}

void GMCardLayer::addchangeboom(){
    if(isLoadT){
        CCAddSpriteFramesAndTextureFile(changeboom_plist,changeboom_png);
        isLoadT = false;
    }
}

//#pragma mark -
//#pragma mark -  计费

//1 为正版验证，2为购买能量，3为购买技能，4为购买武器
void GMCardLayer::addBilling(int index,int index2){
    
    GMPublicMethod::sharedPublicMethod()->setShow91Pause(false);
    
    if(billingModel == B_YiDong){
        if (!_isShowYiDong) {
            _isShowYiDong = true;
            showYidongSdkView(index);
        }
    }
    else if(billingModel==B_Telecom){
        if(!_isShowYiDong){
            _isShowYiDong = true;
            showTelecomSMSView(index);
        }
    }
    else if(billingModel == B_91_Android && index == 1){
        ZPJNIHelper::setAllPay(6);
        this->schedule(schedule_selector(GMCardLayer::check91BillingPoint));
    }
    else{
    //#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        GMBillingLayer *billingLayer = GMBillingLayer::create();
        billingLayer->setDelegate(this);
        billingLayer->setIndex(index);
        billingLayer->setStartBliling(false);
        billingLayer->setClassType(2);
        switch (index) {
            case 1:{
                if(billingModel == B_YiDong) {
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
                else if(billingModel == B_Unicom_Android){
                    billingLayer->showSecondaryConfirmationTips(0);
                }
                else {
//                    腾讯正版验证暂时注销2次确认
                    billingLayer->showSecondaryConfirmationTips(0);
                }
            }   break;
            case 2:{
                if(billingModel == B_91_IOS || billingModel == B_91_Android){
                    billingLayer->show91Shop();
                }
                else {
                    billingLayer->showThePurchaseOfEnergy(2,1);
                }
            }   break;
            case 6:{
                addchangeboom();
                billingLayer->setStartBliling(true);
                billingLayer->showGenuineValidationTips();
    //            billingLayer->showSecondaryConfirmationTips(0);
            }   break;
            case 7:{
                billingLayer->show91MobileView();
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

void GMCardLayer::removeBilling(int index,bool _isClickClose,int tag){
  
#if (JNIHELPER_INDEX == JNIHELPER_91_IOS)
    if( _isClickClose /*|| PublicCPP::getMobileBilling()*/)
#endif
    {
        GMBillingLayer *tempBillingLayer = (GMBillingLayer*)this->getChildByTag(Billing_tag);
        if(tempBillingLayer)
            this->removeChild(tempBillingLayer, true);
    }

    if(_isClickClose==false){
        
        switch (index) {
            case 1:{
                if(_isClickClose==false){
                    if( billingModel == B_91){
                        GMAccessData::sharedAccessData()->saveGenuineValidationStatus(2);
                        
                        int money = GMAccessData::sharedAccessData()->getTotalMoneyNum();
                        money += 5000;
                        GMAccessData::sharedAccessData()->saveTotalMoneyNum(money);
                        
                        int num = GMAccessData::sharedAccessData()->getSkillBloodNum();
                        num = num+5;
                        GMAccessData::sharedAccessData()->saveSkillBloodNum(num);
                    }
                    else if(billingModel == B_YiDong){//移动计费
#if (JNIHELPER_INDEX == JNIHELPER_YiDong)
                        ZPJNIHelper::setYiDongBilling(1);
                        this->schedule(schedule_selector(GMCardLayer::checkBillingPoint));
#endif
                    }
                    else if (billingModel == B_91_IOS) {
#if (JNIHELPER_INDEX == JNIHELPER_91_IOS)
//                        if(PublicCPP::getMobileBilling()){
//                            addBilling(8,0);
//                        }
//                        else
                        {
                            //PublicCPP::paymentAll(6);
                            this->schedule(schedule_selector(GMCardLayer::check91BillingPoint));
                        }
#endif
                    }
//                    else if(billingModel == B_TengXunBilling){//腾讯暂时注销二次确认
//                        ZPJNIHelper::sendSMSBillingPoint(1);
//                        this->schedule(schedule_selector(GMCardLayer::checkBillingPoint));
//                    }
                    else if(billingModel == B_Unicom_Android){
                        ZPJNIHelper::sendSMSBillingPoint(1);
                        this->schedule(schedule_selector(GMCardLayer::checkBillingPoint));
                    }
                    else {
                        GMAccessData::sharedAccessData()->saveGenuineValidationStatus(1);
                        addBilling(6,0);
                    }
                }
            }   break;
            case 2:{
                if(billingModel == B_TengXunBilling){
                    ZPJNIHelper::sendSMSBillingPoint(3);
                    this->schedule(schedule_selector(GMCardLayer::checkBillingPoint));
                }
                else if(billingModel == B_91_IOS || billingModel == B_91_Android){
                    int tempIndex = 1;
                    if(tag == 1){
                        tempIndex = 2;
                    }
                    else if(tag == 2){
                        tempIndex = 3;
                    }
                    else if(tag == 3){
                       tempIndex = 4;
                    }
#if (JNIHELPER_INDEX == JNIHELPER_91_IOS)
//                    if(PublicCPP::getMobileBilling()){
//                        GMPublicMethod::sharedPublicMethod()->setBillingIndex(tempIndex);
//                        addBilling(7,tempIndex);
//                    }
//                    else
                    {
                        //PublicCPP::paymentAll(tempIndex);
                        this->schedule(schedule_selector(GMCardLayer::check91BillingPoint));
                    }
#endif
#if (JNIHELPER_INDEX == JNIHELPER_91_Android)
                    
                    ZPJNIHelper::setAllPay(tempIndex);
                    this->schedule(schedule_selector(GMCardLayer::check91BillingPoint));
#endif
                }
                else if(billingModel == B_YiDong){
#if (JNIHELPER_INDEX == JNIHELPER_YiDong)
                    ZPJNIHelper::setYiDongBilling(3);
                    this->schedule(schedule_selector(GMCardLayer::checkBillingPoint));
#endif
                }
                else if(billingModel == B_Unicom_Android){
                    ZPJNIHelper::sendSMSBillingPoint(3);
                    this->schedule(schedule_selector(GMCardLayer::checkBillingPoint));
                }
            }   break;
            case 6:{
                if(_isClickClose==false && billingModel != B_91){
                    if(billingModel == B_TengXunBilling){
                        ZPJNIHelper::sendSMSBillingPoint(1);
                        this->schedule(schedule_selector(GMCardLayer::checkBillingPoint));
                    }
                }
            }   break;
            case 7:{
                addBilling(8, 0);
            }   break;
            case 8:{
                this->schedule(schedule_selector(GMCardLayer::check91BillingPoint));
            }   break;
            default:
                break;
        }
    }
}

void GMCardLayer::checkBillingPoint(float dt){
    int status = ZPJNIHelper::getSendSMSBillingPointStatus();
    ZPLog("GMCardLayer ::getSendSMSBillingPointStatus %d",status);
    if(status!=0){
        if(status == 1){
            int index = ZPJNIHelper::getBillingIndex();
            if (index == 3) {
                int tempM = GMAccessData::sharedAccessData()->getTotalMoneyNum();
                tempM += 5000;
                GMAccessData::sharedAccessData()->saveTotalMoneyNum(tempM);
//                m_pTotalEnergy->setNumber(tempM);
                setMoney();
                ZPLog("GMCardLayer 获取能量计费  计费索引 3");
            }
            else if(index == 1){
                GMAccessData::sharedAccessData()->saveGenuineValidationStatus(2);
                int money = GMAccessData::sharedAccessData()->getTotalMoneyNum();
                money += 5000;
                GMAccessData::sharedAccessData()->saveTotalMoneyNum(money);
                
                int num = GMAccessData::sharedAccessData()->getSkillBloodNum();
                num = num+5;
                GMAccessData::sharedAccessData()->saveSkillBloodNum(num);
                ZPLog("GMCardLayer 正版验证计费  计费索引 1");
            }
        }

        ZPJNIHelper::setSMSBillingPointStatus();//  将状态付值为0 (腾讯 移动 通用方法)
        this->unschedule(schedule_selector(GMCardLayer::checkBillingPoint));
        _isShowYiDong = false;
    }
}

//91 移动 获取验证码和好友手机号
void GMCardLayer::check91BillingCode(float dt){
    
}

void GMCardLayer::check91BillingPoint(float dt){
    int tempStatus = 0;
    int tempInde = 0;
#if (JNIHELPER_INDEX == JNIHELPER_91_IOS)
    //tempStatus = PublicCPP::getPaymentSuccess();
    //tempInde = PublicCPP::getBillingIndex();
#endif
#if (JNIHELPER_INDEX == JNIHELPER_91_Android)
    tempStatus = ZPJNIHelper::getSendSMSBillingPointStatus();
    tempInde = ZPJNIHelper::getBillingIndex();
#endif
    if(tempStatus != 0){
        if(tempStatus==1){
            char keyName[30] = {0};
            int tempM = GMAccessData::sharedAccessData()->getTotalMoneyNum();
            if(tempInde == 2){//购买能量 （5000）
                tempM += 5000;
                sprintf(keyName, "恭喜获得%d能量",5000);
            }
            else if(tempInde == 3){//购买能量 （13000）
                tempM += 13000;
                sprintf(keyName, "恭喜获得%d能量",13000);
            }
            else if(tempInde == 4){//购买能量 （40000）
                tempM += 40000;
                sprintf(keyName, "恭喜获得%d能量",40000);
            }
            else if(tempInde == 6){
                if(ZPJNIHelper::getOperators() == 1){
                    tempM += 13000;
                }
                GMAccessData::sharedAccessData()->saveGenuineValidationStatus(2);
                sprintf(keyName, "恭喜您开启所有关卡");
    
            }
            else{
                sprintf(keyName, "恭喜获得%d能量",0);
            }
            GMAccessData::sharedAccessData()->saveTotalMoneyNum(tempM);
//            m_pTotalEnergy->setNumber(tempM);
            setMoney();
#if (JNIHELPER_INDEX == JNIHELPER_91_IOS)
            //PublicCPP::removeRecord(tempInde);
#endif
            GMPublicMethod::sharedPublicMethod()->showTipView(this,keyName);
            this->scheduleOnce(schedule_selector(GMCardLayer::removeTipView), 1);
        }
        else if(tempStatus==2){
            if(tempInde == 6){
                GMAccessData::sharedAccessData()->saveGenuineValidationStatus(0);
            }
#if (JNIHELPER_INDEX == JNIHELPER_91_IOS)
            //PublicCPP::messageBox();
#endif
        }
#if (JNIHELPER_INDEX == JNIHELPER_91_IOS)
        //PublicCPP::setPaymentSuccess(0);
#endif
        ZPJNIHelper::setSMSBillingPointStatus();//将状态付值为0 (腾讯 移动 通用方法)
        this->unschedule(schedule_selector(GMCardLayer::check91BillingPoint));
        GMBillingLayer *tempBillingLayer = (GMBillingLayer*)this->getChildByTag(Billing_tag);
        if(tempBillingLayer)
            this->removeChild(tempBillingLayer, true);
    }
}

void GMCardLayer::removeTipView(float dt){
    GMPublicMethod::sharedPublicMethod()->removeTipView(this);
}

//#pragma mark - 移动 网乐
void GMCardLayer::showYidongSdkView(int index){
#if (JNIHELPER_INDEX == JNIHELPER_YiDong)
    switch (index) {
        case 1:{
            ZPJNIHelper::setYiDongBilling(1);
            this->schedule(schedule_selector(GMCardLayer::checkBillingPoint));

        } break;
        case 2:{
            ZPJNIHelper::setYiDongBilling(3);
            this->schedule(schedule_selector(GMCardLayer::checkBillingPoint));
        }   break;
        default:
            break;
    }
#endif
}

//#pragma mark - 电信计费相关的方法
void GMCardLayer::showTelecomSMSView(int _index){
#if (JNIHELPER_INDEX == JNIHELPER_Telecom)
    switch (_index) {
        case 1:{
            _isShowYiDong = true;
            ZPJNIHelper::sendSMSBillingPoint(1);
            this->schedule(schedule_selector(GMCardLayer::checkBillingPoint));
        } break;
        case 2:{
            ZPJNIHelper::sendSMSBillingPoint(3);
            this->schedule(schedule_selector(GMCardLayer::checkBillingPoint));
        }   break;
        default:
            break;
    }
#endif
}
//#pragma mark - Android
void GMCardLayer::keyBackClicked(){
    ZPLog("GMCardLayer::keyBackClicked");
    backAction(NULL);
}

//#pragma mark - ~GMCardLayer
GMCardLayer::~GMCardLayer()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
    
    CCLayer *eachLevel = (CCLayer*)this->getChildByTag(EL_Tag00 + checkpoints_index);
    m_pLayer->removeChild(eachLevel, true);
    
    this->removeChild(m_pLayer, true);
    
    CCRemoveSpriteFramesAndTextureForKey(changeboom_plist,changeboom_png)
    
    CCRemoveSpriteFrameByName(card_plist);
    CCRemoveTextureForKey(card_png);
    
    CCRemoveSpriteFramesAndTextureForKey(ui_checkpointsfish_plist,ui_checkpointsfish_png);
    
    //this->unschedule(schedule_selector(GMCardLayer::chooseLevel));
    //this->unschedule(schedule_selector(GMCardLayer::backAction));
    //this->unschedule(schedule_selector(GMCardLayer::goleAction));
    //this->unschedule(schedule_selector(GMCardLayer::startAction));
    this->cleanup();
    
}


