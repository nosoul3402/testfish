//
//  GMEnemy.cpp
//  FishX
//
//  Created by peng on 12-12-21.
//
//

#include "GMEnemy.h"

using namespace cocos2d;

bool GMEnemy::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCSprite::init() )
    {
        return false;
    }
    
    _countTime = 0;
    
    return true;
}

GMEnemy::~GMEnemy()
{
    _name = NULL;
    this->cleanup();
}


GMEnemy* GMEnemy::createEnemyName(const char *name)
{
    GMEnemy *enemy = (GMEnemy*)CCSprite::create(name);
    
    return enemy;
}

GMEnemy* GMEnemy::createEnemyFrameName(const char *name)
{
    GMEnemy *enemy = (GMEnemy*)CCSprite::createWithSpriteFrameName(name);
    return enemy;
}

GMEnemy* GMEnemy::createEnemyFrame(CCSpriteFrame *frame)
{
    GMEnemy *enemy = (GMEnemy*)CCSprite::createWithSpriteFrame(frame);
    return enemy;
}


void GMEnemy::setValue(CCDictionary *dictionary)
{
    _id = ((CCString*)dictionary->valueForKey("id"))->intValue();//类型
    _name = ((CCString*)dictionary->valueForKey("name"))->getCString();
    _type = ((CCString*)dictionary->valueForKey("type"))->intValue();
    _numerical = ((CCString*)dictionary->valueForKey("numerical"))->intValue();//数值
    _life = ((CCString*)dictionary->valueForKey("life"))->floatValue();//生命
    _burst_rate = ((CCString*)dictionary->valueForKey("burst_rate"))->floatValue();//_burst_rate
    _bulletId = ((CCString*)dictionary->valueForKey("bulletId"))->intValue();;//对应子弹id
    _bullet_firing_frequency = ((CCString*)dictionary->valueForKey("bullet_firing_frequency"))->floatValue();//子弹发射频率
    _shells_affect_rates = ((CCString*)dictionary->valueForKey("shells_affect_rates"))->floatValue();//炮弹影响率
    _limit_burst_rate = ((CCString*)dictionary->valueForKey("limit_burst_rate"))->floatValue();//极限爆率
    _speed = ((CCString*)dictionary->valueForKey("speed"))->intValue();//速度
    _time  = ((CCString*)dictionary->valueForKey("time"))->intValue();//间隔时间
    _angle = ((CCString*)dictionary->valueForKey("angle"))->intValue();//浮动角
    _accelerate = ((CCString*)dictionary->valueForKey("accelerate"))->intValue();

    setRouteStatus(R_NONE);
    _countTime = 0;
    _deathStatus = 1;
}


void GMEnemy::setValue(GMEnemy*enemy)
{
    _id = enemy->_id;//类型
    _name = enemy->_name;
    _type = enemy->_type;
    _numerical = enemy->_numerical;//数值
    _life = enemy->_life;//生命
    _burst_rate = enemy->_burst_rate;//_burst_rate
    _bulletId = enemy->_bulletId;//对应子弹id
    _bullet_firing_frequency = enemy->_bullet_firing_frequency;//子弹发射频率
    _shells_affect_rates = enemy->_shells_affect_rates;//炮弹影响率
    _limit_burst_rate = enemy->_limit_burst_rate;//极限爆率
    _speed = enemy->_speed;//速度
    _time  = enemy->_time;//间隔时间
    _angle = enemy->_angle;//浮动角
    _unRemoveTheScreen = false;
     _accelerate = enemy->_accelerate;
    _deathStatus = 1;
}


void GMEnemy::setHurtEffect()
{
    CCTintTo *tintTo = CCTintTo::create(0.2f,214,0,0);
    CCTintTo *tintTo2 = CCTintTo::create(0.2f,255,255,255);
    CCActionInterval *sequence = (CCActionInterval*)CCSequence::create(tintTo,tintTo2, NULL);
    this->runAction(sequence);
}

void GMEnemy::setEnemyTag(int tag){
    this->setTag(tag);
}


