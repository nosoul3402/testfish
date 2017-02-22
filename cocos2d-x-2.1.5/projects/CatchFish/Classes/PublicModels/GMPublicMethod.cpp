//
//  GMPublicMethod.cpp
//  FishX
//
//  Created by peng on 13-1-15.
//
//

#include "GMPublicMethod.h"
#include "GMAccessData.h"
#include "../Config/GMHeaderConfig.h"
#include "../Models/GMPoint.h"
#include "../Models/GMGoods.h"
#include "../Models/GMAchievement.h"

const int GMPublicMethod::_animationFrames[][3] = {
    { 4, 8, 0},//1
    { 4, 4, 0},//2
    { 4, 4, 0},//3
    { 8, 4, 0},//4
    { 4, 4, 0},//5
    { 8, 4, 0},//6
    { 6, 4, 0},//7
    { 7, 4, 0},//8
    {16, 4, 0},//9
    { 8, 4, 0},//10
    { 4, 3, 4},//11
    { 7, 7, 7},//12
    { 4, 4, 7},//13
    { 8, 2, 7},//14
    { 8,10, 0},//15
    { 8, 0, 0},//16
    { 0, 0, 0},//17
    { 0, 0, 0},//18
    {12,12,12},//19
    { 6, 7, 7},//20
};
                                    //id = 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,15,16,17,18,19,20
const int GMPublicMethod::_bExplosion[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 2};
const int GMPublicMethod::_eExplosion[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 4, 4, 5, 0, 0, 0, 0, 3, 6};

GMPublicMethod* GMPublicMethod::m_pPublicMethod = 0;

GMPublicMethod* GMPublicMethod::sharedPublicMethod()
{
    if (! m_pPublicMethod)
    {
        m_pPublicMethod = new GMPublicMethod();
        m_pPublicMethod->initValue();
    }
    
    return m_pPublicMethod;
}

GMPublicMethod::GMPublicMethod(): consumption_of_energy(0), gain_energy(0),
m_pPhoneNumber(new std::string),tipLabelTTF(NULL),tipSpriteBg(NULL),_isShow91Pause(false)
{
    
}

void GMPublicMethod::initValue()
{
    setSkillType(SKILL_NONE);
    hitArray = new CCArray();
    m_nCheckpointsIndex = 1;
    setOpenMusic(false);
    setAndroidPlayVideo(false);
    _AudioStatus = 0;
    setShowLogo(false);
}

//#pragma mark -

void GMPublicMethod::purgeSharedPublicMethod()
{
    CC_SAFE_DELETE(m_pPublicMethod);
    m_pPublicMethod = NULL;
}

GMPublicMethod::~GMPublicMethod()
{
    CC_SAFE_DELETE(m_pPhoneNumber);
    consumption_of_energy = 0;
    hitArray->release();
    hitArray = NULL;
    m_pPublicMethod = NULL;
}

//#pragma mark -

int GMPublicMethod::getScoreNum(int num)
{
    int i = 0;
    if (num==0) {
        return 1;
    }
    while (1) {
        if (num<=0) {
            break;
        }
        i++;
        num = num/10;
    }
    return i;
}

//#pragma mark -

void GMPublicMethod::setEvaluationScore(int score)
{
    evaluationScore = score;
}

void GMPublicMethod::cleanEnergy()
{
    consumption_of_energy = 0;
    gain_energy = 0;
}
void GMPublicMethod::setConsumptionEnergy(int ce)
{
    consumption_of_energy = consumption_of_energy+ce;
}

/*
 *1星：评价分数≤得分≤120%评价分数
 *2星：120%评价分数＜得分≤150%评价分数
 *3星：150%评价分数＜得分
 */
int GMPublicMethod::getStarNum()
{
    int star = 0;
    int cScore = GMPublicMethod::sharedPublicMethod()->getGainEnergy();
    int eScore = GMPublicMethod::sharedPublicMethod()->getEvaluationScore();
    if (cScore == 0){
        star = 0;
    }
    else if (cScore >= eScore && cScore <= eScore*1.2) {
        star = 1;
    }
    else if(cScore > eScore*1.2 && cScore <= eScore*1.5){
        star = 2;
    }
    else if(cScore > eScore*1.5){
        star = 3;
    }

    return star;
}


