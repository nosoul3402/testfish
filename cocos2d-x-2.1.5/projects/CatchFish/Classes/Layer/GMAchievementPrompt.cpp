//
//  GMAchievementPrompt.cpp
//  FishX
//
//  Created by peng on 13-3-12.
//
//

#include "GMAchievementPrompt.h"
#include "../Config/GMHeaderConfig.h"
#include "../Models/GMAchievement.h"
#include "../PublicModels/GMAccessData.h"
#include "GMGameLayer.h"

//static char status[10] = {0};

CCScene* GMAchievementPrompt::scene()
{
    CCScene *scene = CCScene::create();
    GMAchievementPrompt *layer = GMAchievementPrompt::create();
    scene->addChild(layer);
    return scene;
}

GMAchievementPrompt::GMAchievementPrompt()
{
    
}

GMAchievementPrompt::~GMAchievementPrompt()
{
    CCRemoveSpriteFrameByName(achievement1_plist);
    CCRemoveTextureForKey(achievement1_png);
    
    CCRemoveSpriteFramesAndTextureForKey(achievement2_plist,achievement2_png);
    
    CCRemoveSpriteFrameByName(achievement3_plist);
    CCRemoveTextureForKey(achievement3_png);
    
    achievementArray->removeAllObjects();
    achievementArray->release();
    achievementArray = NULL;
    this->removeChild(achievementBatchNode, true);
    achievementBatchNode = NULL;
    ZPLog("~GMAchievementPrompt");
}

// on "init" you need to initialize your instance
bool GMAchievementPrompt::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    for (int i =0; i < 3; i ++) {
        view[i]._bg = NULL;
        view[i]._countShowTime = 0;
        view[i]._isShow = false;
        view[i]._energe = 0;
    }
    initElement();
    
    int status = GMAccessData::sharedAccessData()->getEnergePromptStatus();
    if (status == 0) {
        eStatus = 5;
    }
    else {
        eStatus = status;
    }
//    countShowTime = 0;
    showNum = 0;

    isShow = false;
    return true;
}


void GMAchievementPrompt::initElement()
{
    CCAddSpriteFramesWithFile(achievement1_plist);
    achievementBatchNode = CCSpriteBatchNode::create(achievement1_png);
    this->addChild(achievementBatchNode);

    CCAddSpriteFramesAndTextureFile(achievement2_plist,achievement2_png);
    
    CCAddSpriteFramesWithFile(achievement3_plist);
    CCSpriteBatchNode *achievementBatchNode3 = CCSpriteBatchNode::create(achievement3_png);
    this->addChild(achievementBatchNode3);
    
    achievementArray = new CCArray();
    GMPublicMethod::getAchievementPrompFromFile(APromptList_plist,achievementArray);
}

/*
 *  index  为数组索引
 */
