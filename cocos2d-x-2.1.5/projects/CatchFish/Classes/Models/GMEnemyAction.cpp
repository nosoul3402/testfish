//
//  GMEnemyAction.cpp
//  FishX
//
//  Created by peng on 13-1-7.
//
//

#include "GMEnemyAction.h"
#include "GMPoint.h"
#include "../PublicModels/CCLagrange.h"
#include "../Config/GMHeaderConfig.h"
#include "../PublicModels/CCLagrangeConfig.h"
#include "../Layer/GMGameLayer.h"

//static ccBezier ccbezier[10];
//static char fishName[40] = {0};

//const int GMEnemyAction::_animationFrames[][3] = {
//    { 4, 8, 0},//1
//    { 4, 4, 0},//2
//    { 4, 4, 0},//3
//    { 8, 4, 0},//4
//    { 4, 4, 0},//5
//    { 8, 4, 0},//6
//    { 6, 4, 0},//7
//    { 7, 4, 0},//8
//    {16, 4, 0},//9
//    { 8, 4, 0},//10
//    { 4, 3, 4},//11
//    { 7, 7, 7},//12
//    { 4, 4, 7},//13
//    { 8, 2, 7},//14
//    { 8,10, 0},//15
//    { 8, 0, 0}//16
//};

bool GMEnemyAction::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCSprite::init() )
    {
        return false;
    }
    
    return true;
}

//#pragma mark - 初始
GMEnemyAction::GMEnemyAction(void)
{
//    initValue();
	curveNum = 0;
	countNum = 0;
}

GMEnemyAction* GMEnemyAction::createEnemyName(const char *name)
{
    GMEnemyAction *enemy = (GMEnemyAction*)CCSprite::create(name);
    enemy->initValue();
    return enemy;
}

GMEnemyAction* GMEnemyAction::createEnemyFrameName(const char *name)
{
    GMEnemyAction *enemy = (GMEnemyAction*)CCSprite::createWithSpriteFrameName(name);
    enemy->initValue();
    return enemy;
}

GMEnemyAction* GMEnemyAction::createEnemyFrame(CCSpriteFrame *frame)
{
    GMEnemyAction *enemy = (GMEnemyAction*)CCSprite::createWithSpriteFrame(frame);
    enemy->initValue();
    return enemy;
}

void GMEnemyAction::setInitTheseProperties(CCObject *target, GMEnemy *enemy,float sacle)
{
    setDelegate(target);
    if (enemy) 
        setValue(enemy);
    char fishName[20] = {0};
    sprintf(fishName,"yu%02d%s%03d.png",_id,"a",1);
    this->initWithSpriteFrameName(fishName);
    this->setScale(sacle);
    this->setPosition(ccp(100, 200));
    setEnemyAnimation(true, "a");
//    CCRotateBy *rotate = CCRotateBy::create(0.2, 30);
//    CCRepeatForever *repeateF = CCRepeatForever::create(rotate);
//    this->runAction(repeateF);

}

void GMEnemyAction::setRandEnemyValue(CCObject *target, GMEnemy *enemy,float sacle)
{
//    _delegate = target;
//    setValue(enemy);
//    char fishName[40] = {0};
//    sprintf(fishName,"yu%02d%s%03d.png",_id,"a",1);
//    this->initWithSpriteFrameName(fishName);
//    this->setScale(sacle);
//    this->setPosition(ccp(100, 200));
//    setEnemyAnimation(true, "a");
    setInitTheseProperties(target,enemy,sacle);
//    randDirection();
}

void GMEnemyAction::setCurveValue(CCObject *target,GMEnemy *enemy,CCPoint point,CCArray*array ,int direction, int row, float delay,float sacle )
{
//    _delegate = target;
//    char fishName[40] = {0};
//    setValue(enemy);
//    sprintf(fishName,"yu%02d%s%03d.png",_id,"a",1);
//    this->initWithSpriteFrameName(fishName);
//    this->setPosition(point);
//    this->setScale(sacle);
//    if (direction==1) {
//        this->setPosition(ccp(-100, -100));
//    }
//    else if(direction == 2){
//        this->setPosition(ccp(WINSIZE_W + 100, -100));
//    }
//   
//    setEnemyAnimation(true, "a");
    setInitTheseProperties(target,enemy,sacle);
    if (direction==1) {
        this->setPosition(ccp(-100, -100));
    }
    else if(direction == 2){
        this->setPosition(ccp(WINSIZE_W + 100, -100));
    }
    this->setRotation(90);
    setBezier(array,direction,row,delay);
//    allEnemyArray->addObject(this);
//    layer->addChild(this);
    
}