//#pragma mark - 动画
/*
 *  精灵动画
 *  s 起始帧， e 结束帧
 */
void GMPublicMethod::setSpriteAnimation(CCSprite *sprite,int s,int e,const char *name,CCObject *pSelectorTarget,SEL_CallFuncN selector)
{
    CCArray *temp = CCArray::create();
    char strName[40] = {0};
    for (int j = s; j <= e; j++) {
        sprintf(strName,"%s%03d.png",name,j);
        CCSpriteFrame *spriteFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(strName);
        temp->addObject(spriteFrame);
    }
    CCAnimation *m_pAnimation = CCAnimation::createWithSpriteFrames(temp,0.1);
    CCAnimate *animate = CCAnimate::create(m_pAnimation);
//    CCRepeatForever *repeateF = CCRepeatForever::create(animate);
    CCCallFuncN *callFuncN = CCCallFuncN::create(pSelectorTarget, selector);
    CCFiniteTimeAction *sequence = CCSequence::create(animate,callFuncN,NULL);
//    sprite->stopAllActions();
    sprite->runAction(sequence);
}

void GMPublicMethod::setSpriteAnimation(CCSprite *sprite,int s,int e,const char *name,float time,CCObject *pSelectorTarget,SEL_CallFuncN selector)
{
    CCArray *temp = CCArray::create();
    char strName[40] = {0};
    for (int j = s; j <= e; j++) {
        sprintf(strName,"%s%03d.png",name,j);
        CCSpriteFrame *spriteFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(strName);
        temp->addObject(spriteFrame);
    }
    CCAnimation *m_pAnimation = CCAnimation::createWithSpriteFrames(temp,time);
    CCAnimate *animate = CCAnimate::create(m_pAnimation);
    //    CCRepeatForever *repeateF = CCRepeatForever::create(animate);
    CCCallFuncN *callFuncN = CCCallFuncN::create(pSelectorTarget, selector);
    CCFiniteTimeAction *sequence = CCSequence::create(animate,callFuncN,NULL);
    //    sprite->stopAllActions();
    sprite->runAction(sequence);
}

/*
 *  循环精灵动画
 *  s 起始帧， e 结束帧
 *  png 文件格式 time = 0.1
 */
void GMPublicMethod::setRepeatAnimation(CCSprite *sprite,int s,int e,const char *name,const char *png,float time,bool isStop)
{
    CCArray *temp = CCArray::create();
    char strName[40] = {0};
    for (int j = s; j <= e; j++) {
        sprintf(strName,"%s%03d.%s",name,j,png);
        CCSpriteFrame *spriteFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(strName);
        temp->addObject(spriteFrame);
    }
    CCAnimation *m_pAnimation = CCAnimation::createWithSpriteFrames(temp,time);
    CCAnimate *animate = CCAnimate::create(m_pAnimation);
    CCRepeatForever *repeateF = CCRepeatForever::create(animate);
//    CCFiniteTimeAction *sequence = CCSequence::create(repeateF,NULL);
    if (isStop) {
        sprite->stopAllActions();
    }
    sprite->runAction(repeateF);
}

/*
 *  计算两点间的角度
 */
