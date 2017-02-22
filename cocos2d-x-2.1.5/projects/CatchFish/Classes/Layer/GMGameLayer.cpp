
//  GMGameLayer.cpp
//  FishX
//
//  Created by peng on 12-12-24.
//
//

#include "GMGameLayer.h"

#include "GMCardLayer.h"
#include "GMWinLayer.h"
#include "GMLoseLayer.h"

#include "../Models/GMEnemyAction.h"
#include "../Models/GMCheckpoints.h"
#include "../Models/GMStrange.h"
#include "../Models/GMNet.h"
#include "../Models/GMPoint.h"

#include "../Models/GMBoss1Action.h"
#include "../Config/GMHeaderConfig.h"
#include "../Models/GMGoods.h"
#include "../Models/GMBossOctopus.h"
#include "../Models/GMBossStarfishKing.h"
#include "../PublicModels/ZPDialogLayer.h"
#include "GMMainLayer.h"
#include "../Models/GMBossPoseidon.h"
#include "../PublicModels/GMBillingLayer.h"
#include "../Models/CountBullet.h"
#include "../PublicModels/ZPJNIHelper.h"


static int64_t millisecondNow() {
	struct timeval tv;
	gettimeofday(&tv, (struct timezone *) NULL);
	int64_t when = tv.tv_sec * 1000LL + tv.tv_usec / 1000;
	return when;
}

CCScene* GMGameLayer::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    GMGameLayer *layer = GMGameLayer::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
	layer->setTag(0xff001f);
	// temp add lable


    // return the scene
    return scene;
}


void GMGameLayer::draw()
{
//    CCLayer::draw();

    if (bossLayer) {
//        GMBossOctopus *bossOctopus = (GMBossOctopus*)bossLayer->getChildByTag(BOSS_TAG2);
//        if (bossOctopus) {
//            ccDrawCircle( ccp(WINSIZE_W/2,WINSIZE_H-177*Scale_Y/2), 62, 360,360,false);
//        }
//        GMBossPoseidon *bossPoseidon = (GMBossPoseidon*)bossLayer->getChildByTag(BOSS_TAG4);
//        if (bossPoseidon) {
//            float enemyImageSize = 200/2*Scale_X;
//            ccDrawCircle( bossPoseidon->getBossPoseidonPoint(), enemyImageSize, 360,360,false);
//        }
        
    }
//    CCObject *pObject;
//    GMBullet *tempBullet;
//    CCARRAY_FOREACH(allEnemyBulletArray,pObject) {
//        tempBullet = (GMBullet*)pObject;
//        float tt = 10;;
//        ccDrawCircle( tempBullet->getPosition(), tt, 360,360,false);
//    }
//    
//    GMNet *net;
//    CCARRAY_FOREACH(allNetArray,pObject) {
//        net = (GMNet*)pObject;
//        float tt = (net->getNetBox().size.width-10)/2;
//        ccDrawCircle( net->getPoint(), tt, 360,360,false);
//    }
//    CCObject *pObject;
//    GMBullet *tempBullet;
//    CCARRAY_FOREACH(allEnemyBulletArray,pObject) {
//        tempBullet = (GMBullet*)pObject;
//        float tempW = tempBullet->getContentSize().width/2;
//        
//        ccDrawCircle( tempBullet->getPosition(), tempW, 360,360,false);
//        
////        float a = DADIANS_TO_DEGREES1(tempBullet->getRotation());
////       
////        float tempx = sinf(a)*tempW;
////        float tempy = cosf(a)*tempW;
////        CCPoint point = ccp(tempBullet->getPosition().x+tempx,tempBullet->getPosition().y+tempy);
////        ccDrawCircle( point, tempW, 360,360,false);
////        tempx = sinf(a)*tempW;
////        tempy = cosf(a)*tempW;
////        point = ccp(tempBullet->getPosition().x-tempx,tempBullet->getPosition().y-tempy);
////        ccDrawCircle( point, tempW, 360,360,false);
//
//    }
    
//    CCObject *nObject;
//    GMNet *tempNet;
//    CCARRAY_FOREACH(allNetArray,nObject) {
//        tempNet = (GMNet*)nObject;
//        float tempW = tempNet->getNetWidth()/2;
//        
//        ccDrawCircle( tempNet->getPoint(), tempW, 360,360,false);
//    }
}
// on "init" you need to initialize your instance

GMGameLayer::GMGameLayer()
{
    init();
}
bool GMGameLayer::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    this->setTouchEnabled(true);

    gameMode = GMPublicMethod::sharedPublicMethod()->getGameMode();
    billingModel = GMPublicMethod::sharedPublicMethod()->getBillingModel();
    
    if(gameMode == Story_Mode)
        currentLevel = GMAccessData::sharedAccessData()->getCurrentLevel();
    else
        currentLevel = 0;
    /*
     *
     */
    int tempStatus = GMAccessData::sharedAccessData()->getGenuineValidationStatus();
    if(tempStatus != 2)
        GMAccessData::sharedAccessData()->saveGenuineValidationStatus(0);
  
    if(gameMode == Boot_Mode){
        GMAccessData::sharedAccessData()->saveTotalMoneyNum(2000);
        GMAccessData::sharedAccessData()->saveSkillBloodNum(2);
        GMAccessData::sharedAccessData()->saveSkillPaysNum(2);
    }

	char str[50];
	sprintf(str, "the platform is %d", CC_TARGET_PLATFORM);
	CCLabelTTF *lable = CCLabelTTF::create(str, "", 50);
	lable->setPositionX(400);
	lable->setPositionY(500);
	lable->setTag(999012);
	
	this->addChild(lable);
	this->fireDelay = 100;
	this->fireOn = 0;
	this->arrowDir = 0;
	this->arrowTurnSpeed = 5;
    initValue();
    
    this->setKeypadEnabled(true);
	this->shootting = false;
	this->fireTimeCount = 0;
	this->choosedSkill = 0;
	this->touchLocation = ccp(400, 500);
    return true;
}

void GMGameLayer::initValue()
{
    isAgainTransform = true;
    isCheckBatter = false;
    checkBatterTimes = 0;
    _isLaser = false;
    countFrozenTime = 0;
    isFrozen = false;
    bossLayer = NULL;
    m_nCurrentScore = 0;
    taskHitNum = 0;
    countCritTime = 0;
    countPaysScore = 0;
    brushSTimes = 0.0;
    countbrushSTimes = 0.0;
    countTime = 0;
    countNum = 0;
    countHitNum = 0;
    taskOverTimes = 0;
    countPaysScore = 0;
    laserTimes = GMAccessData::sharedAccessData()->getAngerValue();
    laserTotalNum = 0;
    countCardTime = 0;
    
    wheelLayer = NULL;
    bootModeLayer = NULL;
    m_pLaserBullet = NULL;
    targetLayer = NULL;
    pauseLayer = NULL;
    
    isHitIDFish15 = false;
    m_nTotalMoney = 0;
    isAndroidBack = false;
    _isExistboss = 0;
    countTotalTime = 0;
    bulletGrade = 1;
    m_nMagnification = 1;
    m_nEndlessModeDataIndex = 1;
    countAllFishTag = 0;
    countFishBulletTag = 0;
    isShowDialogLayer = false;
    isShowDialogLayer2 = false;
    isShowDialogLayer3 = false;
    isShowPromptOpenCannon = false;
    countShootBulletTag = 0;
    m_pShootBullet = NULL;
    
    countSkillTime[0] = 0;
    countSkillTime[1] = 0;
    _isShowYiDong = false;
    
    _billing91Again = false;
    giftTime = GMAccessData::sharedAccessData()->getGiftCountdown();
//    srand( (unsigned)time( NULL ) );//srand()函数产生一个以当前时间开始的随机种子
}

void GMGameLayer::loadData(int status){
    switch (status) {
        case 5:{
            initFishFrames();
        }   break;
        case 10:{
            menuLayer = GMMenuLayer::create();
            this->addChild(menuLayer, MENU_Layer);
            menuLayer->delegateGame = this;
        }   break;
        case 12:{
            menuLayer->loadingData(0);
        }   break;
        case 15:{
            menuLayer->loadingData(1);
        }   break;
        case 20:{
            menuLayer->loadingData(2);
        }   break;
        case 23:{
            menuLayer->loadingData(3);
        }   break;
        case 26:{
            menuLayer->loadingData(4);
            int tempStatus = GMAccessData::sharedAccessData()->getRoleDeathStatus();
            if (gameMode == Boot_Mode && tempStatus == 0) {
                menuLayer->setSkill1Enabled(false);
                menuLayer->setSkill2Enabled(false);
                menuLayer->setMinusAndPlusEnabled(false);
            }
            else{
                menuLayer->setAllMenuEnabled(true);
            }
            menuLayer->setAngerValue(laserTimes);
            menuLayer->showCurrentScore(0);
            
            int num = GMAccessData::sharedAccessData()->getSkillBloodNum();
            menuLayer->setSKillNum1(num);
            num = GMAccessData::sharedAccessData()->getSkillPaysNum();
            menuLayer->setSKillNum2(num);

        }   break;
        case 30:{
            elementLayer = GMElementLayer::create();
            this->addChild(elementLayer,Element_Layer);
            elementLayer->setDelegate(this);
        }   break;
        case 32:{
            elementLayer->loadingData(0);
        }   break;
        case 34:{
            elementLayer->loadingData(1);
        }   break;
        case 36:{
            elementLayer->loadingData(2);
        }   break;
        case 38:{
            elementLayer->loadingData(3);
        }   break;
        case 40:{
            elementLayer->loadingData(4);
//            if(gameMode != Boot_Mode && billingModel!= B_Free && billingModel != B_91_IOS && billingModel!=B_YiDong)
            if(gameMode != Boot_Mode && billingModel == B_TengXunBilling)
            {
                elementLayer->addGift();
            }
        }   break;
        case 42:{
            skillElementLayer = GMElementLayer::create();
            this->addChild(skillElementLayer,0);
            skillElementLayer->setDelegate(this);
        }   break;
        case 45:{
             skillElementLayer->loadingData(5);
        }   break;
        case 55:{
            initTiledMap();
        }   break;
        case 60:{
            initElement();
        }   break;
        case 65:{
            
        }   break;
        case 70:{
            initBullet();
        }   break;
        case 75:{
            achievementPrompt = GMAchievementPrompt::create();
            this->addChild(achievementPrompt,APrompt_Layer);
            achievementPrompt->_delegate = this;
            //    achievementPrompt->showAchievement();
        }   break;
        case 80:{
            if (gameMode == Boot_Mode){
                bootModeLayer = GMBootModeLayer::create();
                this->addChild(bootModeLayer,100);
                bootModeLayer->setDelegate(this);
            }
        }   break;
        case 82:{
            //清空击中的鱼
            GMPublicMethod::sharedPublicMethod()->cleanHitArray();
            //清空技能状态
            GMPublicMethod::sharedPublicMethod()->setSkillType(SKILL_NONE);
            
            GMPublicMethod::sharedPublicMethod()->cleanEnergy();
        }   break;
        case 85:{
            //转盘
//            CCAddSpriteFramesWithFile(luck_plist1);
//            CCSpriteBatchNode *wheelBatchNode1 = CCSpriteBatchNode::create(luck_png1);
//            this->addChild(wheelBatchNode1);
        }   break;
        case 99:{
            if (gameMode == Boot_Mode) {
                brushSTimes = 0.8;
//                startGame();
//                bootModeLayer->showBootModeStory(0,0);
            }
            GMAudioPlay::sharedAudioPlay()->playBGMusic(Audio_Gmae1);
        }   break;
        default:
            break;
    }
}

void GMGameLayer::setFirstBootMode()
{
    if (gameMode == Boot_Mode) {
        bootModeLayer->showBootModeStory(0,0);
    }
}

void GMGameLayer::initElement()
{
    m_nTotalMoney = GMAccessData::sharedAccessData()->getTotalMoneyNum();
    ZPLog("游戏中第一次获取 money %d",m_nTotalMoney);
    menuLayer->setTotalMoneyNum(m_nTotalMoney);
    /*
     *  关卡所包含的数据
     */
    checkpointsList = new GMCheckpointsList();
    checkpointsList->readEnemyListOfFile("File/enemyList001.plist");
    checkpointsList->readFishBulletList();
    /*
     *  
     */
//    GMPublicMethod::sharedPublicMethod()->setConsumptionEnergy(0);
//    GMPublicMethod::sharedPublicMethod()->setGainEnergy(0);
    
    GMPublicMethod::sharedPublicMethod()->setEvaluationScore(0);
    
    countNum = 0;
    energyTime = EnergyTime;
    setReadNewFileData(1);
    if (gameMode == Endless_Mode) {
//        elementLayer->initBoss1BulletExplosionEffect();
//        elementLayer->initBossbloodFile();
//        initBossLayer();
//        initBoss1();
    }
    else if (gameMode == Boot_Mode) {
        elementLayer->initPetrifactionFile();
        elementLayer->initBoss1BulletExplosionEffect();
        elementLayer->initBossbloodFile();
    }
    
    int exist = GMAccessData::sharedAccessData()->getEachAchievementStatus(25);
    if (exist == 0) {
        m_pShootBullet = new CCArray();
    }
}

void GMGameLayer::setReadNewFileData(int index)
{
    strangeNum = 0;
//    currentScore = 0;
    GMCheckpoints *checkpoints = NULL;
        
    if (m_nEndlessModeDataIndex == 6) {
        index = 3;
    }
    
    if (index != 3) {
        char string[30] = {0};
        if (gameMode == Boot_Mode) {
            sprintf(string,"File/Checkpoints000.plist");
        }
        else if (gameMode == Endless_Mode) {
            sprintf(string,"File/Checkpoints%03d.plist",m_nEndlessModeDataIndex);
            currentLevel = m_nEndlessModeDataIndex;
        }
        else if(gameMode == Story_Mode){
            sprintf(string,"File/Checkpoints%03d.plist",currentLevel);
//            if (currentLevel%10 == 5 || (currentLevel==11))
            {
                
            }
        }
        CCAddSpriteFramesAndTextureFile(guide2_plist,guide2_png);
        checkpointsList->readWithContentsOfFile(string);
        
        checkpoints = checkpointsList->getCheckpoint(0);
        if(checkpoints){
            countCardTime = checkpoints->_time;
            taskShowTime = checkpoints->_trigger_task_time;
            totalNum = checkpoints->_brush_strange_num;
            
            menuLayer->setTargetScore(checkpoints->_target_score);
//            menuLayer->setCurrentScore(0);
            
            GMPublicMethod::sharedPublicMethod()->setEvaluationScore(checkpoints->_evaluation_score);
            int time = checkpoints->_brush_strange_end_time-checkpoints->_brush_strange_start_time;
            startBrushSTime = checkpoints->_brush_strange_start_time;
            brushSTimes = (float)time/(float)checkpoints->_brush_strange_num;
            ZPLog("随机刷怪时间： %f",brushSTimes);
            
            _isExistboss = checkpoints->_isExistboss;
            menuLayer->showCountdown(_isExistboss);
            index = _isExistboss;
        }
        
        task = NULL;
        if (checkpointsList->getTaskCount()>0) {
            task = checkpointsList->getGMTask(0);
        }
        
        strangeNum = checkpointsList->getStrangeCount();
    }

    if (gameMode == Story_Mode || gameMode == Endless_Mode) {
        if (index!=3) {
            menuLayer->setCheckpointsTimeValue(countCardTime);
            
        }
        targetLayer = GMTargetLayer::create();
        if (targetLayer) {
            targetLayer->initElement(index,m_nEndlessModeDataIndex);
            this->addChild(targetLayer, Target_Layer);
            targetLayer->_delegate = this;
            if (index == 0) {
                if (checkpoints)
                    targetLayer->showFishKind(checkpoints->_target_score,checkpointsList->getStrangeArray());
            }
            else if(index == 1){
                GMStrange *strange = (GMStrange*)checkpointsList->getStrange(0);
                GMEnemy *enemy = checkpointsList->getEnemy(strange->_strange_id-1);
                int tempId = enemy->_id;
                targetLayer->showBossIcon(tempId);
            }
            else if(index == 2){
                if (checkpoints)
                    targetLayer->showScoreAndTime(checkpoints->_target_score,countCardTime);
            }
            else if(index == 3){
                winOverSaveData(false);
                targetLayer->showAllValue();
                int num = GMAccessData::sharedAccessData()->getEndlessModeNum();
                if(num == 0)
                    GMAccessData::sharedAccessData()->saveEndlessModeNum(1);
            }
            if (gameMode == Endless_Mode){
                m_nEndlessModeDataIndex++;
            }
        }
    }
}

void GMGameLayer::startGame()
{
    for (int i = 0; i < RandFishNum; i++) {
        for (int j = 0; j < 2; j ++) {
            countStrangeNum[i][j] = 0;
        }
    }
    
    countTime = 0;
    
    GMPublicMethod::sharedPublicMethod()->setGameStatus(Game_Status);
//    if (gameMode != Boot_Mode){
//        GMPublicMethod::sharedPublicMethod()->setGameStatus1(Game_Status);
//    }
    this->removeChild(targetLayer, true);
    targetLayer = NULL;
   
    GMPublicMethod::sharedPublicMethod()->setMoveStatus(M_Status);
  
    unscheduleGame();
    
    this->schedule(schedule_selector(GMGameLayer::checkUpadte), 1);
    this->schedule(schedule_selector(GMGameLayer::update), 0.05);
    this->schedule(schedule_selector(GMGameLayer::updateCheckNetAndFish));

    pauseAllAction(false);
    
    achievementPrompt->showEnergePrompt(500);
    
    menuLayer->showTargetProTimer(m_nCurrentScore,true,currentLevel);
    
    if (gameMode == Story_Mode && currentLevel == 11) {
        showDialogLayer();
    }
    
    int tempVS = GMAccessData::sharedAccessData()->getGenuineValidationStatus();
    if(tempVS!=2)
        GMAccessData::sharedAccessData()->saveGenuineValidationStatus(0);
//    initBossLayer();
//    initBossPoseidon();
//
//    elementLayer->initBoss1BulletExplosionEffect();
//    elementLayer->initBossbloodFile();
//    elementLayer->showBoosBlood();
    
//    addBilling(1,0);
    int time = GMAccessData::sharedAccessData()->getGiftCountdown();
    if(time == 0 && billingModel!= B_Free && billingModel != B_91_IOS){
        elementLayer->setGiftTime(time);
    }
}

//#pragma mark - CCTMXTiledMap
void GMGameLayer::initTiledMap()
{
    /*
     *  水泡粒子特效
     */
    elementLayer->showParticles(Particles4,ccp(50, 0));
    elementLayer->showParticles(Particles4,ccp(WINSIZE_W-50, 0));
    
    /*
     *  获取所有的曲线
     */
    curvePointArray = new CCArray();
    GMPublicMethod::getCurveDataFromTiledMap(curvePointArray);
   
    fishArrayData = new CCArray();
    GMPublicMethod::getFishArrayDataFromTiledMap(fishArrayData);
    
    allEnemyArray = new CCArray();
    allEnemyBulletArray = new CCArray();
    allBulletArray = new CCArray();
    allNetArray = new CCArray();
}

//#pragma mark - enemy
/*
 *  加载鱼的资源文件
 */
void GMGameLayer::initFishFrames(){
    CCAddSpriteFramesWithFile(Fish_plist1);
    fishBatchNode1 = CCSpriteBatchNode::create(Fish_png1);
    this->addChild(fishBatchNode1);
    
    CCAddSpriteFramesWithFile(Fish_plist2);
    attackfishBatchNode1 = CCSpriteBatchNode::create(Fish_png2);
    this->addChild(attackfishBatchNode1);
    
    fishLayer = new CCLayer();
    this->addChild(fishLayer,1 );
    
    if(gameMode ==  Boot_Mode){
        CCAddSpriteFramesWithFile(mermaid_plist);
        CCSpriteBatchNode *mermaidBatchNode = CCSpriteBatchNode::create(mermaid_png);
        this->addChild(mermaidBatchNode);
    }
    
    scaleValue = FISH_SCALE;
}

void GMGameLayer::randEnemy()
{
    int randValue = rand()%100+1;
    for (int i = 0; i < strangeNum; i ++) {
        GMStrange *strange = checkpointsList->getStrange(i);
        if (randValue > strange->_interval_range1 && randValue <= strange->_interval_range2) {
            int index = strange->_id-1;
            countStrangeNum[index][0] = strange->_id;
            if (countStrangeNum[index][1] < strange->_limit_num){
                if (strange->_fishArray_id == 0) {
                    addEnemy(strange->_strange_id,R_Rand,ccp(100.0f,200.0f));
                    countStrangeNum[index][1] = countStrangeNum[index][1]+1;
                }
                else if( strange->_fishArray_id != 0 && countTime%5==0){
                    setRandCurve(strange);
                    countStrangeNum[index][1] = countStrangeNum[index][1]+1;
                }
            }
        }
    }
    
//    for(int i = 0 ; i < strangeNum; i++)
//    {
//        CCLog("随机鱼的数量 %d (%d %d)",i,countStrangeNum[i][0],countStrangeNum[i][1]);
//    }

}

