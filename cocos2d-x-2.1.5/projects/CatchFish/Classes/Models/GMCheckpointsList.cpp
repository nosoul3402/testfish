//
//  GMCardList.cpp
//  FishX
//
//  Created by peng on 13-1-10.
//
//

#include "GMCheckpointsList.h"

using namespace cocos2d;

bool GMCheckpointsList::init()
{
    //////////////////////////////
    // 1. super init first
//    if ( !CCSprite::init() )
//    {
//        return false;
//    }
//    
    return true;
}

GMCheckpointsList::GMCheckpointsList()
{
    checkpointArray = new CCArray();
    strangeArray = new CCArray();
    taskArray = new CCArray();
    enemyArray = new CCArray();
    strangeTableArray = new CCArray();
    bulletArray = new CCArray();
}

/*
 *
 */
GMCheckpointsList::~GMCheckpointsList()
{
    checkpointArray->removeAllObjects();
    checkpointArray->release();
    checkpointArray = NULL;
    strangeArray->removeAllObjects();
    strangeArray->release();
    strangeArray = NULL;
    taskArray->removeAllObjects();
    taskArray->release();
    taskArray = NULL;
    enemyArray->removeAllObjects();
    enemyArray->release();
    enemyArray = NULL;
    strangeTableArray->removeAllObjects();
    strangeTableArray->release();
    strangeTableArray = NULL;
    bulletArray->removeAllObjects();
    bulletArray->release();
    bulletArray = NULL;
    CCLog("~GMCardList");
}
/*
 *  读取UI配置数据
 */
void GMCheckpointsList::readWithContentsOfFile(const char *fileName)
{
    CCAutoreleasePool* pPool = new CCAutoreleasePool();
    CCDictionary *productsDic = CCDictionary::createWithContentsOfFile(fileName);
    
    checkpointArray->removeAllObjects();
    strangeArray->removeAllObjects();
    taskArray->removeAllObjects();
    strangeTableArray->removeAllObjects();
    
    CCDictionary*tempCard = (CCDictionary*)productsDic->objectForKey("Checkpoints");
    if (tempCard && tempCard->count()>0) {
        GMCheckpoints *checkpoints = new GMCheckpoints();
        checkpoints->setValue(tempCard);
        checkpointArray->addObject(checkpoints);
        checkpoints->release();
    }
    char key[30] = {0};
    CCDictionary*tempStrange = (CCDictionary*)productsDic->objectForKey("StrangeRand");
    if (tempStrange && tempStrange->count()>0) {
        for (int i = 0; i < tempStrange->count(); i ++) {
            sprintf(key,"strange%d",i+1);
            CCDictionary*tempS = (CCDictionary*)tempStrange->objectForKey(key);
            GMStrange *strange = new GMStrange();
            strange->setValue(tempS);
            strangeArray->addObject(strange);
            strange->release();
        }
    }

    CCDictionary*tempTask = (CCDictionary*)productsDic->objectForKey("Task");
    if (tempTask && tempTask->count()>0) {
        for (int i = 0; i < tempTask->count(); i ++) {
            sprintf(key,"task%d",i+1);
            CCDictionary*tempT = (CCDictionary*)tempTask->objectForKey(key);
            GMTask *task = new GMTask();
            task->setValue(tempT);
            taskArray->addObject(task);
            task->release();
        }
    }
    
    CCDictionary*strangeTable = (CCDictionary*)productsDic->objectForKey("StrangeTable");
    if (strangeTable && strangeTable->count()>0) {
        for (int i = 0; i < strangeTable->count(); i ++) {
            sprintf(key,"strange%d",i+1);
            CCDictionary*tempT = (CCDictionary*)strangeTable->objectForKey(key);
            GMStrange *strange = new GMStrange();
            strange->setValue1(tempT);
            strangeTableArray->addObject(strange);
            strange->release();
        }
    }
    pPool->release();
    
    setRandRange();
}

void GMCheckpointsList::readEnemyListOfFile(const char *fileName)
{
    CCAutoreleasePool* pPool = new CCAutoreleasePool();
    CCDictionary *productsDic = CCDictionary::createWithContentsOfFile(fileName);
    char key[30] = {0};
    CCDictionary*enemyListDic = (CCDictionary*)productsDic->objectForKey("EnemyList");
    if (enemyListDic && enemyListDic->count()>0) {
        for (int i = 0; i < enemyListDic->count(); i ++) {
            sprintf(key,"enemy%d",i+1);
            CCDictionary*tempE = (CCDictionary*)enemyListDic->objectForKey(key);
            GMEnemy *enemy = new GMEnemy();
            enemy->setValue(tempE);
            enemyArray->addObject(enemy);
            enemy->release();
        }
    }
    pPool->release();
}