double GMPublicMethod::pointToAngle(CCPoint AOrigin, CCPoint APoint, double AEccentricity)
{
    
    if (APoint.x == AOrigin.x){
        if (APoint.y > AOrigin.y){
            return _PI * 0.5;
        }
        else{
            return 180;//_PI * 1.5;
        }
    }
    else if (APoint.y == AOrigin.y){
        if (APoint.x > AOrigin.x){
            return 0;
        } else{
            return _PI;
        }
    }
    else{
        double Result = atan((AOrigin.y - APoint.y) /
                                  (AOrigin.x - APoint.x) * AEccentricity);
        
//        return Result;
//        if ((APoint.x < AOrigin.x) && (APoint.y > AOrigin.y)){
//            return Result + _PI;
//        }else if ((APoint.x < AOrigin.x) && (APoint.y < AOrigin.y)){
//            return Result + _PI;
//        } else if ((APoint.x > AOrigin.x) && (APoint.y < AOrigin.y)){
//            return Result + 2*_PI;
//        }else{
//            return Result;
//        }
        
        float angle = RADIANS_TO_DEGREES( fabs(Result) );
//        CCLOG("%f",angle);
        float cocosAngle;
        if (AOrigin.x==WINSIZE_W/2) {
            cocosAngle = 180;
        }
        else if (AOrigin.x>WINSIZE_W/2) {
            cocosAngle = 180 + ( 90-angle );
        }
        else {
            cocosAngle = 90 + angle;
        }
        return cocosAngle;
    }
}


/*
 *  点与矩形的碰撞检测
 */
bool GMPublicMethod::checkRectContainsPoint( CCRect rect, CCPoint point)
{
    if ( rect.containsPoint(point) ) {
        return true;
    }
    return false;
}


/*
 *  从 tiled map 获取曲线
 */
void GMPublicMethod::getCurveDataFromTiledMap(CCArray *array )
{
    CCTMXTiledMap *pDesertTileMap = CCTMXTiledMap::create("tile/T_Orbit1.tmx");
    //
    CCTMXObjectGroup *objGroup = pDesertTileMap->objectGroupNamed("orbit1");
    char tileMap[30] = {0};
    int j = 1;
    while (objGroup) {
        CCArray *tempArray = CCArray::create();
        char *tempKey=new char[30];//
        int count = objGroup->getObjects()->count();
        for (int i = 0; i < count; i++) {
            memset(tempKey,0,30);
            sprintf(tempKey,"%d",i);
            GMPoint *gmPoint = new GMPoint();
            CCDictionary *spawnPoint = objGroup->objectNamed(tempKey);
            float x = spawnPoint->valueForKey("x")->floatValue();
            float y = spawnPoint->valueForKey("y")->floatValue();
//            int id = spawnPoint->valueForKey("id")->intValue();
//            int start = spawnPoint->valueForKey("start")->intValue();
            int curveNum = spawnPoint->valueForKey("Num")->intValue();
            gmPoint->_point = ccp(x*Scale_X,y*Scale_Y);
//            gmPoint->_id = id;
//            gmPoint->_start = start;
            gmPoint->_curveNum = curveNum;
            
            tempArray->addObject(gmPoint);
            gmPoint->release();
        }
        delete tempKey;
        array->addObject(tempArray);
        j++;
        sprintf(tileMap,"orbit%d",j);
        objGroup = pDesertTileMap->objectGroupNamed(tileMap);
    }
}

/*
 *  从 tiled map 获取鱼阵
 */
void GMPublicMethod::getFishArrayDataFromTiledMap(CCArray *array )
{    
    
    CCTMXTiledMap *pDesertTileMap = CCTMXTiledMap::create("tile/T_FishArray.tmx");
    //
    char tileMap[30] = {0};//
    CCTMXObjectGroup *objGroup = pDesertTileMap->objectGroupNamed("fisharray1");
    int j = 1;
    while (objGroup) {
        char *tempKey=new char[20];//
        CCArray *tempArray = CCArray::create();
        int count = objGroup->getObjects()->count();
        for (int i = 0; i < count; i++) {
            memset(tempKey,0,20);
            sprintf(tempKey,"%d",i+1);
            GMPoint *gmPoint = new GMPoint();
            CCDictionary *spawnPoint = objGroup->objectNamed(tempKey);
            float x = spawnPoint->valueForKey("x")->floatValue();
            float y = spawnPoint->valueForKey("y")->floatValue();
            int id = spawnPoint->valueForKey("id")->intValue();
            gmPoint->_point = ccp(x*Scale_X,y*Scale_Y);
            gmPoint->_id = id;
//            gmPoint->_t_row = spawnPoint->valueForKey("t_row")->intValue();
//            gmPoint->_t_columns = spawnPoint->valueForKey("t_columns")->intValue();
//            gmPoint->_e_row = spawnPoint->valueForKey("e_row")->intValue();
//            gmPoint->_e_columns = spawnPoint->valueForKey("e_columns")->intValue();
            gmPoint->_time = spawnPoint->valueForKey("time")->floatValue();
            gmPoint->_row = spawnPoint->valueForKey("row")->intValue();
//            gmPoint->_columns = spawnPoint->valueForKey("row1")->intValue();
            tempArray->addObject(gmPoint);
            gmPoint->release();
        }
        delete tempKey;
        j++;
        sprintf(tileMap,"fisharray%d",j);
        objGroup = pDesertTileMap->objectGroupNamed(tileMap);
        array->addObject(tempArray);
    }
}