void GMGameLayer::addEnemy(int _id, EnemyRouteStatus status,CCPoint point)
{
    countNum++;
    GMEnemy *enemy = checkpointsList->getEnemy(_id-1);

    GMEnemyAction *enemyAction = new GMEnemyAction();
    enemyAction->setInitValue();
    enemyAction->setRouteStatus(status);
//    enemyAction->setRandEnemyValue(this,enemy,scaleValue);
    enemyAction->setInitTheseProperties(this,enemy,scaleValue);
    if (status == R_Rand) {
        enemyAction->randDirection();
    }
    else if (status == R_NotMoveOut)  {
        enemyAction->setPosition(point);
        enemyAction->randRotationMove();
    }
    enemyAction->setEnemyTag(++countAllFishTag);
    allEnemyArray->addObject(enemyAction);
    fishLayer->addChild(enemyAction);
    //enemyAction->release();
    //enemyAction = NULL;
}

// 鱼阵 
void GMGameLayer::addFishArray(GMStrange *strange ,EnemyRouteStatus status)
{
    int fishArray_id = strange->_fishArray_id-1;
    int obrit_id = strange->_obrit_id-1;
    int direction = strange->_direction;
    
    CCArray *tempCurve = (CCArray*)curvePointArray->objectAtIndex(obrit_id);
    if (strange->_type == 2) {
        CCArray *temp = (CCArray*)fishArrayData->objectAtIndex(fishArray_id);
        if (temp->count()>0) {
            for (int i = 0; i < temp->count(); i ++) {
                GMPoint *pPoint = (GMPoint*)temp->objectAtIndex(i);
                GMEnemy *enemy = checkpointsList->getEnemy(pPoint->_id-1);

                GMEnemyAction *enemyAction = new GMEnemyAction();
                enemyAction->setInitValue();
                enemyAction->setRouteStatus(status);
                enemyAction->setCurveValue(this,enemy,pPoint->_point,tempCurve,direction,pPoint->_row,pPoint->_time,scaleValue);
                enemyAction->setEnemyTag(++countAllFishTag);
                fishLayer->addChild(enemyAction);
                allEnemyArray->addObject(enemyAction);
                enemyAction->release();
                enemyAction = NULL;
            }
        }
    }
    else if(strange->_type == 1)
    {
//        ZPLog("%d",strange->_strange_id);
        GMEnemy *enemy = checkpointsList->getEnemy(strange->_strange_id-1);
        char fishName[40] = {0};
        sprintf(fishName,"yu%02d%s%03d.png",strange->_strange_id,"a",1);
        GMEnemyAction *enemyAction = new GMEnemyAction();
        enemyAction->setInitValue();
        enemyAction->setRouteStatus(R_Curve_Single);
        enemyAction->setCurveValue(this,enemy,ccp(-100, -100),tempCurve,direction,1,0,scaleValue);
        enemyAction->setEnemyTag(++countAllFishTag);
        fishLayer->addChild(enemyAction);
        allEnemyArray->addObject(enemyAction);
        enemyAction->release();
        enemyAction = NULL;
    }
}

void GMGameLayer::setRandCurve(GMStrange *strange ){
    int fishArrayIndex = strange->_fishArray_id-1;
    ccBezier tempBezier1  = GMPublicMethod::getRandCurveBezier();
    CCArray *temp = (CCArray*)fishArrayData->objectAtIndex(fishArrayIndex);
    if (temp->count()>0) {
        for (int i = 0; i < temp->count(); i ++) {
            GMPoint *pPoint = (GMPoint*)temp->objectAtIndex(i);
            GMEnemy *enemy = checkpointsList->getEnemy(pPoint->_id-1);
            GMEnemyAction *enemyAction = new GMEnemyAction();
            enemyAction->setInitValue();
            enemyAction->setRandCurvePoint(enemy,this,tempBezier1,pPoint->_row,pPoint->_time,scaleValue);
            enemyAction->setDelegate(this);
            enemyAction->setEnemyTag(++countAllFishTag);
            fishLayer->addChild(enemyAction);
            allEnemyArray->addObject(enemyAction);
            enemyAction->release();
            enemyAction = NULL;
        }
    }
}

void GMGameLayer::enemyDeath(GMEnemyAction* enemyAction)
{
    if (bootModeLayer != NULL) {
        if (gameMode == Boot_Mode && enemyAction->_id == 15 && bootModeLayer->getStoryStatus() == 10 && enemyAction->_deathStatus == 1) {
            bootModeLayer->setOtherValue();
        }
    }
//    ZPLog("deathStatus %d",enemyAction->_deathStatus);
    if (enemyAction->_id == 15 && enemyAction->_deathStatus == 2) {
        showWheelView();
        isHitIDFish15 = false;
    }
    /*
     *  显示能量和数字
     */
    if (enemyAction->_deathStatus == 2) {
        elementLayer->addEnergeBlink(enemyAction->getPosition(),scaleValue);
        
        int tempScore = 0;
        m_nMagnification = GMPublicMethod::getChooseMagnificationModel();
        if(countHitNum>0){
            tempScore = enemyAction->_numerical*m_nMagnification+enemyAction->_numerical*m_nMagnification/100*countHitNum*countHitNum+countHitNum/2;
        }
        else {
            tempScore = enemyAction->_numerical*m_nMagnification;
        }
        elementLayer->showNumber(tempScore,enemyAction->getPosition());
    }

    removeEnemyFromBatchNode(enemyAction);
}

//#pragma mark - 鱼的子弹
/*
 *  添加鱼的子弹
 */
void GMGameLayer::addFishBullet(CCNode *pNode)
{
    GMEnemyAction *enemyAction = (GMEnemyAction*)pNode;
    enemyAction->_isShootBullet = true;
    
    setFishBullet(enemyAction->getRotation(),enemyAction->getPosition(),enemyAction->_id);
    
//    float a = DADIANS_TO_DEGREES1( enemyAction->getRotation() );
//    float tempx = sinf(a)*30;
//    float tempy = cosf(a)*30;
//    float tempX = enemyAction->getPosition().x;
//    float tempY = enemyAction->getPosition().y;
//    //1
//    CCPoint point = ccp(tempX+tempx,tempY+tempy);
//    GMBullet *fBullet = new GMBullet();
//    fBullet->setFishBullerValue(enemyAction->_id,point,checkpointsList->getFishBullet(enemyAction->_id));
//    
//    fBullet->setDelegate(this);
//    fBullet->fishBulletMove(ccp(WINSIZE_W/2,30*Scale_X),6);
//    fBullet->setBulletTag(countFishBulletTag++);
//    allEnemyBulletArray->addObject(fBullet);
//    fishBulletLayer->addChild(fBullet);
//    fBullet->release();
//    fBullet = NULL;
    
    enemyAction->_isShootBullet = false;
    enemyAction->setAttackTime(0);

    enemyAction->continueMoveAction1();
    ZPLog("攻击鱼再次游动");
}

void GMGameLayer::setFishBullet(float rotation,CCPoint point,int _id)
{
    float a = DADIANS_TO_DEGREES1( rotation );
    float tempx = sinf(a)*30;
    float tempy = cosf(a)*30;
    float tempX = point.x;
    float tempY = point.y;
    //1
    point = ccp(tempX+tempx,tempY+tempy);
    GMBullet *fBullet = new GMBullet();
    fBullet->setFishBullerValue(_id,point,checkpointsList->getFishBullet(_id));
    
    fBullet->setDelegate(this);
    fBullet->fishBulletMove(ccp(WINSIZE_W/2,30*Scale_X),6);
    fBullet->setBulletTag(++countFishBulletTag);
    allEnemyBulletArray->addObject(fBullet);
    fishBulletLayer->addChild(fBullet);
    fBullet->release();
    fBullet = NULL;
}


void GMGameLayer::fishBulletMove(GMBullet *fBullet)
{
    CCMoveTo *moveTo = CCMoveTo::create(1, ccp(WINSIZE_W/2,20));
    CCCallFuncN  *callfunc = CCCallFuncN::create(this, callfuncN_selector( GMGameLayer::fishBulletMoveAfter ) );
    CCFiniteTimeAction *sequence = CCSequence::create(moveTo,callfunc,NULL);
    fBullet->runAction(sequence);
}

void GMGameLayer::fishBulletMoveAfter(CCNode *pNode)
{
	GMBullet *bullet = (GMBullet *)pNode;
    GMAudioPlay::sharedAudioPlay()->playAttackEffect(Audio_attack2);
    if (bullet->_id == 1 || bullet->_id == 2) {
        elementLayer->boss1ExplosionAnimation(bullet->_id,ccp(bullet->getPosition().x,bullet->getPosition().y+10));
    }
    else {
        elementLayer->bulletExplosionAnimation(bullet->_id,bullet->getPosition(),scaleValue);
    }
    removeFishBullet(bullet);
}

void GMGameLayer::removeFishBullet(GMBullet *bullet)
{
    allEnemyBulletArray->removeObject(bullet);
    fishBulletLayer->removeChild(bullet, true);
    bullet = NULL;
}

void GMGameLayer::removeCollisionFishBullet(GMBullet *bullet)
{
    removeFishBullet(bullet);
}
//#pragma mark - 更换炮台
void GMGameLayer::changeCannon(int index)
{
    if (index <= 0) {
        index = 1;
    }
    menuLayer->cannonIndex = index;
    menuLayer->changeCannon(menuLayer->cannonIndex);
    elementLayer->changeShowNumeber(menuLayer->cannonIndex);
    bulletGrade = menuLayer->cannonIndex;
}

//#pragma mark - bullet
void GMGameLayer::initBullet()
{
    // 炮台纹理
//    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(Buttle_plist1);
    CCAddSpriteFramesWithFile(Buttle_plist1);
    bulletSheet = CCSpriteBatchNode::create(Buttle_png1);
    this->addChild(bulletSheet,Bullet_Layer);
    
    CCAddSpriteFramesWithFile(Jiguang_plist);
    laserSheet = CCSpriteBatchNode::create(Jiguang_png);
    this->addChild(laserSheet,Bullet_Layer);
    
    CCAddSpriteFramesWithFile(yuwang_plist);
    netBatchNode = CCSpriteBatchNode::create(yuwang_png);
    this->addChild(netBatchNode,Bullet_Layer);
    
    CCAddSpriteFramesWithFile(fishBullet_plist);
    fishBulletBatchNode = CCSpriteBatchNode::create(fishBullet_png);
    this->addChild(fishBulletBatchNode,Bullet_Layer+3);
    
    fishBulletLayer = CCLayer::create();
    menuLayer->addChild(fishBulletLayer,Bullet_Layer);
    
    //子弹粒子层
    netParticleLayer = CCLayer::create();
    netParticleLayer->setContentSize(CCSizeMake(WINSIZE_W, WINSIZE_H));
    netParticleLayer->setAnchorPoint(ccp(0, 0));
    netParticleLayer->setPosition(ccp(0,0));
    this->addChild(netParticleLayer,Bullet_Layer);
    
}

void GMGameLayer::addBullet(CCPoint shootVector)
{
    GMAudioPlay::sharedAudioPlay()->playAttackEffect(Audio_attack1);
    
    _isLaser = false;
    
    int index = menuLayer->cannonIndex;
    bulletGrade = index;
    GMBullet *roleBullet = new GMBullet();
    roleBullet->setCannonBullerValue(index,menuLayer->getTransformAngle(),menuLayer->getCannonPointX());

    CCPoint normalizedShootVector = ccpNormalize(shootVector);
    CCPoint overshotVector = ccpMult(normalizedShootVector, WINSIZE_W);
    CCPoint offscreenPoint = ccpAdd(roleBullet->getPosition(), overshotVector);
    float dt = 2.0f;
    CCMoveTo *moveTo = CCMoveTo::create(dt,offscreenPoint);
    CCCallFuncN *callfuncN = CCCallFuncN::create(this, callfuncN_selector(GMGameLayer::automaticallyRemovedBullet));
    CCFiniteTimeAction* sequence = CCSequence::create(moveTo,callfuncN,NULL);
    roleBullet->runAction(sequence);
    
    roleBullet->setTag(++countShootBulletTag);
    
    allBulletArray->addObject(roleBullet);
    bulletSheet->addChild(roleBullet);
    roleBullet->release();
    roleBullet = NULL;
    
    m_nMagnification = GMPublicMethod::getChooseMagnificationModel();
    //减能量
    int tempValue = bulletGrade*m_nMagnification;//menuLayer->cannonIndex*m_nMagnification;
    
	//测试
	tempValue = 0;

    setTotalMoney(-tempValue);
//    totalMoney = totalMoney-tempValue;
//    if(totalMoney<=0){
//        totalMoney = 0;
//    }
//    menuLayer->setTotalMoneyNum(totalMoney);
    GMPublicMethod::sharedPublicMethod()->setConsumptionEnergy(tempValue);
}

void GMGameLayer::automaticallyRemovedBullet(CCNode *pNode)
{
	GMBullet *bullet = (GMBullet*)pNode;
    if (m_pShootBullet) {
        CountBullet *countBullet = new CountBullet();
        countBullet->setBulletTag(bullet->getTag());
        countBullet->setFishNum(1);
        m_pShootBullet->addObject(countBullet);
        countBullet->release();
        
        ZPLog("m_pShootBullet %d",m_pShootBullet->count());
    }
    removeBullet(bullet);
}

void GMGameLayer::removeBullet(GMBullet*bullet)
{
    allBulletArray->removeObject(bullet);
    bulletSheet->removeChild(bullet, true);
}

//#pragma mark - Laser
void GMGameLayer::addLaser()
{
    if (_isLaser) {
        return;
    }
    GMAudioPlay::sharedAudioPlay()->playAngerEffect();
//    menuLayer->setAnger();
    _isLaser = true;
    ZPLog("addLaser %d",_isLaser);
    laserTimes = 0;
    m_pLaserBullet = new GMBullet();
    m_pLaserBullet->initWithSpriteFrameName("jiguang001.png");
    m_pLaserBullet->isLaser = true;
    m_pLaserBullet->setAnchorPoint(ccp(0.5, 0.2));
    SetScale2(m_pLaserBullet, scaleValue);
    float angle = menuLayer->getTransformAngle();
    float tempy = 100;
    float a = DADIANS_TO_DEGREES1(angle);
    float tempx = tempy*sinf(a);
    tempy = tempy*cosf(a);
    tempx = menuLayer->getCannonPointX()+tempx;
    CCPoint point = ccp(tempx, tempy);
    m_pLaserBullet->setPosition(point);
    m_pLaserBullet->setRotation(angle);
    m_pLaserBullet->setLaserAnimation(this,callfuncN_selector(GMGameLayer::removeLaser));
    
    laserSheet->addChild(m_pLaserBullet);
    ZPLog("添加技能===============1");
}

void GMGameLayer::removeLaser(CCNode *pNode)
{
    GMAccessData::sharedAccessData()->saveAngerValue(0);
    
    _isLaser = false;
    laserTimes = 0;
    m_pLaserBullet->cleanup();
    laserSheet->removeChild(m_pLaserBullet, true);
    m_pLaserBullet = NULL;
    
    menuLayer->showLaser(_isLaser);
    ZPLog("释放技能===============1");
    menuLayer->setAnger();
    
    this->scheduleOnce(schedule_selector(GMGameLayer::showLaserReward), 1);
}

void GMGameLayer::showLaserReward(float dt){
    if(laserTotalNum > Max_Score1){
        elementLayer->showRewardEffect(laserTotalNum);
    }
    laserTotalNum = 0;
}

//#pragma mark - net
void GMGameLayer::addNet(CCPoint point,int tag){
    GMNet *net = new GMNet();
    net->addNet(point,bulletGrade,this,scaleValue);
    net->setTag(tag);
    allNetArray->addObject(net);
    netParticleLayer->addChild(net);
    net->release();
    net = NULL;
}

void GMGameLayer::removeNet(int num,GMNet *net){
//    this->unschedule(schedule_selector(GMGameLayer::removeNet));
    int tempNetTag = net->getTag();
    allNetArray->removeObject(net);
    netParticleLayer->removeChild(net, true);
    net = NULL;
    achievementPrompt->showhitFishPrompt(num);
    
    CountBullet *countBullet = NULL;
    
    if(m_pShootBullet){
        bool exit = false;
        CCObject *tempObject;
        CCARRAY_FOREACH(m_pShootBullet,tempObject){
            countBullet = (CountBullet*)tempObject;
            if( countBullet->getBulletTag() == tempNetTag && countBullet->getFishNum() == 0 ){
                exit = true;
                countBullet->setFishNum(num);
            }
        }
        
        if(exit == false){
            countBullet = new CountBullet();
            countBullet->setBulletTag(tempNetTag);
            countBullet->setFishNum(1);
            m_pShootBullet->addObject(countBullet);
            countBullet->release();
        }
    }
    
    //连击效果
    if (num>0) {
        //击中效果
        checkBatter();
        if(m_pShootBullet){
            int tempTag2 = 0;
            bool isE = false;
            while (tempTag2 <= tempNetTag && isE == false) {
                for (int i = 0; i < m_pShootBullet->count(); i++) {
                    countBullet = (CountBullet*)m_pShootBullet->objectAtIndex(i);
                    tempTag2 = countBullet->getBulletTag();
                    ZPLog("tempNetTag %d %d",tempTag2, tempNetTag);
                    if(tempTag2<= tempNetTag){
                        m_pShootBullet->removeObjectAtIndex(i);
                        if(tempTag2 == tempNetTag)
                            isE = true;
                        break;
                    }
                }
            }
        }
    }
}

//#pragma mark - 发射子弹
/*
 *  发射子弹
 */
void GMGameLayer::firedBullets(CCPoint shootVector)
{
    if (m_nTotalMoney>0 ) {
        if (menuLayer->getAnger() == true && menuLayer->isShootLaser == true) {
            addLaser();
        }
        else if(menuLayer->getAnger() == false){
//            ZPLog("测试7");
            addBullet(shootVector);
        }
    }
    else {
        GMAudioPlay::sharedAudioPlay()->playOtherEffect(Audio_Rayover,false);
    }
}

void GMGameLayer::finishShoot()
{
	char str[128];
	sprintf(str, " into finishShoot location is x%f,y%f, direction%d, fire%d", this->touchLocation.x, this->touchLocation.y, this->arrowDir, this->fireOn);
	CCLog(str);
	isAgainTransform = true;
	if (this->fireOn == 0) return;
	this->fireOn = 0;
    int _pauseStatus = GMAccessData::sharedAccessData()->getPauseStatus();
    if(_pauseStatus == 1){
        
        ZPLog("暂停状态为一");
        return;
	}
    if( billingModel != B_Free && gameMode != Boot_Mode){
        if (showPromptOpenCannon()) {
            return;
        }        
    }
     m_nMagnification = GMPublicMethod::getChooseMagnificationModel();
    if (m_nTotalMoney>0 && m_nTotalMoney < bulletGrade*m_nMagnification) {
        if (m_nMagnification != 1) {
            menuLayer->setMagnificationModel1(-1);
            m_nMagnification = GMPublicMethod::getChooseMagnificationModel();
        }
        else {
            changeCannon(m_nTotalMoney);
        }
        return;
    }
    else if(m_nTotalMoney <= 0){
        if (billingModel != B_YiDong && billingModel != B_Telecom) {
            addBilling(2,0);
        }
    }
    GMSkill skilltype = GMPublicMethod::sharedPublicMethod()->getSkillType();
    if (skilltype != SKILL_PAYS) {
        firedBullets(tempVector);
    }
}

void GMGameLayer::spriteMoveFinished(CCObject *object){
    GMBullet *roleBullet = (GMBullet *)object;
    bulletSheet->removeChild(roleBullet, true);
    roleBullet = NULL;
}

//#pragma mark - 设置能量
void GMGameLayer::setCurrentScore(int scroe)
{
    m_nCurrentScore = m_nCurrentScore+scroe;
}

void GMGameLayer::setTotalMoney(int money)
{
	ZPLog("1 totalMoney %d == money %d",m_nTotalMoney,money);
    m_nTotalMoney = m_nTotalMoney+money;
    if(m_nTotalMoney<=0){
        m_nTotalMoney = 0;
    }
    menuLayer->setTotalMoneyNum(m_nTotalMoney);
//    ZPLog("2 totalMoney %d == money %d",m_nTotalMoney,money);
}
//获取能量阶段概率
float GMGameLayer::getStageRate(){
    float tempRate = 1.0f;
    if(billingModel == B_91_IOS || billingModel == B_91_Android){
        if(m_nTotalMoney<=3000){
            tempRate = 1;
        }
        else if(m_nTotalMoney >= 3001 && m_nTotalMoney <= 6000){
            tempRate = 0.8;
        }
        else if(m_nTotalMoney >= 6001 && m_nTotalMoney <= 10000){
            tempRate = 0.6;
        }
        else if(m_nTotalMoney >= 10001){
            tempRate = 0.4;
        }
    }
    else {
        if(m_nTotalMoney<=3000){
            tempRate = 1.2;
        }
        else if(m_nTotalMoney >= 3001 && m_nTotalMoney <= 6000){
            tempRate = 1;
        }
        else if(m_nTotalMoney >= 6001 && m_nTotalMoney <= 10000){
            tempRate = 0.8;
        }
        else if(m_nTotalMoney >= 10001){
            tempRate = 0.6;
        }
    }
    
    return tempRate;
}

//#pragma mark - 概率
/*
 *  获取倍率
 */
float GMGameLayer::getStoryModeRatio()
{
    /*
     *  剧情模式 倍率系统
     */
    float tempValue = 1.0f;
    int level = GMAccessData::sharedAccessData()->getCurrentMagnificationModel();//currentLevel/10;
    tempValue = 1 - ((level-1.0)/10);
    return tempValue;
}

/*
 *  怪物的爆率+怪物对炮弹影响率*炮弹等级
 */