void GMAchievementPrompt::showAchievement(int index)
{
    showNum ++;
    if (showNum>3) {
        showNum = 0;
    }
    char score[30];
    for (int i = 0; i < showNum; i++) {
        if (view[i]._bg) {
            continue;
        }
        float scale = Scale_Y;
        view[i]._bg = CCSprite::createWithSpriteFrameName("achievement011.png");
        view[i]._bg->setPosition(ccp(WINSIZE_W/2,WINSIZE_H/2));
        SetScale2(view[i]._bg,scale);
        this->addChild(view[i]._bg,1);
        
        GMAchievement *ach = (GMAchievement*)achievementArray->objectAtIndex(index);
        sprintf(score, "achievementtu%03d.png",ach->_id-1);
        ZPLog("成就图标名称 : %s",score);
        CCSprite *aIcon = CCSprite::createWithSpriteFrameName(score);
        aIcon->setAnchorPoint(ccp(0,0));
        aIcon->setPosition(ccp(10,10));
        view[i]._bg->addChild(aIcon,2);
        
        sprintf(score, "achievementzi%03d.png",ach->_id-1);
        ZPLog("成就图标名称 : %s",score);
        CCSprite *title = CCSprite::createWithSpriteFrameName(score);
        title->setAnchorPoint(ccp(0,0));
        float tempX = (219-title->getContentSize().width)/2;
        title->setPosition(ccp(108+tempX,60));
        view[i]._bg->addChild(title,2);
//        sprintf(score, "%d",ach->_energe);
//        CCLabelTTF* labelt = CCLabelTTF::create(score, "Arial Rounded MT Bold", 25,CCSize(220, 86), kCCTextAlignmentCenter);
//        labelt->setVerticalAlignment(kCCVerticalTextAlignmentCenter);
//        labelt->setAnchorPoint(ccp(0, 0));
//        labelt->setPosition( ccp( 85 , -10 ));
//        labelt->setColor(ccORANGE);
        
        int num = GMPublicMethod::getScoreNum(ach->_energe);
        UIRollNum *rollNum = UIRollNum::create();
        rollNum->setEffect("game/number11.png",num,25,33,NumStyleNormal0);
        rollNum->setNumber(ach->_energe);
        rollNum->setPosition( ccp(195+num*25, 40) );
        view[i]._bg->addChild(rollNum);
        
        CCSprite *eSprite = CCSprite::createWithSpriteFrameName("achievement012.png");
        eSprite->setAnchorPoint(ccp(0,0.5));
        eSprite->setPosition(ccp(195+num*25, 35));
        view[i]._bg->addChild(eSprite);
        
        view[i]._isShow = true;
        view[i]._energe = ach->_energe;
        
        
        if (i == 1) {
            view[0]._bg->setPosition(ccp(WINSIZE_W/2, WINSIZE_H/2+Get_H(Get_Rect(view[0]._bg))/2*scale ));
            view[1]._bg->setPosition(ccp(WINSIZE_W/2, WINSIZE_H/2-Get_H(Get_Rect(view[0]._bg))/2*scale ));
        }
        else if(i == 2){
            view[0]._bg->setPosition(ccp(WINSIZE_W/2, WINSIZE_H/2+Get_H(Get_Rect(view[0]._bg))*scale ));
            view[1]._bg->setPosition(ccp(WINSIZE_W/2, WINSIZE_H/2 ));
            view[2]._bg->setPosition(ccp(WINSIZE_W/2, WINSIZE_H/2-Get_H(Get_Rect(view[0]._bg))*scale ));
        }
        
//        sprintf(status, "%d",1);
        GMAccessData::sharedAccessData()->saveEachAchievementStatus(ach->_id,1);
    }
    
}

/*
 *  过关成就
 */
void GMAchievementPrompt::showGMCheckpointsPrompt(int index)
{
    int status = GMAccessData::sharedAccessData()->getEachAchievementStatus(index);
    if(status == 0)
        showAchievement(index-1);
}

/*
 *  能量成就
 */
void GMAchievementPrompt::showEnergePrompt(int curEnerge)
{
//    curEnerge = 600;
//    eStatus = 5;
    if (curEnerge>= 2500 && curEnerge < 5000 && eStatus == 5) {
        showAchievement(eStatus);
        eStatus = 6;
    }
    else if (curEnerge>= 5000 && curEnerge < 10000 && eStatus == 6){
        showAchievement(eStatus);
        eStatus = 7;
    }
    else if (curEnerge>= 10000 && curEnerge < 25000 && eStatus == 7){
        showAchievement(eStatus);
        eStatus = 8;
    }
    else if (curEnerge>= 25000 && curEnerge < 50000 && eStatus == 8){
        showAchievement(eStatus);
        eStatus = 9;
    }
    else if (curEnerge>= 50000 && eStatus == 9){
        showAchievement(eStatus);
        eStatus = 10;
    }
    char value[20];
    sprintf(value, "%d",eStatus);
    GMAccessData::sharedAccessData()->saveEnergePromptStatus(value);
}

/*
 *  Swirl 漩涡成就
 */
void GMAchievementPrompt::showSwirlPrompt()
{
    countPayNum = GMAccessData::sharedAccessData()->getSwirlAmount();
    if (countPayNum == 1) {
        int status = GMAccessData::sharedAccessData()->getEachAchievementStatus(11);
        if(status==0)
            showAchievement(10);
    }
    else if (countPayNum == 3) {
        int status = GMAccessData::sharedAccessData()->getEachAchievementStatus(12);
        if(status==0)
            showAchievement(11);
    }
    else if (countPayNum == 5) {
        int status = GMAccessData::sharedAccessData()->getEachAchievementStatus(13);
        if(status==0)
            showAchievement(12);
    }
    else if (countPayNum == 10) {
        int status = GMAccessData::sharedAccessData()->getEachAchievementStatus(14);
        if(status==0)
            showAchievement(13);
    }
    else if (countPayNum == 20) {
        int status = GMAccessData::sharedAccessData()->getEachAchievementStatus(15);
        if(status==0)
            showAchievement(14);
    }
    else if (countPayNum == 50) {
        int status = GMAccessData::sharedAccessData()->getEachAchievementStatus(16);
        if(status==0)
            showAchievement(15);
    }
    else if (countPayNum == 100) {
        int status = GMAccessData::sharedAccessData()->getEachAchievementStatus(17);
        if(status==0)
            showAchievement(16);
    }
}