void GMEnemyAction::setInitValue()
{
    initValue();
}

void GMEnemyAction::initValue()
{
    setAttackTime(0);
    
	isSpeed				= false;
    _isCatch			= false;
    isRotationAndMove	= false;
	_isShootBullet		= false;
	isCheckRandEnemy	= false;
//    color3b = this->getColor();
    setFrozen(false);
    
	movex			= 0;
	movey			= 0;
	countNum		= 0;
	curveNum		= 0;
    _checkTime		= 0;
	_countAttackTime= 0;
	_direction		= 0;
	_row 			= 0;
	
	rotationAngle = 0.0f;

    _enemyStatus = S_NONE;

    pointArray  = NULL;
    curveAction = NULL;
    enemySpeed  = NULL;
    setRouteStatus(R_NONE);
}

void GMEnemyAction::setAttackTime(int t)
{
    if (t==0) {
        _countAttackTime = t;
    }
    else {
        _countAttackTime += t;
    }
//    ZPLog("%d",_countAttackTime);
}


//#pragma mark - 动画
/*
 *  name : a(游动)、b(死亡)、c(攻击)
 *  index : 0、1、2  动作帧数索引 
 *  repeat : 为 true 时重复播放动作 
 */
void GMEnemyAction::setAnimation(const char *name,int index,float time,bool repeat,CCObject* target, SEL_CallFuncN selector)
{
    CCArray *temp = CCArray::create();
    int num = GMPublicMethod::_animationFrames[_id-1][index];
    for (int j = 1; j <= num; j++) {
//        sprintf(fishName,"yu%02d%s%03d.png",_id,name,j);
//        std::string = "yu%02d"+_id+name+"%03d.png";
        CCString *string = CCString::createWithFormat("yu%02d%s%03d.png",_id,name,j);
        CCSpriteFrame *spriteFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(string->getCString());
        temp->addObject(spriteFrame);
    }
    CCAnimation *m_pAnimation = CCAnimation::createWithSpriteFrames(temp,time);
    CCAnimate *animate = CCAnimate::create(m_pAnimation);
    CCFiniteTimeAction *sequence = NULL;
    if (repeat) {
        CCRepeatForever *repeateF =  CCRepeatForever::create(animate);
        sequence = CCSequence::create(repeateF,NULL);
    }
    else{//this, callfuncN_selector(GMEnemyAction::removeObject)
        CCCallFuncN *callFunc = CCCallFuncN::create(target, selector);
        sequence = CCSequence::create(animate,callFunc,NULL);
    }
    sequence->setTag(animation_tag1);
    this->stopAllActions();
    this->runAction(sequence);
}
/*
 *  游动动作
 */
void GMEnemyAction::setEnemyAnimation(bool cache,const char *name)
{
    _enemyStatus = S_Move;
    setAnimation(name, 0, 0.15,true, NULL, NULL);
}
/*
 *  死亡动作
 */
void GMEnemyAction::setDeathAnimation()
{
    this->stopAllActions();
    _enemyStatus = S_Death;
    this->setColor(ccc3(255,255,255));
    setAnimation("b", 1, 0.15,false, this, callfuncN_selector(GMEnemyAction::enemyDeathAfter));
}

void GMEnemyAction::enemyDeathAfterNoPara()
{
	/*GMEnemyAction *enemyAction = (GMEnemyAction *)pNode;
	GMGameLayer *temp = (GMGameLayer*)_delegate;
	temp-> enemyDeath(this);*/
}

void GMEnemyAction::enemyDeathAfter(CCNode *pNode)
{
	GMEnemyAction *enemyAction = (GMEnemyAction *)pNode;
    GMGameLayer *temp = (GMGameLayer*)_delegate;
    temp-> enemyDeath(this);
}
/*
 *  攻击动作
 */
void GMEnemyAction::setAttackAnimation(const char *name,CCObject* target, SEL_CallFuncN selector)
{
    this->stopAllActions();
    _enemyStatus = S_Attack;
    this->setColor(ccc3(255,255,255));
    setAnimation(name, 2, 0.15,false, target, selector);
}


//#pragma mark - 路线

ccBezier GMEnemyAction::getBezier(CCPoint p1,CCPoint p2,CCPoint p3)
{
    ccBezier ccb;
    ccb._sp = p1;
    ccb._p1 = ccb._sp;
    ccb._p2 = p2;
    ccb._ep = p3;
    return ccb;
}

void GMEnemyAction::setBezier(CCArray*array ,int direction, int row, float delay)
{
    if (array->count()<=0) {
        return;
    }

    curveNum = ((GMPoint*)array->objectAtIndex(0))->_curveNum;
    countNum = 0;
    _direction = direction;
    _row = row;
    pointArray = array;
    pointArray->retain();
    
    this->scheduleOnce(schedule_selector(GMEnemyAction::addCurveMoveAtion), delay);
}