float GMGameLayer::getRate(GMEnemyAction* enmey)
{
    float tempValue2 = 1.5;
    if (_isLaser==true) {
        float temp = 0;
        float temp2 = GMPublicMethod::getChooseMagnificationModel1();
        if (critSkill == SKILL_Crit) {
            temp = enmey->_burst_rate + enmey->_shells_affect_rates*temp2*bulletGrade*2*tempValue2;
        }
        else {
            temp = enmey->_burst_rate + enmey->_shells_affect_rates*temp2*bulletGrade*tempValue2;
        }
        return temp;
    }
    else {
        float tempRate = getStageRate();
        /*
         * 倍率系统
         */
        float tempValue = getStoryModeRatio();
        float temp = 0;
        if (critSkill == SKILL_Crit) {//暴击翻倍
            temp = enmey->_burst_rate*tempValue*tempRate + enmey->_shells_affect_rates*bulletGrade*2*tempValue2;
        }
        else {
            temp = enmey->_burst_rate*tempValue*tempRate + enmey->_shells_affect_rates*bulletGrade*tempValue2;
        }
        if (temp > enmey->_limit_burst_rate*tempValue*tempRate) {
            temp = enmey->_limit_burst_rate*tempValue*tempRate;
        }
    //    ZPLog("getRate %d %f = (%f + %f x %d)", enmey->_id,temp,enmey->_burst_rate,enmey->_shells_affect_rates,bulletGrade);
        return temp;
    }
    return 0;
}

bool GMGameLayer::randRates(float rate){
    float w = rate;//*100;
    int randNum = rand()%1000;
    float m_fRandNum = randNum*0.1;
//    ZPLog("getRate %f == %d == %f ",w,randNum,m_fRandNum);
    if (m_fRandNum < w) {
        return true;
    }
    return false;
}
/*
 *  设置总能量和当前的分数
 */
void GMGameLayer::setMoneyAndSocre(int value)
{
    //设置总分数
    setTotalMoney(value);
    
    //当前的分数
    setCurrentScore(value);
    menuLayer->showCurrentScore(m_nCurrentScore);
    menuLayer->showTargetProTimer(m_nCurrentScore,false,currentLevel);
}
//void GMGameLayer::setCountBullet(int tag,int index,bool clean){
//    if(clean){
//        for (int i = 0 ; i < 10; i++) {
//            for (int j = 0; j < 2; i++) {
//                countShootBullet[i][j] = 0;
//            }
//        }
//    }
//    else {
//        for (int i = 0; i < 10; i++) {
//            if(countShootBullet[i][0]==0){
//                countShootBullet[i][0] = tag;
//            }
//        }
//    }
//}

//#pragma mark - 检测

//检测连击
void GMGameLayer::checkBatter()
{
    if (isCheckBatter) {
        checkBatterTimes = 0;
        countHitNum++;
        menuLayer->addBatterEffect(countHitNum);
        if (countHitNum == 2) {
            showPromptBatter();
        }
    }
    else {
        countHitNum = 0;
        isCheckBatter = true;
    }
}

void GMGameLayer::checkTaskFinshed(GMEnemyAction* enemyAction)
{
    if (menuLayer->isShowTaskBox && task) {
        
        if (enemyAction && enemyAction->_id == task->_strange_id) {
            taskHitNum++;
            menuLayer->setTaskNum(taskHitNum);
        }
        else if (enemyAction == NULL) {
            if ( taskHitNum >= task->_num && taskOverTimes==0) {
                //任务成功提示1
                menuLayer->setTaskTip(true);
                taskOverTimes = 0;
                setCurrentScore(task->_rewards);
                setTotalMoney(task->_rewards);
            }
            
            if (taskTimes <= 0 && taskHitNum < task->_num && taskOverTimes == 0){
                //任务失败提示
                menuLayer->setTaskTip(false);
                taskOverTimes = 0;
            }
            
            if(taskHitNum >= task->_num || (taskTimes <= 0 && taskHitNum < task->_num)){
                taskOverTimes++;
            }
            
            if (taskOverTimes==5) {
                menuLayer->removeTaskBox();
                
                //任务成功提示2
                if (taskHitNum >= task->_num ){
                    elementLayer->showTaskPrompt2(task->_rewards);
                }
            }
            else if(taskOverTimes == 7){
                elementLayer->removeTaskPrompt2();
                menuLayer->isShowTaskBox = false;
                taskOverTimes = 0;
            }
        }
    }
}

void GMGameLayer::winOverSaveData(bool isScore)
{
    GMAccessData::sharedAccessData()->saveGiftCountdown(giftTime);
    
    menuLayer->setTotalMoneyNum(m_nTotalMoney);
    ZPLog("保存 money %d",m_nTotalMoney);
    GMAccessData::sharedAccessData()->saveTotalMoneyNum(m_nTotalMoney);
    
    GMPublicMethod::sharedPublicMethod()->setGainEnergy(m_nCurrentScore);
    //保存本关的分数
    if(gameMode == Story_Mode){
        int tempScore = GMAccessData::sharedAccessData()->getEachLevelScore(currentLevel);
        if (m_nCurrentScore>tempScore) {
            GMAccessData::sharedAccessData()->saveEachLevelScore(currentLevel,m_nCurrentScore);
            int num = GMPublicMethod::getStarNum();
            int saveNum = GMAccessData::sharedAccessData()->getEachLevelStar(currentLevel);
            if (num > saveNum && isScore) {
                GMAccessData::sharedAccessData()->saveEachLevelStar(currentLevel,num);
            }
        }
    }
}

void GMGameLayer::checkWinOrFail()
{
//    winOverSaveData();

    GMCheckpoints *checkpoints = checkpointsList->getCheckpoint(0);
    if (gameMode == Story_Mode) {
        //检测
        if (countCardTime <= 0) {
            
            if (checkpoints && m_nCurrentScore >= checkpoints->_target_score && menuLayer->getLifeValue()>0) {
                this->cleanup();
                unscheduleGame();
                
                if (_isExistboss == 1) {
                    if(bossLayer){
                        GMBossOctopus *bossOctopus = (GMBossOctopus*)bossLayer->getChildByTag(BOSS_TAG2);
                        if (bossOctopus) {
                            if (bossOctopus->getOctousLife()<0) {
//                                GMAccessData::saveOpenCheckpoints((currentLevel/10),(currentLevel+1));
//                                CCScene *pScene = CCTransitionFade::create(0.0, GMWinLayer::scene(), ccWHITE);
//                                CCDirector::sharedDirector()->replaceScene(pScene);
                                skipWinLayer(0);
                            }
                            else {
//                                CCScene *pScene = CCTransitionFade::create(0.0, GMLoseLayer::scene(), ccWHITE);
//                                CCDirector::sharedDirector()->replaceScene(pScene);
                                skipLoseLayer();
                            }
                        }
                    }
                }
                else{
                    if(showOpenCannon()){

                    }
                    else {
                        if(billingModel == B_Free /*billingModel == B_91_IOS*//* || billingModel == B_91_Android*/){
                            if(currentLevel == GoToEndless){
                                if(showDialogLayer2()){
                                    winOverSaveData(true);
                                    GMAccessData::sharedAccessData()->saveOpenCheckpoints(currentLevel+1,1);
                                }
                                else {
                                    skipWinLayer(0);
                                }
                            }
                            else {
                                 skipWinLayer(0);
                            }
                        }
                        else {
                            int tempStatus = GMAccessData::sharedAccessData()->getGenuineValidationStatus();
                            int tempStatus1 = GMAccessData::sharedAccessData()->getEndlessModeStatus();
                            if (billingModel == B_Free) {
                                if(showDialogLayer2()){
                                    winOverSaveData(true);
                                    GMAccessData::sharedAccessData()->saveOpenCheckpoints(currentLevel+1,1);
                                }
                            }
                            else if(tempStatus != 2 && currentLevel == GoToEndless && tempStatus1 == 0){
                                winOverSaveData(true);
                                GMAccessData::sharedAccessData()->saveRoleDeathStatus(1);
                                addBilling(1,0);
                                GMAccessData::sharedAccessData()->saveOpenCheckpoints(currentLevel+1,1);
                            }
                            else if(tempStatus == 2 && currentLevel == GoToEndless){
                                if(showDialogLayer2()){
                                    winOverSaveData(true);
                                    GMAccessData::sharedAccessData()->saveOpenCheckpoints(currentLevel+1,1);
                                }
                                else {
                                    skipWinLayer(0);
                                }
                            }
                            else {
                                skipWinLayer(0);
                            }
                        }
                    }
//                    GMAccessData::saveOpenCheckpoints((currentLevel/10),(currentLevel+1));
//                    CCScene *pScene = CCTransitionFade::create(0.0, GMWinLayer::scene(), ccWHITE);
//                    CCDirector::sharedDirector()->replaceScene(pScene);
                }
            }
            else {
                this->cleanup();
                unscheduleGame();
//                
//                CCScene *pScene = CCTransitionFade::create(0.0, GMLoseLayer::scene(), ccWHITE);
//                CCDirector::sharedDirector()->replaceScene(pScene);
                skipLoseLayer();
            }
            
            GMAudioPlay::sharedAudioPlay()->stopBGMusic();
        }
    }
    
    /*
     *  当生命值小于0时over
     */
    if(menuLayer->getLifeValue()<=0){
        this->cleanup();
        unscheduleGame();
        if (gameMode == Endless_Mode) {
            countTotalTime = countTotalTime+countTime;
            setReadNewFileData(3);
            pauseAllAction(true);
            return;
        }
        else {
            if (bootModeLayer) {
                if(gameMode == Boot_Mode && bootModeLayer->getStoryStatus() == 15){
                    GMAccessData::sharedAccessData()->saveRoleDeathStatus(1);
                    ZPLog("GMAccessData::saveRoleDeathStatus(1);");
                }
            }
//            CCScene *pScene = CCTransitionFade::create(0.0, GMLoseLayer::scene(), ccWHITE);
//            CCDirector::sharedDirector()->replaceScene(pScene);
            GMAudioPlay::sharedAudioPlay()->stopBGMusic();
            skipLoseLayer();
        }
    }
}



void GMGameLayer::removeEnemyFromBatchNode (CCNode *pNode)
{
	GMEnemyAction* enemyAction = (GMEnemyAction*)pNode;
    GMSkill skilltype = GMPublicMethod::sharedPublicMethod()->getSkillType();
    if (skilltype == SKILL_PAYS) {
        /*
         *  记录总分值
         */
        countPaysScore = countPaysScore+enemyAction->_numerical;
        /*
         *  记录击中鱼的数目
         */
        GMPublicMethod::sharedPublicMethod()->setHitValue(enemyAction->_id);
    }
    /*
     *  任务计数
     */
    if (enemyAction->_deathStatus == 2) {
        checkTaskFinshed(enemyAction);
    }
    
    enemyAction->cleanup();
    allEnemyArray->removeObject(enemyAction);
    fishLayer->removeChild(enemyAction,true);
    enemyAction = NULL;
}

/*
 *  检测固定刷怪
 */
void GMGameLayer::checkFixedBrushStrange(int time)
{
    if (gameMode == Boot_Mode) {
        int tempStatus = GMAccessData::sharedAccessData()->getRoleDeathStatus();
        if (tempStatus != 1) {
            for (int i = 0; i < checkpointsList->getStrangeTableCount(); i++) {
                GMStrange *strange = checkpointsList->getStrangeTable(i);
                if (strange->_time == time) {
                    addFishArray(strange,R_Curve_Formation);
                }
            }
        }
    }
    else {
        for (int i = 0; i < checkpointsList->getStrangeTableCount(); i++) {
            GMStrange *strange = checkpointsList->getStrangeTable(i);
            if (strange->_time == time) {
                addFishArray(strange,R_Curve_Formation);
            }
        }
    }
    
}

//#pragma mark - 击中效果
void GMGameLayer::hitEffect(GMEnemyAction* enemyAction)
{
    /*
     *  显示你真牛
     */
     m_nMagnification = GMPublicMethod::getChooseMagnificationModel();
    if (enemyAction->_numerical*m_nMagnification > Max_Score1 && _isLaser==false) {
        if (enemyAction->_id == 10) {
            elementLayer->setPaysStats(3);
        }
        else {
            elementLayer->setPaysStats(0);
        }
        elementLayer->showRewardEffect(enemyAction->_numerical*m_nMagnification);
    }
    
    int tempScore = 0;
   
    if(countHitNum>0){
        tempScore = enemyAction->_numerical*m_nMagnification+enemyAction->_numerical*m_nMagnification/100*countHitNum*countHitNum+countHitNum/2;
    }
    else {
        tempScore = enemyAction->_numerical*m_nMagnification;
    }

    setMoneyAndSocre(tempScore);
    
    achievementPrompt->showEnergePrompt(m_nTotalMoney);
    //怒气值
    if (_isLaser==false) {
        laserTimes = GMAccessData::sharedAccessData()->getAngerValue();
        laserTimes = laserTimes+tempScore;//enemyAction->_numerical;
        menuLayer->setAngerValue(laserTimes);
        GMAccessData::sharedAccessData()->saveAngerValue(laserTimes);
        
        if(menuLayer->getAnger() == true){
            showPromptLaser();
        }
    }

    /*
     *  记录击中鱼的数目
     */
    GMPublicMethod::sharedPublicMethod()->setHitValue(enemyAction->_id);
    enemyAction->_deathStatus = 2;
    enemyAction->setDeathAnimation();
    
//    ZPLog("测试闪退1");
    /*
     *  显示能量和数字
     */
//    elementLayer->addEnergeBlink(enemyAction->getPosition(),scaleValue);
//    
//    elementLayer->showNumber(tempScore,enemyAction->getPosition());
    
    checkTaskFinshed(enemyAction);
    
    GMAudioPlay::sharedAudioPlay()->playEnergeEffect();
}
//#pragma mark - 结束提示
//结束效果
void GMGameLayer::showOver()
{
    menuLayer->showOverView();
    elementLayer->showOverView();
}

//#pragma mark -       ----     update
void GMGameLayer::brushStrange(float ct)
{
    /****************************************************************************
     *  引导模式时不执行下面方法
     */
    if(getPauseStatus() == true) {
        return;
    }
    if( gameMode != Boot_Mode)
    {
        countbrushSTimes = 0;
        //随即刷怪
        GMSkill skilltype = GMPublicMethod::sharedPublicMethod()->getSkillType();
        if (skilltype == SKILL_NONE || skilltype == SKILL_BLOOD) {
            randEnemy();
        }
    }
}

void GMGameLayer::checkUpadte(float t)
{
    if(getPauseStatus() == true) {
        return;
    }
    /****************************************************************************
     *  顺时针计时
     */
    if (countTime == startBrushSTime && (_isExistboss == 0 || _isExistboss == 2)){
        this->schedule(schedule_selector(GMGameLayer::brushStrange), brushSTimes);
    }
    countTime ++;
    
    if(giftTime>=0 && gameMode != Boot_Mode && billingModel!= B_Free && billingModel != B_91_IOS){
        elementLayer->setGiftTime(giftTime);
        giftTime--;
    }
    /**************************************************************************
     *  检测 固定刷怪
     */
    checkFixedBrushStrange(countTime);
    
    /**************************************************************************
     *  引导模式
     */
    if (gameMode == Boot_Mode) {
        int tempEnemyCount = allEnemyArray->count();
        bootModeLayer->showBootModeStory(countTime,tempEnemyCount);
        if (countTime == 12) {
            menuLayer->setMinusAndPlusEnabled(true);
        }
    }
    
    /****************************************************************************
     *  剧情模式才开始倒计时
     */
    if (gameMode == Story_Mode || gameMode == Endless_Mode) {
        if (countCardTime>0 && _isExistboss!=1) {
            countCardTime--;
            menuLayer->setCheckpointsTimeValue(countCardTime);
            if (countCardTime==5) {
                menuLayer->setCountdownAnimation();
                GMAudioPlay::sharedAudioPlay()->playOtherEffect(Audio_Over,true);
            }
            else if(countCardTime==0){
                menuLayer->setStopCountdownAnimation();
                GMAudioPlay::sharedAudioPlay()->stopMyAllEffects();
                if(gameMode == Story_Mode){
                    isAndroidBack = true;
                    showOver();
                    return;
                }
                else if (gameMode == Endless_Mode) {
                    countTotalTime = countTotalTime+countTime;
                    unscheduleGame();
                    GMCheckpoints *checkpoints = checkpointsList->getCheckpoint(0);
                    
                    if ((checkpoints && m_nCurrentScore < checkpoints->_target_score)||(menuLayer->getLifeValue()<=0)) {
                        setReadNewFileData(3);
                    }
                    else{
                        setReadNewFileData(1);
                    }
                    pauseAllAction(true);
                    return;
                }
            }
        }
        /****************************************************************************
         *  出现 boss 条件
         */
        if (_isExistboss == 1 && countTime == startBrushSTime) {
            if (currentLevel%10 == 5) {
                initBossLayer();
                int tempLevel = currentLevel/10;
                if(tempLevel == 1){
                    initBossOctopus();
                }
                else if(tempLevel == 2){
                    initStarfishKing();
                }
                else if(tempLevel == 3){
                    initBoss1();
                    elementLayer->initPetrifactionFile();
                }
                else if(tempLevel == 4){
                    initBossPoseidon(0);
                }
                elementLayer->initBoss1BulletExplosionEffect();
                elementLayer->initBossbloodFile();
                elementLayer->showBoosBlood();
            }
        }
    }
    
    menuLayer->showBloodb();
    /***************************************************************************
     *  显示任务
     */    
    if ( gameMode != Boot_Mode && task && countTime < taskShowTime + 6) {
        if (countTime == taskShowTime) { //
            menuLayer->showTaskScaleAnimation();
        }
        else if (countTime == taskShowTime+5 && menuLayer->isShowTaskBox == false){
            taskTimes = task->_time;
            menuLayer->showTaskBox(task->_strange_id, task->_num);
        }
    }
    //任务框
    if (menuLayer->isShowTaskBox) {
        taskTimes--;
        menuLayer->setTaskTime(taskTimes);
        checkTaskFinshed(NULL);
    }
    
    
    if (critSkill == SKILL_Crit) {
        countCritTime++;
        if (countCritTime == 10) {
            critSkill = SKILL_NONE;
            countCritTime = 0;
            elementLayer->removeBaoji019Sprite();
        }
    }
    
    /**************************************************************************/
    //当能量小于200时开始送能量
    if (m_nTotalMoney < 200 ) {
        energyTime--;
        if (energyTime<=0) {
            energyTime = EnergyTime;
            setTotalMoney(10);
            GMAccessData::sharedAccessData()->saveGoldCoinsTime(GMPublicMethod::getTime());
        }
        menuLayer->setEnergyTime(energyTime);
    }
    
    /****************************************************************************
     *  
     */
    if(isFrozen){
        countFrozenTime++;
        if (countFrozenTime >= 5) {
            countFrozenTime = 5;
        }
    }
    
    GMEnemyAction *enemyAction;
    CCObject *fObject = NULL;
    CCARRAY_FOREACH(allEnemyArray, fObject) {
        enemyAction = (GMEnemyAction*)fObject;
        float tempW = Get_Box(enemyAction).size.width/2;
        CCRect rect = CCRect(tempW,200*Scale_X,WINSIZE_W-tempW,WINSIZE_H-tempW);
        enemyAction->_countTime++;
        if (GMPublicMethod::checkRectContainsPoint(rect, enemyAction->getPosition())) {
            enemyAction->_checkTime++;
            if (enemyAction->_checkTime >= 5) {
                enemyAction->_checkTime = 5;
            }
            /*
             *  攻击鱼发射子弹
             */
            if (enemyAction->_bulletId != 0) {
                GMSkill skilltype = GMPublicMethod::sharedPublicMethod()->getSkillType();
                MoveStatus tempMove = GMPublicMethod::sharedPublicMethod()->getMoveStatus();
                if (enemyAction->getPosition().y > 50  && (skilltype != SKILL_PAYS && skilltype != SKILL_ICE) &&
                    tempMove != P_Status ) {
                    enemyAction->setAttackTime(1);
                    if (enemyAction->getAttackTime() == enemyAction->_bullet_firing_frequency && enemyAction->_isCatch == false) {
                        //                    enemyAction->stopCurveAtion();
                        enemyAction->setAttackAngle();
                        enemyAction->setAttackAnimation("c", this, callfuncN_selector(GMGameLayer::addFishBullet));
                    }
                }
            }
        }
    }
    
    /*
     *  boss 存在时执行
     */
    if (bossLayer) {
        GMBoss1Action * boss1 = (GMBoss1Action*)bossLayer->getChildByTag(BOSS_TAG1);
        if (boss1) {
            if (bossLayer->getChildren()->count()>0){
                boss1->_attackTime++;
                if (boss1->_attackTime == 5) {
                    boss1->_attackTime = 0;
                    boss1->shootBossBullet();
                }
            }
            if (elementLayer->getPetrifaction()) {
                elementLayer->countPetrifactionTime++;
                if (elementLayer->countPetrifactionTime == 2) {
                    elementLayer->showPetrifactionEffect2();
                }
            }
        }
         // 章鱼 发射子弹
        GMBossOctopus *bossOctopus = (GMBossOctopus*)bossLayer->getChildByTag(BOSS_TAG2);
        if (bossOctopus) {
            bossOctopus->setCountShootBulletTime();
        }
        // 海星星 
        GMBossStarfishKing *starfishKing = (GMBossStarfishKing*)bossLayer->getChildByTag(BOSS_TAG3);
        if (starfishKing) {
            starfishKing->setRunTime(allEnemyArray->count());
        }
        //婆塞冬
        GMBossPoseidon *bossPoseidon = (GMBossPoseidon*)bossLayer->getChildByTag(BOSS_TAG4);
        if (bossPoseidon) {
            bossPoseidon->updata();
        }
    }
    
    if (isCheckBatter) {
        checkBatterTimes++;
        if (checkBatterTimes == 2 ) {
            isCheckBatter = false;
        }
    }
    /*
     *  奖励时间
     */
    elementLayer->countRewaradTime();
    
    elementLayer->setCountSillTime();
    /*
     *  成就
     */
    achievementPrompt->showAchievementPromptViewTime();
    
    
    if(m_pShootBullet && m_pShootBullet->count() >= 10){
        achievementPrompt->showhitFishPrompt(103);
        m_pShootBullet->removeAllObjects();
        m_pShootBullet->release();
        m_pShootBullet = NULL;
    }
    /***************************************************************************
     *  检测 胜利失败
     */
    checkWinOrFail();
}

