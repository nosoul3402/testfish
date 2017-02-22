//
//  GMMenuLayer.cpp
//  FishX
//
//  Created by peng on 13-1-4.
//
//

#include "GMMenuLayer.h"
//#include "GMPauseLayer.h"
#include "../Config/GMHeaderConfig.h"
#include "GMGameLayer.h"

#define Anger_tag      95
#define Batter_Tag     100
#define Task_Tag        200
#define UI_tag          300

const int GMMenuLayer::juneng[] = {8,8,8,8,12,12};
const int GMMenuLayer::juneng1[] = {10,10,9,9,9,9};

GMMenuLayer::GMMenuLayer()
{
	delegateGame = NULL;
	effect = NULL;
	menuBatchNode = NULL;
	cannonSheet = NULL;
	cannon = NULL;
	loadingCt1 = NULL;
	loadingCt2 = NULL;
	pauseItem = NULL;
	skill1 = NULL;
	skill2 = NULL;
	bloodb = NULL;
	cupSprite = NULL;
	targetScoreProTimer = NULL;

	m_pScoreNum = NULL;
	m_pScoreNum1 = NULL;
	m_pTimeGNum = NULL;
	m_pTimeMNum = NULL;
	m_pTotalMoneyNum = NULL;

	toTheTiming = NULL;
	batterLayer = NULL;
}

CCScene* GMMenuLayer::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    GMMenuLayer *layer = GMMenuLayer::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GMMenuLayer::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    m_pTimeM = 56;
    laserIndex = 7 ;
    
//    initElement();
//    initCannon();
    
    return true;
}

void GMMenuLayer::loadingData(int index)
{
    switch (index) {
        case 0:{
            initValue();
        }  break;
        case 1:{
            loadData();
        }  break;
        case 2:{
            loadData1();
        }   break;
        case 3:{
            initElement();
        }   break;
        case 4:{
            initCannon();
        }   break;
        default:
            break;
    }
}
void GMMenuLayer::initValue()
{
    isLaser = false;
    isAnger = false;
    isShowTaskBox = false;
    mPercentage = 100.0f;
    oldAngerValue = newAngerValue = 100.0f;
    m_LifeValue = 100;
    setShootAgain(true);
    
    m_pTimeGNum = NULL;
    moneyNum = 0;
}

void GMMenuLayer::loadData()
{
    CCAddSpriteFramesWithFile(mainmenu_plist);
    menuBatchNode = CCSpriteBatchNode::create(mainmenu_png);
    this->addChild(menuBatchNode,MENU_Layer);
    
    CCAddSpriteFramesWithFile(mainmenu021_plist);
    CCSpriteBatchNode *mainmenu021BatchNode = CCSpriteBatchNode::create(mainmenu021_png);
    this->addChild(mainmenu021BatchNode,MENU_Layer);
    
//    CCAddSpriteFramesWithFile(mainmenuTask_plist);
//    CCSpriteBatchNode *taskBatchNode = CCSpriteBatchNode::create(mainmenuTask_png);
//    this->addChild(taskBatchNode,MENU_Layer);
//    
//    CCAddSpriteFramesAndTextureFile(liuguang_plist,liuguang_png);
}

void GMMenuLayer::loadData1()
{
    
    CCAddSpriteFramesWithFile(mainmenuTask_plist);
    CCSpriteBatchNode *taskBatchNode = CCSpriteBatchNode::create(mainmenuTask_png);
    this->addChild(taskBatchNode,MENU_Layer);
    
    CCAddSpriteFramesAndTextureFile(liuguang_plist,liuguang_png);
}