//float GMEnemyAction::getAngle1(CCPoint p1,CCPoint p2)
//{
//    CCPoint vector = ccpSub( p1,p2);
//    float mAngle = ccpToAngle(vector);
//    float cocosAngle = RADIANS_TO_DEGREES(mAngle);
//    float angle;
//    if (cocosAngle<0) {
//        angle = -(90+cocosAngle);
//    }
//    else if (cocosAngle>0){
//        angle = 90 - cocosAngle;
//    }
//    return angle;
//}

void GMEnemyAction::addCurveMoveAtion(float dt)
{
    if (_direction == 2) {
        int j = 0;
        for (int i = curveNum-1; i >= 0; i--) {
            CCPoint p1, p2, p3;
            int index = 2+i*2;
            p1 = ((GMPoint*)pointArray->objectAtIndex(index))->_point;
            index = 1+i*2;
            p2 = ((GMPoint*)pointArray->objectAtIndex(index))->_point;
            index = 0+i*2;
            p3 = ((GMPoint*)pointArray->objectAtIndex(index))->_point;
            ccbezier[j] = getBezier(p1, p2, p3);
            j++;
        }
    }
    else if (_direction == 1){
        for (int i = 0; i < curveNum; i++) {
            CCPoint p1, p2, p3;
            int index = 0+i*2;
            p1 = ((GMPoint*)pointArray->objectAtIndex(index))->_point;
            index = 1+i*2;
            p2 = ((GMPoint*)pointArray->objectAtIndex(index))->_point;
            index = 2+i*2;
            p3 = ((GMPoint*)pointArray->objectAtIndex(index))->_point;
            ccbezier[i] = getBezier(p1, p2, p3);
        }
    }

    float tempH = (_row-1)*35*Scale_Y;
    
    ccLagrangeConfig *m_config = new ccLagrangeConfig[curveNum];//[curveNum];
    CCLagrange **a = new CCLagrange*[curveNum];//[curveNum];

    for (int i = 0; i < curveNum; i++) {
        a[i] = NULL;
    }

    for (int i = 0; i < curveNum; i ++) {
        m_config[i] = wylcQuad(ccbezier[i]._sp.x,
                               ccbezier[i]._sp.y-tempH,
                               ccbezier[i]._ep.x,
                               ccbezier[i]._ep.y-tempH,
                               ccbezier[i]._p2.x,
                               ccbezier[i]._p2.y-tempH);
        if (curveNum == 1) {
            a[i] = CCLagrange::create(13, m_config[i]);
        }
        else if (curveNum == 2){
            a[i] = CCLagrange::create(7, m_config[i]);
        }
        else if (curveNum == 3){
            a[i] = CCLagrange::create(6, m_config[i]);
        }
        else if (curveNum == 7){
            a[i] = CCLagrange::create(4, m_config[i]);
        }
        a[i]->setAutoRotate(true, 90);
    }

    CCCallFunc *callFunc = CCCallFunc::create(this, callfunc_selector(GMEnemyAction::enemyDeathAfterNoPara));
    curveAction = NULL;
    
    CCArray *arrayOfActions = CCArray::create();
    
    for (int i = 0; i < curveNum; i++) {
        if (a[i]) {
            arrayOfActions->addObject(a[i]);
        }
        else{
            break;
        }
    }

    arrayOfActions->addObject(callFunc);
//    if (curveNum == 1) {
//        curveAction = CCSequence::create(a[0],callFunc,NULL);
//    }
//    else if (curveNum == 2) {
//        curveAction= CCSequence::create(a[0],a[1],callFunc,NULL);
//    }
//    else if (curveNum == 3) {
//        curveAction= CCSequence::create(a[0],a[1],a[2],callFunc,NULL);
//    }
//    else if(curveNum == 7){
//        curveAction= CCSequence::create(a[0],a[1],a[2],a[3],a[4],a[5],a[6],callFunc,NULL);
//    }
    curveAction= CCSequence::create(arrayOfActions);
    curveAction->setTag(move_tag1);
    //curveAction->retain();
    this->runAction(curveAction);
}

void GMEnemyAction::stopCurveAtion()
{
    if (curveAction) {
        if (_isCatch == false) {
            if (enemySpeed && _routeStatus == R_RandCurve) {
                this->stopAction(enemySpeed);
                enemySpeed->release();
                enemySpeed = NULL;
            }
            this->stopAction(curveAction);
            curveAction = NULL;
            setRouteStatus(R_Rand);
            _angle = 10;
            _time = 2;
        }
    }
}