/*
 * 子弹与鱼的碰撞
 */
void GMGameLayer::checkAllBullet(){
    
    CCObject *bObject = NULL;
    CCObject *bObject1 = NULL;
    GMBullet *tempBullet;
    GMBullet *tempBullet1 = NULL;
//    GMBullet *laserBullet = NULL;
    CCARRAY_FOREACH(allBulletArray,bObject) {
        tempBullet = (GMBullet*)bObject;
        int retainCount = tempBullet->retainCount();
        if (retainCount <= 0) {
            continue;
        }
        //检测炮台子弹是否在屏幕了
        CCRect bulletRect = Get_Box(tempBullet);
        CCRect bulletRect1 = CCRect(-Get_H(bulletRect)/2,-Get_H(bulletRect)/2,WINSIZE_W+Get_H(bulletRect)/2,WINSIZE_H+Get_H(bulletRect)/2);
        if(GMPublicMethod::checkRectContainsPoint(bulletRect1, tempBullet->getPosition())) {

        }
        else {
            automaticallyRemovedBullet(tempBullet);
            continue;
        }
        //鱼的子弹与炮台子弹的检测
        CCARRAY_FOREACH(allEnemyBulletArray, bObject1){
            tempBullet1 = (GMBullet*)bObject1;
            retainCount = tempBullet1->retainCount();
            if (retainCount <= 0) {
                continue;
            }
            if (tempBullet == NULL) {
                break;
            }
            
            if (GMPublicMethod::checkRectContainsPoint(tempBullet1->boundingBox(), tempBullet->getPosition())){
                addNet(tempBullet->getPosition(),tempBullet->getTag());
                removeBullet(tempBullet);
                tempBullet = NULL;
                
                GMAudioPlay::sharedAudioPlay()->playOtherEffect(Audio_Attack3,false);
                break;
            }
        }
        
        /*
         *  子弹与boss 的碰撞
         */
        if (bossLayer && tempBullet) {
            // 美杜莎
            float tempValue = GMPublicMethod::getChooseMagnificationModel();
            GMBoss1Action * boss1 = (GMBoss1Action*)bossLayer->getChildByTag(BOSS_TAG1);
            if (boss1) {
                if (bossLayer->getChildren()->count()>0) {
                    //子弹与boss 的碰撞
                    CCRect bossRect = CCRect(WINSIZE_W/2-308/2*Scale_X,WINSIZE_H-125*Scale_X,308*Scale_X,125*Scale_X);
                    if (GMPublicMethod::checkRectContainsPoint(bossRect,tempBullet->getPosition())) {
                        addNet(tempBullet->getPosition(),tempBullet->getTag());
                        
                        removeBullet(tempBullet);
                        tempBullet = NULL;
                        /*
                         * 倍率系统
                         */
                        boss1->setBossHurtEffect();
                        float tempHurt = boss1->_shells_affect_rates*tempValue*bulletGrade;
                        elementLayer->setBossBloodValue(tempHurt);
                        boss1->checkLife();
                        boss1->_countLife = boss1->_countLife - tempHurt;
/*****************************************************************************/
                        //正版验证
                        if(billingModel == B_TengXunBilling || billingModel == B_91 ||billingModel == B_91_IOS || billingModel == B_91_Android || billingModel == B_Unicom_Android){
                            int tempStatus = GMAccessData::sharedAccessData()->getGenuineValidationStatus();
                            ZPLog("正版验证 %d",tempStatus);
                            if(boss1->_countLife <= 30.0f && tempStatus == 0){
                                GMAccessData::sharedAccessData()->saveRoleDeathStatus(1);
                                addBilling(1,0);
                            }
                        }
/*****************************************************************************/
                        removeBoss1();
                        break;
                    }
                }
            }
            // 章鱼
            GMBossOctopus *bossOctopus = (GMBossOctopus*)bossLayer->getChildByTag(BOSS_TAG2);
            if (bossOctopus) {
                float collisionW = 20.0*Scale_X;
                CCPoint collisionP = tempBullet->getPosition();
                for (int i = 0; i < 5; i++) {
                    bool isCollision = bossOctopus->checkCollision(collisionW,collisionP, 1, 0.5,i);
                    if (isCollision) {
                        addNet(tempBullet->getPosition(),tempBullet->getTag());
                        removeBullet(tempBullet);
                        tempBullet = NULL;
                        break;
                    }
                }
            }
            //海星星
            GMBossStarfishKing *starfishKing = (GMBossStarfishKing*)bossLayer->getChildByTag(BOSS_TAG3);
            if (starfishKing) {
                float collisionW = 20.0*Scale_X;
                CCPoint collisionP = tempBullet->getPosition();
                bool isCollision = starfishKing->checkCollision(collisionW,collisionP, 1, 1);
                if (isCollision) {
                    addNet(tempBullet->getPosition(),tempBullet->getTag());
                    removeBullet(tempBullet);
                    tempBullet = NULL;
                    break;
                }
            }
            //波塞冬
            GMBossPoseidon *poseidon = (GMBossPoseidon*)bossLayer->getChildByTag(BOSS_TAG4);
            if(poseidon){
                float collisionW = 20.0*Scale_X;
                CCPoint collisionP = tempBullet->getPosition();
                bool isCollision = poseidon->checkBossCollision(collisionW,collisionP, 1, 1);
                if (isCollision) {
                    addNet(tempBullet->getPosition(),tempBullet->getTag());
                    removeBullet(tempBullet);
                    tempBullet = NULL;
                    break;
                }

            }
        }
    }
    
    //鱼的子弹与炮台子弹的检测
    CCARRAY_FOREACH(allEnemyBulletArray, bObject1){
        tempBullet1 = (GMBullet*)bObject1;
        int retainCount = tempBullet1->retainCount();
        if (retainCount <= 0) {
            continue;
        }
        if (tempBullet1 == NULL) {
            break;
        }
        GMSkill skilltype = GMPublicMethod::sharedPublicMethod()->getSkillType();
        if (skilltype == SKILL_PAYS) {
            tempBullet1->setRotationAndMove();
            continue;
        }
        else{
            /*
             *  鱼和boss子弹 与 炮台的碰撞
             */
            CCRect rect = CCRect(WINSIZE_W/2-80*Scale_X, 0, 80*Scale_X*2, 38*Scale_X);
            if (GMPublicMethod::checkRectContainsPoint(rect,tempBullet1->getPosition())) {
                ZPLog("子弹伤害值 ：%d",tempBullet1->_hurt_Value);
                menuLayer->setLifeValue(-tempBullet1->_hurt_Value);
                fishBulletMoveAfter(tempBullet1);
                tempBullet1 = NULL;
                
                if (menuLayer->getLifeValue()<50) {
                    elementLayer->setRedlightningEffect();
                }
            }
        }
    }
}

void GMGameLayer::logicProcessing(GMEnemyAction *enemyAction)
{
    GMBullet *tempBullet;
//    GMNet *net;
    CCObject *bObject = NULL;
//    CCObject *nObject = NULL;
    
//    if (enemyAction->_isCatch == false)
    {
        GMSkill skilltype = GMPublicMethod::sharedPublicMethod()->getSkillType();
        if (skilltype == SKILL_PAYS) {
            enemyAction->setRotationAndMove(this,callfuncN_selector(GMGameLayer::removeEnemyFromBatchNode));
            return;
        }
        else if(skilltype == SKILL_ICE){ // 冰冻
            if (enemyAction->getFrozen() == false) {
                enemyAction->stopMoveAction();
                enemyAction->pauseCurveAtion();
            }
        }
        /*
         *  冰河世纪解除
         */
        if (countFrozenTime >= 5 && isFrozen && enemyAction->getFrozen()) {
            enemyAction->continueMoveAction();
            enemyAction->resumeCurveAtion();
        }
        //普通子弹
        CCARRAY_FOREACH(allBulletArray,bObject) {
            tempBullet = (GMBullet*)bObject;
            //子弹与鱼的碰撞
            if (tempBullet) {
                float collisionW = tempBullet->getContentSize().width;
                CCPoint collisionP = tempBullet->getPosition();
                bool collision = enemyAction->checkCollision(collisionW,collisionP,0.4,0.4);
                if (collision){
                    CCPoint tempPoint = tempBullet->getPosition();
                    addNet(tempPoint,tempBullet->getTag());
                    removeBullet(tempBullet);
                    tempBullet = NULL;
                    bObject = NULL;
                    GMAudioPlay::sharedAudioPlay()->playOtherEffect(Audio_Attack3,false);
                    break;
                }
            }
        }
    }
}

void GMGameLayer::update(float t){
	
	/*if (GetAsyncKeyState(VK_LEFT) & 0x8000 ? 1 : 0) {
		CCLabelTTF* label1 = (CCLabelTTF*)getChildByTag(999012);
		label1->setString("key down left");
	}
	else if (GetAsyncKeyState(VK_RIGHT) & 0x8000 ? 1 : 0) {
		CCLabelTTF* label1 = (CCLabelTTF*)getChildByTag(999012);
		label1->setString("key down right");
	}
	else {
		CCLabelTTF* label1 = (CCLabelTTF*)getChildByTag(999012);
		label1->setString("Hello world~~");
	}*/
	//CCKeyp
	this->fireTimeCount += 1;
	if (this->shootting && this->fireTimeCount >= 4) {
		this->fireTimeCount = 0;
		fireOn = 1;
		transformCannon(this->touchLocation);
	}

    if(getPauseStatus() == true) {
        return;
    }

    GMEnemyAction *enemyAction;
    CCObject *pObject = NULL;
    // 在 fishSheet 取出 Enemy
    //普通鱼的检测
    GMSkill skilltype = GMPublicMethod::sharedPublicMethod()->getSkillType();
    
    if (skilltype == SKILL_PAYS) {
        skillElementLayer->showPayTittle(15.0);
    }
    CCARRAY_FOREACH(allEnemyArray, pObject) {
        enemyAction = (GMEnemyAction*)pObject;
        if (enemyAction) {
            int retainCount = enemyAction->retainCount();
            if (retainCount>0) {
                if (enemyAction->_isCatch == false) {
                    if (enemyAction->_id != 16) {
                        logicProcessing(enemyAction);
                    }
                    retainCount = enemyAction->retainCount();
                    if (retainCount > 0 && skilltype != SKILL_ICE && enemyAction->getFrozen()==false) {
                        EnemyRouteStatus tempStatus = enemyAction->getRouteStatus();
                        if ((tempStatus == R_Rand || tempStatus == R_NotMoveOut) && enemyAction->_isCatch == false) {
                            if (enemyAction->_enemyStatus != S_Attack) {
                                enemyAction->setUnRemoveTheScreen();
                                if ( enemyAction->_countTime >= enemyAction->_time ) {
                                    enemyAction->_countTime = 0;
                                    enemyAction->randRotationMove();
                                    if (enemyAction->_checkTime >= 1) {
                                        enemyAction->checkIsRemove();
                                    }
                                }
                            }
                        }
                        else if(enemyAction->getRouteStatus() != R_Rand){
                            
                        }
                    }
                }
            }
        }
    }

    /*
     *  子弹
     */
    checkAllBullet();
    
    /*
     *  冰河世纪技能
     */
    elementLayer->iceMoveAction();
    
    elementLayer->baoJiTitleMove();
    
    if (bossLayer) {
        GMSkill skilltype = GMPublicMethod::sharedPublicMethod()->getSkillType();
        GMBossOctopus *bossOctopus = (GMBossOctopus*)bossLayer->getChildByTag(BOSS_TAG2);
        if (bossOctopus) {
            if(skilltype == SKILL_ICE){
                if (bossOctopus->getFrozen() == false) {
                    bossOctopus->setFrozen(true);
                    bossOctopus->setAllFrozen(true);
                    bossOctopus->unscheduleAllSelectors();
                }
            }
            else {
                bossOctopus->setOctopusMove();
            }
            if (countFrozenTime >= 5 && isFrozen && bossOctopus->getFrozen()) {
                bossOctopus->setFrozen(false);
                bossOctopus->setAllFrozen(false);
                bossOctopus->resumeSchedulerAndActions();
            }
        }
        GMBossStarfishKing *starfishKing = (GMBossStarfishKing*)bossLayer->getChildByTag(BOSS_TAG3);
        if (starfishKing) {
            starfishKing->setStarfishKingMove();
        }
    }
//    struct cc_timeval now;
//    CCTime::gettimeofdayCocos2d(&now, NULL);
//    struct tm * tm;
//    tm = localtime(&now.tv_sec);
//    int year = tm->tm_year + 1900;
//    int month = tm->tm_mon + 1;
//    int day = tm->tm_mday;
//    int hour = tm->tm_hour;
//    int min = tm->tm_min;
//    int sec = tm->tm_sec;
//    ZPLog("(%ld== %ld)%d-%d-%d-%d-%d-%d",now.tv_sec,now.tv_usec,year,month,day,hour,min,sec);
}

void GMGameLayer::updateCheckNetAndFish(float t)
{
    if(getPauseStatus() == true) {
        return;
    }
    
    GMEnemyAction *tempEnemy = NULL;
    CCObject *pObject = NULL;
    CCObject *bObject = NULL;
    CCObject *bObject1 = NULL;
    CCObject *nObject = NULL;
    GMBullet *tempFishBullet = NULL;
    GMNet *tempNet = NULL;
    /*
     *  激光
     */
//    ZPLog("%1 ld",millisecondNow());
    m_nMagnification = GMPublicMethod::getChooseMagnificationModel();
    bObject = NULL;
    if (_isLaser && m_pLaserBullet) {
        ZPLog("2222222222222");
        
        CCARRAY_FOREACH(allEnemyArray, pObject) {
            tempEnemy = (GMEnemyAction*)pObject;
            if (tempEnemy) {
                int retainCount = tempEnemy->retainCount();
                if (retainCount>0) {
                    if (tempEnemy ->_isCatch == false) {
                        int fishTag = tempEnemy->getTag();
                        if (m_pLaserBullet->getNotesFishTag(fishTag)) {
                            continue;
                        }
                        float collisionW = tempEnemy->getContentSize().width;
                        bool collision = false;
                        if (tempEnemy->_id == 10) {
                            collision = m_pLaserBullet->checkCollision1(collisionW,tempEnemy->getPosition(),tempEnemy->getRotation());
                            if (collision) {
                                if (randRates(getRate(tempEnemy))) {
                                    tempEnemy->_isCatch = true;
                                    laserTotalNum = laserTotalNum+tempEnemy->_numerical*m_nMagnification;
                                    hitEffect(tempEnemy);
                                    tempEnemy->setHurtEffect();
                                    tempEnemy = NULL;
                                    break;
                                }
                                else {
                                    tempEnemy->setHurtEffect();
                                    m_pLaserBullet->setNotesFishTag(fishTag);
                                }
                            }
                        }
                        else {
                            collision = m_pLaserBullet->checkCollision(collisionW,tempEnemy->getPosition(),1,0.5);
                            if (collision){
                                if(randRates(getRate(tempEnemy))){
                                    tempEnemy->_isCatch = true;
                                    laserTotalNum = laserTotalNum+tempEnemy->_numerical*m_nMagnification;
                                    hitEffect(tempEnemy);
                                    tempEnemy = NULL;
                                    break;
                                }
                                else {
                                    tempEnemy->setHurtEffect();
                                    m_pLaserBullet->setNotesFishTag(fishTag);
                                    isCheckBatter = false;
                                }
                            }
                        }
                    }
                }
            }
        }
        
        CCARRAY_FOREACH(allEnemyBulletArray, bObject1){
            tempFishBullet = (GMBullet*)bObject1;
            if (tempFishBullet == NULL) {
                break;
            }
            int retainCount = tempFishBullet->retainCount();
            if (retainCount <= 0) {
                continue;
            }
            
            int enemyBulletTag = tempFishBullet->getTag();
            float collisionW = tempFishBullet->getContentSize().width;
            bool collision = m_pLaserBullet->checkCollision(collisionW,tempFishBullet->getPosition(),1,1);
            bool isExit = m_pLaserBullet->getNotesBulletTag(enemyBulletTag);
            
            if(collision && isExit == false) {
                m_pLaserBullet->setNotesBulletTag(enemyBulletTag);
                
                float temp2 = GMPublicMethod::getChooseMagnificationModel1();
                tempFishBullet->_life_Value = tempFishBullet->_life_Value - tempFishBullet->_rates_Value*temp2;
                
                if (tempFishBullet->_life_Value <= 0) {
                    GMAudioPlay::sharedAudioPlay()->playAttackEffect(Audio_attack2);
                    elementLayer->bulletExplosionAnimation(14,tempFishBullet->getPosition(),scaleValue);
                    tempFishBullet->cleanup();
                    allEnemyBulletArray->removeObject(tempFishBullet);
                    fishBulletLayer->removeChild(tempFishBullet, true);
                }
                break;
            }
        }
        
        //boss
        if (bossLayer) {
            float tempValue = GMPublicMethod::getChooseMagnificationModel();
            
            GMBoss1Action * boss1 = (GMBoss1Action*)bossLayer->getChildByTag(BOSS_TAG1);
            if (boss1) {
                if (bossLayer->getChildren()->count()>0) {
                    //子弹与boss 的碰撞
                    CCRect bossRect = CCRect(WINSIZE_W/2-308/2*Scale_X,WINSIZE_H-125*Scale_X,308*Scale_X,125*Scale_X);
                    for (int i = 0;  i < 20; i++) {
                        float tempW = m_pLaserBullet->getContentSize().width*0.5*i;
                        CCPoint p1 = m_pLaserBullet->getPosition();
                        float angle = m_pLaserBullet->getRotation();
                        float a = DADIANS_TO_DEGREES1(angle);
                        float tempx = sinf(a)*tempW;
                        float tempy = cosf(a)*tempW;
                        float tempX = p1.x;
                        float tempY = p1.y;
                        //1
                        CCPoint point = ccp(tempX+tempx,tempY+tempy);
                        if (GMPublicMethod::checkRectContainsPoint(bossRect,point)) {
                            // 倍率系统
                            boss1->setBossHurtEffect();
                            float tempHurt = boss1->_shells_affect_rates*tempValue*bulletGrade;
                            elementLayer->setBossBloodValue(tempHurt);
                            boss1->checkLife();
                            boss1->_countLife = boss1->_countLife - tempHurt;
                            removeBoss1();
                            break;
                        }

                    }
                }
            }

            
            bool isHit = m_pLaserBullet->getHitBossValue();
            GMBossOctopus *bossOctopus = (GMBossOctopus*)bossLayer->getChildByTag(BOSS_TAG2);
            if (bossOctopus && isHit == false) {
                for (int i = 0; i < 5; i++) {
                    float collisionW = bossOctopus->getSubBossWidth(i);
                    bool collision = m_pLaserBullet->checkCollision(collisionW,bossOctopus->getBossPoint(i),1,0.5);
                    if(collision){
                        m_pLaserBullet->setHitBossValue(true);
                        float temp2 = GMPublicMethod::getChooseMagnificationModel1();
                        float tempHurt = bossOctopus->getHurt(temp2*tempValue);
                        if (bossOctopus->getHurtBOLL()) {
                            elementLayer->setBossBloodValue(tempHurt);
                        }
                        bossOctopus->setHurt(tempHurt);
                        bool isOctopusDeath = bossOctopus->setAllValue(tempHurt,i);
                        if (isOctopusDeath) {
                            setMoneyAndSocre(200);
                            
                            this->scheduleOnce(schedule_selector(GMGameLayer::removeAllBoss), 2);
                        }
                    }
                }
            }
            //海星星
            GMBossStarfishKing *starfishKing = (GMBossStarfishKing*)bossLayer->getChildByTag(BOSS_TAG3);
            if (starfishKing) {
                bool isHit = m_pLaserBullet->getHitBossValue();
                float collisionW = starfishKing->getContentSize().width;
                bool collision = m_pLaserBullet->checkCollision(collisionW,starfishKing->getPosition(),1,0.5);
                if (collision && isHit == false) {
                    m_pLaserBullet->setHitBossValue(true);
                    
                    starfishKing->setHurtEffect();
                    float tempValue = GMPublicMethod::getChooseMagnificationModel();
                    float temp2 = GMPublicMethod::getChooseMagnificationModel1();
                    tempValue = - starfishKing->_shells_affect_rates*tempValue*temp2;
                    elementLayer->setBossBloodValue(-tempValue);
                    starfishKing->setStarfishKingLifeValue(tempValue);
                    starfishKing->setDeathEffcet();
                }
            }
            //波塞冬
            GMBossPoseidon *poseidon = (GMBossPoseidon*)bossLayer->getChildByTag(BOSS_TAG4);
            if(poseidon){
                bool isHit = m_pLaserBullet->getHitBossValue();
                float collisionW = 200/2*Scale_X;;
                bool isCollision = m_pLaserBullet->checkCollision(collisionW,poseidon->getBossPoseidonPoint(), 1, 1);
                if (isCollision && isHit == false) {
                    m_pLaserBullet->setHitBossValue(true);
                    poseidon->setHurtEffect();
                    float tempValue = GMPublicMethod::getChooseMagnificationModel();
                    float temp2 = GMPublicMethod::getChooseMagnificationModel1();
                    tempValue = -poseidon->getShellAffectRates()*tempValue*temp2;
                    elementLayer->setBossBloodValue(-tempValue);
                    poseidon->setBossLife(tempValue);
                }
            }
        }
        
//        ZPLog("2 %ld",millisecondNow());
    }
    
    /*
     *  鱼 与 网 的碰撞
     */
    tempFishBullet = NULL;
    tempEnemy = NULL;
    CCARRAY_FOREACH(allNetArray,nObject) {
        tempNet = (GMNet*)nObject;
        float collisionW = tempNet->getNetWidth();//tempNet->getNetBox().size.width-10;
        CCPoint collisionP = tempNet->getPoint();
        
        CCARRAY_FOREACH(allEnemyArray, pObject) {
            tempEnemy = (GMEnemyAction*)pObject;
            if (tempEnemy) {
                if (tempEnemy->_isCatch == false) {
                    int tag = tempEnemy->getTag();
                    if (tempNet->getNotesFishTag(tag)) {
                        continue;
                    }
                    bool collision = tempEnemy->checkCollision(collisionW,collisionP,0.4,0.5);
                    if (collision) {
                        if (gameMode == Boot_Mode && tempEnemy->_id == 15 && bootModeLayer->getStoryStatus() == 10) {
                            tempEnemy->_isCatch = true;
                            isHitIDFish15 = true;
                            hitEffect(tempEnemy);
                            bootModeLayer->isHitFishId15 = true;
                            break;
                        }
                        else if ( randRates(getRate(tempEnemy)) ){
                            if (gameMode == Boot_Mode && tempEnemy->_id == 15) { }
                            else {
                                tempEnemy->_isCatch = true;
                                tempNet->countHitNum++;
                                if (tempEnemy->_id == 15) {
                                    isHitIDFish15 = true;
                                }
                                hitEffect(tempEnemy);
                                break;
                            }
                        }
                        else {
                            tempEnemy->setAccelerate();
                            tempEnemy->setHurtEffect();
                            tempNet->setNotesFishTag(tag);
                        }
                    }
                }
            }
        }
        
        //鱼的子弹 与 网 的碰撞
        bObject = NULL;
        CCARRAY_FOREACH(allEnemyBulletArray, bObject){
            tempFishBullet = (GMBullet*)bObject;
           
            if (!tempFishBullet)
                continue;
            
            int bulletTag = tempFishBullet->getTag();
            if (tempNet->getNotesBulletTag(bulletTag))
                continue;
            
            bool collision = tempFishBullet->checkCollision(collisionW,collisionP,1,0.5);
            if (collision) {
                tempNet->setNotesBulletTag(bulletTag);
                /*
                 * 倍率系统
                 */
                float tempValue = GMPublicMethod::getChooseMagnificationModel();
                tempFishBullet->_life_Value = tempFishBullet->_life_Value - tempFishBullet->_rates_Value*tempValue*bulletGrade;
                ZPLog("子弹当前生命 %f",tempFishBullet->_life_Value);
                if (tempFishBullet->_life_Value <= 0) {
                    GMAudioPlay::sharedAudioPlay()->playAttackEffect(Audio_attack2);
                    elementLayer->bulletExplosionAnimation(14/*bullet->_id*/,tempFishBullet->getPosition(),scaleValue);
                    tempFishBullet->cleanup();
                    allEnemyBulletArray->removeObject(tempFishBullet);
                    fishBulletLayer->removeChild(tempFishBullet, true);
                    tempFishBullet = NULL;
                }
                bObject = NULL;
                break;
            }
        }
        
        if (bossLayer && tempNet) {
            // 章鱼
            float tempValue = GMPublicMethod::getChooseMagnificationModel();
            bool isHit = tempNet->getHitBossValue();
            GMBossOctopus *bossOctopus = (GMBossOctopus*)bossLayer->getChildByTag(BOSS_TAG2);
            if (bossOctopus && isHit == false) {
                for (int i = 0; i < 5; i++) {
                    bool isCollision = bossOctopus->checkCollision(collisionW,collisionP, 1, 0.5,i);
                    if (isCollision) {
                        tempNet->setHitBossValue(true);
                        float tempHurt = bossOctopus->getHurt(bulletGrade*tempValue);
                        if (bossOctopus->getHurtBOLL()) {
                            elementLayer->setBossBloodValue(tempHurt);
                        }
                        bossOctopus->setHurt(tempHurt);
                        bool isOctopusDeath = bossOctopus->setAllValue(tempHurt);
                        if (isOctopusDeath) {
                            setMoneyAndSocre(200);
                            this->scheduleOnce(schedule_selector(GMGameLayer::removeAllBoss), 2);
                        }
                    }
                }
                
            }
            //海星星
            GMBossStarfishKing *starfishKing = (GMBossStarfishKing*)bossLayer->getChildByTag(BOSS_TAG3);
            if (starfishKing) {
                bool isHit = tempNet->getHitBossValue();
                bool isCollision = starfishKing->checkCollision(collisionW,collisionP, 0.5, 0.5);
                if (isCollision && isHit == false) {
                    tempNet->setHitBossValue(true);
                    starfishKing->setHurtEffect();
                    float tempValue = GMPublicMethod::getChooseMagnificationModel();
                    tempValue = - starfishKing->_shells_affect_rates*tempValue*bulletGrade;
                    elementLayer->setBossBloodValue(-tempValue);
                    starfishKing->setStarfishKingLifeValue(tempValue);
                    
                    starfishKing->setDeathEffcet();
                    break;
                }
            }
            //波塞冬
            GMBossPoseidon *poseidon = (GMBossPoseidon*)bossLayer->getChildByTag(BOSS_TAG4);
            if(poseidon){
                bool isHit = tempNet->getHitBossValue();
                bool isCollision = poseidon->checkBossCollision(collisionW*0.4,collisionP, 1, 1);
                if (isCollision && isHit == false) {
                    tempNet->setHitBossValue(true);
                    poseidon->setHurtEffect();
                    float tempValue = GMPublicMethod::getChooseMagnificationModel();
                    tempValue = -poseidon->getShellAffectRates()*tempValue*bulletGrade;
                    elementLayer->setBossBloodValue(-tempValue);
                    poseidon->setBossLife(tempValue);
                    break;
                }
            }
        }
    }
    
//    ZPLog("3 %ld",millisecondNow());
}