void GMMenuLayer::initElement()
{
    /*
     *   中间的血条在怒气
     */
    CCSprite *loading1 = CCSprite::createWithSpriteFrameName("mainmenu001.png");
    CCRect rect = Get_Rect(loading1);
    TopTempW = WINSIZE_H-Get_H(rect)/2*Scale_X;
    SetScale2(loading1,Scale_X);
    loading1->setPosition(ccp(WINSIZE_W/2,TopTempW));
    menuBatchNode->addChild(loading1,MENU_Layer+2);
    
    //暂停按钮
    CCSprite *normalSprite = NULL;
//    normalSprite->setColor(ccc3(0,0,3));
    CCSprite* selectedSprite = CCSprite::createWithSpriteFrameName("mainmenu010.png");
    pauseItem = NULL;
    normalSprite = CCSprite::createWithSpriteFrameName("mainmenu009.png");
    pauseItem = CCMenuItemSprite::create(normalSprite, selectedSprite, this, menu_selector(GMMenuLayer::pauseAction));
    SetScale2(pauseItem,Scale_X);
    pauseItem->setAnchorPoint(ccp(0,0.5));
    pauseItem->setPosition(ccp(0,TopTempW));
    
    /*
     *  倍率
     */
    CCSprite *normalSprite1 = CCSprite::createWithSpriteFrameName("mainmenu0025.png");;
    CCSprite* selectedSprite1 = CCSprite::createWithSpriteFrameName("mainmenu0026.png");
    CCMenuItemSprite *magnificat = CCMenuItemSprite::create(normalSprite1, selectedSprite1, this, menu_selector(GMMenuLayer::setMagnificationModel));
    magnificat->setPosition(ccp(WINSIZE_W/2,TopTempW+1));
    magnificat->setScale(Scale_X);
    
    CCSprite *xSprinte = CCSprite::createWithSpriteFrameName("mainmenu027.png");
    xSprinte->setPosition(ccp(18,64/2));
    magnificat->addChild(xSprinte,1,1);

    int temp1 = GMPublicMethod::getChooseMagnificationModel();
    m_pMagnificat = UIRollNum::create();
    m_pMagnificat->setEffect("game/number10.png",2,16,20,NumStyleNormal0);
    m_pMagnificat->setNumber(temp1);
    m_pMagnificat->setPosition(ccp(58, 64/2));
    magnificat->addChild(m_pMagnificat,MENU_NUM_Layer);
    
    CCMenu *pauseMenu = CCMenu::create(pauseItem,magnificat,NULL);
    pauseMenu->setPosition(CCPointZero);
    this->addChild(pauseMenu,MENU_Layer+3);
    
    float temp = 27*Scale_X;
    //左 血条
    CCSprite *loading2 = CCSprite::createWithSpriteFrameName("mainmenu002.png");
    SetScale2(loading2,Scale_X);
    CCRect loadrect = Get_Rect(loading2);
    loading2->setPosition(ccp(WINSIZE_W/2-Get_W(loadrect)/2*Scale_X-temp,TopTempW+0.2));
    menuBatchNode->addChild(loading2,MENU_Layer);
    
    CCSprite *loading4 = CCSprite::createWithSpriteFrameName("mainmenu004.png");
    loadingCt1= CCProgressTimer::create(loading4);
    SetScale2(loadingCt1,Scale_X);
    loadingCt1->setPosition(ccp(WINSIZE_W/2-Get_W(loadrect)/2*Scale_X-temp+1.8,TopTempW-0.5));
    loadingCt1->setType(kCCProgressTimerTypeBar);//
    /*
     *应该使用kCCProgressTimerTypeBar这种类型，然后设置其起点midpoint属性为ccp（0,x），0<=x<=1，从左边开始，或者ccp（1,x），从右边开始。然后设置其barChangeRate属性为ccp（x，y），表示横竖两个方向的增长率，要进度条从左到右的话，设置成ccp(1,0)即可。
     */
    loadingCt1->setMidpoint(ccp(0, 1));
    loadingCt1->setBarChangeRate(ccp(1, 0));
    this->addChild(loadingCt1 ,MENU_Layer+2 ,90);
    loadingCt1->setPercentage(mPercentage); //当前进度

    // 右怒气
    temp1 = 26*Scale_X;
    CCSprite *loading5 = CCSprite::createWithSpriteFrameName("mainmenu005a1.png");
    loading5->setPosition(ccp(WINSIZE_W/2+Get_W(loadrect)/2*Scale_X+temp1,TopTempW-0.5));
    SetScale2(loading5,Scale_X);
    menuBatchNode->addChild(loading5,MENU_Layer-1,Anger_tag);
    setAngerAnimation(loading5,"a");

    CCSprite *loading3 = CCSprite::createWithSpriteFrameName("mainmenu003.png");
    loadingCt2= CCProgressTimer::create(loading3);
    SetScale2(loadingCt2,Scale_X);
    loadingCt2->setPosition(ccp(WINSIZE_W/2+Get_W(loadrect)/2*Scale_X+temp1+1,TopTempW));
    loadingCt2->setType(kCCProgressTimerTypeBar);//
    loadingCt2->setMidpoint(ccp(1, 0));
    loadingCt2->setBarChangeRate(ccp(1, 0));
    this->addChild(loadingCt2 ,MENU_Layer ,91);
    loadingCt2->setPercentage(mPercentage); //当前进度
    
    /*
     *  底部 总能量 menu
     */
    CCSprite *mainmenu011 = CCSprite::createWithSpriteFrameName("mainmenu011.png");
    SetScale2(mainmenu011,Scale_X);
    CCRect rect11 = Get_Rect(mainmenu011);
//    mainmenu011->getContentSize().width;
    mainmenu011->setAnchorPoint(ccp(0,0));
    mainmenu011->setPosition(ccp(10*Scale_X,10*Scale_X));
    this->addChild(mainmenu011,MENU_Layer);
    
    int tempM1 = 256700;
    int num1 = GMPublicMethod::getScoreNum(tempM1);
    int tempM2 = GMAccessData::sharedAccessData()->getTotalMoneyNum();
    int num2 = GMPublicMethod::getScoreNum(tempM2);
    
    moneyNum = (num1 > num2 ? num1 : num2);
    m_pTotalMoney = (tempM1 > tempM2 ? tempM1 : tempM2);
  
    m_pTotalMoneyNum = UIRollNum::create();
    m_pTotalMoneyNum->setEffect("game/mainmenuTask004b.png",moneyNum,17,16,NumStyleNormal);
    m_pTotalMoneyNum->setNumber(m_pTotalMoney);
    m_pTotalMoneyNum->setScale(0.9);
    m_pTotalMoneyNum->setPosition(ccp(Get_W(rect11)/2+25, Get_H(rect11)/2));
    mainmenu011->addChild(m_pTotalMoneyNum,MENU_NUM_Layer);

    m_pTimeMNum = UIRollNum::create();
    m_pTimeMNum->setEffect("game/mainmenuTask004a.png",2,19,20,NumStyleNormal0);
    m_pTimeMNum->setNumber(EnergyTime);
    m_pTimeMNum->setPosition(ccp(Get_W(rect11)/2+70, Get_H(rect11)/2-2));
    mainmenu011->addChild(m_pTimeMNum,MENU_NUM_Layer);
    //逗号
    CCSprite *mainmenu0013 = CCSprite::createWithSpriteFrameName("mainmenu013.png");
    mainmenu0013->setPosition(ccp( Get_W(rect11)/2+75 ,Get_H(rect11)-15));
    mainmenu011->addChild(mainmenu0013,MENU_Layer+3);
    /*
     *  站台
     */
    CCSprite *mainmenu020 = CCSprite::createWithSpriteFrameName("mainmenu020.png");
    SetScale2(mainmenu020,Scale_X);
    mainmenu020->setPosition(ccp(WINSIZE_W/2,Get_H(Get_Box(mainmenu020))/2));
    this->addChild(mainmenu020,Bullet_Layer-1);
    float temp20W = 111;
    CCSprite *normalSprite16 = CCSprite::createWithSpriteFrameName("mainmenu016.png");
    CCSprite* selectedSprite17 = CCSprite::createWithSpriteFrameName("mainmenu017.png");
    minusItem = CCMenuItemSprite::create(normalSprite16, selectedSprite17, this, menu_selector(GMMenuLayer::smallerAction));
    SetScale2(minusItem, Scale_X);
    minusItem->setAnchorPoint(ccp(0,0));
    minusItem->setPosition(ccp(WINSIZE_W/2-(temp20W-20)*Scale_X,-2*Scale_X));
    CCSprite *normalSprite18 = CCSprite::createWithSpriteFrameName("mainmenu018.png");
    CCSprite* selectedSprite19 = CCSprite::createWithSpriteFrameName("mainmenu019.png");
    plusItem = CCMenuItemSprite::create(normalSprite18, selectedSprite19, this, menu_selector(GMMenuLayer::largerAction));
    SetScale2(plusItem, Scale_X);
    plusItem->setAnchorPoint(ccp(1,0));
    plusItem->setPosition(ccp(WINSIZE_W/2+(temp20W-20)*Scale_X,-2*Scale_X));
    
    
    CCMenuItemSprite *buyEnergy = NULL;
    
#if(JNIHELPER_INDEX == JNIHELPER_91_IOS || JNIHELPER_INDEX == JNIHELPER_91_Android)
    CCSprite *bnormalSprite = CCSprite::create("game/mainmenu063.png");
    CCSprite* bselectedSprite = CCSprite::create("game/mainmenu064.png");
    buyEnergy = CCMenuItemSprite::create(bnormalSprite, bselectedSprite, this, menu_selector(GMMenuLayer::bugEnergyAction));
    SetScale2(buyEnergy, Scale_X);
    buyEnergy->setAnchorPoint(ccp(1,0));
    buyEnergy->setPosition(ccp(WINSIZE_W/2-(120)*Scale_X,10*Scale_X));
    
#endif
    
    CCMenu *mainMenu = CCMenu::create(minusItem,plusItem,buyEnergy,NULL);
//    mainMenu->setAnchorPoint(ccp(0.5,0));
//    mainMenu->alignItemsHorizontallyWithPadding(temp20W-125);
//    mainMenu->setPosition(ccp(temp20W/2,15));
    mainMenu->setPosition(CCPointZero);
    this->addChild(mainMenu,Bullet_Layer-1);
//    mainmenu020->addChild(mainMenu,MENU_Layer);

    showTargetScore();
    
    addSkill();
    showSkillNum();
    

}

/*
 *  倒计时
 */