void GMEnemyAction::pauseCurveAtion()
{
    this->pauseSchedulerAndActions();
}

void GMEnemyAction::resumeCurveAtion()
{
    this->resumeSchedulerAndActions();
}

//#pragma mark - 随机鱼阵
/*
 *  随机3个点或4个点
 */
void GMEnemyAction::setRandCurvePoint(GMEnemy *enemy,CCObject *target,ccBezier bezier,int row,float delay,float sacle)
{
    this->setRouteStatus(R_RandCurve);
    this->setValue(enemy);
    char fishName[30];
    sprintf(fishName,"yu%02d%s%03d.png",_id,"a",1);
    this->initWithSpriteFrameName(fishName);
    this->setDelegate(target);
    randCurveBezier = bezier;
    this->setPosition(randCurveBezier._sp);
    setEnemyAnimation(true, "a");
    this->setScale(sacle);
    _row = row;    
    this->scheduleOnce(schedule_selector(GMEnemyAction::setRandCurveMove), delay);
}

void GMEnemyAction::setRandCurveMove(float dt)
{
    CCAutoreleasePool* pPool = new CCAutoreleasePool();
    
    ccLagrangeConfig m_configRandCurve;

    float tempH = (_row-1)*45*Scale_Y;
    
    if (randCurveBezier._p1.x == 0) {
        m_configRandCurve = wylcQuad(randCurveBezier._sp.x,
                                     randCurveBezier._sp.y-tempH,
                                     randCurveBezier._ep.x,
                                     randCurveBezier._ep.y-tempH,
                                     randCurveBezier._p2.x,
                                     randCurveBezier._p2.y-tempH);
    }
    else {
        m_configRandCurve = wylcCubic(randCurveBezier._sp.x,
                                     randCurveBezier._sp.y-tempH,
                                     randCurveBezier._ep.x,
                                     randCurveBezier._ep.y-tempH,
                                     randCurveBezier._p1.x,
                                     randCurveBezier._p1.y-tempH,
                                     randCurveBezier._p2.x,
                                     randCurveBezier._p2.y-tempH);
    }
    
    float c =  (randCurveBezier._sp.x-randCurveBezier._ep.x)*(randCurveBezier._sp.x-randCurveBezier._ep.x)+(randCurveBezier._sp.y-randCurveBezier._ep.y)*(randCurveBezier._sp.y-randCurveBezier._ep.y);
    float cc = (sqrtf(c));
    cc = cc/100+10;
    CCLagrange *m_pCCLagrange = CCLagrange::create(cc, m_configRandCurve);
    m_pCCLagrange->setAutoRotate(true, 90);

    CCCallFunc *callFunc = CCCallFunc::create(this, callfunc_selector(GMEnemyAction::enemyDeathAfterNoPara));
    CCActionInterval *randSequence = (CCActionInterval*)CCSequence::create(m_pCCLagrange,callFunc,NULL);
    randSequence->setTag(move_tag1);
    enemySpeed = CCSpeed::create(randSequence, 1);
    if (enemySpeed) {
        enemySpeed->retain();
        this->runAction(enemySpeed);
    }
    
    pPool->release();
}

//#pragma mark - 随机移动
void GMEnemyAction::randDirection(){
    CCPoint startPoint;
    float tempx = 0.0f;
    float tempy = 0.0f;
    
    int d = rand()%4+1;
//    if(_unRemoveTheScreen){
//        d = 2;
//    }
    
    //ccp(WINSIZE_W/2, WINSIZE_H/2);
    if (d == D_LEFT) {
        tempy = rand()%(int)WINSIZE_H;
        startPoint = ccp(-Get_H(Get_Box(this))/2, tempy);
        direction = D_LEFT;
        this->setRotation(90);
    }
    else if(d == D_RIGHT){
        tempy = rand()%(int)WINSIZE_H;
        startPoint = ccp(WINSIZE_W+Get_H(Get_Box(this))/2, tempy);
        direction = D_RIGHT;
        this->setRotation(-90);
    }
    else if(d == D_UP){
        tempx = rand()%(int)WINSIZE_W;
        startPoint = ccp(tempx, WINSIZE_H+Get_H(Get_Box(this))/2);
        this->setRotation(180);
        direction = D_UP;
    }
    else if(d == D_DOWN){
        int space = WINSIZE_W/2-111*Scale_X;//222/2
        tempx = rand()%2 == 0 ? rand()%space : WINSIZE_W/2+111*Scale_X+rand()%space;
        startPoint = ccp(tempx, -Get_H(Get_Box(this))/2);
        direction = D_UP;
    }
    
    this->setPosition(startPoint);
    isCheckRandEnemy = false;
    randRotationMove();
    //2013-3-28晚上调试注销
//    randRotationAngle();
}