//#pragma mark- pauseAllAction
void GMGameLayer::setCurveEnemyAction(bool stop)
{
    GMEnemyAction *enemyAction;
    CCObject *pObject = NULL;
    CCARRAY_FOREACH(allEnemyArray, pObject)
    {
        enemyAction = (GMEnemyAction*)pObject;
        if (enemyAction) {
            if (stop) {
                if(gameMode == Boot_Mode && enemyAction->_id == 15)
                    fish15Point = enemyAction->getPosition();
                if (enemyAction->_deathStatus != 2) {
                    enemyAction->pauseCurveAtion();
                }
            }
            else {
                GMSkill skilltype = GMPublicMethod::sharedPublicMethod()->getSkillType();
                if(skilltype != SKILL_ICE && enemyAction->getFrozen() == false){
                    enemyAction->resumeCurveAtion();
                }
            }
        }
    }
}

void GMGameLayer::setBulletEnemyAction(bool stop)
{
    GMBullet *bullet;
    CCObject *pObject = NULL;
    if (allEnemyBulletArray) {
        CCARRAY_FOREACH(allEnemyBulletArray, pObject)
        {
            bullet = (GMBullet*)pObject;
            if (bullet) {
                if (stop) {
                    bullet->pauseSchedulerAndActions();
                }
                else {
                    bullet->resumeSchedulerAndActions();
                }
            }
        }
    }
    
    if(allBulletArray){
        CCARRAY_FOREACH(allBulletArray,pObject) {
            bullet = (GMBullet*)pObject;
            if (bullet) {
                if (stop) {
                    bullet->pauseSchedulerAndActions();
                }
                else {
                    bullet->resumeSchedulerAndActions();
                }
            }
        }
    }
}

void GMGameLayer::pauseAllAction(bool pause)
{
    if (pause) {
        GMAccessData::sharedAccessData()->savePauseStatus(1);
        GMPublicMethod::sharedPublicMethod()->setMoveStatus(P_Status);
//        this->pauseSchedulerAndActions();
    }
    else {
        GMAccessData::sharedAccessData()->savePauseStatus(0);
        GMPublicMethod::sharedPublicMethod()->setMoveStatus(M_Status);
//        this->resumeSchedulerAndActions();
    }
    if(bossLayer){
        GMBossPoseidon *bossPoseidon = (GMBossPoseidon*)bossLayer->getChildByTag(BOSS_TAG4);
        if(bossPoseidon){
            bossPoseidon->pauseActions(pause);
        }

    }
    setCurveEnemyAction(pause);
    setBulletEnemyAction(pause);
}

//#pragma mark - public action
void GMGameLayer::minusAction()
{
    if(_isLaser==false){
        isAgainTransform = true;
        menuLayer->commonConnon(-1);
        bulletGrade = menuLayer->cannonIndex;
        elementLayer->changeShowNumeber(menuLayer->cannonIndex);
    }
    else if(_isLaser){
        ZPLog("激光不能切换");
    }
}

void GMGameLayer::setMinusAndPlusEnabled(int index)
{
    if (index == 3) {
        menuLayer->setMinusAndPlusEnabled(true);
    }
    else if (index == 6) {
        menuLayer->setSkill1Enabled(true);
    }
    else if(index == 11){
        menuLayer->setSkill2Enabled(true);
    }
}

void GMGameLayer::plusAction(){
    ZPLog("激光不能切换 %d",_isLaser);
    if(_isLaser) {
        ZPLog("激光不能切换 ");
    }
    else if(_isLaser==false){
        ZPLog("激光不能切换 plusAction");
        isAgainTransform = true;
        menuLayer->commonConnon(1);
        bulletGrade = menuLayer->cannonIndex;
        elementLayer->changeShowNumeber(menuLayer->cannonIndex);
    }
}

bool GMGameLayer::getPauseStatus(){
    int pauseStatus = GMAccessData::sharedAccessData()->getPauseStatus();
    if(pauseStatus == 1) {
        return true;
    }
    return false;
}

void GMGameLayer::pauseAction()
{
    GMAccessData::sharedAccessData()->saveGiftCountdown(giftTime);
    if(getPauseStatus() == true) {
        return;
    }
    if(!_isLaser){
        ZPLog("测试暂停界面2");
        GMAudioPlay::sharedAudioPlay()->playButtonEffect();
        
        pauseAllAction(true);
        
        this->pauseSchedulerAndActions();
        
        if(billingModel != B_Telecom){
            CCDirector::sharedDirector()->pause();
        }
        pauseLayer = GMPauseLayer::create();
        if (pauseLayer) {
            pauseLayer->delegateGame = this;
            this->addChild(pauseLayer,Index_Pause,1);
        }
        isAndroidBack = true;
//#if (JNIHELPER_INDEX == JNIHELPER_91_IOS)       
//        PublicCPP::sharedSpriteCPP()->show91NdPause();
//#endif
        
        ZPJNIHelper::setPauseView();
        
    //    GMPublicMethod::sharedPublicMethod()->setGameStatus1(Pause_Status);
//        GMPublicMethod::sharedPublicMethod()->setGameStatus(Pause_Status);
    }
}

void GMGameLayer::continueGame()
{
    ZPLog("continueGame 1");
//    if(billingModel != B_Telecom)
    {
        this->resumeSchedulerAndActions();
    }
    this->removeChild(pauseLayer, true);
    pauseLayer = NULL;
    isAndroidBack = false;
    pauseAllAction(false);
    ZPLog("continueGame 2")
//    GMPublicMethod::sharedPublicMethod()->setGameStatus1(Game_Status);
//    GMPublicMethod::sharedPublicMethod()->setGameStatus(Game_Status);
}

void GMGameLayer::usedSkill1(CCObject *object)
{
    if(getPauseStatus() == true) {
        return;
    }
    int num = GMAccessData::sharedAccessData()->getSkillBloodNum();
    if (menuLayer->getLifeValue() < 100) {
        if(billingModel == B_Free){
            GMAudioPlay::sharedAudioPlay()->playOtherEffect(Audio_Blood,false);
            elementLayer->showBloodEffect(scaleValue);
            menuLayer->setLifeValue(10);
        }
        else {
            GMAudioPlay::sharedAudioPlay()->playOtherEffect(Audio_Button,false);
            if(num > 0 && countSkillTime[0] == 0 ){
                elementLayer->showBloodEffect(scaleValue);
                menuLayer->setLifeValue(100);
                num--;
                menuLayer->setSKillNum1(num);
                GMAccessData::sharedAccessData()->saveSkillBloodNum(num);
                countSkillTime[0] = 1;
                GMAudioPlay::sharedAudioPlay()->playOtherEffect(Audio_Blood,false);
            }
            else if(num <= 0){
                addBilling(3, 0);
            }
        }
    }
    else {
        GMAudioPlay::sharedAudioPlay()->playOtherEffect(Audio_Button,false);
        if(num <= 0){
            addBilling(3, 0);
        }
        ZPLog("满血");
    }
}

void GMGameLayer::removeBloodEffect(){
    countSkillTime[0] = 0;
}

void GMGameLayer::usedSkill2(CCObject *object)
{
    if(getPauseStatus() == true) {
        return;
    }
    GMAudioPlay::sharedAudioPlay()->playButtonEffect();
    if(billingModel == B_Free){
        setSkillValue();
    }
    else {
        int num = GMAccessData::sharedAccessData()->getSkillPaysNum();
        if(num > 0 && countSkillTime[1] == 0){
            setSkillValue();
            num--;
            menuLayer->setSKillNum2(num);
            GMAccessData::sharedAccessData()->saveSkillPaysNum(num);
            countSkillTime[1] = 1;
        }
        else if(num <= 0){
            addBilling(3, 0);
        }
    }
}

void GMGameLayer::setSkillValue(){
    if (gameMode == Boot_Mode) {
        if (bootModeLayer->_status == 4) {
            bootModeLayer->removePrompView();
        }
        if (bootModeLayer->getStoryStatus() == 11) {
            pauseAllAction(false);
            bootModeLayer->curTimes = countTime;
        }
    }
    GMSkill skilltype = GMPublicMethod::sharedPublicMethod()->getSkillType();
    if (skilltype == SKILL_NONE) {
        GMPublicMethod::sharedPublicMethod()->setSkillType(SKILL_PAYS);
        skillElementLayer->showPayskillEffect();
        
        int swirlAmount = GMAccessData::sharedAccessData()->getSwirlAmount();
        swirlAmount++;
        GMAccessData::sharedAccessData()->saveSwirlAmount(swirlAmount);
        
        GMAudioPlay::sharedAudioPlay()->playOtherEffect(Audio_Pays,false);
    }
    countFrozenTime = 0;
    isFrozen = true;

}
void GMGameLayer::removePayskillEffect()
{
    setMoneyAndSocre(countPaysScore);
    if (countPaysScore > 10) {
        elementLayer->setPaysStats(2);
        elementLayer->showRewardEffect(countPaysScore);
    }
    else {
        /*
         *  漩涡次数提示
         */
        achievementPrompt->showSwirlPrompt();
    }
    countPaysScore = 0;
    countSkillTime[1] = 0;
    GMPublicMethod::sharedPublicMethod()->setSkillType(SKILL_NONE);
}

void GMGameLayer::rewaradPayskillEffect()
{
    if (elementLayer->getPaysStats() == 3) {
        achievementPrompt->showhitFishPrompt(101);
    }
    else if (elementLayer->getPaysStats() == 2) {
        achievementPrompt->showSwirlPrompt();
    }
    elementLayer->setPaysStats(0);
    
}

void GMGameLayer::petrifactionEffect()
{
    elementLayer->showPetrifactionEffect();
}

void GMGameLayer::nextAction(int index)
{
    if (bootModeLayer) {
        if(index == 1){
            if (gameMode == Boot_Mode) {
                brushSTimes = 0.8;
                startGame();
            }
        }
        else if(index == 8){
            GMStrange *strange = checkpointsList->getStrangeTable(6);
            addFishArray(strange,R_Curve_Formation);
        }
        else if(index == 10){
            
        }
        else if(index == 11){
            GMStrange *strange = checkpointsList->getStrangeTable(7);
            addFishArray(strange,R_Curve_Formation);
        }
        else if(index == 13){
            int tempStatus = GMAccessData::sharedAccessData()->getRoleDeathStatus();
            if (tempStatus == 1) {
                brushSTimes = 0.8;
                startGame();
            }
            
            initBossLayer();
            initBoss1();
            elementLayer->showBoosBlood();
//            bootModeLayer->curTimes = countTime;
        }
        else if(index == 15){
//            this->cleanup();
//            CCScene *pScene = CCTransitionFade::create(0.0, GMCardLayer::scene(), ccWHITE);
//            CCDirector::sharedDirector()->replaceScene(pScene);
             showOpenCannon();
        }
    }
}

void GMGameLayer::achievementEnerge(int score,CCPoint point)
{
    ZPLog("奖励的分数 %d",score);
    //设置总分数
//    totalMoney = totalMoney+score;
//    menuLayer->setTotalMoneyNum(totalMoney);
    setTotalMoney(score);
    /*
     *  显示能量和数字
     */
    elementLayer->addEnergeBlink(point,scaleValue);
    elementLayer->showNumber(score,point);
}
/*
 *  引导模式出现雅典娜
 */
void GMGameLayer::showBootModeFIshID16()
{
    GMEnemy *enemy = checkpointsList->getEnemy(16-1);
    char fishName[40] = {0};
    sprintf(fishName,"yu%02d%s%03d.png",16,"a",1);
    GMEnemyAction *enemyAction = new GMEnemyAction();
    enemyAction->setInitValue();
    enemyAction->setDelegate(this);
    enemyAction->setRouteStatus(R_Rand);
    enemyAction->initWithSpriteFrameName(fishName);
    enemyAction->setPosition(ccp(WINSIZE_W/2, 0));
    enemyAction->setValue(enemy);
    enemyAction->setTag(++countAllFishTag);
    enemyAction->setEnemyAnimation(true, "a");
    enemyAction->setScale(scaleValue);
//    enemyAction->randRotationAngle();
    enemyAction->randRotationMove();
    allEnemyArray->addObject(enemyAction);
    fishLayer->addChild(enemyAction);
    
    enemyAction->release();
    enemyAction = NULL;
}

bool GMGameLayer::getBootModeCastSkill()
{
    if(gameMode == Boot_Mode && bootModeLayer && bootModeLayer->getClickSkill() == false){
        return true;
    }
    return false;
}
/*
 *  施放技能
 */
void GMGameLayer::setCastSkill(int goodsId)
{
    GMAudioPlay::sharedAudioPlay()->playButtonEffect();
    if (goodsId == 1) {
        critSkill = SKILL_Crit;
        countCritTime = 0;
        elementLayer->showBaoJiEffect();
    }
    else if (goodsId == 2) {
        GMSkill skilltype = GMPublicMethod::sharedPublicMethod()->getSkillType();
        if (skilltype == SKILL_NONE) {
            GMPublicMethod::sharedPublicMethod()->setSkillType(SKILL_BLOOD);
            elementLayer->showBloodEffect(scaleValue);
            
            menuLayer->setLifeValue(10);
        }
    }
    else if (goodsId == 3) {
        GMSkill skilltype = GMPublicMethod::sharedPublicMethod()->getSkillType();
        if (skilltype == SKILL_NONE) {
            GMPublicMethod::sharedPublicMethod()->setSkillType(SKILL_ICE);
            elementLayer->showIceEffect();
            countFrozenTime = 0;
            isFrozen = true;
        }
        
        if (gameMode == Boot_Mode) {
            elementLayer->removeOtherSkill();
        }
    }
    else if (goodsId == 4) {
        GMSkill skilltype = GMPublicMethod::sharedPublicMethod()->getSkillType();
        if (skilltype == SKILL_NONE) {
            GMPublicMethod::sharedPublicMethod()->setSkillType(SKILL_PAYS);
            skillElementLayer->showPayskillEffect();
        }
    }
    
    removeWheelRes();
}

void GMGameLayer::showEnergeDialog()
{
    if (gameMode == Boot_Mode) {
        int _pauseStatus = GMAccessData::sharedAccessData()->getPauseStatus();
        if(_pauseStatus == 1){
            ZPLog("暂停状态为一");
            return;
        }
        bootModeLayer->showDialogueNum();
    }
}

void GMGameLayer::setGiftAtion(){
    int index = GMAccessData::sharedAccessData()->getGiftStatus();
    if(index == 3)
        addBilling(2,index);
    else if(index < 3)
        addBilling(5,index);
}

void GMGameLayer::againAction(){
    
    _billing91Again = true;
    int satatus =  GMAccessData::sharedAccessData()->getGenuineValidationStatus();
    if (/*billingModel!=B_91_IOS &&*/ billingModel!=B_Free && billingModel!=B_Telecom && satatus != 2 ){
        addBilling(1,0);
    }
    else {
        GMAudioPlay::sharedAudioPlay()->stopBGMusic();
        GMAudioPlay::sharedAudioPlay()->stopMyAllEffects();
        GMAudioPlay::sharedAudioPlay()->playButtonEffect();
        
        cleanup();
        unscheduleGame();
        CCScene *pScene = CCTransitionFade::create(0.0, GMMainLayer::scene(), ccWHITE);
        CCDirector::sharedDirector()->replaceScene(pScene);
    }
}