/*
 *  一炮击中n条鱼的 提示
 */
void GMAchievementPrompt::showhitFishPrompt(int num)
{
    int exist = -1;
    if (num == 2) {
        exist = GMAccessData::sharedAccessData()->getEachAchievementStatus(18);
        if (exist == 0) {
            showAchievement(17);
        }
    }
    else if (num == 5) {
        exist = GMAccessData::sharedAccessData()->getEachAchievementStatus(19);
        if (exist == 0) {
            showAchievement(18);
        }
    }
    else if (num == 10) {
        exist = GMAccessData::sharedAccessData()->getEachAchievementStatus(20);
        if (exist == 0) {
            showAchievement(19);
        }
    }
    else if (num == 20) {
        exist = GMAccessData::sharedAccessData()->getEachAchievementStatus(21);
        if (exist == 0) {
            showAchievement(20);
        }
    }
    else if (num == 50) {
        exist = GMAccessData::sharedAccessData()->getEachAchievementStatus(22);
        if (exist == 0) {
            showAchievement(21);
        }
    }
    else if(num == 100){ //海神的武器
        exist = GMAccessData::sharedAccessData()->getEachAchievementStatus(23);
        if (exist == 0) {
            showAchievement(22);
        }
    }
    else if(num == 101){ //幸运儿
        exist = GMAccessData::sharedAccessData()->getEachAchievementStatus(24);
        if (exist == 0) {
            showAchievement(23);
        }
    }
    else if(num == 103){ //犯太岁
        exist = GMAccessData::sharedAccessData()->getEachAchievementStatus(25);
        if (exist == 0) {
            showAchievement(24);
        }
    }
}


/*
 *  显示成就界面持续时间
 */
void GMAchievementPrompt::showAchievementPromptViewTime(){
    
    for (int i = 0; i < 3; i++) {
        if (view[i]._isShow) {
            view[i]._countShowTime++;
            if (view[i]._countShowTime == 2) {
                view[i]._isShow = false;
                CCScaleBy *scale = CCScaleBy::create(0.2,0);
                CCFadeOut *fade = CCFadeOut::create(0.5);
                CCActionInterval * action = (CCActionInterval*)CCSpawn::create(scale, fade,NULL);
                CCCallFunc *callFunc = CCCallFunc::create(this, callfunc_selector(GMAchievementPrompt::removeAchievementPromptView));
                CCFiniteTimeAction *sequence = CCSequence::create(action,callFunc,NULL);
                view[i]._bg->runAction(sequence);
            }
        }
    }
    
}

void GMAchievementPrompt::removeAchievementPromptView(){
    
    showNum--;
    for (int i = 0; i < 3; i++) {
        if (view[i]._isShow == false && view[i]._bg) {
            CCPoint point = view[i]._bg->getPosition();
            GMGameLayer *temp = (GMGameLayer*)_delegate;
            temp->achievementEnerge(view[i]._energe,point);
            
            view[i]._energe = 0;
            view[i]._countShowTime = 0;
            CCSprite *sprite;
            CCObject *fObject = NULL;
            CCARRAY_FOREACH(view[i]._bg->getChildren(), fObject) {
                sprite = (CCSprite*)fObject;
                view[i]._bg->removeChild(sprite, true);
                sprite = NULL;
            }
            this->removeChild(view[i]._bg, true);
            view[i]._bg = NULL;
        }
    }
//    countShowTime = 0;
//    CCSprite *sprite;
//    CCObject *fObject = NULL;
//    CCARRAY_FOREACH(bg[0]->getChildren(), fObject) {
//        sprite = (CCSprite*)fObject;
//        bg[0]->removeChild(sprite, true);
//        sprite = NULL;
//    }
//    this->removeChild(bg[0], true);
//    bg[0] = NULL;
}