//void GMEnemyAction::randRotationAngle()
//{
//    float s = 1.5;//50;//_speed*_time; //10*2;
//    int d = 1;
//    if (rand()%2==0) {
//        d = 1;
//    }
//    else {
//        d = -1;
//    }
//    int ta = rand()%_angle;
//    rotationAngle = this->getRotation()+ta*d;
//    if (_unRemoveTheScreen && this->_checkTime == 5)
//    {
//        CCPoint oldP = this->getPosition();
//        if (oldP.x <= 0) {
//            rotationAngle = rand()%180;
//        }
//        else if (oldP.x >= WINSIZE_W) {
////            int n = rand()%3;
////            if (n == 0) {
////                rotationAngle = rand()%45;
////            }
////            else if(n == 1){
////                rotationAngle = rand()%180+136;
////            }
////            else if(n == 2)
//            {
//                rotationAngle = -rand()%180;
//            }
//        }
//        else if(oldP.y <= 0){
//            if (rand()%2==0) {
//                d = 1;
//            }
//            else {
//                d = -1;
//            }
//            rotationAngle = (rand()%90)*d;
//        }
//        else if(oldP.y >= WINSIZE_H){
//            if (rand()%2==0) {
//                d = 1;
//            }
//            else {
//                d = -1;
//            }
//            rotationAngle = (rand()%135+45)*d;
//        }
//    }
//    
//    float a = DADIANS_TO_DEGREES1(rotationAngle);//_angle*M_PI/180; //RADIANS_TO_DEGREES(_angle);
//    float tempx = sinf(a)*s;
//    float tempy = cosf(a)*s;
//    CCRotateTo *rotateAction = CCRotateTo::create(0.01, rotationAngle);
//    this->runAction(rotateAction);
//    if (_id == 16) {
//        tempy+=1;
//    }
//    _moveV = ccp(tempx,tempy);
//}

//void GMEnemyAction::toMoveBetweenTwoPoints()
//{
//    CCPoint oldP = this->getPosition();
//    if (_unRemoveTheScreen && this->_checkTime == 5) {
//       
//        if (oldP.x <= 0) {
//            ZPLog("1 %f",this->getRotation());
//            randRotationAngle();
//        }
//        else if( oldP.x >= WINSIZE_W){
//            randRotationAngle();
//            ZPLog("2 %f",this->getRotation());
//        }
//        else if( oldP.y <= 0){
//            randRotationAngle();
//            ZPLog("3 %f",this->getRotation());
//        }
//        else if( oldP.y >= WINSIZE_H){
//            randRotationAngle();
//            ZPLog("4 %f",this->getRotation());
//        }
//    }
//    
//    CCPoint newP = ccpAdd(oldP, _moveV);
//    this->setPosition(newP);
//    
//}

void GMEnemyAction::randRotationMove()
{
    float s = 100;
    CCAutoreleasePool* pPool = new CCAutoreleasePool();
    
    int d = 1;
    if (rand()%2==0) {
        d = 1;
    }
    else {
        d = -1;
    }
    int ta = rand()%_angle;
    rotationAngle = this->getRotation()+ta*d;
    if (enemySpeed) {
        this->unschedule(schedule_selector(GMEnemyAction::setSpeedOfRecovery));
        //this->unschedule(schedule_selector(GMEnemyAction::randRotationMove));
        this->stopAction(enemySpeed);
        enemySpeed->release();
        enemySpeed = NULL;
    }
    float a = DADIANS_TO_DEGREES1(rotationAngle);
    float tempx = sinf(a)*s;
    float tempy = cosf(a)*s;
//    this->setRotation(rotationAngle);
    if (_id == 16) {
        tempy+=1;
    }
    
    _moveV = ccp(tempx,tempy);
    CCPoint newP = ccpAdd(this->getPosition(), _moveV);
    float c =  (WINSIZE_W/2)*(WINSIZE_W/2)+WINSIZE_H*WINSIZE_H;
    float cc = (sqrtf(c));
    
    CCPoint shootVector = ccpSub(newP, this->getPosition());
    CCPoint normalizedShootVector = ccpNormalize(shootVector);
    CCPoint overshotVector = ccpMult(normalizedShootVector, cc);
    CCPoint offscreenPoint = ccpAdd(this->getPosition(), overshotVector);
    
    float tempTime = (_id == 16) ? 5 : 10.0f+_speed;
    CCRotateTo *rotateTo = CCRotateTo::create(0.02, rotationAngle);
    CCMoveTo *moveTo = CCMoveTo::create(tempTime,offscreenPoint);
    CCCallFunc *callFunc = CCCallFunc::create(this, callfunc_selector(GMEnemyAction::randRotationMove));
    CCActionInterval *randSequence = (CCActionInterval*)CCSequence::create(rotateTo,moveTo,callFunc,NULL);
    enemySpeed = CCSpeed::create(randSequence, 1);
    enemySpeed->retain();
    this->runAction(enemySpeed);
    pPool->release();
}