GMCheckpoints* GMCheckpointsList::getCheckpoint(int index)
{
    if (index >= checkpointArray->count()) {
        return NULL;
    }
    return (GMCheckpoints*)checkpointArray->objectAtIndex(index);
}

/*
 *  随机刷怪
 */
int GMCheckpointsList::getStrangeCount()
{
    return strangeArray->count();
}

void GMCheckpointsList::setRandRange()
{
    for (int i = 0; i < getStrangeCount(); i++) {
        GMStrange *strange = NULL;
        if (i == 0) {
            strange = getStrange(i);
            //            CCLog("0 i = %d range1 = %d range2 = %d rate = %f",i , strange->_interval_range1,strange->_interval_range2,strange->_rate);
            if (strange) {
                strange->_interval_range1 = 0;
                strange->_interval_range2 = strange->_rate;
            }
        }
        else{
            strange = getStrange(i);
            //            CCLog("0 i = %d range1 = %d range2 = %d rate = %f",i , strange->_interval_range1,strange->_interval_range2,strange->_rate);
            GMStrange *temp = getStrange(i-1);
            if (strange) {
                strange->_interval_range1 = temp->_interval_range2;
                strange->_interval_range2 = strange->_rate+strange->_interval_range1;
            }
        }
        
        //        strangeArray->replaceObjectAtIndex(i, strange);
        
    }
    
    //    for (int i = 0; i < getStrangeCount(); i++) {
    //        GMStrange *strange = getStrange(i);
    //        CCLog("1-> i = %d range1 = %d range2 = %d rate = %f",i , strange->_interval_range1,strange->_interval_range2,strange->_rate);
    //    }
}
GMStrange* GMCheckpointsList::getStrange(int index)
{
    if (index >= strangeArray->count()) {
        return NULL;
    }
    return (GMStrange*)strangeArray->objectAtIndex(index);
}

/*
 *  任务
 */
int GMCheckpointsList::getTaskCount()
{
    return taskArray->count();
}

GMTask* GMCheckpointsList::getGMTask(int index)
{
    if (index >= taskArray->count()) {
        return NULL;
    }
    return (GMTask*)taskArray->objectAtIndex(index);
}

/*
 *  鱼
 */
GMEnemy* GMCheckpointsList::getEnemy(int index)
{
    if (index >= enemyArray->count()) {
        return NULL;
    }
    return (GMEnemy*)enemyArray->objectAtIndex(index);
}

/*
 *  固定刷怪
 */

int GMCheckpointsList::getStrangeTableCount()
{
    if (strangeTableArray) {
        return strangeTableArray->count();
    }
    return 0;
}

GMStrange* GMCheckpointsList::getStrangeTable(int index)
{
    if (index >= strangeTableArray->count()) {
        return NULL;
    }
    return (GMStrange*)strangeTableArray->objectAtIndex(index);
}

/*
 *  鱼的子弹
 */
void GMCheckpointsList::readFishBulletList()
{
    CCAutoreleasePool* pPool = new CCAutoreleasePool();
    CCDictionary *productsDic = CCDictionary::createWithContentsOfFile("File/enemyBullet.plist");
    char key[30] = {0};
    if (productsDic && productsDic->count()>0) {
        for (int i = 0; i < productsDic->count(); i ++) {
            sprintf(key,"bullet%d",i+1);
            CCDictionary*tempE = (CCDictionary*)productsDic->objectForKey(key);
            GMFishBullet *fishBuller = new GMFishBullet();
            fishBuller->setValue(tempE);
            bulletArray->addObject(fishBuller);
            fishBuller->release();
        }
    }
    pPool->release();
}

GMFishBullet* GMCheckpointsList::getFishBullet(int _id)
{
    GMFishBullet *tFishBuller = NULL;
    for (int i = 0; i < bulletArray->count(); i ++) {
        GMFishBullet *fishBuller = (GMFishBullet*)bulletArray->objectAtIndex(i);
        if (_id == fishBuller->_id) {
            tFishBuller = fishBuller;
            break;
        }
    }
    return tFishBuller;
}