//#pragma mark - goods 
void GMPublicMethod::readGoodsListFromFile(const char *fileName,CCArray *arrar)
{
    CCAutoreleasePool* pPool = new CCAutoreleasePool();
    CCDictionary *productsDic = CCDictionary::createWithContentsOfFile(fileName);
    char key[30] = {0};
    if (productsDic && productsDic->count()>0) {
        for (int i = 0; i < productsDic->count(); i ++) {
            sprintf(key,"goods%d",i+1);
            CCDictionary*tempE = (CCDictionary*)productsDic->objectForKey(key);
            GMGoods *goods = new GMGoods();
            goods->setValue(tempE);
            arrar->addObject(goods);
            goods->release();
        }
    }
    pPool->release();
}

//#pragma mark - APromptList
void GMPublicMethod::getAchievementPrompFromFile(const char *fileName,CCArray *arrar)
{
    CCAutoreleasePool* pPool = new CCAutoreleasePool();
    CCDictionary *productsDic = CCDictionary::createWithContentsOfFile(fileName);
    char key[30] = {0};
    if (productsDic && productsDic->count()>0) {
        for (int i = 0; i < productsDic->count(); i ++) {
            sprintf(key,"achievement%d",i);
            CCDictionary*tempE = (CCDictionary*)productsDic->objectForKey(key);
            GMAchievement *achievement = new GMAchievement();
            achievement->setValue(tempE);
            arrar->addObject(achievement);
            achievement->release();
        }
    }
    pPool->release();
}

//#pragma mark -  GMStrange

void GMPublicMethod::setHitValue(int strangeId)
{
    bool isExist = false;
    for (int i = 0; i < hitArray->count(); i++) {
        GMStrange *strange = (GMStrange*)hitArray->objectAtIndex(i);
        if (strange->_strange_id == strangeId) {
            strange->_countNum++;
//            ZPLog("记录数目 怪物id: %d 、击中数目: %d",strange->_strange_id,strange->_countNum);
            hitArray->replaceObjectAtIndex(i,strange);
            isExist = true;
            break;
        }
    }
    
    if (!isExist) {
        GMStrange *strange = new GMStrange();
        strange->_strange_id = strangeId;
        strange->_countNum++;
        
        hitArray->addObject(strange);
        strange->release();
    }
}

int GMPublicMethod::getHitNum(){
    if (hitArray<=0) {
        return 0;
    }
    return hitArray->count();
}

GMStrange* GMPublicMethod::getHitStrange(int index){
    if (hitArray<=0) {
        return NULL;
    }
    GMStrange *strange = (GMStrange*)hitArray->objectAtIndex(index);
    return strange;
}

void GMPublicMethod::cleanHitArray()
{
    hitArray->removeAllObjects();
}


/*
 *  angle:当前鱼的角度
 *  r0:离中心点的距离（有正反）r1:鱼的半径（宽） r2:子弹的半径（宽） p1:鱼的位置  p2:子弹的位置
 */
