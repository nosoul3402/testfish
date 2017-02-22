//
//  UINumber.cpp
//  FishX
//
//  Created by peng on 12-12-27.
//
//

#include "UINumber.h"


bool UINumber::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCSprite::init() )
    {
        return false;
    }
    
    m_texture = NULL;
    m_style = NumStyleNormal;
    m_num = 0;
    m_nPosCur = 0;
    m_nPosEnd = 0;
    
    return true;
}

void UINumber::setTyle(NumStyle style)
{
    m_texture = NULL;
    m_style = style;
    m_num = 0;
    m_nPosCur = 0;
    m_nPosEnd = 0;
}
/*
 *  设置纹理
 */
void UINumber::setTexture(const char *name,float w ,float h)
{
    textW = w;
    textH = h;

    m_texture =  CCTextureCache::sharedTextureCache()->addImage(name);    
//    CCSpriteFrame *frame = CCSpriteFrame::createWithTexture(m_texture, CCRect(0, 0, NUM_WIDTH, NUM_HEIGHT));
//    setDisplayFrame(frame);
    setTextureIndex(0);
}

void UINumber::setTextureFromSpriteFrame(const char *name,float w ,float h)
{
    textW = w;
    textH = h;
    CCSpriteFrame *spriteFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(name);
    m_texture = spriteFrame->getTexture();
    setTextureIndex(0);
}

/*
 *
 */
void UINumber::setTextureIndex(float x)
{
    CCSpriteFrame *frame = NULL;
    if (NumStyleNormal0 == m_style) {
     frame = CCSpriteFrame::createWithTexture(m_texture, CCRect(x, 0, textW, textH));
    }
    else {
         frame = CCSpriteFrame::createWithTexture(m_texture, CCRect(0, x, textW, textH));
    }
    setDisplayFrame(frame);
}

/*
 * setNumber 设置显示的数字
 */
void UINumber::setNumber(int num)
{
    
//    IOSLog("%d",m_nPosEnd);
    if (NumStyleNormal0 == m_style) {
        m_nPosCur = textW * m_num;
        m_nPosEnd = textW * num;
        
        setTextureIndex(m_nPosEnd);
    }
    else{
        m_nPosCur = textH * m_num;
        m_nPosEnd = textH * num;
        
        if (NumStyleNormal == m_style) {
            m_nMoveLen = 4;
        }
        else if (NumStyleSameTime == m_style) {
            m_nMoveLen = (m_nPosEnd-m_nPosCur)/20;
        }
        if (NumStyleNormal0) {
            
        }
        if (m_num > num) {
            this->unschedule(schedule_selector(UINumber::onRollUP));
            this->schedule(schedule_selector(UINumber::onRollUP), 0.03f);
        }
        else {
            this->unschedule(schedule_selector(UINumber::onRollDown));
            this->schedule(schedule_selector(UINumber::onRollDown), 0.03f);
        }
        m_num = num;
    }
   
}


void UINumber::setDisplayFrame(CCSpriteFrame*frame)
{
	m_obUnflippedOffsetPositionFromCenter = frame->getOffset();
    
	CCTexture2D *newTexture = frame->getTexture();
	// update texture before updating texture rect
    CCTexture2D *oldTexture = CCSprite::getTexture();
	if ( ( oldTexture==NULL ) || ( newTexture->getName() != oldTexture->getName() ) )
		CCSprite::setTexture( newTexture );
    
	// update rect
	m_bRectRotated = frame->isRotated();
    
//	[self setTextureRect:frame.rect rotated:rectRotated_ untrimmedSize:frame.originalSize];
    this->setTextureRect(frame->getRect(), m_bRectRotated, frame->getOriginalSize() );
}


/*
 * onRollDown 向下滚动
 */
void UINumber::onRollDown(float dt){
    m_nPosCur += m_nMoveLen;
    if (m_nPosCur >= m_nPosEnd) {
        m_nPosCur = m_nPosEnd;
        this->unschedule(schedule_selector(UINumber::onRollDown));
    }
//    IOSLog("%d",m_nPosCur);
    setTextureIndex(m_nPosCur);
}


/*
 * onRollUP 向上滚动
 */
void UINumber::onRollUP(float dt){
    m_nPosCur -= 4;
    if (m_nPosCur <= m_nPosEnd) {
        m_nPosCur = m_nPosEnd;
        this->unschedule(schedule_selector(UINumber::onRollUP));
    }
    setTextureIndex(m_nPosCur);
}