void GMMenuLayer::showCountdown(int index)
{
    GameMode gameMode = GMPublicMethod::sharedPublicMethod()->getGameMode();
    /*
     *  倒计时
     */
    toTheTiming = CCSprite::createWithSpriteFrameName("timeup001.png");
    toTheTiming->setAnchorPoint(ccp(0.5,0.5));
    SetScale2(toTheTiming,Scale_X);
    toTheTiming->setPosition(ccp( 66*Scale_X + Get_W(Get_Rect(toTheTiming))/2*Scale_X, TopTempW));
    this->addChild(toTheTiming,MENU_Layer,UI_tag+7);
    
    m_pTimeG = 156;
    int num;
    if (gameMode == Boot_Mode || index == 1) {
        CCSprite *timeTip = CCSprite::createWithSpriteFrameName("mainmenu060.png");
        timeTip->setPosition(ccp((Get_W(Get_Rect(toTheTiming)))/2+30, (Get_H(Get_Rect(toTheTiming)))/2+10));
        toTheTiming->addChild(timeTip,MENU_NUM_Layer);
    }
    else {
        num = GMPublicMethod::getScoreNum(m_pTimeG);
        m_pTimeGNum = UIRollNum::create();
        m_pTimeGNum->setEffect("game/mainmenu007.png",num,19,20,NumStyleNormal0);
        m_pTimeGNum->setNumber(m_pTimeG);
        m_pTimeGNum->setPosition(ccp((Get_W(Get_Rect(toTheTiming)))-10, (Get_H(Get_Rect(toTheTiming)))/2+10));
        toTheTiming->addChild(m_pTimeGNum,MENU_NUM_Layer);
    }
}
/*
 *  目标分数
 */
void GMMenuLayer::showTargetScore()
{
    CCSprite *mainmenu021000 = CCSprite::createWithSpriteFrameName("mainmenu021000.png");
    mainmenu021000->setAnchorPoint(ccp(1,0.5));
    SetScale2(mainmenu021000,Scale_X);
    mainmenu021000->setPosition(ccp(WINSIZE_W-10,TopTempW));
    this->addChild(mainmenu021000);
    
    cupSprite = CCSprite::createWithSpriteFrameName("mainmenu021002.png");
    cupSprite->setAnchorPoint(ccp(0,0));
    cupSprite->setPosition(ccp(0,0));
    mainmenu021000->addChild(cupSprite,2);
    
    CCSprite *mainmenu021001 = CCSprite::createWithSpriteFrameName("mainmenu021001.png");
    targetScoreProTimer = CCProgressTimer::create(mainmenu021001);
    targetScoreProTimer->setAnchorPoint(ccp(0,0));
    targetScoreProTimer->setPosition(ccp(0,0));
    targetScoreProTimer->setType(kCCProgressTimerTypeBar);//
    targetScoreProTimer->setMidpoint(ccp(0, 1));
    targetScoreProTimer->setBarChangeRate(ccp(1, 0));
    mainmenu021000->addChild(targetScoreProTimer ,1 );
    
    targetScoreProTimer->setPercentage(0); //当前进度
    
    m_pScoreNum = UIRollNum::create();
    m_pScoreNum->setEffect("game/mainmenu007.png",6,19,20,NumStyleNormal0);
    m_pScoreNum->setNumber(100000);
    m_pScoreNum->setPosition(ccp(Get_W(Get_Rect(mainmenu021000))+5,Get_H(Get_Rect(mainmenu021000))/2+5));
    targetScoreProTimer->addChild(m_pScoreNum,MENU_NUM_Layer);
    
    isFulfill = false;
}

void GMMenuLayer::setTargetScore(int score)
{
    curScore =  (score == 0 ? 0 : (100.0/score));
//    ZPLog("curScore %f == score %d", curScore,score);
}

void GMMenuLayer::showTargetProTimer(int score,bool clean,int leve)
{
    float tempScore = score*curScore;
    if (tempScore >= 100.0) {
        tempScore = 100.0;
    }
    if(clean){
        targetScoreProTimer->setPercentage(tempScore);
        cupSprite->stopAllActions();
        CCSpriteFrame *spriteFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("mainmenu021002.png");
        cupSprite->setDisplayFrame(spriteFrame);
        isFulfill = false;
    }
    else {
        if (isFulfill == false) {
            if(leve%10 != 5 && leve > 0){
                targetScoreProTimer->setPercentage(tempScore); //当前进度
                if (tempScore == 100.0 ) {
                    GMPublicMethod::setRepeatAnimation(cupSprite, 2, 5, "mainmenu021", "png", 0.1,true);
                    isFulfill = true;
                }
            }
        }

    }
}

void GMMenuLayer::showCurrentScore(int score)
{
    int num1 = GMPublicMethod::getScoreNum(score);
    if (num1>6) {
        return;
    }
    if (m_pScoreNum) {
        if (score == 0) {
            cupSprite->stopAllActions();
            CCSpriteFrame *spriteFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("mainmenu021002.png");
            cupSprite->setDisplayFrame(spriteFrame);
            isFulfill = false;
        }
        m_pScoreNum->setNumber(score);
    }
}

void GMMenuLayer::setAllMenuEnabled(bool value){
//    pauseItem->setEnabled(value);
    skill1->setEnabled(value);
    skill2->setEnabled(value);
}

//#pragma mark - skill
void GMMenuLayer::addSkill()
{
//    menuLayer->addSkill(this,menu_selector(GMGameLayer::usedSkill1),menu_selector(GMGameLayer::usedSkill2));
    CCSprite *normalSprite14 = CCSprite::createWithSpriteFrameName("mainmenu014b.png");
    CCSprite *selectedSprite1 = CCSprite::createWithSpriteFrameName("mainmenu014b1.png");
    skill1 = CCMenuItemSprite::create(normalSprite14, selectedSprite1, this, menu_selector(GMMenuLayer::usedSkill1));
    skill1->setTag(1);
    skill1->setAnchorPoint(ccp(1,0));
    SetScale2(skill1, Scale_X);
    CCRect rect16 = skill1->boundingBox();
    skill1->setPosition(ccp(WINSIZE_W-(85+20)*Scale_X, 10*Scale_X));
    
    CCSprite *normalSprite14a = CCSprite::createWithSpriteFrameName("mainmenu014a.png");
    CCSprite *selectedSprite2 = CCSprite::createWithSpriteFrameName("mainmenu014a1.png");
    skill2 = CCMenuItemSprite::create(normalSprite14a, selectedSprite2,this, menu_selector(GMMenuLayer::usedSkill2));
    skill2->setTag(2);
    SetScale2(skill2, Scale_X);
    skill2->setAnchorPoint(ccp(1,0));
    skill2->setPosition(ccp(WINSIZE_W - 10*Scale_X, 10*Scale_X));
    
    CCMenu *mainMenu = CCMenu::create(skill1,skill2,NULL);
    mainMenu->setPosition(CCPointZero);
    this->addChild(mainMenu,Bullet_Layer+1);
}

void GMMenuLayer::usedSkill1(CCObject *object){
    ((GMGameLayer*)delegateGame)->usedSkill1(object);
}

void GMMenuLayer::usedSkill2(CCObject *object){
    ((GMGameLayer*)delegateGame)->usedSkill2(object);
}

void GMMenuLayer::setSkill1Enabled(bool enabled){
    CCSprite *normalSprite;
    skill1->setEnabled(enabled);
    if (enabled) {
        normalSprite = CCSprite::createWithSpriteFrameName("mainmenu014b.png");
    }
    else {
        normalSprite = CCSprite::createWithSpriteFrameName("mainmenu014b1.png");
    }
    skill1->setNormalImage(normalSprite);
}

void GMMenuLayer::setSkill2Enabled(bool enabled)
{
    CCSprite *normalSprite;
    skill2->setEnabled(enabled);
    if (enabled) {
        normalSprite = CCSprite::createWithSpriteFrameName("mainmenu014a.png");
    }
    else {
        normalSprite = CCSprite::createWithSpriteFrameName("mainmenu014a1.png");
    }
    skill2->setNormalImage(normalSprite);
}