bool GMPublicMethod::getCollisionValue(float angle,int r0,float r1,float r2,CCPoint p1, CCPoint p2)
{
    float a = DADIANS_TO_DEGREES1(angle);
    float tempx = sinf(a)*r0;
    float tempy = cosf(a)*r0;
    float tempX = p1.x;
    float tempY = p1.y;
    //1
    CCPoint point = ccp(tempX+tempx,tempY+tempy);
    float maxCollisionDistance = r1 + r2;
    float actualDistance = ccpDistance(point, p2);
    if (actualDistance < maxCollisionDistance) {
        return true;
    }
    return false;
}

/*
 *  获取送金币时间
 */
long GMPublicMethod::getTime()
{
    struct cc_timeval now;
    CCTime::gettimeofdayCocos2d(&now, NULL);
    //    struct tm * tm;
    //    tm = localtime(&now.tv_sec);
    //    int year = tm->tm_year + 1900;
    //    int month = tm->tm_mon + 1;
    //    int day = tm->tm_mday;
    //    int hour = tm->tm_hour;
    //    int min = tm->tm_min;
    //    int sec = tm->tm_sec;
    //    ZPLog("(%ld== %ld)%d-%d-%d-%d-%d-%d",now.tv_sec,now.tv_usec,year,month,day,hour,min,sec);
    return now.tv_sec;
}

void GMPublicMethod::getGoldCoinsTime()
{
    long oldTime = GMAccessData::sharedAccessData()->getGoldCoinsTime();
    if (oldTime != 0){
        int time = GMPublicMethod::getTime()-oldTime;
        int times = time/60;
        int allMoney = GMAccessData::sharedAccessData()->getTotalMoneyNum();
        if (allMoney < 200) {
            int goldCoins = times*10;
            if (goldCoins >= 200) {
                goldCoins = 200;
            }
            allMoney = allMoney+goldCoins;
            GMAccessData::sharedAccessData()->saveTotalMoneyNum(allMoney);
        }
    }
}
/*
 *  获取随机曲线点
 */