void GMGameLayer::bugEnergyAction(){
     addBilling(2,0);
}

//#pragma mark-  transform
void GMGameLayer::transformCannon(CCPoint location)
{

	char str[128];
	sprintf(str, " into cannon location is x%f,y%f, direction%d, fire%d", this->touchLocation.x, this->touchLocation.y, this->arrowDir, this->fireOn);
	CCLog(str);
    if (!isAgainTransform) {
        return;
    }
    isAgainTransform = false;
    CCPoint shootVector = ccpSub(location, menuLayer->getCannon()->getPosition());
	this->touchLocation = location;
    float shootAngle = ccpToAngle(shootVector);
    float cocosAngle = RADIANS_TO_DEGREES(shootAngle);
    tempVector = shootVector;
    float angle;
    if (cocosAngle<0) {
        angle = -(90+cocosAngle);
    }
    else if (cocosAngle>0){
        angle = 90 - cocosAngle;
    }
    //
//    float curAngle = menuLayer->getCannon()->getRotation();
//    float rotateDiff = cocosAngle - curAngle;
//    //    // More clear way
//    float rotateSpeed = 360; // degrees per second
//    float rotateDuration = fabs(rotateDiff / rotateSpeed);
    menuLayer->setCannonRotation(angle);
//    IOSLog("rotateDuration = %f",rotateDuration);
    CCRotateTo *rotateTo = CCRotateTo::create(0.01,angle);
    CCCallFunc *callfunc = CCCallFunc::create(this, callfunc_selector(GMGameLayer::finishShoot));
    CCFiniteTimeAction* sequence = CCSequence::create(rotateTo,callfunc,NULL);
    ((GMBullet*)menuLayer->getCannon())->runAction(sequence);
    
    elementLayer->setbaojiRotation(angle);
//    firedBullets(shootVector);
}

//#pragma mark -  Boss 区域
//#pragma mark - 美杜莎
void GMGameLayer::initBossLayer()
{
    bossLayer = CCLayer::create();
    bossLayer->setPosition(ccp(0, 0));
    this->addChild(bossLayer,Enemy_Layer);
    
    GMPublicMethod::sharedPublicMethod()->setGameStatus(Boss_Status);
    
//    if (gameMode != Boot_Mode) {
//        GMPublicMethod::sharedPublicMethod()->setGameStatus1(Boss_Status);
//    }
    GMAudioPlay::sharedAudioPlay()->playBGMusic(Audio_BG_Boss);
}

void GMGameLayer::initBoss1()
{
    GMBoss1Action *boss1 = GMBoss1Action::create();
    boss1->setPosition(ccp(WINSIZE_W/2, WINSIZE_H+20));
    SetScale2(boss1, Scale_X);
    bossLayer->addChild(boss1,Enemy_Layer,BOSS_TAG1);
    boss1->delegate = this;
    CCMoveTo *moveTo = CCMoveTo::create(1, ccp(WINSIZE_W/2, WINSIZE_H-80*Scale_X));
    boss1->runAction(moveTo);
}

void GMGameLayer::removeBoss1()
{
    if (bossLayer) {
        GMBoss1Action *boss1 = (GMBoss1Action*)bossLayer->getChildByTag(BOSS_TAG1);
        if (boss1) {
            if (boss1->_countLife <= 0 && boss1->getDeathStatus() == false) {
                boss1->setDeathStatus(true);
                GMAudioPlay::sharedAudioPlay()->playOtherEffect(Audio_Boss1Death,false);
                GMAudioPlay::sharedAudioPlay()->playBGMusic(Audio_Gmae1);
                
                CCMoveTo *moveTo = CCMoveTo::create(0.5, ccp(WINSIZE_W/2, WINSIZE_H+50));
                CCCallFuncN *callFunc = CCCallFuncN::create(this, callfuncN_selector(GMGameLayer::cleanBoss1));
                CCActionInterval* sequence = (CCActionInterval*)CCSequence::create(moveTo,callFunc,NULL);
                boss1->runAction(sequence);
                if (gameMode == Boot_Mode) {
                    GMAccessData::sharedAccessData()->saveBootModeStatus(1);
                    achievementPrompt->showGMCheckpointsPrompt(1);
                }
            }
        }
    }
}

void GMGameLayer::cleanBoss1(CCNode *pNode)
{
    this->removeChild(bossLayer, true);
    bossLayer = NULL;
    elementLayer->removeBossBlood();
    this->scheduleOnce(schedule_selector(GMGameLayer::goToCardLayeFormBootMOde), 1.0f);
}

void GMGameLayer::goToCardLayeFormBootMOde(float dt)
{
    if (gameMode == Boot_Mode) {
        bootModeLayer->showBossDeath();
    }
    else if(gameMode == Story_Mode){
        this->cleanup();
        removeAllBoss(0);
    }
}

void GMGameLayer::shootBossBullet()
{
    GMBoss1Action * boss1 = (GMBoss1Action*)bossLayer->getChildByTag(BOSS_TAG1);
    int tag = boss1->_tag;
    
    GMBullet *bullet = NULL;
    if (tag == 11) {
        bullet = new GMBullet();
        bullet->initWithSpriteFrameName("bossgx012.png");
        GMPublicMethod::setRepeatAnimation(bullet, 12, 14, "bossgx", "png", 0.1,true);
    }
    else {
        bullet = new GMBullet();
        bullet->initWithSpriteFrameName("bossgx019.png");
        GMPublicMethod::setRepeatAnimation(bullet, 19, 22, "bossgx", "png", 0.1,true);
    }
    bullet->setScale(scaleValue);
    CCPoint point;
//    CCLOG("tag = %d",tag);
    if (tag == 2) {
        point = ccp(WINSIZE_W/2-80*Scale_X,WINSIZE_H-200*Scale_X);
    }
    else if(tag == 3){
        point = ccp(WINSIZE_W/2+80*Scale_X,WINSIZE_H-200*Scale_X);
    }
    else if(tag == 4){
        point = ccp(WINSIZE_W/2-57*Scale_X,WINSIZE_H-230*Scale_X);
    }
    else if(tag == 5){
        point = ccp(WINSIZE_W/2+57*Scale_X,WINSIZE_H-230*Scale_X);
    }
    else if(tag == 11)
    {
        point = ccp(WINSIZE_W/2,WINSIZE_H-(173+93*0.8)*Scale_X);
    }
    bullet->setPosition(point);
    
    bullet->setValue(checkpointsList->getFishBullet(boss1->_bulletId));
    
    bullet->setDelegate(this);
    bullet->fishBulletMove(ccp(WINSIZE_W/2,30*Scale_X),6);
    bullet->setScale(scaleValue);
    allEnemyBulletArray->addObject(bullet);
    fishBulletLayer->addChild(bullet,Bullet_Layer);
    bullet->release();
    bullet = NULL;
}
//#pragma mark - Octopus
/*
 *  boss章鱼
 */
void GMGameLayer::initBossOctopus()
{
    GMEnemy *enemy = checkpointsList->getEnemy(18-1);
    GMBossOctopus *bossOctopus = GMBossOctopus::create();
//    bossOctopus->setContentSize(CCSize(WINSIZE_W, WINSIZE_H-177*Scale_Y));
    bossOctopus->setPosition(ccp(0,0));
    bossOctopus->setDelegate(this);
    bossOctopus->setValue(enemy);
    bossLayer->addChild(bossOctopus,Enemy_Layer,BOSS_TAG2);
//    bossOctopus->setOctopusMove();

//    CCMoveTo *moveTo = CCMoveTo::create(1, ccp(02, WINSIZE_H-177*Scale_Y));
//    bossOctopus->runAction(moveTo);
}

void GMGameLayer::removeAllBoss(float dt)
{
    this->removeChild(bossLayer, true);
    bossLayer = NULL;
    
    elementLayer->removeBossBlood();
    
    this->cleanup();
    winOverSaveData(true);
    if(showDialogLayer3()){
        
    }
    else {
//        if(showDialogLayer2()){
//            GMAccessData::sharedAccessData()->saveOpenCheckpoints(21,1);
//        }
//        else {
//            skipWinLayer();
//        }
        skipWinLayer(0);
    }
}

void GMGameLayer::setOctopusShootBullet(CCPoint point ,float rotation)
{
    GMBossOctopus *bossOctopus = (GMBossOctopus*)bossLayer->getChildByTag(BOSS_TAG2);
    if (bossOctopus) {
        GMBullet *bullet = new GMBullet();
        bullet->initWithSpriteFrameName("octopus_b_001.png");
        GMPublicMethod::setSpriteAnimation(bullet, 1, 3, "octopus_b_", this, callfuncN_selector(GMGameLayer::setOctopusShootBulletAfter));
        bullet->setScale(scaleValue);
               
        bullet->setValue(checkpointsList->getFishBullet(18));
        bullet->setPosition(point);
        bullet->setRotation(rotation);
        bullet->setDelegate(this);
        bullet->fishBulletMove(ccp(WINSIZE_W/2,30*Scale_X),6);
        
        allEnemyBulletArray->addObject(bullet);
        fishBulletLayer->addChild(bullet,Bullet_Layer);
        bullet->release();
        bullet = NULL;
    }//
}

void GMGameLayer::setOctopusShootBulletAfter(CCNode *pNode)
{
	GMBullet *bullet = (GMBullet *)pNode;
    GMPublicMethod::setRepeatAnimation(bullet, 4, 6, "octopus_b_", "png", 0.1,false);
}

//#pragma mark - StarfishKing
/*
 *  boss海星
 */
void GMGameLayer::initStarfishKing(){
    GMEnemy *enemy = checkpointsList->getEnemy(19-1);
    GMBossStarfishKing *starfishKing = new GMBossStarfishKing();
    starfishKing->initStarfishKing(this,enemy);
    starfishKing->setPosition(ccp(WINSIZE_W/2, WINSIZE_H-131/2));
    bossLayer->addChild(starfishKing,Enemy_Layer,BOSS_TAG3);
    starfishKing->release();
}

void GMGameLayer::setCallTwoStarFish(int num){
    if (bossLayer) {
        GMBossStarfishKing *starfishKing = (GMBossStarfishKing*)bossLayer->getChildByTag(BOSS_TAG3);
        if(starfishKing){
            for (int i = 0; i < num; i ++) {
                addEnemy(12,R_NotMoveOut,starfishKing->getPosition());
            }
        }
    }
}

void GMGameLayer::setRestoreLife(){
    GMEnemyAction *enemyAction;
    CCObject *pObject = NULL;
    //普通鱼的检测
    if(bossLayer){
        GMBossStarfishKing *starfishKing = (GMBossStarfishKing*)bossLayer->getChildByTag(BOSS_TAG3);
        if (starfishKing) {
            GMSkill skilltype = GMPublicMethod::sharedPublicMethod()->getSkillType();
            countSmallStarNum = allEnemyArray->count();
            if (skilltype != SKILL_ICE) {
                CCARRAY_FOREACH(allEnemyArray, pObject) {
                    enemyAction = (GMEnemyAction*)pObject;
                    enemyAction->setBossRestoreLife(starfishKing->getPosition(),this,callfuncN_selector(GMGameLayer::removeSubBoss));
                }
            }
        }
    }
    this->scheduleOnce(schedule_selector(GMGameLayer::setRestoreLifeEffect), 1);
}

void GMGameLayer::setRestoreLifeEffect(float dt){
    if(bossLayer){
        GMBossStarfishKing *starfishKing = (GMBossStarfishKing*)bossLayer->getChildByTag(BOSS_TAG3);
        if (starfishKing)
            starfishKing->setRestoreLifeEffect(countSmallStarNum);
    }
}

void GMGameLayer::setRestoreLifeValue(float value){
    elementLayer->setBossBloodValue(-value);
}

void GMGameLayer::removeSubBoss(CCNode *pNode){
	GMEnemyAction *enemyAction = (GMEnemyAction *)pNode;
    removeEnemyFromBatchNode(enemyAction);
}

void GMGameLayer::removeStarfishKing()
{
    if(bossLayer){
        GMBossStarfishKing *starfishKing = (GMBossStarfishKing*)bossLayer->getChildByTag(BOSS_TAG3);
        if (starfishKing){
            this->unschedule(schedule_selector(GMGameLayer::setRestoreLifeEffect));
            bossLayer->removeChild(starfishKing, true);
            this->removeChild(bossLayer, true);
            bossLayer = NULL;
        }
    }
    elementLayer->removeBossBlood();
    
    winOverSaveData(true);
    if(showDialogLayer3()){
        
    }
    else {
        this->scheduleOnce(schedule_selector(GMGameLayer::skipWinLayer), 2);
    }
}

//#pragma mark - GMBossPoseidon

void GMGameLayer::initBossPoseidon(float dt){
    GMEnemy *enemy = checkpointsList->getEnemy(20-1);
    GMBossPoseidon *bossPoseidon = new GMBossPoseidon();
    bossPoseidon->showBoss(this, enemy, ccp(100,100), Scale_X);
    bossLayer->addChild(bossPoseidon,Enemy_Layer,BOSS_TAG4);
    bossPoseidon->release();
}

void GMGameLayer::showBossPoseidonBullet(CCPoint point,float rotation)
{
//    if(bossLayer){
//        GMBossPoseidon *bossPoseidon = (GMBossPoseidon*)bossLayer->getChildByTag(BOSS_TAG4);
//        if(bossPoseidon){
////            bossPoseidon->setAttackAfterValue();
//        }
//    }
    
    GMBullet *bullet = new GMBullet();
    bullet->initWithSpriteFrameName("bullet_20_1_000.png");
    GMPublicMethod::setRepeatAnimation(bullet, 0, 2, "bullet_20_1_","png", 0.1, false);
    bullet->setScale(scaleValue);
    
    bullet->setValue(checkpointsList->getFishBullet(20));
    bullet->setPosition(point);
    bullet->setRotation(rotation);
    bullet->setDelegate(this);
    bullet->fishBulletMove(ccp(WINSIZE_W/2,30*Scale_X),bullet->_speed);
    
    allEnemyBulletArray->addObject(bullet);
    fishBulletLayer->addChild(bullet,Bullet_Layer);
    bullet->release();
    bullet = NULL;

}

void GMGameLayer::removeBossPoseidon()
{
    if(bossLayer){
        this->removeChild(bossLayer, true);
        bossLayer = NULL;
    }
    elementLayer->removeBossBlood();
    
    winOverSaveData(true);
    
    if(showDialogLayer3()){
        
    }
    else {
        this->scheduleOnce(schedule_selector(GMGameLayer::skipWinLayer), 2);
    }
}
//#pragma mark - 胜利失败
void GMGameLayer::skipWinLayer(float dt)
{
    winOverSaveData(true);
    this->cleanup();
    CCScene *pScene = CCTransitionFade::create(0.0, GMWinLayer::scene(), ccWHITE);
    CCDirector::sharedDirector()->replaceScene(pScene);
}

void GMGameLayer::skipLoseLayer()
{
    winOverSaveData(false);
    this->cleanup();
    CCScene *pScene = CCTransitionFade::create(0.0, GMLoseLayer::scene(), ccWHITE);
    CCDirector::sharedDirector()->replaceScene(pScene);
}

void GMGameLayer::skipEndlessMode(){
    this->cleanup();
    GMPublicMethod::sharedPublicMethod()->setGameMode(Endless_Mode);
    CCScene *pScene = CCTransitionFade::create(0.0, GMMainLayer::scene(), ccWHITE);
    CCDirector::sharedDirector()->replaceScene(pScene);
}

void GMGameLayer::skipGMCardLayer(){
    
    CCScene *pScene = CCTransitionFade::create(0.0, GMCardLayer::scene(), ccWHITE);
    CCDirector::sharedDirector()->replaceScene(pScene);
}
//#pragma mark - 抽奖

void GMGameLayer::showWheelView()
{
    if (wheelLayer) {
        return;
    }
    pauseAllAction(true);
    
    CCAddSpriteFramesWithFile(luck_plist1);
    wheelBatchNode = CCSpriteBatchNode::create(luck_png1);
    this->addChild(wheelBatchNode);
    
    GMAudioPlay::sharedAudioPlay()->stopBGMusic();
    GMAudioPlay::sharedAudioPlay()->playOtherEffect(Audio_Wheel,true);
    
    CCArray *temp = CCArray::create();
    GMPublicMethod::readGoodsListFromFile("File/goodsList.plist",temp);
    bool chooseId = false;
    if (gameMode == Boot_Mode) {
        goods = (GMGoods*)temp->objectAtIndex(2);
    }
    else{
        for (int i = 0; i < 4; i++) {
            GMGoods *tGoods = (GMGoods*)temp->objectAtIndex(i);
            if (tGoods->_type == 1) {
                int tempRate1 = rand()%100;
                int tempRate2 = tGoods->_rate*100;
                if (tempRate1 <= tempRate2) {
                    chooseId = true;
                    goods = tGoods;
                    break;
                }
            }
        }
        
        if (!chooseId) {
            int index = rand()%4 + 4;
            goods = (GMGoods*)temp->objectAtIndex(index);
        }
    }
    
    goods->retain();
    //转盘
    wheelLayer = GMWheelLayer::create();
    this->addChild(wheelLayer,Wheel_Layer);
    wheelLayer->delegateGame = this;
    wheelLayer->showWheelOfFortune(goods->_angle);
    
}

void GMGameLayer::removeWheelView(CCNode *pNode)
{
    GMAudioPlay::sharedAudioPlay()->stopMyAllEffects();
    GMAudioPlay::sharedAudioPlay()->playBGMusic(Audio_Gmae1);
    pauseAllAction(false);
    this->removeChild(wheelLayer, true);
    if (goods->_id == 1) {
        elementLayer->setOtheSkill(1);
    }
    else if (goods->_id == 2) {
        elementLayer->setOtheSkill(2);
    }
    else if (goods->_id == 3) {

        elementLayer->setOtheSkill(3);
    }
    else if (goods->_id == 4) {

        elementLayer->setOtheSkill(4);
    }
    else if (goods->_id >= 5) {
        elementLayer->addEnergeBlink(ccp(WINSIZE_W/2, WINSIZE_H-100),scaleValue);
        elementLayer->showNumber(goods->_energe,ccp(WINSIZE_W/2, WINSIZE_H-100));
        
        setTotalMoney(goods->_energe);
        removeWheelRes();
    }
    goods->release();
    goods = NULL;
    
    wheelLayer = NULL;
}

void GMGameLayer::removeWheelRes()
{
    if (wheelBatchNode) {
        this->removeChild(wheelBatchNode, true);
        wheelBatchNode = NULL;
        CCRemoveSpriteFramesAndTextureForKey(luck_plist1,luck_png1);
    }
}

//#pragma mark - Dialog

void GMGameLayer::showDialogLayer()
{
    int tempStatus = GMAccessData::sharedAccessData()->getTaskTipsStatus();
    if(isShowDialogLayer  == false && tempStatus == 0){
        ZPDialogLayer *dialogLayer = ZPDialogLayer::create();
        dialogLayer->initView2();
        dialogLayer->setLabel("规定时间内达到关卡目标即可通关");
        dialogLayer->addMenu("guide009.png", "guide010.png",true);
        dialogLayer->setSelectorTarget(this);
        dialogLayer->setSELCallFun(callfuncN_selector(GMGameLayer::removeDialog));
//        dialogLayer->setAnimation(false);
        this->addChild(dialogLayer,Dialog_Layer);
        isShowDialogLayer = true;
        pauseAllAction(true);
        GMAccessData::sharedAccessData()->saveTaskTipsStatus(1);
    }
    
    isAndroidBack = true;
}

//#pragma mark- 进无尽模式
bool GMGameLayer::showDialogLayer2()
{
    int tempStatus = GMAccessData::sharedAccessData()->getEndlessModeStatus();
    if(isShowDialogLayer2  == false && tempStatus == 0){
        
        elementLayer->removeOverSprite();
      
        ZPDialogLayer *dialogLayer = ZPDialogLayer::create();
        dialogLayer->initView("game/gamegoal000.png", NULL);
        dialogLayer->addPromptTexture("game/gamegoal014.png");
        dialogLayer->addMenu("game/gamegoal012.png", "game/gamegoal013.png",false);
        dialogLayer->setSelectorTarget(this);
        dialogLayer->setSELCallFun(callfuncN_selector(GMGameLayer::removeDialog));
        dialogLayer->setAnimation(false,1);
        this->addChild(dialogLayer,Dialog_Layer);
        isShowDialogLayer2 = true;
        pauseAllAction(true);
        GMAccessData::sharedAccessData()->saveEndlessModeStatus(2);
        isAndroidBack = true;
        return true;
    }
    return false;
}

void GMGameLayer::removeDialog(CCNode *dialog)
{
    removeDialogLayer(dialog);
    
    isAndroidBack = false;
    int tempStatus = GMAccessData::sharedAccessData()->getEndlessModeStatus();
    if (tempStatus == 2 && isShowDialogLayer2) {
//        this->cleanup();
//        GMPublicMethod::sharedPublicMethod()->setGameMode(Endless_Mode);
//        CCScene *pScene = CCTransitionFade::create(0.0, GMMainLayer::scene(), ccWHITE);
//        CCDirector::sharedDirector()->replaceScene(pScene);
        skipEndlessMode();
    }
}