void GMMenuLayer::showSkillNum(){
    skillRollNum1 = UIRollNum::create();
    skillRollNum1->setEffect("game/number13.png",2,7.0,9.0,NumStyleNormal0);
    skillRollNum1->setNumber(1);
    skillRollNum1->setPosition(ccp(88-10,20));
    skill1->addChild(skillRollNum1,MENU_NUM_Layer);
    
    skillRollNum2 = UIRollNum::create();
    skillRollNum2->setEffect("game/number13.png",2,7.0,9.0,NumStyleNormal0);
    skillRollNum2->setNumber(1);
    skillRollNum2->setPosition(ccp(88-10,20));
    skill2->addChild(skillRollNum2,MENU_NUM_Layer);
}

void GMMenuLayer::setSKillNum1(int num1){
    skillRollNum1->setNumber(num1);
}

void GMMenuLayer::setSKillNum2(int num2){
    skillRollNum2->setNumber(num2);
}

void GMMenuLayer::bugEnergyAction(CCObject *object){
    ((GMGameLayer*)delegateGame)->bugEnergyAction();
}

//#pragma mark -
void GMMenuLayer::setMinusAndPlusEnabled(bool enabled)
{
    CCSprite *normalSprite;
    CCSprite *normalSprite1;
    minusItem->setEnabled(enabled);
    plusItem->setEnabled(enabled);

    if (enabled) {
        normalSprite = CCSprite::createWithSpriteFrameName("mainmenu016.png");
        normalSprite1 = CCSprite::createWithSpriteFrameName("mainmenu018.png");
    }
    else {
        normalSprite = CCSprite::createWithSpriteFrameName("mainmenu017.png");
        normalSprite1 = CCSprite::createWithSpriteFrameName("mainmenu019.png");
    }
    
    minusItem->setNormalImage(normalSprite);
    plusItem->setNormalImage(normalSprite1);
}

//#pragma mark -
void GMMenuLayer::setCheckpointsTimeValue(int time)
{
    if(m_pTimeGNum)
        m_pTimeGNum->setNumber(time);
}

//#pragma mark - Anger

void GMMenuLayer::setAngerAnimation(CCSprite *sprite,const char *name)
{
    CCArray *temploading = CCArray::create();
    char strName[30] = {0};
    for (int j = 1; j <= 4; j++) {
        sprintf(strName,"mainmenu005%s%d.png",name,j);
        CCSpriteFrame *spriteFrame  = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(strName);
        temploading->addObject(spriteFrame);
    }
    CCAnimation *m_pAnimation = CCAnimation::createWithSpriteFrames(temploading,0.1);
    CCAnimate *animate = CCAnimate::create(m_pAnimation);
    CCRepeatForever *repeateF = CCRepeatForever::create(animate);
    CCFiniteTimeAction *sequence = CCSequence::create(repeateF,NULL);
    sprite->stopAllActions();
    sprite->runAction(sequence);
}

//设置怒气值
void GMMenuLayer::setAngerValue(int value)
{
    float progress = 0.0f;
    int tempM = GMAccessData::sharedAccessData()->getCurrentMagnificationModel();
    if(value>0){
        switch (tempM) {
            case 1:{
                progress = value/10.0f;
            }  break;
            case 2:{
                progress = value/25.0f;
            }   break;
            case 3:{
                progress = value/50.0f;
            }   break;
            case 4:{
                progress = value/80.0f;
            }   break;
            case 5:{
                progress = value/150.0f;
            }   break;
            default:
                progress = 0.0f;
                break;
        }
    }
    else {
        progress = 0.0f;
    }
    if (isAnger == false) {
        newAngerValue = mPercentage -progress;
        if (newAngerValue <= 0) {
            newAngerValue = 0;
            isAnger = true;
            CCSprite *anger = (CCSprite*)menuBatchNode->getChildByTag(Anger_tag);
            setAngerAnimation(anger,"b");
            showLaser(true);
        }
        if (newAngerValue >= 0 && oldAngerValue != newAngerValue) {
            loadingCt2->setPercentage(newAngerValue);
        }
        oldAngerValue = newAngerValue;
    }
    
}

void GMMenuLayer::setAnger()
{
    newAngerValue = 100.0;
    oldAngerValue = 100.0;
    isAnger = false;
    loadingCt2->setPercentage(newAngerValue);
    CCSprite *anger = (CCSprite*)menuBatchNode->getChildByTag(Anger_tag);
    if (anger) 
        setAngerAnimation(anger,"a");
    setAngerValue(0);
}

void GMMenuLayer::setLifeValue(int value)
{
    m_LifeValue = m_LifeValue+value;
    if (m_LifeValue>=mPercentage) {
        m_LifeValue = mPercentage;
    }
    if (m_LifeValue<=0) {
        m_LifeValue = 0;
    }
    loadingCt1->setPercentage(m_LifeValue);
}

void GMMenuLayer::setTotalMoneyNum(int num)
{
    int num2 = GMPublicMethod::getScoreNum(num);
    if (num2 > moneyNum) {
        moneyNum = num2;
        m_pTotalMoneyNum->setEffect("game/mainmenuTask004b.png",moneyNum,17,16,NumStyleNormal);
    }
    m_pTotalMoneyNum->setNumber(num);
}

void GMMenuLayer::setEnergyTime(int time)
{
    m_pTimeMNum->setNumber(time);
}

//#pragma mark - 倒计时动画

void GMMenuLayer::setCountdownAnimation()
{
    CCArray *temp = CCArray::create();
    char strName[30] = {0};
    for (int j = 1; j <= 6; j++) {
        sprintf(strName,"timeup%03d.png",j);
        CCSpriteFrame * spriteFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(strName);
        temp->addObject(spriteFrame);
    }
    CCAnimation *m_pAnimation = CCAnimation::createWithSpriteFrames(temp,0.1);
    CCAnimate *animate = CCAnimate::create(m_pAnimation);
    CCRepeatForever *repeateF = CCRepeatForever::create(animate);
    CCFiniteTimeAction *sequence = CCSequence::create(repeateF,NULL);
    toTheTiming->runAction(sequence);
}

void GMMenuLayer::setStopCountdownAnimation(){
    toTheTiming->stopAllActions();
    CCSpriteFrame * spriteFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("timeup001.png");
    toTheTiming->setDisplayFrame(spriteFrame);
}
//#pragma mark - 结束提示

void GMMenuLayer::showOverView()
{
    toTheTiming->stopAllActions();
}

//#pragma mark - 没血的提示
void GMMenuLayer::showBloodb(){
    int temp = 20;
    if (m_LifeValue<=temp && bloodb == NULL) {
        bloodb = CCSprite::createWithSpriteFrameName("bloodb001.png");
        SetScale1(bloodb);
        SetScale2(bloodb, Scale_X);
        bloodb->setAnchorPoint(ccp(1,1));
        GMPublicMethod::setRepeatAnimation(bloodb, 1, 6, "bloodb", "png", 0.1,true);
        bloodb->setPosition(ccp(WINSIZE_W/2-20*Scale_X,WINSIZE_H));
        menuBatchNode->addChild(bloodb,MENU_Layer+1);
    }
    else if(m_LifeValue>temp && bloodb){
        menuBatchNode->removeChild(bloodb, true);
        bloodb = NULL;
    }
}

