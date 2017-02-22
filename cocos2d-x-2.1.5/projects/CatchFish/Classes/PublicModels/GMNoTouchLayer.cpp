//
//  GMNoTouchLayer.cpp
//  FishX
//
//  Created by peng on 12-12-25.
//
//

#include "GMNoTouchLayer.h"

bool GMNoTouchLayer::init(){
    if (!CCLayerColor::init() )
    {
        return false;
    }
    
    this->setTouchEnabled(true);
    
    return true;
}

void GMNoTouchLayer::setBgColor(const ccColor3B& color,GLubyte opacity){
    this->setColor(color);
    this->setOpacity(opacity);
}


void GMNoTouchLayer::registerWithTouchDispatcher()
{
    //1.x
    //CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate(this, std::numeric_limits <int> ::min() , true);
    //2.x
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, /*std::numeric_limits <int> ::min()*/kCCMenuHandlerPriority, true);
    //使用int最小值做最高优先级,并且吞掉事件true
    
    CCLayer::registerWithTouchDispatcher();
}

//#pragma mark - 重构

//void GMNoTouchLayer::onEnter()
//{
//    CCLayer::onEnter();
//    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, kCCMenuHandlerPriority - 1, true);
//}
//
//void GMNoTouchLayer::onExit()
//{
//    CCLayer::onExit();
//    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
//}


bool GMNoTouchLayer::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
   
    
    return true;
}

void GMNoTouchLayer::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    if (m_bTouchedMenu) {
        
    }
}

void GMNoTouchLayer::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    if (m_bTouchedMenu) {
        
        m_bTouchedMenu = false;
    }
}

void GMNoTouchLayer::ccTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    if (m_bTouchedMenu) {
        
        m_bTouchedMenu = false;
    }
}

void GMNoTouchLayer::removeTouchDelegate()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
}

GMNoTouchLayer::~GMNoTouchLayer()
{
    this->cleanup();
}