void GMEnemyAction::setAttackAngle()
{
    stopCurveAtion();
    _oldAngle = this->getRotation();
    float cocosAngle = GMPublicMethod::pointToAngle(this->getPosition(), ccp(WINSIZE_W/2,0), 1);
    this->setRotation(cocosAngle);
}

//#pragma mark - 设置加速 和恢复加速
void GMEnemyAction::setAccelerate(){
    if (getRouteStatus() == R_Rand || getRouteStatus() == R_RandCurve) {
        if(enemySpeed && isSpeed == false && _accelerate != 0){
            int tempSpeed = rand()%100+1;
            if (tempSpeed <= _accelerate) {
                enemySpeed->setSpeed(2.0f);
                this->unschedule(schedule_selector(GMEnemyAction::setSpeedOfRecovery));
                this->scheduleOnce(schedule_selector(GMEnemyAction::setSpeedOfRecovery), 1);
                isSpeed = true;
            }
        }
    }
}

void GMEnemyAction::setSpeedOfRecovery(float dt)
{
    if (enemySpeed) {
        enemySpeed->setSpeed(1.0f);
    }
}

void GMEnemyAction::setUnRemoveTheScreen()
{
    int d = 1;
//    if (rand()%2==0) {
//        d = 1;
//    }
//    else {
//        d = -1;
//    }
//    int ta = rand()%_angle;
//    rotationAngle = this->getRotation()+ta*d;
    if (getRouteStatus() == R_NotMoveOut)
    {
        bool isAgainMove = false;
        CCPoint oldP = this->getPosition();
        if (oldP.x <= 0) {
            rotationAngle = rand()%180;
            isAgainMove = true;
        }
        else if (oldP.x >= WINSIZE_W) {
            rotationAngle = -rand()%180;
            isAgainMove = true;
        }
        else if(oldP.y <= 0){
            if (rand()%2==0) {
                d = 1;
            }
            else {
                d = -1;
            }
            rotationAngle = (rand()%90)*d;
            isAgainMove = true;
        }
        else if(oldP.y >= WINSIZE_H){
            if (rand()%2==0) {
                d = 1;
            }
            else {
                d = -1;
            }
            rotationAngle = (rand()%135+45)*d;
            isAgainMove = true;
        }
        
        if (isAgainMove == true){
            randRotationMove();
            _countTime= 0;
        }
    }

}

//#pragma mark - continue action
/*
 *  冰冻后继续移动
 */
void GMEnemyAction::continueMoveAction()
{
//    ZPLog("(%d,%d,%d)",color3b.r,color3b.b,color3b.g);
    if (this->getFrozen() == true) {
        this->setColor(ccc3(255,255,255));
        this->setOpacity(225);
        this->setFrozen(false);
        this->_enemyStatus = S_Move;
        if(getRouteStatus() == R_Rand)
        {
            //2013-3-28晚上调试注销
            randRotationMove();
//            randRotationAngle();
        }
    }
}
/*
 *  攻击后继续移动
 */
void GMEnemyAction::continueMoveAction1()
{
    this->stopAllActions();
    this->setRotation(_oldAngle);
    setEnemyAnimation(true, "a");
    _enemyStatus = S_Move;
    _countTime = 0;

    randRotationMove();
}

//#pragma mark - 释放冰河世纪是停止
void GMEnemyAction::stopMoveAction()
{
//    CCSpeed *speed = (CCSpeed*)this->getActionByTag(speed_tag1);
//    this->stopAction(speed);
// 
//    CCAction* action = (CCAction*)this->getActionByTag(move_tag1);
//    this->stopAction(action);
    if (this->getFrozen() == false) {
        this->_enemyStatus = S_Stop;
        this->setOpacity(220);
        this->setColor(ccc3(41,41,147));
        this->setFrozen(true);
    }
    
}


//#pragma mark - 取消回调函数
//void GMEnemyAction::unscheduleRandFashion()
//{
//    this->unschedule(schedule_selector(GMEnemyAction::randEnemyMove));
//}