ccBezier GMPublicMethod::getRandCurveBezier()
{
    float x = 0.0f;
    float y = 0.0f;
    ccBezier tempBezier;
    float tempH = 186*Scale_X/2;
    //    if (rand()%2 == 0)
    {
        switch (rand()%6) {
            case 0:{
                x = -tempH;
                y = rand()%(int)WINSIZE_H;
                tempBezier._sp = ccp(x,y);
                x = WINSIZE_W*2/5+rand()%(int)(WINSIZE_W/5);
                y = rand()%(int)(WINSIZE_H-100*Scale_X) + 100*Scale_X-tempH;
                tempBezier._p2 = ccp(x,y);
                x = WINSIZE_W+tempH;
                y = rand()%(int)(WINSIZE_H);
                tempBezier._ep = ccp(x,y);
            } break;
            case 1:{
                x = -tempH;
                y = rand()%(int)WINSIZE_H;
                tempBezier._ep = ccp(x,y);
                x = WINSIZE_W*2/5+rand()%(int)(WINSIZE_W/5);
                y = rand()%(int)(WINSIZE_H-100*Scale_X) + 100*Scale_X-tempH;
                tempBezier._p2 = ccp(x,y);
                x = WINSIZE_W+tempH;
                y = rand()%(int)(WINSIZE_H);
                tempBezier._sp = ccp(x,y);
            } break;
            case 2:{
                x = -tempH;
                y = rand()%(int)WINSIZE_H;
                tempBezier._sp = ccp(x,y);
                x = WINSIZE_W*2/5+rand()%(int)(WINSIZE_W/5);
                y = rand()%(int)(WINSIZE_H-150*Scale_X) + 150*Scale_X-tempH;
                tempBezier._p2 = ccp(x,y);
                x = rand()%(int)(WINSIZE_W);
                y = (rand()%2==0 ? -tempH : (WINSIZE_H+tempH));
                tempBezier._ep = ccp(x,y);
            }   break;
            case 3:{
                x = WINSIZE_W+tempH;
                y = rand()%(int)WINSIZE_H;
                tempBezier._sp = ccp(x,y);
                x = WINSIZE_W*2/5+rand()%(int)(WINSIZE_W/5);
                y = rand()%(int)(WINSIZE_H-150*Scale_X) + 150*Scale_X-tempH;
                tempBezier._p2 = ccp(x,y);
                x = rand()%(int)(WINSIZE_W);
                y = (rand()%2==0 ? -tempH : (WINSIZE_H+tempH));
                tempBezier._ep = ccp(x,y);
            }   break;
            case 4:{
                x = -tempH;
                y = rand()%(int)WINSIZE_H;
                tempBezier._sp = ccp(x,y);
                x = WINSIZE_W/3;
                y = rand()%(int)(WINSIZE_H-150*Scale_X) + 150*Scale_X-tempH;
                tempBezier._p1 = ccp(x,y);
                x = WINSIZE_W*2/3;
                y = rand()%(int)(WINSIZE_H-150*Scale_X) + 150*Scale_X-tempH;
                tempBezier._p2 = ccp(x,y);
                x = WINSIZE_W+tempH;
                y = (rand()%2==0 ? -tempH : (WINSIZE_H+tempH));
                tempBezier._ep = ccp(x,y);
            }   break;
            case 5:{
                x = WINSIZE_W+tempH;
                y = rand()%(int)WINSIZE_H;
                tempBezier._sp = ccp(x,y);
                x = WINSIZE_W*2/3;
                y = rand()%(int)(WINSIZE_H-150*Scale_X) + 150*Scale_X-tempH;
                tempBezier._p1 = ccp(x,y);
                x = WINSIZE_W/3;
                y = rand()%(int)(WINSIZE_H-150*Scale_X) + 150*Scale_X-tempH;
                tempBezier._p2 = ccp(x,y);
                x = -tempH;
                y = (rand()%2==0 ? -tempH : (WINSIZE_H+tempH));
                tempBezier._ep = ccp(x,y);
            }   break;
            default:
                break;
        }
    }
    return tempBezier;
}

//#pragma mark - 
//#pragma mark 倍率模式
/*
 *  index 为-1 和 1
 */
void GMPublicMethod::setCurrentMagnificationModel(int index)
{
    int temp1 = GMAccessData::sharedAccessData()->getCurrentMagnificationModel();
    int temp2 = GMAccessData::sharedAccessData()->getMagnificationModel();
    ZPLog("开启的倍率 数 %d",temp2);
    temp1 += index;
    
    if (temp1 > temp2) {
        temp1 = 1;
    }
    if (temp1 <= 1) {
        temp1 = 1;
    }
    GMAccessData::sharedAccessData()->saveCurrentMagnificationModel(temp1);
}

int GMPublicMethod::getMagnificationModel(int index)
{
    int temp1 = 1;
    switch (index) {
        case 1:{
            temp1 = 1;
        }   break;
        case 2:{
            temp1 = 2;
        }   break;
        case 3:{
            temp1 = 3;
        }   break;
        case 4:{
            temp1 = 5;
        }   break;
        case 5:{
            temp1 = 10;
        }   break;
        default:
            break;
    }
//    if (index == 1) {
//        temp1 = 1;
//    }
//    else if(index == 2){
//        temp1 = 2;
//    }
//    else if(index == 3){
//        temp1 = 3;
//    }
//    else if(index == 4){
//        temp1 = 5;
//    }
//    else if(index == 5){
//        temp1 = 10;
//    }
    return temp1;
}


int GMPublicMethod::getOpenMagnificationModel()
{
    int temp1 = GMAccessData::sharedAccessData()->getMagnificationModel();
//    if (temp1 == 1) {
//        temp1 = 1;
//    }
//    else if(temp1 == 2){
//        temp1 = 2;
//    }
//    else if(temp1 == 3){
//        temp1 = 3;
//    }
//    else if(temp1 == 4){
//        temp1 = 5;
//    }
//    else if(temp1 == 5){
//        temp1 = 10;
//    }
    int temp2 = GMPublicMethod::getMagnificationModel(temp1);
    return temp2;
}