//#pragma mark - cannon
void GMMenuLayer::initCannon()
{
    cannonIndex = 1;
    // 炮台纹理
    CCAddSpriteFramesWithFile(cannon_plist);
    cannonSheet = CCSpriteBatchNode::create(cannon_png);
    this->addChild(cannonSheet,MENU_C_Layer);
    
//    CCAddSpriteFramesWithFile(juneng_plist);
//    junengSheet = CCSpriteBatchNode::create(juneng_png);
//    this->addChild(junengSheet,MENU_C_Layer);
    
    CCAddSpriteFramesAndTextureFile(juneng_plist,juneng_png);
    
    CCAddSpriteFramesWithFile(changeboom_plist);
    CCSpriteBatchNode *changeboomSheet = CCSpriteBatchNode::create(changeboom_png);
    this->addChild(changeboomSheet,MENU_C_Layer);
    
    sprintf(cannonName,"mainmenu03%d.png",1);
    cannon = GMBullet::createBulletFrameName(cannonName);
    SetScale2(cannon, Scale_X);
    cannon->setAnchorPoint(ccp(0.5, 0.25));
    cannonPoint = ccp(WINSIZE_W/2, 0);
    cannon->setPosition(cannonPoint);
    this->addChild(cannon,Bullet_Layer-1);

	CCLabelTTF* label = CCLabelTTF::create("          = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =", "", 80);
	label->setRotation(-90);
	cannon->addChild(label);
	label->setPosition(ccp(185, 0));

    setEffect();
//    changeCannon(cannonIndex);
}

//add 羽翼
void GMMenuLayer::setEffect()
{
    char cannonNameE[30] = {0};
    sprintf(cannonNameE,"mainmenu_effect03%d.png",cannonIndex);
    effect = CCSprite::createWithSpriteFrameName(cannonNameE);
    CCPoint tempP = ccp(0,0);
    effect->setPosition(tempP);
    effect->setAnchorPoint(ccp(0, 0));
    cannon->addChild(effect,1);
    isEffectOpacity = false;
    effectOpacity = 255;
    
    sprintf(cannonNameE,"juneng%d001.png",cannonIndex);
    junengEffect = CCSprite::createWithSpriteFrameName(cannonNameE);
    int num = juneng[cannonIndex-1];
    sprintf(cannonNameE,"juneng%d",cannonIndex);
    GMPublicMethod::setRepeatAnimation(junengEffect, 1, num, cannonNameE,"png",0.1,true);
    junengEffect->setAnchorPoint(ccp(0.5, 0.5));
    
    //    float a = DADIANS_TO_DEGREES1(cannon->getRotation());
    //    float tempH = Get_H(Get_Box(cannon));
    //    float tempx = sinf(a)*tempH;
    //    float tempy = cosf(a)*tempH;
    //    float tempX = cannon->getPosition().x;
    //    float tempY = cannon->getPosition().y;
    //1
    //    junengPoint = ccp(tempX+tempx,tempY+tempy);

    junengEffect->setPosition(ccp(GetSize(cannon).width/2,130));
    cannon->addChild(junengEffect,3);
    
//    changeboomEffect = CCSprite::createWithSpriteFrameName("changeboom1001.png");
//    changeboomEffect->setPosition(ccp(Get_Size(cannon).width/2,130));
//    cannon->addChild(changeboomEffect,3);
}

//显示激光
void GMMenuLayer::showLaser(bool laser)
{
    isLaser = laser;
    moveCannonDown();
//    if (laser) {
//        moveCannonDown();
//    }
//    else {
//        moveCannonDown();
//    }    
}

void GMMenuLayer::setEffectOpacity()
{
    if (isLaser) {
        effect->setOpacity(255);
        //this->unschedule(schedule_selector(GMMenuLayer::setEffectOpacity));
    }
    else if (effect) {
        if (isEffectOpacity) {
            effectOpacity+=25;
            if (effectOpacity>=255) {
                isEffectOpacity = false;
            }
        }
        else {
            effectOpacity-=25;
            if (effectOpacity<=180) {
                isEffectOpacity = true;
            }
        }
        effect->setOpacity( effectOpacity );
        CCFadeTo *fadeTo = CCFadeTo::create(0.2, effectOpacity);
        CCCallFunc *callfunc = CCCallFunc::create(this, callfunc_selector(GMMenuLayer::setEffectOpacity));
        CCFiniteTimeAction *sequence = CCSequence::create(fadeTo,callfunc,NULL);
        effect->runAction(sequence);
    }
}


GMBullet* GMMenuLayer::getCannon()
{
    return cannon;
}

float GMMenuLayer::getCannonRotation()
{
    return cannon->getRotation();
}

float GMMenuLayer::getCannonPointX()
{
    return cannon->getPosition().x;
}

void GMMenuLayer::changeCannon(int index)
{
    if (index <=0) {
        return;
    }
    sprintf(cannonName,"mainmenu03%d.png",index);
    CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(cannonName);
    cannon->setDisplayFrame(frame);
    
    char cannonNameE[30] = {0};
    sprintf(cannonNameE,"mainmenu_effect03%d.png",index);
    CCSpriteFrame *frameE = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(cannonNameE);
    effect->setDisplayFrame(frameE);
    
    setCannonRotation(0);
    
    if (isLaser) {
        isShootLaser = false;
        //this->unschedule(schedule_selector(GMMenuLayer::setEffectOpacity));
        effect->setOpacity(255);
        junengEffect->stopAllActions();
        junengEffect->setOpacity(0);
        if (cannonIndex == 6) {
            effect6->setOpacity(0);
        }
    }
    else{
        cannonIndex = index;
        if (cannonIndex == 6) {
            effect6 = CCSprite::createWithSpriteFrameName("mainmenu036b.png");
            effect6->setAnchorPoint(ccp(0,0));
            effect6->setPosition(ccp(0,0));
            cannon->addChild(effect6,3);
            effect6->setOpacity(255);
        }
        else {
            cannon->removeChild(effect6, true);
            effect6 = NULL;
        }
        setEffectOpacity();
        junengEffect->setOpacity(255);

        int num = juneng[cannonIndex-1];
        sprintf(cannonNameE,"juneng%d",cannonIndex);
        junengEffect->stopAllActions();
        GMPublicMethod::setRepeatAnimation(junengEffect, 1, num, cannonNameE,"png",0.1,true);
    }
}

void GMMenuLayer::shootLaser()
{
    isShootLaser = true;
}

void GMMenuLayer::setAgainJunengEffect(CCNode *pNode)
{
    char cannonNameE[30] = {0};
    int num = juneng[cannonIndex-1];
    sprintf(cannonNameE,"juneng%d",cannonIndex);
    junengEffect->stopAllActions();
    GMPublicMethod::setRepeatAnimation(junengEffect, 1, num, cannonNameE,"png",0.1,true);
}

