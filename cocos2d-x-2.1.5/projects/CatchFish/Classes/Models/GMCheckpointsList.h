//
//  GMCardList.h
//  FishX
//
//  Created by peng on 13-1-10.
//
//

#ifndef __FishX__GMCardList__
#define __FishX__GMCardList__

#include <iostream>
#include "cocos2d.h"
#include "GMCheckpoints.h"
#include "GMStrange.h"
#include "GMEnemy.h"
#include "GMTask.h"
#include "GMFishBullet.h"

class GMCheckpointsList : public cocos2d::CCObject
{
public:
    virtual bool init();
    CREATE_FUNC(GMCheckpointsList);
    
    GMCheckpointsList();
    virtual ~GMCheckpointsList(void);
        
protected:
    cocos2d::CCArray         *checkpointArray;
    cocos2d::CCArray         *strangeArray;
    cocos2d::CCArray         *taskArray;
    cocos2d::CCArray         *enemyArray;
    cocos2d::CCArray         *strangeTableArray;
    cocos2d::CCArray         *bulletArray;
    /*
     *  设置随机鱼的范围
     */
    void setRandRange();
public:
    void readWithContentsOfFile(const char *fileName);
    void readEnemyListOfFile(const char *fileName);
    
    GMCheckpoints* getCheckpoint(int index);
    
    /*
     *  随机刷怪
     */
    int getStrangeCount();
    GMStrange* getStrange(int index);
    CCArray* getStrangeArray() {return strangeArray;}
    /*
     *  任务
     */
    int getTaskCount();
    GMTask* getGMTask(int index);
    
    /*
     *  鱼
     */
    GMEnemy* getEnemy(int index);
    /*
     *  固定刷怪
     */
    int getStrangeTableCount();
    GMStrange* getStrangeTable(int index);
    
    /*
     *  鱼的子弹
     */
    void readFishBulletList();
    GMFishBullet* getFishBullet(int _id);
    
};

#endif /* defined(__FishX__GMCardList__) */