float GMEnemyAction::getAngle(CCPoint p1,CCPoint p2)
{
    CCPoint shootVector = ccpSub( p1,p2);
    float shootAngle = ccpToAngle(shootVector);
    float cocosAngle = RADIANS_TO_DEGREES(shootAngle);
    float angle;
    if (cocosAngle<0) {
        angle = -(90+cocosAngle);
    }
    else if (cocosAngle>0){
        angle = 90 - cocosAngle;
    }
    return angle;
}

//#pragma mark - 
//void GMEnemyAction::setRotationAndMove()
void GMEnemyAction::setRotationAndMove(CCObject* target, SEL_CallFuncN selector)
{
    CCPoint oldPoint = this->getPosition();
    if (GMPublicMethod::checkRectContainsPoint(CCRect(0, 0, WINSIZE_W, WINSIZE_H),oldPoint)) {
        CCPoint newPoint;
        float anger = this->getRotation();
        anger += 50;
        this->setRotation(anger);
        if (!isRotationAndMove) {
            _deathStatus = 2;
            isRotationAndMove = true;
            this->stopAllActions();
            
            CCPoint moveToPoint = ccp(WINSIZE_W/2,WINSIZE_H/2);
            CCMoveTo *moveTo = CCMoveTo::create(0.6, moveToPoint);
            CCScaleTo *scaleTo = CCScaleTo::create(0.6, 0);
            CCActionInterval * action = (CCActionInterval*)CCSpawn::create(moveTo, scaleTo,NULL);
            CCCallFuncN *callFunc = CCCallFuncN::create(target, selector);
            CCActionInterval* sequence = (CCActionInterval*)CCSequence::create(action,callFunc,NULL);
            this->runAction(sequence);
        }
    }
}

void GMEnemyAction::setBossRestoreLife(CCPoint point,CCObject* target, SEL_CallFuncN selector)
{
    CCPoint oldPoint = this->getPosition();
    if (!isRotationAndMove) {
        _deathStatus = 1;
        isRotationAndMove = true;
        this->stopAllActions();
        CCMoveTo *moveTo = CCMoveTo::create(0.6, point);
        CCScaleTo *scaleTo = CCScaleTo::create(0.6, 0);
        CCActionInterval * action = (CCActionInterval*)CCSpawn::create(moveTo, scaleTo,NULL);
        CCCallFuncN *callFunc = CCCallFuncN::create(target, selector);
        CCActionInterval* sequence = (CCActionInterval*)CCSequence::create(action,callFunc,NULL);
        this->runAction(sequence);
    }
}
//#pragma mark - 检查移除
/*
 *  检测是否移到屏幕外
 */
void GMEnemyAction::checkIsRemove()
{
//    if(_id != 16)
    {
//        float tempw = Get_W(Get_Box(this));
        float temph = Get_H(Get_Box(this));
//        float x = this->getPosition().x;
//        float y = this->getPosition().y;
        CCPoint point = this->getPosition();
        CCRect tempRect = CCRect(-temph, -temph, WINSIZE_W+temph, WINSIZE_H+temph);
        
        if (!GMPublicMethod::checkRectContainsPoint(tempRect,point)) {
            GMGameLayer *temp = (GMGameLayer*)_delegate;
            temp->removeEnemyFromBatchNode(this);
        }
        
        //从左到又
//        if ( x < -tempw)
//        {
//            GMGameLayer *temp = (GMGameLayer*)_delegate;
//            temp->removeEnemyFromBatchNode(this);
//            return;
//        }
//        else if( x > WINSIZE_W+tempw)
//        {
//            GMGameLayer *temp = (GMGameLayer*)_delegate;
//            temp->removeEnemyFromBatchNode(this);
//            return;
//        }
//        
//        if (y < -temph) {
//            GMGameLayer *temp = (GMGameLayer*)_delegate;
//            temp->removeEnemyFromBatchNode(this);
//            return;
//        }
//        else if( y > WINSIZE_H+temph){
//            GMGameLayer *temp = (GMGameLayer*)_delegate;
//            temp->removeEnemyFromBatchNode(this);
//            return;
//        }
    }
}