//#pragma mark -  赔率开启提示
bool GMGameLayer::showDialogLayer3()
{
    int temp1 = GMAccessData::sharedAccessData()->getMagnificationModel();
    int temp2 = (currentLevel/10)+1;
    if(isShowDialogLayer3  == false && temp1 < temp2){
        GMAccessData::sharedAccessData()->saveMagnificationModel(temp2);
        
        ZPDialogLayer *dialogLayer = ZPDialogLayer::create();
        dialogLayer->setSelectorTarget(this);
        dialogLayer->setSELMenuHandler(menu_selector(GMGameLayer::removeDialogLayer3));
        dialogLayer->initView1();
        char label[150] = {0};
        int temp3 = GMPublicMethod::getOpenMagnificationModel();
        int temp4 = GMAccessData::sharedAccessData()->getMagnificationModel();
        temp4 = GMPublicMethod::getMagnificationModel(temp4+1);
        if(temp3!=10)
            sprintf(label, "恭喜你成功开启%d倍模式，点击切换!通过第%d关可以开启%d倍模式哦！",temp3,5*temp2,temp4);
        else
            sprintf(label, "恭喜你成功开启%d倍模式，点击切换!",temp3);
        dialogLayer->setLabel(label);
        this->addChild(dialogLayer,Dialog_Layer,1000000);
        isShowDialogLayer3 = true;
        pauseAllAction(true);
        isAndroidBack = true;
        
        GMAccessData::sharedAccessData()->saveCurrentMagnificationModel(temp2-1);
        
        return true;
    }
    return false;
}

void GMGameLayer::removeDialogLayer3(CCObject *pSender){
    ZPLog("removeDialogLayer3");
    ZPDialogLayer *dialogLayer = (ZPDialogLayer*)this->getChildByTag(1000000);
    this->removeChild(dialogLayer, true);
    pauseAllAction(false);
    isAndroidBack = false;
    menuLayer->setMagnificationModel(NULL);
    if (isShowDialogLayer3 == true) {
        if(showDialogLayer2()){
            GMAccessData::sharedAccessData()->saveOpenCheckpoints(21,1);
            GMAccessData::sharedAccessData()->saveEachAchievementStatus(2,1);
            GMAccessData::sharedAccessData()->saveCurrentCheckpoints(2);
        }
        else {
            this->scheduleOnce(schedule_selector(GMGameLayer::skipWinLayer), 2);
        }
    }
}

//#pragma mark- initDialogLayer

void GMGameLayer::initDialogLayer2(const char *string,SEL_CallFuncN sel)
{
    ZPDialogLayer *dialogLayer = ZPDialogLayer::create();
    dialogLayer->setSelectorTarget(this);
    dialogLayer->setSELCallFun(sel);
    dialogLayer->initView(NULL,"guide015.png");
    dialogLayer->setLabel(string);
    this->addChild(dialogLayer,Dialog_Layer);
    dialogLayer->setAnimation(true,1.5);
    pauseAllAction(true);
}

void GMGameLayer::initDialogLayer(const char *string,SEL_CallFuncN sel)
{
    ZPDialogLayer *dialogLayer = ZPDialogLayer::create();
    dialogLayer->setSelectorTarget(this);
    dialogLayer->setSELCallFun(sel);
    dialogLayer->initView("game/gamegoal000.png",NULL);
    dialogLayer->setLabel2(string);
    this->addChild(dialogLayer,Dialog_Layer);
    dialogLayer->setAnimation(true,1.5);
    pauseAllAction(true);
}

void GMGameLayer::removeDialogLayer(CCNode *dialog)
{
    ZPDialogLayer *dialogLayer = (ZPDialogLayer*)dialog;
    this->removeChild(dialogLayer, true);
    pauseAllAction(false);
}

//#pragma mark- 连击提示
bool GMGameLayer::showPromptBatter()
{
    bool isShow = false;
    if(gameMode == Boot_Mode && bootModeLayer && bootModeLayer->getShow()){
        isShow = true;
    }
    
    int tempStatus = GMAccessData::sharedAccessData()->getPromptBatterStatus();
    if (tempStatus==0 && isShow == false) {
        initDialogLayer2("连击越高，得分加成越高哦！",callfuncN_selector(GMGameLayer::removeDialogLayer));
        GMAccessData::sharedAccessData()->savePromptBatterStatus(1);
        return true;
    }
    return false;
}
//#pragma mark- 激光
bool GMGameLayer::showPromptLaser()
{
    bool isShow = false;
    if(gameMode == Boot_Mode && bootModeLayer && bootModeLayer->getShow()){
        isShow = true;
    }
    int tempStatus = GMAccessData::sharedAccessData()->getPromptLaserStatus();
    if (tempStatus==0 && isShow==false) {
        ZPDialogLayer *dialogLayer = ZPDialogLayer::create();
        dialogLayer->initPromptLaser(this,"怒气满了可以发射超级激光哦！",callfuncN_selector(GMGameLayer::removeDialogLayer));
        this->addChild(dialogLayer,Dialog_Layer);
        pauseAllAction(true);
        GMAccessData::sharedAccessData()->savePromptLaserStatus(1);
        return true;
    }
    return false;
}
//#pragma mark- 炮台开启提示

bool GMGameLayer::showPromptOpenCannon()
{
    int cannonIndex = GMAccessData::sharedAccessData()->getOpenCannonLeve();
    if(bulletGrade > cannonIndex && isShowPromptOpenCannon == false){
        isShowPromptOpenCannon = true;
        int index = 0;
        
        if(billingModel == B_Free){
            index = (bulletGrade-2)*2;
        }
        else {
            if (bulletGrade == 3) {
                index = 3;
            }
            else if(bulletGrade == 4){
                index = 6;
            }
            else if(bulletGrade == 5){
                index = 9;
            }
        }
        switch (billingModel) {
            case B_Free:{
                char label[50] = {0};
//                if(bulletGrade == 6){
//                    sprintf(label, "你需要通过购买才能开启哦！");
//                }
//                else {
                sprintf(label, "你需要通过第%d关才能开启哦！",index);
//                }
                initDialogLayer(label,callfuncN_selector(GMGameLayer::removePromptOpenCannon2));
            }   break;
            default:
                addBilling(4,bulletGrade);
                break;
        }
            isAndroidBack = true;
        return true;
    }
    else if(isShowPromptOpenCannon){
        return true;
    }
    return false;
}

void GMGameLayer::removePromptOpenCannon2(CCNode *dialog)
{
    removeDialogLayer(dialog);
    isShowPromptOpenCannon = false;

    int tempCannonIndex = GMAccessData::sharedAccessData()->getOpenCannonLeve();
    changeCannon(tempCannonIndex);
}

//#pragma mark - 开启炮台提示
bool GMGameLayer::showOpenCannon()
{
    int tag = GMAccessData::sharedAccessData()->getOpenCannonLeve();
//    ((billingModel == B_TengXunBilling || billingModel == B_YiDong || billingModel==B_91_IOS || billingModel ==B_Telecom || billingModel == B_91_Android)
    if(gameMode == Boot_Mode ||
       (billingModel == B_Free && ((tag < 3 && currentLevel == 12) || (tag < 4 && currentLevel==14) || (tag < 5 && currentLevel == 21) || (tag < 6 && currentLevel == 23))) ||
       ((billingModel != B_Free) && ( (tag < 3 && currentLevel == 13) || (tag < 4 && currentLevel==21) ||(tag < 5 && currentLevel == 24) ))
    ){
//    if(gameMode == Boot_Mode ||
//       (tag < 3 && currentLevel == 13) || (tag < 4 && currentLevel==21)||
//       (tag < 5 && currentLevel == 24)){
//       (tag < 3 && currentLevel == 12) || (tag < 4 && currentLevel==14)||
//       (tag < 5 && currentLevel == 21) || (tag < 6 && currentLevel == 23)){
        tag++;
        
        ZPLog("guide009  %d",tag);
        elementLayer->removeOverSprite();
        
        ZPDialogLayer *dialogLayer = ZPDialogLayer::create();
        dialogLayer->setSelectorTarget(this);
        dialogLayer->setSELCallFun(callfuncN_selector(GMGameLayer::removePromptOpenCannon));
        dialogLayer->showPromptOpenCannon(tag);
        dialogLayer->addMenu("game/guide009.png","game/guide010.png",false);
        this->addChild(dialogLayer,Dialog_Layer);
        GMAccessData::sharedAccessData()->saveOpenCannonLeve(tag);
        
        pauseAllAction(true);
        return true;
    }
    return false;
}

void GMGameLayer::removePromptOpenCannon(CCNode *dialog)
{
    removeDialogLayer(dialog);
    if(gameMode == Boot_Mode){
        this->cleanup();
        /*****************************************************************************/
        //正版验证
        if(billingModel == B_YiDong || billingModel == B_Telecom){
            int tempStatus = GMAccessData::sharedAccessData()->getGenuineValidationStatus();
            if(tempStatus == 0){
                GMAccessData::sharedAccessData()->saveRoleDeathStatus(1);
                addBilling(1,0);
            }
        }
        /*****************************************************************************/
        else {
            skipGMCardLayer();
        }
    }
    else {
        skipWinLayer(0);
    }
}

//#pragma mark- touch
void GMGameLayer::ccTouchesMoved(CCSet* touches, CCEvent* event)
{}

void GMGameLayer::ccTouchesEnded(CCSet* touches, CCEvent* event)
{
    /**************************************************************************
     *引导模式
     */
    if (gameMode == Boot_Mode) {
        MoveStatus tempMove = GMPublicMethod::sharedPublicMethod()->getMoveStatus();
        if (tempMove == P_Status) {
            return;
        }
    }
    
    if (elementLayer->getPetrifaction()) {
        return;
    }
    
    if (menuLayer->getShootAgain() == false) {
        return;
    }
    
    int pauseStatus = GMAccessData::sharedAccessData()->getPauseStatus();
    if(pauseStatus == 1){
        return;
    }
    /**************************************************************************/
	CCTouch* touch = (CCTouch*)( touches->anyObject() );
	CCPoint location = touch->getLocationInView();
    //    locationInView(touch->view());
	char str[111];
	sprintf(str, "touch loc is %f,%f", location.x, location.y);
	CCLog(str);
    //  倒换
	location = CCDirector::sharedDirector()->convertToGL(location);
	char str2[111];
	sprintf(str2, "touch converd is %f,%f", location.x, location.y);
	CCLog(str2);
	this->fireOn = 1;
    transformCannon(location);
    elementLayer->showWater(location);
}

//#pragma mark -  计费

void GMGameLayer::setAllSkillNum(){
    int num = GMAccessData::sharedAccessData()->getSkillBloodNum();
    num += 5;
    GMAccessData::sharedAccessData()->saveSkillBloodNum(num);
    menuLayer->setSKillNum1(num);
    num = GMAccessData::sharedAccessData()->getSkillPaysNum();
    num += 5;
    GMAccessData::sharedAccessData()->saveSkillPaysNum(num);
    menuLayer->setSKillNum2(num);
}

void GMGameLayer::setUpgradeWeapons(){
    GMAccessData::sharedAccessData()->saveOpenCannonLeve(6);
    int tempCannonIndex = GMAccessData::sharedAccessData()->getOpenCannonLeve();
    changeCannon(tempCannonIndex);
}