int GMPublicMethod::getChooseMagnificationModel()
{
    //1,2,3,5,10
    int temp1 = GMAccessData::sharedAccessData()->getCurrentMagnificationModel();
    int temp2 = GMPublicMethod::getMagnificationModel(temp1);
//    if (temp1 == 1) {
//        temp1 = 1;
//    }
//    else if(temp1 == 2){
//        temp1 = 2;
//    }
//    else if(temp1 == 3){
//        temp1 = 3;
//    }
//    else if(temp1 == 4){
//        temp1 = 5;
//    }
//    else if(temp1 == 5){
//        temp1 = 10;
//    }
    return temp2;
}

int GMPublicMethod::getChooseMagnificationModel1()
{
    //1,2,3,5,10
    int temp1 = GMAccessData::sharedAccessData()->getCurrentMagnificationModel();
    int temp2 = 1;
    if (temp1 == 1) {
        temp2 = 40;
    }
    else if(temp1 == 2){
        temp2 = 35;
    }
    else if(temp1 == 3){
        temp2 = 30;
    }
    else if(temp1 == 4){
        temp2 = 25;
    }
    else if(temp1 == 5){
        temp2 = 20;
    }
    return temp2;
}


//#pragma mark -
void GMPublicMethod::setPhoneNumber(const char *text)
{
    CC_SAFE_DELETE(m_pPhoneNumber);
    
    if (text){
        m_pPhoneNumber = new std::string(text);
    }
    else{
        m_pPhoneNumber = new std::string;
    }
}

const char* GMPublicMethod::getPhoneNumber()
{
    return m_pPhoneNumber->c_str();
}

//#pragma mark -
void GMPublicMethod::showTipView(CCNode *node ,const char*text){
//    CC_SAFE_DELETE(tipLabelTTF);
//    if(tipLabelTTF)
    {
        tipSpriteBg = CCSprite::create("91jifei/jifei008.png");
        tipSpriteBg->setPosition(ccp(WINSIZE_W/2, WINSIZE_H/2));
        node->addChild(tipSpriteBg,1000);
        //"Verdana-Bold"
        tipLabelTTF = CCLabelTTF::create(text, "Marker Felt", 20,CCSize(230,30), kCCTextAlignmentCenter);
        tipLabelTTF->setAnchorPoint(ccp(0, 0));
        tipLabelTTF->setPosition( ccp( 2, 2));
        tipLabelTTF->setColor(ccWHITE);
        tipSpriteBg->addChild(tipLabelTTF);
        SetScale2(tipSpriteBg, Scale_X);
    }
}
void GMPublicMethod::removeTipView(CCNode *node){
    node->removeChild(tipSpriteBg, true);
    tipSpriteBg = NULL;
}

/*
 *  获取
 */
bool GMPublicMethod::getChangeTime(int year,int mon,int day)
{
    GMBillingModel billingModel = GMPublicMethod::sharedPublicMethod()->getBillingModel();
    if(billingModel!=B_TengXunBilling)
        return true;
    
    struct cc_timeval now;
    CCTime::gettimeofdayCocos2d(&now, NULL);
    struct tm * tm;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)  
	//win32平台
	time_t timep; 
	time(&timep); 
	tm = localtime(&timep);
#else 
	//android、ios平台
	tm = localtime(&now.tv_sec);
#endif
    int m_year = tm->tm_year + 1900;
    int m_month = tm->tm_mon + 1;
    int m_day = tm->tm_mday;
    
    ZPLog("(%ld== %ld)%d-%d-%d",now.tv_sec,now.tv_usec,m_year,m_month,m_day);
    if(m_year > year){
        return true;
    }
    else if(m_month > mon || (m_month == mon && m_day >= day)){
        return true;
    }
    return false;
}