void GMMenuLayer::setCannonRotation(float angle)
{
    transformAngle = angle;
    cannon->setRotation(angle);
//    effect->setRotation(angle);
    
    if (!isLaser) {
        
        cannon->stopAllActions();
        
        int num = juneng1[cannonIndex-1];
        char cannonNameE[30] = {0};
        sprintf(cannonNameE,"changeboom%d",cannonIndex);
        junengEffect->stopAllActions();
        GMPublicMethod::setSpriteAnimation(junengEffect, 1, num, cannonNameE, this, callfuncN_selector(GMMenuLayer::setAgainJunengEffect));
        float a = DADIANS_TO_DEGREES1(cannon->getRotation());
        float tempH = -15;
        float tempx = sinf(a)*tempH;
        float tempy = cosf(a)*tempH;
        float tempX = cannonPoint.x;
        float tempY = cannonPoint.y;
        CCPoint point = ccp(tempX+tempx,tempY+tempy);
        CCMoveTo *moveTo1 = CCMoveTo::create(0.1, cannonPoint);
        CCMoveTo *moveTo2 = CCMoveTo::create(0.1, point);
        CCAction* ation = CCSequence::create(moveTo1,moveTo2,moveTo1,NULL);
        cannon->runAction(ation);
    }
    
//    CCMoveTo *moveTo11 = CCMoveTo::create(0.1, ccp(effect->getPosition().x,effect->getPosition().y));
//    CCMoveTo *moveTo22 = CCMoveTo::create(0.1, ccp(effect->getPosition().x,effect->getPosition().y-5));
//    CCAction* ation1 = CCSequence::create(moveTo11,moveTo22,moveTo11,NULL);
//    effect->runAction(ation1);
    
//    float a = DADIANS_TO_DEGREES1(cannon->getRotation());
//    float tempH = 75*Scale_Y;//Get_H(Get_Rect(cannon))*0.32;
//    float tempx = sinf(a)*tempH;
//    float tempy = cosf(a)*tempH;
//    float tempX = cannon->getPosition().x;
//    float tempY = cannon->getPosition().y;
//    //1
//    CCPoint point = ccp(tempX+tempx,tempY+tempy);
//    junengEffect->setPosition(point);
}
//#pragma mark - 换弓

void GMMenuLayer::commonConnon(int index)
{
    if (!isLaser)
    {
        if (index<0) {
            cannonIndex--;
            if (cannonIndex<=0) {
                cannonIndex = 6;
            }
        }
        else
        {
            cannonIndex++;
            if (cannonIndex>=7) {
                cannonIndex = 1;
            }
        }
        changeCannon(cannonIndex);
        GMAudioPlay::sharedAudioPlay()->playButtonEffect();
    }
    
}
void GMMenuLayer::smallerAction(CCObject *pSender)
{
    if (!isLaser)
    {
//        cannonIndex--;
//        if (cannonIndex<=0) {
//            cannonIndex = 6;
//        }
//        changeCannon(cannonIndex);
//        GMAudioPlay::sharedAudioPlay()->playButtonEffect();
        GMGameLayer *temp = (GMGameLayer*)delegateGame;
        temp->minusAction();
    }
}

void GMMenuLayer::largerAction(CCObject *pSender)
{
    if (!isLaser)
    {
//        cannonIndex++;
//        if (cannonIndex>=7) {
//            cannonIndex = 1;
//        }
//        changeCannon(cannonIndex);
//        
//        GMAudioPlay::sharedAudioPlay()->playButtonEffect();
//        GMGameLayer *temp = (GMGameLayer*)delegateGame;
//        temp->largerAction();
        GMGameLayer *temp = (GMGameLayer*)delegateGame;
        temp->plusAction();
    }
//    GMAudioPlay::sharedAudioPlay()->playButtonEffect();
   
}


void GMMenuLayer::moveCannonDown()
{
    isShootLaser = false;
    setShootAgain(false);
    
//    cannon->stopAllActions();
    CCPoint point = ccp(cannonPoint.x,cannonPoint.y-150*Scale_X);
    CCMoveTo *moveTo = CCMoveTo::create(1, point);
    CCCallFunc *callFunc = CCCallFunc::create(this, callfunc_selector(GMMenuLayer::moveCannonUp));
    CCAction* ation = CCSequence::create(moveTo,callFunc,NULL);
    cannon->runAction(ation);
  
    junengEffect->setOpacity(0) ;
}

void GMMenuLayer::moveCannonUp()
{
    if (isLaser) {
        changeCannon(7);
    }
    else {
        changeCannon(cannonIndex);
    }
    
    CCMoveTo *moveTo = CCMoveTo::create(1, cannonPoint);
    CCCallFunc *callFunc = CCCallFunc::create(this, callfunc_selector(GMMenuLayer::scaleAfter));
    CCAction* ation = CCSequence::create(moveTo,callFunc,NULL);
    cannon->runAction(ation);
}


void GMMenuLayer::scaleAfter()
{
    isShootLaser = true;
    setShootAgain(true);
}

//#pragma mark - 连击
void GMMenuLayer::addBatterEffect(int num)
{
    batterNum = num;
    remvoeBatterEffect();
   
    batterCount = GMPublicMethod::getScoreNum(batterNum);
    battercount1 = batterCount-1;
    if (batterCount>=4) {
        return;
    }

    batterLayer = CCLayer::create();//ccc4(0, 0, 0, 125)
    batterLayer->setContentSize(CCSizeMake(batterCount*(46)+(156), 43));
    batterLayer->setAnchorPoint(ccp(0.5, 0.5));
    CCRect rect = Get_Box(batterLayer);
    batterLayer->setPosition(ccp((WINSIZE_W-Get_W(rect))/2, (WINSIZE_H-Get_H(rect))/2));
    this->addChild( batterLayer, 1, Batter_Tag);
    SetScale2(batterLayer, Scale_X);
    
    char strName[30] = {0};
    int tmepNum = batterCount-1;
    int tempBatterNum = batterNum;
    while (tmepNum >= 0) {
        if (batterNum<=0) {
            break;
        }
        int showNum = tempBatterNum%10;

        sprintf(strName,"mainmenuzi_a_%03d.png",showNum);
        CCSprite *batterNumS = CCSprite::createWithSpriteFrameName(strName);//003-012  012-022
        batterNumS->setAnchorPoint(ccp(0, 0.5));
        batterNumS->setPosition(ccp(tmepNum*46, Get_H(rect)/2));
        batterLayer->addChild(batterNumS,1,Batter_Tag+2+tmepNum);
        tmepNum -- ;
        tempBatterNum = tempBatterNum/10;
    }
    
    CCSprite *batter1_0 = CCSprite::createWithSpriteFrameName("mainmenuzi001.png");
    batter1_0->setAnchorPoint(ccp(0, 0.5));
    batter1_0->setPosition( ccp(batterCount*(46),Get_H(rect)/2) );
    batterLayer->addChild(batter1_0,1,Batter_Tag+1);
    
    CCSprite *batter1_1 = CCSprite::createWithSpriteFrameName("mainmenuzi002.png");
    CCProgressTimer *batter_timer_1= CCProgressTimer::create(batter1_1);
    batter_timer_1->setAnchorPoint(ccp(0, 0.5));
    batter_timer_1->setPosition( batter1_0->getPosition() );
    batter_timer_1->setType(kCCProgressTimerTypeBar);
    batter_timer_1->setMidpoint(ccp(1, 0));
    batter_timer_1->setBarChangeRate(ccp(1, 0));
    batterLayer->addChild(batter_timer_1 ,MENU_Layer ,Batter_Tag+3);
    CCProgressTo* to2 = CCProgressTo::create(1,100);
    CCCallFunc *callFunc = CCCallFunc::create(this, callfunc_selector(GMMenuLayer::moveNumProgress));
    CCActionInterval* sequence = (CCActionInterval*)CCSequence::create(to2,callFunc,NULL);
    batter_timer_1->runAction(sequence);

}