//#pragma mark - 检查碰撞
bool GMEnemyAction::checkCollision(float collisionW,CCPoint collisionP,float scale1,float scale2)
{
    bool isCollision = false;
    if (GMPublicMethod::checkRectContainsPoint(CCRect(0, 0, WINSIZE_W, WINSIZE_H),this->getPosition())) {
    }
    else {
        return false;
    }
    
    float enemyImageSize = this->boundingBox().size.width;//this->getContentSize().width;
//    ZPLog("1 %f",enemyImageSize);
//    ZPLog("2 %f",this->boundingBox().size.width);
    
    float collisionImageSize = collisionW;
    float enemyCollisionRadius = enemyImageSize * scale1;
    float collisionRadius = collisionImageSize * scale2;
    float maxCollisionDistance = enemyCollisionRadius + collisionRadius;
    float actualDistance = ccpDistance(this->getPosition(), collisionP);
    
    CCPoint p1 = this->getPosition();
    CCPoint p2 = collisionP;
    
    if (_id == 1 || _id == 2 || _id == 3) {
        if (actualDistance < maxCollisionDistance) {
            return true;
        }
    }
    else if(_id == 4) {
        if (GMPublicMethod::getCollisionValue(0,0,enemyImageSize * 0.2f,collisionRadius,p1,p2)) {
            return true;
        }
    }
    else if(_id != 10) {
        if (GMPublicMethod::getCollisionValue(0,0,enemyImageSize * 0.3f,collisionRadius,p1,p2)) {
            return true;
        }
    }
    else  if (_id == 10) {
        float angle = this->getRotation();
        if (GMPublicMethod::getCollisionValue(angle,70,enemyImageSize*0.25,collisionRadius,p1,p2)) {
            return  true;
        }
        else if(GMPublicMethod::getCollisionValue(angle,36,enemyImageSize*0.25,collisionRadius,p1,p2)){
            return  true;
        }
        else if(GMPublicMethod::getCollisionValue(angle,0,enemyImageSize*0.2,collisionRadius,p1,p2)){
            return  true;
        }
        else if(GMPublicMethod::getCollisionValue(angle,-36,enemyImageSize*0.15,collisionRadius,p1,p2)){
            return  true;
        }
        else if(GMPublicMethod::getCollisionValue(angle,-50,enemyImageSize*0.1,collisionRadius,p1,p2)){
            return  true;
        }
        else if(GMPublicMethod::getCollisionValue(angle,-65,enemyImageSize*0.1,collisionRadius,p1,p2)){
            return  true;
        }
        else if(GMPublicMethod::getCollisionValue(angle,-80,enemyImageSize*0.1,collisionRadius,p1,p2)){
            return  true;
        }
    }
    return isCollision;
}

/**
 * 计算得到向量方向的弧度
 *
 * @param v 向量
 * @return 向量方向的弧度，返回值范围在[-pi, pi]
 */
//static inline float wypToRadian(CCPoint v) {
//	return atan2(v.y, v.x);
//}
//static float r2d(float radian) {
//	return (radian / M_PI * 180.0f);
//}
///**
// * 计算得到向量方向的角度
// *
// * @param v 向量
// * @return 向量方向的角度，返回值范围在[-180, 180]
// */
//static inline float wypToDegree(CCPoint v) {
//	return r2d(wypToRadian(v));
//}
//
//void GMEnemyAction::updateLagrange()
//{
//    CCPoint m_pinPoint = ccp(MAXFLOAT, MAXFLOAT);
//    
//    
//    ccLagrangeConfig m_config = wylcQuad(0,
//                                          50,
//                                          WINSIZE_W/2,
//                                          200,
//                                          WINSIZE_W,
//                                          50);
//    float t = 0.115;
//    CCPoint p = wylcPointAt(m_config, t);
//	this->setPosition( ccp(p.x, p.y));
//    bool m_autoRotate = true;
//	// check direction
//	if(m_autoRotate) {
//		CCPoint p2 = wylcPointAt(m_config, t + 0.016f);
//		CCPoint d = ccpSub(p2, p);
//		float angle = - wypToDegree(d);
////		angle += m_angleDelta;
//        angle += 90;
//		this->setRotation(angle);
//	} else if(m_pinPoint.x != MAXFLOAT && m_pinPoint.y != MAXFLOAT) {
//		CCPoint anchor = ccp(this->getAnchorPoint().x, this->getAnchorPoint().y);
//		anchor = this->convertToWorldSpace(anchor);
//		float angle = wypToDegree(ccpSub(m_pinPoint, anchor));
////		this->setRotation(-angle + m_pinDelta);
//        this->setRotation(-angle);
//	}
//
//}

//#pragma mark -
void GMEnemyAction::removeObject(CCSprite* mSprite)
{
    this->removeFromParentAndCleanup(true);
}

GMEnemyAction::~GMEnemyAction()
{
    this->cleanup();
    if (pointArray) {
        pointArray->release();
    }
    if (enemySpeed) {
        enemySpeed->release();
//        randSequence = NULL;
        enemySpeed = NULL;
    }
    pointArray = NULL;
    
    _delegate = NULL;
    curveAction = NULL;
//    ZPLog("~GMEnemyAction");
}