//1 为正版验证，2为购买能量，3为购买技能，4为购买武器
void GMGameLayer::addBilling(int index,int index2){
    int _pauseStatus = GMAccessData::sharedAccessData()->getPauseStatus();
    if(_pauseStatus != 1){
        if(billingModel == B_Telecom && index!=1){
//              pauseAction();
            ZPLog("%pauseAction");
        } else{
            pauseAllAction(true);
            ZPLog("%pauseAllAction");
        }
    }
    
    GMPublicMethod::sharedPublicMethod()->setShow91Pause(false);
    GMPublicMethod::sharedPublicMethod()->setAndroidPlayVideo(true);
    
    if (billingModel == B_YiDong && index != 5) {
        if(!_isShowYiDong){
            _isShowYiDong = true;
            showYidongSdkView(index);
        }
    }
    else if(billingModel == B_Telecom && index!=5){
        ZPLog("index index == %d",index);
        if(!_isShowYiDong){
            _isShowYiDong = true;
            showTelecomSMSView(index);
        }
    }
    else if(billingModel == B_91_Android && index == 1){
#if (JNIHELPER_INDEX == JNIHELPER_91_Android)
        ZPJNIHelper::setAllPay(6);
        pauseAllAction(true);
        this->schedule(schedule_selector(GMGameLayer::check91BillingPoint));
#endif
    }
    else if(billingModel == B_91_Android && index == 3){
#if (JNIHELPER_INDEX == JNIHELPER_91_Android)
            ZPJNIHelper::setAllPay(1);
            pauseAllAction(true);
            this->schedule(schedule_selector(GMGameLayer::check91BillingPoint));
#endif
    }
    else if(billingModel == B_91_Android && index == 4){
#if (JNIHELPER_INDEX == JNIHELPER_91_Android)
        ZPJNIHelper::setAllPay(5);
        pauseAllAction(true);
        this->schedule(schedule_selector(GMGameLayer::check91BillingPoint));
#endif
    }
    else {
        GMBillingLayer *billingLayer = GMBillingLayer::create();
        billingLayer->setDelegate(this);
        billingLayer->setIndex(index);
        billingLayer->setStartBliling(false);
        billingLayer->setClassType(1);
        switch (index) {
            case 1:{
                if(billingModel == B_YiDong){
                    billingLayer->setStartBliling(true);
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
                        billingLayer->setStartBliling(true);
                        billingLayer->showGenuineValidationTips();
                    }
#endif
                }
                else{
                    int tempStatus = GMAccessData::sharedAccessData()->getEndlessModeStatus();
                    if(tempStatus == 0 && gameMode == Story_Mode){
                        billingLayer->showSecondaryConfirmationTips(1);
                    }
                    else if(gameMode == Boot_Mode || gameMode == Endless_Mode){
//                        billingLayer->setStartBliling(true);
//                        billingLayer->showGenuineValidationTips();
                        billingLayer->showSecondaryConfirmationTips(0);
                    }
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
            case 3:{
                billingLayer->showPurchasingSkills();
            }   break;
            case 4:{
                billingLayer->showWeaponUpgrades(index2);
            }   break;
            case 5:{
                billingLayer->showThePurchaseOfEnergy(1,index2);
            }   break;
            case 6:{
                billingLayer->showGenuineValidationTips();
                billingLayer->setStartBliling(true);
//                if (gameMode == Boot_Mode) {
//                    billingLayer->showGenuineValidationTips();
//                }
//                else {
//                    billingLayer->setStartBliling(true);
//                    int tempStatus = GMAccessData::sharedAccessData()->getEndlessModeStatus();
//                    if(tempStatus == 0 && gameMode != Boot_Mode)
//                        billingLayer->showSecondaryConfirmationTips(1);
//                    else
//                        billingLayer->showSecondaryConfirmationTips(0);
//                }
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
    }
}

void GMGameLayer::removeBilling(int index,bool _isClickClose,int type){
    
    if(gameMode == Endless_Mode && (index == 1 || index == 6)){
        //无尽模式但计费点
    }
    else {
        pauseAllAction(false);
    }
    
#if (JNIHELPER_INDEX == JNIHELPER_91_IOS)
    if( _isClickClose /*|| PublicCPP::getMobileBilling()*/)
#endif
    {
        GMBillingLayer *tempBillingLayer = (GMBillingLayer*)this->getChildByTag(Billing_tag);
        if(tempBillingLayer)
            this->removeChild(tempBillingLayer, true);
    }
    
    switch (index) {
        case 1:{
            if(_isClickClose==false){
                if(billingModel == B_91){
                    GMAccessData::sharedAccessData()->saveGenuineValidationStatus(2);//已验证
                    GMAccessData::sharedAccessData()->saveAngerValue(10000);
                    menuLayer->setAngerValue(10000);
                    setTotalMoney(5000);
                    int num = GMAccessData::sharedAccessData()->getSkillBloodNum();
                    num = num+5;
                    menuLayer->setSKillNum1(num);
                    GMAccessData::sharedAccessData()->saveSkillBloodNum(num);
                    
                    if(gameMode != Boot_Mode){
                        int tempStatus = GMAccessData::sharedAccessData()->getGenuineValidationStatus();
                        int tempStatus1 = GMAccessData::sharedAccessData()->getEndlessModeStatus();
                        if(tempStatus == 2 && currentLevel == 12 && tempStatus1!=2 ){
                            showDialogLayer2();
                        }
                        else if(tempStatus1 == 2){
                            if(gameMode == Story_Mode)
                                skipWinLayer(0);
                        }
                    }
                }
                else if(billingModel == B_YiDong){
                }
                else if (billingModel == B_91_IOS) {
#if (JNIHELPER_INDEX == JNIHELPER_91_IOS)
//                    if(PublicCPP::getMobileBilling()){
//                        addBilling(8,0);
//                    }
//                    else
                    {
                        //PublicCPP::paymentAll(6);//
                        this->schedule(schedule_selector(GMGameLayer::check91BillingPoint));
                        pauseAllAction(true);
                    }
#endif
                }
                else if(billingModel == B_TengXunBilling){
//                    腾讯正版验证暂时注销2次确认
                    GMAccessData::sharedAccessData()->saveGenuineValidationStatus(1);
                    addBilling(6,0);
                }
                else if(billingModel == B_Unicom_Android){
                    ZPLog("index index %d",index);
                    if(index == 3)
                        index = 2;
                    ZPJNIHelper::sendSMSBillingPoint(index);
                    this->schedule(schedule_selector(GMGameLayer::checkBillingPoint));
                }
            }
            else {
                GMAccessData::sharedAccessData()->saveGenuineValidationStatus(1);
                int tempStatus = GMAccessData::sharedAccessData()->getGenuineValidationStatus();
                int tempStatus1 = GMAccessData::sharedAccessData()->getEndlessModeStatus();
                if(tempStatus != 2 && currentLevel == GoToEndless && tempStatus1 != 2){
                    if(showDialogLayer2())
                        GMAccessData::sharedAccessData()->saveOpenCheckpoints(currentLevel+1,1);
                }
                else if(tempStatus1 == 2){
                    if(gameMode == Story_Mode)
                        skipWinLayer(0);
                }
            }
        }   break;
        case 2:{
            if(_isClickClose==false){
                
                if(billingModel == B_91_IOS || billingModel == B_91_Android){
                    ZPLog("type %d",type);
                    int tag = type;
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
                        pauseAllAction(true);
                        this->schedule(schedule_selector(GMGameLayer::check91BillingPoint));
                    }
#endif
#if (JNIHELPER_INDEX == JNIHELPER_91_Android)
                    ZPJNIHelper::setAllPay(tempIndex);
                    pauseAllAction(true);
                    this->schedule(schedule_selector(GMGameLayer::check91BillingPoint));
#endif
                }
                else {
                    if(type == 2){
                        if(billingModel == B_TengXunBilling){
                            ZPJNIHelper::sendSMSBillingPoint(3);
                            this->schedule(schedule_selector(GMGameLayer::checkBillingPoint));
                            pauseAllAction(true);
                        }
                        else if(billingModel == B_YiDong){
//#if (JNIHELPER_INDEX == JNIHELPER_YiDong)
//                            ZPJNIHelper::setYiDongBilling(3);
//                            pauseAllAction(true);
//                            this->schedule(schedule_selector(GMGameLayer::checkBillingPoint));
//#endif
                        }
                        else if(billingModel == B_Unicom_Android){
                            ZPLog("index index %d",index);
                            if(index == 3)
                                index = 2;
                            ZPJNIHelper::sendSMSBillingPoint(index);
                            this->schedule(schedule_selector(GMGameLayer::checkBillingPoint));
                        }
                    }
                    else {
                        int index = GMAccessData::sharedAccessData()->getGiftStatus();
                        index++;
                        GMAccessData::sharedAccessData()->saveGiftStatus(index);
                        elementLayer->setGiftValue();
                    }
                }
            }
        }   break;
        case 3:{//购买特殊道具（技能）
            if(_isClickClose==false){
                if(billingModel == B_Free){
                    setAllSkillNum();
                }
                else if(billingModel == B_TengXunBilling){
                    ZPJNIHelper::sendSMSBillingPoint(2);
                    this->schedule(schedule_selector(GMGameLayer::checkBillingPoint));
                    pauseAllAction(true);
                }
                else if(billingModel==B_91_IOS){
#if (JNIHELPER_INDEX == JNIHELPER_91_IOS)
//                    if(PublicCPP::getMobileBilling()){
//                        GMPublicMethod::sharedPublicMethod()->setBillingIndex(1);
//                        addBilling(7, 0);
//                    }
//                    else
                    {
                        //PublicCPP::paymentAll(1);//
                        this->schedule(schedule_selector(GMGameLayer::check91BillingPoint));
                        pauseAllAction(true);
                    }
#endif
                }
//                else if(billingModel == B_91_Android){
//#if (JNIHELPER_INDEX == JNIHELPER_91_Android)
//                    ZPJNIHelper::setAllPay(1);
//                    pauseAllAction(true);
//                    this->schedule(schedule_selector(GMGameLayer::check91BillingPoint));
//#endif
//                }
                else if(billingModel == B_YiDong){
//#if (JNIHELPER_INDEX == JNIHELPER_YiDong)
//                    ZPJNIHelper::setYiDongBilling(2);
//                    pauseAllAction(true);
//                    this->schedule(schedule_selector(GMGameLayer::checkBillingPoint));
//#endif
                }
                else if(billingModel == B_Unicom_Android){
                    ZPLog("index index %d",index);
                    if(index == 3)
                        index = 2;
                    ZPJNIHelper::sendSMSBillingPoint(index);
                    this->schedule(schedule_selector(GMGameLayer::checkBillingPoint));
                }
            }
        }   break;
        case 4:{//升级武器
            isShowPromptOpenCannon = false;
            if(_isClickClose==false){
                if(billingModel == B_TengXunBilling){
                    ZPJNIHelper::sendSMSBillingPoint(4);
                    this->schedule(schedule_selector(GMGameLayer::checkBillingPoint));
                    pauseAllAction(true);
                }
                else if(billingModel==B_91_IOS){
#if (JNIHELPER_INDEX == JNIHELPER_91_IOS)
//                    if(PublicCPP::getMobileBilling()){
//                        GMPublicMethod::sharedPublicMethod()->setBillingIndex(5);
//                        addBilling(7, 0);
////                        pauseAllAction(true);
//                    }
//                    else
                    {
                        //PublicCPP::paymentAll(5);//购买武器
                        pauseAllAction(true);
                        this->schedule(schedule_selector(GMGameLayer::check91BillingPoint));
                    }
#endif
                }
//                else if(billingModel == B_91_Android){
//#if (JNIHELPER_INDEX == JNIHELPER_91_Android)
//                    ZPJNIHelper::setAllPay(5);
//                    pauseAllAction(true);
//                    this->schedule(schedule_selector(GMGameLayer::check91BillingPoint));
//#endif
//                }
                else if(billingModel == B_YiDong){
                }
                else if(billingModel == B_Unicom_Android){
                    ZPLog("index index %d",index);
                    if(index == 3)
                        index = 2;
                    ZPJNIHelper::sendSMSBillingPoint(index);
                    this->schedule(schedule_selector(GMGameLayer::checkBillingPoint));
                }
            }
            else {
                int tempCannonIndex = GMAccessData::sharedAccessData()->getOpenCannonLeve();
                changeCannon(tempCannonIndex);
            }
        }   break;
        case 5:{
            if(_isClickClose==false){
                int index = GMAccessData::sharedAccessData()->getGiftStatus();
                if(index == 1){
                    setTotalMoney(400);
                }
                else if(index == 2){
                    setTotalMoney(1000);
                }
                index++;
                GMAccessData::sharedAccessData()->saveGiftStatus(index);
                giftTime = 15*index;//60*index;
                elementLayer->setGiftValue();
            }
        }   break;
        case 6:{
            if(_isClickClose==false){
                ZPLog("计费索引   6");
                if(billingModel == B_TengXunBilling){
                    ZPJNIHelper::sendSMSBillingPoint(1);
                    this->schedule(schedule_selector(GMGameLayer::checkBillingPoint));
                    pauseAllAction(true);
                }
            }
            else {
                int tempStatus = GMAccessData::sharedAccessData()->getGenuineValidationStatus();
                int tempStatus1 = GMAccessData::sharedAccessData()->getEndlessModeStatus();
                if(tempStatus != 2 && currentLevel == GoToEndless && tempStatus1!=2){
                    showDialogLayer2();
                }
                else if(tempStatus1 == 2){
                    if(gameMode == Story_Mode)
                        skipWinLayer(0);
                }
            }
        }   break;
        case 7:{
            if(_isClickClose==false)
                addBilling(8, 0);
        }   break;
        case 8:{
            if(_isClickClose==false){
                this->schedule(schedule_selector(GMGameLayer::check91BillingPoint));
            }
        }   break;
        default:
            break;
    }
}

//#pragma mark - 腾讯计费回调方法 /联通
void GMGameLayer::checkBillingPoint(float dt){
    int status = ZPJNIHelper::getSendSMSBillingPointStatus();
	////TTTTTTTTTTT
	status = 0;
    ZPLog("计费成功与否 的状态 = %d",status);
    int index = ZPJNIHelper::getBillingIndex();
	index = 2;
	setTotalMoney(5000);
	setAllSkillNum();
	GMAccessData::sharedAccessData()->saveOpenCannonLeve(6);
    ZPLog("计费点的索引 index = %d",index);
    if(status != 0){
        if(status == 1){
            if(index == 1){
                GMAccessData::sharedAccessData()->saveGenuineValidationStatus(2);
                GMAccessData::sharedAccessData()->saveAngerValue(10000);
                menuLayer->setAngerValue(10000);
                setTotalMoney(5000);
                
                int num = GMAccessData::sharedAccessData()->getSkillBloodNum();
                num = num+5;
                menuLayer->setSKillNum1(num);
                GMAccessData::sharedAccessData()->saveSkillBloodNum(num);
                winOverSaveData(false);
                if(gameMode == Story_Mode){
                    GMAccessData::sharedAccessData()->saveEndlessModeStatus(2);
                    skipEndlessMode();
                }
                else if((billingModel == B_YiDong || billingModel == B_Telecom) && gameMode == Boot_Mode){
                    skipGMCardLayer();
                }
                ZPLog("GMGameLayer 正版验证计费  计费索引 1");
            }
            else if (index == 2) {
                setAllSkillNum();
                ZPLog("GMGameLayer 购买道具计费  计费索引 2");
            }
            else if(index == 3){
                setTotalMoney(5000);
                int index = GMAccessData::sharedAccessData()->getGiftStatus();
                CCLog("当前礼盒状态2 %d",index);
                index++;
                GMAccessData::sharedAccessData()->saveGiftStatus(index);
                CCLog("当前礼盒状态3 %d",index);
                elementLayer->setGiftValue();
                ZPLog("GMGameLayer 获取能量计费  计费索引 3");
            }
            else if(index == 4){
                setUpgradeWeapons();
                ZPLog("GMGameLayer 购买武器计费  计费索引 4");
            }
            
//            ZPJNIHelper::setSMSBillingPointStatus();// 将状态付值为0 (腾讯 移动 通用方法)
//            this->unschedule(schedule_selector(GMGameLayer::checkBillingPoint));
//            pauseAllAction(false);
//            isShowPromptOpenCannon = false;
//            _isShowYiDong = false;
        }
        else if(status == 2){
//            ZPJNIHelper::setSMSBillingPointStatus();// 将状态付值为0 (腾讯 移动 通用方法)
            if((billingModel == B_YiDong || billingModel == B_Telecom)  && index == 1 && gameMode == Boot_Mode){
                skipGMCardLayer();
            }
            else if(index == 1){
                if(gameMode == Boot_Mode){
                    int tempVS = GMAccessData::sharedAccessData()->getGenuineValidationStatus();
                    if(tempVS!=2)
                        GMAccessData::sharedAccessData()->saveGenuineValidationStatus(1);
                }
                else if(gameMode == Story_Mode){
                    showDialogLayer2();
                }
            }
            else  if (/*(billingModel == B_YiDong || billingModel == B_Telecom || billingModel == B_Unicom_Android) &&*/ index == 4) {
                int tempCannonIndex = GMAccessData::sharedAccessData()->getOpenCannonLeve();
                changeCannon(tempCannonIndex);
                isShowPromptOpenCannon = false; 
            }
//            this->unschedule(schedule_selector(GMGameLayer::checkBillingPoint));
//            pauseAllAction(false);
//            _isShowYiDong = false;
        }
        ZPJNIHelper::setSMSBillingPointStatus();// 将状态付值为0 (腾讯 移动 通用方法)
        this->unschedule(schedule_selector(GMGameLayer::checkBillingPoint));
        
        if(billingModel == B_Unicom_Android && index ==1 && gameMode != Boot_Mode){
            
        }else if(billingIndex!=B_Telecom){
            pauseAllAction(false);
        }
        isShowPromptOpenCannon = false;
        _isShowYiDong = false;
    }
}

//#pragma mark - 91 计费回调方法
void GMGameLayer::check91BillingPoint(float dt){
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
            char keyName[80] = {0};
            if(tempInde == 1){//特殊道具（技能）
                setAllSkillNum();
                sprintf(keyName, "恭喜您获得特殊道具");
            }
            else if(tempInde == 2){//购买能量 （5000）
                int tempM = GMAccessData::sharedAccessData()->getTotalMoneyNum();
                tempM += 5000;
                GMAccessData::sharedAccessData()->saveTotalMoneyNum(tempM);
                setTotalMoney(5000);
                sprintf(keyName, "恭喜获得%d能量",5000);
            }
            else if(tempInde == 3){//购买能量 （13000）
                int tempM = GMAccessData::sharedAccessData()->getTotalMoneyNum();
                tempM += 13000;
                GMAccessData::sharedAccessData()->saveTotalMoneyNum(tempM);
                setTotalMoney(13000);
                sprintf(keyName, "恭喜获得%d能量",13000);
            }
            else if(tempInde == 4){//购买能量 （40000）
                int tempM = GMAccessData::sharedAccessData()->getTotalMoneyNum();
                tempM += 40000;
                GMAccessData::sharedAccessData()->saveTotalMoneyNum(tempM);
                setTotalMoney(40000);
                sprintf(keyName, "恭喜获得%d能量",40000);
            }
            else if(tempInde == 5){//升级武器
                setUpgradeWeapons();
                sprintf(keyName, "成功开启所有武器");
            }
            else if(tempInde == 6){
                if(ZPJNIHelper::getOperators() == 1){
                    int tempM = GMAccessData::sharedAccessData()->getTotalMoneyNum();
                    tempM += 13000;
                    GMAccessData::sharedAccessData()->saveTotalMoneyNum(tempM);
                    setTotalMoney(13000);
                }

                GMAccessData::sharedAccessData()->saveGenuineValidationStatus(2);
                if( gameMode != Boot_Mode && showDialogLayer2()){
                    winOverSaveData(true);
                    GMAccessData::sharedAccessData()->saveOpenCheckpoints(currentLevel+1,1);
                }
                sprintf(keyName, "恭喜您开启所有关卡");
            }
#if (JNIHELPER_INDEX == JNIHELPER_91_IOS)
            //PublicCPP::removeRecord(tempInde);
#endif
            GMPublicMethod::sharedPublicMethod()->showTipView(this,keyName);
            this->scheduleOnce(schedule_selector(GMGameLayer::removeTipView), 1);
        }
        else if(tempStatus==2){
            if(tempInde == 5){
                int tempCannonIndex = GMAccessData::sharedAccessData()->getOpenCannonLeve();
                changeCannon(tempCannonIndex);
            }
            else if(tempInde == 6){
                int tempVS = GMAccessData::sharedAccessData()->getGenuineValidationStatus();
                if(tempVS!=2)
                    GMAccessData::sharedAccessData()->saveGenuineValidationStatus(1);
                
                if(gameMode != Boot_Mode && showDialogLayer2()){
                    winOverSaveData(true);
                    GMAccessData::sharedAccessData()->saveOpenCheckpoints(currentLevel+1,1);
                }
            }
#if (JNIHELPER_INDEX == JNIHELPER_91_IOS)
            //PublicCPP::messageBox();
#endif
        }
        GMBillingLayer *tempBillingLayer = (GMBillingLayer*)this->getChildByTag(Billing_tag);
        this->removeChild(tempBillingLayer, true);
#if (JNIHELPER_INDEX == JNIHELPER_91_IOS)
        //PublicCPP::setPaymentSuccess(0);
#endif
        ZPJNIHelper::setSMSBillingPointStatus();//将状态付值为0 (腾讯 移动 通用方法)
        this->unschedule(schedule_selector(GMGameLayer::check91BillingPoint));
        if(!_billing91Again){
            pauseAllAction(false);
        }
        isShowPromptOpenCannon = false;
        _billing91Again = false;
        
//        if(ZPJNIHelper::getOperators() != 1)
//            pauseAction();
    }

}

void GMGameLayer::removeTipView(float dt){
    GMPublicMethod::sharedPublicMethod()->removeTipView(this);
}

//#pragma mark - 移动 网乐
void GMGameLayer::showYidongSdkView(int index){
#if (JNIHELPER_INDEX == JNIHELPER_YiDong)
    this->unschedule(schedule_selector(GMGameLayer::checkBillingPoint));
    switch (index) {
        case 1:{
            GMAccessData::sharedAccessData()->saveGenuineValidationStatus(1);
            ZPJNIHelper::setYiDongBilling(1);
            this->schedule(schedule_selector(GMGameLayer::checkBillingPoint));
        } break;
        case 2:{
            ZPJNIHelper::setYiDongBilling(3);
            this->schedule(schedule_selector(GMGameLayer::checkBillingPoint));
        }   break;
        case 3:{
            ZPJNIHelper::setYiDongBilling(2);
            this->schedule(schedule_selector(GMGameLayer::checkBillingPoint));
        }   break;
        case 4:{
            ZPJNIHelper::setYiDongBilling(4);
            this->schedule(schedule_selector(GMGameLayer::checkBillingPoint));
        }   break;
        default:
            break;
    }
#endif
}
//#pragma mark - 电信计费相关的方法
void GMGameLayer::showTelecomSMSView(int _index){
#if (JNIHELPER_INDEX == JNIHELPER_Telecom)
    this->unschedule(schedule_selector(GMGameLayer::checkBillingPoint));
    switch (_index) {
        case 1:{
            GMAccessData::sharedAccessData()->saveGenuineValidationStatus(1);
            ZPJNIHelper::sendSMSBillingPoint(1);
            this->schedule(schedule_selector(GMGameLayer::checkBillingPoint));
        } break;
        case 2:{
            ZPJNIHelper::sendSMSBillingPoint(3);
            this->schedule(schedule_selector(GMGameLayer::checkBillingPoint));
        }   break;
        case 3:{
            ZPJNIHelper::sendSMSBillingPoint(2);
            this->schedule(schedule_selector(GMGameLayer::checkBillingPoint));
        }   break;
        case 4:{
            ZPJNIHelper::sendSMSBillingPoint(4);
            this->schedule(schedule_selector(GMGameLayer::checkBillingPoint));
        }   break;
        default:
            break;
    }
    if(/*gameMode != Boot_Mode*/ _index != 1)
        pauseAction();
#endif
}

//#pragma mark - Android
void GMGameLayer::keyBackClicked(){
	
    ZPLog("GMGameLayer::keyBackClicked");
    int tempStatus = GMAccessData::sharedAccessData()->getPauseStatus();
    ZPLog("测试暂停界面1 == status %d",tempStatus);
    if(tempStatus==1){
        return;
    }
    if (isAndroidBack == false) {
        isAndroidBack = true;
        pauseAction();
        
        ZPLog("测试暂停界面3 == status %d",tempStatus);
    }
    else{
        if(pauseLayer){
            if (pauseLayer->isShowHelp) {
                pauseLayer->closeHelpAction();
            }
            else {
                pauseLayer->removeTouchDelegate();
                continueGame();
            }
        }
        ZPLog("测试暂停界面3 == status %d",tempStatus);
    }
    
}


//#pragma mark - Android
void GMGameLayer::keyboardHook(int keyCode, int keyEvent){
	if (keyCode == kTypeEnterClicked && keyEvent == kTypeEventKeyUp)
	{
		if (this->choosedSkill > 0) {
			if (this->choosedSkill == 1) {
				this->usedSkill1(NULL);
			}
			else {
				this->usedSkill2(NULL);
			}
			this->choosedSkill = 0;
			this->menuLayer->skill1->stopAllActions();
			this->menuLayer->skill1->setScale(1.0);
			this->menuLayer->skill2->stopAllActions();
			this->menuLayer->skill2->setScale(1.0);
			return;
		}
		GMTargetLayer* targerlayer = (GMTargetLayer*)GMPublicMethod::sharedPublicMethod()->targetLayer;
		if (targerlayer != NULL) {
			targerlayer->goAtion(NULL);
			return;
		}
		if (isShowDialogLayer) {
			CCNode* dailog = this->getChildByTag(Dialog_Layer);
			this->removeDialog(dailog);
			return;
		}
		if (this->isShowDialogLayer2) {
			CCNode* dailog = this->getChildByTag(Dialog_Layer);
			this->removeDialog(dailog);
			return;
		}
		if (this->isShowDialogLayer3) {
			CCNode* dailog = this->getChildByTag(Dialog_Layer);
			this->removeDialogLayer3(dailog);
			return;
		}

		this->shootting = !this->shootting;
	}
	else {
		int arr = 0;
		if (keyCode == kTypeLeftArrowClicked) {
			arr = 1;
		}
		else if (keyCode == kTypeRightArrowClicked) {
			arr = -1;
		}
		else if (keyCode == kTypeUpArrowClicked && keyEvent == kTypeEventKeyUp) {
			this->changeCannon(menuLayer->cannonIndex);
			return;
		}
		else if (keyCode == kTypeDownArrowClicked && keyEvent == kTypeEventKeyUp) {
			this->choosedSkill += 1;
			if (this->choosedSkill > 2) {
				this->choosedSkill = 0;
				this->menuLayer->skill1->stopAllActions();
				this->menuLayer->skill1->setScale(1.0*Scale_X);
				this->menuLayer->skill2->stopAllActions();
				this->menuLayer->skill2->setScale(1.0*Scale_X);
				return;
			}
			CCScaleTo* scale1 = CCScaleTo::create(0.4, 1.5*Scale_X);
			CCScaleTo* scale2 = CCScaleTo::create(0.4, 1.0*Scale_X);
			CCSequence *seq = CCSequence::create(scale1, scale2, NULL);
			CCRepeatForever* rep = CCRepeatForever::create(seq);
			if (this->choosedSkill == 1) {
				this->menuLayer->skill2->stopAllActions();
				this->menuLayer->skill2->setScale(1.0*Scale_X);
				this->menuLayer->skill1->runAction(rep);
			} 
			else if (this->choosedSkill == 2) {
				this->menuLayer->skill1->stopAllActions();
				this->menuLayer->skill1->setScale(1.0*Scale_X);
				this->menuLayer->skill2->runAction(rep);
			}
			else {
			}
		}
		if (arr != 0) {

			CCPoint point = menuLayer->getCannon()->getPosition();
			float radians = CC_DEGREES_TO_RADIANS(arr * 3);
			CCPoint point1 = ccpRotateByAngle(touchLocation, point, radians);
			this->touchLocation = point1;

			transformCannon(this->touchLocation);
		}

	}
}


//#pragma mark - ~GMGameLayer
void GMGameLayer::unscheduleGame()
{
    this->unschedule(schedule_selector(GMGameLayer::brushStrange));
    this->unschedule(schedule_selector(GMGameLayer::update));
    this->unschedule(schedule_selector(GMGameLayer::checkUpadte));
    this->unschedule(schedule_selector(GMGameLayer::updateCheckNetAndFish));
}

GMGameLayer::~GMGameLayer()
{
    unscheduleGame();
    
    if(m_pShootBullet)
        m_pShootBullet->release();

    ZPLog("fish count %d",countAllFishTag);
    ZPLog("fish bullet count %d",countFishBulletTag);
    
    allBulletArray->removeAllObjects();
    allBulletArray->release();
    allBulletArray = NULL;
    allNetArray->removeAllObjects();
    allNetArray->release();
    allNetArray = NULL;
    allEnemyArray->removeAllObjects();
    allEnemyArray->release();
    allEnemyArray = NULL;
    allEnemyBulletArray->removeAllObjects();
    allEnemyBulletArray->release();
    allEnemyBulletArray = NULL;
    
    curvePointArray->removeAllObjects();
    curvePointArray->release();
    curvePointArray = NULL;
    fishArrayData->removeAllObjects();
    fishArrayData->release();
    fishArrayData = NULL;
    
    this->removeChild(elementLayer, true);
    elementLayer = NULL;
    this->removeChild(skillElementLayer, true);
    skillElementLayer = NULL;
    
    checkpointsList->release();
    checkpointsList = NULL;
    
    this->removeChild(fishBatchNode1, true);
    fishBatchNode1 = NULL;
    
    this->removeChild(bulletSheet, true);
    bulletSheet = NULL;
    
    this->removeChild(bootModeLayer, true);
    bootModeLayer = NULL;
    
    this->removeChild(achievementPrompt, true);
    achievementPrompt = NULL;
    
    this->removeChild(wheelLayer, true);
    
    this->removeChild(fishLayer, true);
    fishLayer->release();
    fishLayer = NULL;
    
    this->removeChild(attackfishBatchNode1, true);
    attackfishBatchNode1 = NULL;
    this->removeChild(laserSheet, true);
    laserSheet = NULL;
    this->removeChild(netBatchNode, true);
    netBatchNode = NULL;
    this->removeChild(fishBulletBatchNode, true);
    fishBulletBatchNode = NULL;
    menuLayer->removeChild(fishBulletLayer, true);
    fishBulletLayer = NULL;
    this->removeChild(netParticleLayer, true);
    netParticleLayer = NULL;
    
    this->removeChild(menuLayer, true);
    menuLayer = NULL;
    
    task = NULL;
    
    CC_SAFE_RELEASE_NULL(m_pLaserBullet);
    
    
    CCRemoveSpriteFrameByName(Buttle_plist1);
    CCRemoveTextureForKey(Buttle_png1);
    CCRemoveSpriteFrameByName(Fish_plist1);
    CCRemoveTextureForKey(Fish_png1);
    CCRemoveSpriteFrameByName(Fish_plist2);
    CCRemoveTextureForKey(Fish_png2);
    CCRemoveSpriteFrameByName(Jiguang_plist);
    CCRemoveTextureForKey(Jiguang_png);
    CCRemoveSpriteFrameByName(fishBullet_plist);
    CCRemoveTextureForKey(fishBullet_png);
    
    CCRemoveSpriteFramesAndTextureForKey(luck_plist1,luck_png1);
    
    CCRemoveSpriteFramesAndTextureForKey(guide2_plist,guide2_png);
    
    ZPLog("%d",this->getChildrenCount());

    ZPLog("~GMGameLayer");
}