void GMMenuLayer::moveNumProgress()
{
    char strName[30] = {0};
    int showNum = batterNum%10;
    sprintf(strName,"mainmenuzi_b_%03d.png",showNum);
    CCSprite *batter2_1 = CCSprite::createWithSpriteFrameName(strName);
    CCProgressTimer *batter_timer_2 = CCProgressTimer::create(batter2_1);
    batter_timer_2->setAnchorPoint(ccp(0, 0.5));
    CCPoint point = ccp(battercount1*(46), (43)/2);
    batter_timer_2->setPosition( point );
    batter_timer_2->setType(kCCProgressTimerTypeBar);
    batter_timer_2->setMidpoint(ccp(1, 0));
    batter_timer_2->setBarChangeRate(ccp(1, 0));
    batterLayer->addChild(batter_timer_2 ,MENU_Layer ,Batter_Tag+4);
    CCProgressTo* to2 = CCProgressTo::create(0.5,100);
    CCCallFunc *callFunc = NULL;
    
    if (batterCount <= 1 || battercount1 <= 0) {
        callFunc = CCCallFunc::create(this, callfunc_selector(GMMenuLayer::remvoeBatterEffect));
    }
    else if(battercount1>=1){
        battercount1--;
        batterNum = batterNum/10;
        callFunc = CCCallFunc::create(this, callfunc_selector(GMMenuLayer::moveNumProgress));
    }

    CCActionInterval* sequence = (CCActionInterval*)CCSequence::create(to2,callFunc,NULL);
    batter_timer_2->runAction(sequence);
}

void GMMenuLayer::remvoeBatterEffect()
{
    if (batterLayer) {
        batterLayer->cleanup();
        this->removeChild(batterLayer, true);
        batterLayer = NULL;
    }
}

//#pragma mark - 任务
void GMMenuLayer::showTaskScaleAnimation()
{
    CCSprite *task = CCSprite::createWithSpriteFrameName("mainmenuTask005.png");
    task->setAnchorPoint(ccp(0.5,0));
    task->setPosition(ccp((10+199*0.6)*Scale_X,(10+34)*Scale_X));//(ccp( Get_W(Get_Box(task))/2+10,  Get_H(Get_Box(task))/2+23));
    this->addChild(task,MENU_Layer,Task_Tag);
//    SetScale2(task,Scale_X);
//    (10+199)*Scale_X
    task->setScale(0);
    CCScaleTo *scaleaTo1 = CCScaleTo::create(0.5, 0);
    CCScaleTo *scaleaTo2 = CCScaleTo::create(0.5, Scale_X);
    CCCallFuncN *callFunc = CCCallFuncN::create(this, callfuncN_selector(GMMenuLayer::showTaskAnimation)); 
    CCFiniteTimeAction *sequence = CCSequence::create(scaleaTo1,scaleaTo2,callFunc,NULL);
    task->runAction(sequence);

    GMAudioPlay::sharedAudioPlay()->playOtherEffect(Audio_Task,false);
}

void GMMenuLayer::showTaskAnimation(CCNode *pNode)
{
	CCSprite *sprite = (CCSprite*)pNode;
    GMPublicMethod::setRepeatAnimation(sprite, 5, 6, "mainmenuTask", "png",0.2,true);
    //this->unschedule(schedule_selector(GMMenuLayer::showTaskAnimation));
}

void GMMenuLayer::removeTaskAnimation()
{
    CCSprite *task = (CCSprite*)this->getChildByTag(Task_Tag);
    task->stopAllActions();
    this->removeChild(task, true);
}

void GMMenuLayer::showTaskBox(int strangeId,int taskTotalNum)
{
    removeTaskAnimation();
    isShowTaskBox = true;
    
    taskLayer = CCLayer::create();
    taskLayer->setContentSize(CCSizeMake(171, 104));
    taskLayer->setAnchorPoint(ccp(0, 0));
    taskLayer->setPosition(ccp((10+199*0.1)*Scale_X,(10+45)*Scale_X));
    SetScale2(taskLayer,Scale_X);
//    taskLayer->setPosition(ccp(0+20, 0+28 ));
    this->addChild( taskLayer, MENU_Layer, Task_Tag+1);
    
    // 任务背景图
    CCSprite *taskBox = CCSprite::createWithSpriteFrameName("mainmenuTask001.png");
    taskBox->setPosition(ccp( 171/2,  104/2));
    taskLayer->addChild(taskBox,0,Task_Tag+2);
    
    CCSprite *taskBox1 = CCSprite::createWithSpriteFrameName("mainmenuTaskeffect001.png");
    taskBox1->setPosition(ccp( 171/2,  104/2+5));
    taskLayer->addChild(taskBox1,1,Task_Tag+10);
    GMPublicMethod::setRepeatAnimation(taskBox1, 1, 6, "mainmenuTaskeffect", "png",0.15,true);
    
    // 冒号 :
    CCSprite *colon = CCSprite::createWithSpriteFrameName("mainmenuTask003.png");
    float tempx = Get_W(Get_Box(taskBox))/2;
    float tempy = Get_H(Get_Box(taskBox))-Get_H(Get_Box(colon));
    colon->setPosition(ccp( tempx,  tempy ));
    taskLayer->addChild(colon,1,Task_Tag+3);
    //
    UIRollNum *m_pTaskTime1 = UIRollNum::create();
    m_pTaskTime1->setEffect("game/mainmenuTask002.png",2,21,21,NumStyleNormal0);
    m_pTaskTime1->setNumber(1);
    m_pTaskTime1->setPosition( ccp(tempx - Get_W(Get_Box(colon))/2, tempy-1 ));
    taskLayer->addChild(m_pTaskTime1,1,Task_Tag+4);
    
    UIRollNum *m_pTaskTime2 = UIRollNum::create();
    m_pTaskTime2->setEffect("game/mainmenuTask002.png",2,21,21,NumStyleNormal0);
    m_pTaskTime2->setNumber(16);
    m_pTaskTime2->setPosition( ccp(tempx + Get_W(Get_Box(colon))/2+21*2, tempy-1 ));
    taskLayer->addChild(m_pTaskTime2,1,Task_Tag+5);
    
    char strName[30] = {0};
    sprintf(strName,"mainmenuyu%03d.png",strangeId);
    
    CCSprite *taskSprite = CCSprite::createWithSpriteFrameName(strName);
    taskSprite->setPosition(ccp( tempx - Get_W(Get_Box(taskSprite))/2-10, Get_H(Get_Box(taskSprite))-5 ));
    taskLayer->addChild(taskSprite,1,Task_Tag+6);
    //计数
    int num = GMPublicMethod::getScoreNum(taskTotalNum);
    
    UIRollNum *taskNum = UIRollNum::create();
    taskNum->setEffect("game/mainmenuTask004a.png",num,19,20,NumStyleNormal0);
    taskNum->setNumber(0);
    taskNum->setPosition( ccp(tempx+19, Get_H(Get_Box(taskSprite))-5 ));
    taskLayer->addChild(taskNum,1,Task_Tag+7);
    
    CCSprite *taskSprite1 = CCSprite::createWithSpriteFrameName("mainmenuTask004.png");
    taskSprite1->setPosition(ccp( tempx+19 + Get_W(Get_Box(taskSprite1))/2, Get_H(Get_Box(taskSprite))-5 ));
    taskLayer->addChild(taskSprite1,1,Task_Tag+8);
    
    UIRollNum *taskNum2 = UIRollNum::create();
    taskNum2->setEffect("game/mainmenuTask004a.png",num,19,20,NumStyleNormal0);
    taskNum2->setNumber(taskTotalNum);
    taskNum2->setPosition( ccp(tempx+19 + Get_W(Get_Box(taskSprite1)) + 19*num, Get_H(Get_Box(taskSprite))-5 ));
    taskLayer->addChild(taskNum2,1,Task_Tag+9);
}

void GMMenuLayer::setTaskTime(int time)
{
    if (time<0) {
        return;
    }
    int m = time/60;
    int s = time%60;
    if (taskLayer==NULL) {
        return;
    }
    UIRollNum *taskTime1 = (UIRollNum*)taskLayer->getChildByTag(Task_Tag+4);
    if (taskTime1) {
        taskTime1->setNumber(m);
    }
    
    
    UIRollNum *taskTime2 = (UIRollNum*)taskLayer->getChildByTag(Task_Tag+5);
    if (taskTime2)
        taskTime2->setNumber(s);
}

void GMMenuLayer::setTaskTip(bool win)
{
    CCSprite *taskTip = NULL;
    if (win) {
        taskTip = CCSprite::createWithSpriteFrameName("mainmenuTask007.png");
    }
    else {
        taskTip = CCSprite::createWithSpriteFrameName("mainmenuTask008.png");//失败
    }
    
    taskTip->setPosition(ccp(171/2, 104+52/2));
    taskLayer->addChild(taskTip);
}

void GMMenuLayer::setTaskNum(int num)
{
    if (taskLayer) {
        UIRollNum *taskNum = (UIRollNum*)taskLayer->getChildByTag(Task_Tag+7);
        if (taskNum) {
            taskNum->setNumber(num);
        }
    }
}


void GMMenuLayer::removeTaskBox()
{
    
    UIRollNum *taskTime1 = (UIRollNum*)taskLayer->getChildByTag(Task_Tag+4);
    if (taskTime1) {
        taskLayer->removeChild(taskTime1, true);
        taskTime1 = NULL;
    }

    UIRollNum *taskTime2 = (UIRollNum*)taskLayer->getChildByTag(Task_Tag+5);
    if (taskTime2) {
        taskLayer->removeChild(taskTime2, true);
        taskTime2 = NULL;
    }
    UIRollNum *taskNum = (UIRollNum*)taskLayer->getChildByTag(Task_Tag+7);
    if (taskNum) {
        taskLayer->removeChild(taskNum, true);
        taskNum = NULL;
    }
    UIRollNum *taskNum9 = (UIRollNum*)taskLayer->getChildByTag(Task_Tag+9);
    if (taskNum9) {
        taskLayer->removeChild(taskNum9, true);
        taskNum9 = NULL;
    }
    
    CCObject *node = NULL;
    CCARRAY_FOREACH(taskLayer->getChildren(),node){
        taskLayer->removeChild((CCSprite*)node, true);
    }
    this->removeChild(taskLayer, true);
    taskLayer = NULL;
}

//#pragma mark -
//#pragma mark 赔率按钮
void GMMenuLayer::setMagnificationModel(CCObject *pSender)
{
    GMAudioPlay::sharedAudioPlay()->playButtonEffect();
    setMagnificationModel1(1);
}

void GMMenuLayer::setMagnificationModel1(int index)
{
    CCSprite *sprite = CCSprite::createWithSpriteFrameName("liuguang001.png");
    GMPublicMethod::setSpriteAnimation(sprite, 1, 7, "liuguang", this, callfuncN_selector(GMMenuLayer::removeLiuguang));
    sprite->setPosition(ccp(WINSIZE_W/2,TopTempW));
    sprite->setScale(Scale_X);
    this->addChild(sprite,MENU_Layer+4);
  
    if (isAnger == false) {
        GMPublicMethod::setCurrentMagnificationModel(index);
        int temp1 = GMPublicMethod::getChooseMagnificationModel();
        m_pMagnificat->setNumber(temp1);
        
        int laserValue = GMAccessData::sharedAccessData()->getAngerValue();
        setAngerValue(laserValue);
    }
    
}

void GMMenuLayer::removeLiuguang(CCNode *pNode)
{
	CCSprite *sprite = (CCSprite*)pNode;
    this->removeChild(sprite, true);
    sprite = NULL;
}

//#pragma mark - action
void GMMenuLayer::pauseAction(CCObject *pSender)
{
    GMGameLayer *temp = (GMGameLayer*)delegateGame;
    temp->pauseAction();
    
//    GMAudioPlay::sharedAudioPlay()->playButtonEffect();
//    
//    delegateGame->pauseSchedulerAndActions();
//    CCDirector::sharedDirector()->pause();
//    GMPauseLayer *pauseLayer = GMPauseLayer::create();
//    pauseLayer->delegateGame = delegateGame;
//    delegateGame->addChild(pauseLayer,Index_Pause,1);
    
    //    GMWinLayer *winLayer = GMWinLayer::create();
    //    this->addChild(winLayer,Index_Pause,1);
    
    //    CCDirector::sharedDirector()->resume();
    //    CCScene *pScene = CCTransitionFade::create(1.0, GMLoseLayer::scene(), ccWHITE);
    //    CCDirector::sharedDirector()->replaceScene(pScene);
}


GMMenuLayer::~GMMenuLayer()
{
    delegateGame = NULL;
    effect = NULL;
    menuBatchNode = NULL;
    cannonSheet = NULL;
    cannon = NULL;
    loadingCt1 = NULL;
    loadingCt2 = NULL;
    pauseItem = NULL;
    skill1 = NULL;
    skill2 = NULL;
    bloodb = NULL;
    cupSprite = NULL;
    targetScoreProTimer = NULL;
    
    m_pScoreNum = NULL;
    m_pScoreNum1 = NULL;
    m_pTimeGNum = NULL;
    m_pTimeMNum = NULL;
    m_pTotalMoneyNum = NULL;
    
    toTheTiming = NULL;
    
//    this->removeChild(junengSheet, true);
    this->removeChild(cannonSheet, true);
    this->removeChild(menuBatchNode, true);
    
    CCRemoveSpriteFrameByName(mainmenu_plist);
    CCRemoveSpriteFrameByName(cannon_plist);
//    CCRemoveSpriteFrameByName(juneng_plist);
    CCRemoveSpriteFrameByName(mainmenuTask_plist);
    
    CCRemoveTextureForKey(mainmenu_png);
    CCRemoveTextureForKey(cannon_png);
//    CCRemoveTextureForKey(juneng_png);
    CCRemoveTextureForKey(mainmenuTask_png);
    
    CCRemoveSpriteFrameByName(mainmenu021_plist);
    CCRemoveTextureForKey(mainmenu021_png);
    
    CCRemoveSpriteFrameByName(changeboom_plist);
    CCRemoveTextureForKey(changeboom_png);
    
    CCRemoveSpriteFramesAndTextureForKey(liuguang_plist,liuguang_png);
    
    CCRemoveSpriteFramesAndTextureForKey(juneng_plist,juneng_png);
    
    this->cleanup();
    ZPLog("~~~GMMenuLayer");
}



