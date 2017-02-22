//
//  UIRollNum.cpp
//  FishX
//
//  Created by peng on 12-12-27.
//
//

#include "UIRollNum.h"

/*
 * init 初始化
 */
bool UIRollNum::init()
{
    if ( !CCSprite::init() )
    {
        return false;
    }
    
    m_nNumber = 0;
    m_maxCol = 6;
    numArray = new CCArray();//[[NSMutableArray alloc] init];
    zeroFill = true;
    style = NumStyleNormal;
    
    return true;
}

UIRollNum::~UIRollNum(){
    
    numArray->release();
    numArray = NULL;
}

void UIRollNum::setEffect(const char *name,int col,float w, float h, NumStyle nstyle)
{
    style = nstyle;
    m_maxCol = col;
    clearEffect(name,w,h);
}

void UIRollNum::setEffect1(const char *name,int col,float w, float h, NumStyle nstyle)
{
    style = nstyle;
    m_maxCol = col;
    clearEffect1(name,w,h);
}

void UIRollNum::setEffectSpriteFrame(const char *name,int col,float w, float h, NumStyle nstyle)
{
    style = nstyle;
    m_maxCol = col;
    clearEffectSpriteFrame(name,w,h);
}
/*
 * getNumber 获取显示的数字
 */
int UIRollNum::getNumber(){
    return m_nNumber;
}

/*
 * setNumber 设置显示的数字
 * num int 设置的数字
 */
void UIRollNum::setNumber(int num){
    if (m_nNumber != num) {
        m_nNumber = num;
        rebuildEffect();
    }
}

/*
 * rebuildEffect 重新设置每位数字
 */
void UIRollNum::rebuildEffect(){
    int i=0;
    int num = m_nNumber;
    while (1) {
        if (num<=0) {
            if(m_maxCol<=i && zeroFill)
                break;
        }
        int showNum = num%10;
        
        UINumber* pNumber = (UINumber*)numArray->objectAtIndex(i);
        pNumber->setNumber(showNum);
        i++;
        num = num/10;
    }
}

/*
 * rebuildEffect 清楚每位数字  右边为准，
 */
void UIRollNum::clearEffect(const char *name ,float w,float h){
    for(int i=0; i <numArray->count(); i++) {
        UINumber* pNumber = (UINumber *)numArray->objectAtIndex(i);
        this->removeChild(pNumber,true);
    }
    numArray->removeAllObjects();

    for (int i = 0; i < m_maxCol; i++) {
        UINumber* pNumber = UINumber::create(); //[[UINumber alloc] initWithStyle:style];
        pNumber->setTyle(style);
        pNumber->setTexture(name,w,h);
        numArray->addObject(pNumber);
        pNumber->setNumber(0);
        pNumber->setPosition(ccp(m_point.x - i*w, m_point.y));
        pNumber->setAnchorPoint(ccp(1, 0.5));
        this->addChild(pNumber,100);
    }
}

/*
 *  rebuildEffect 清楚每位数字  中心为准，
 */
void UIRollNum::clearEffect1(const char *name ,float w,float h)
{
    for(int i=0; i <numArray->count(); i++) {
        UINumber* pNumber = (UINumber *)numArray->objectAtIndex(i);
        this->removeChild(pNumber,true);
    }
    numArray->removeAllObjects();
    
    for (int i = 0; i < m_maxCol; i++) {
        UINumber* pNumber = UINumber::create(); 
        pNumber->setTyle(style);
        pNumber->setTexture(name,w,h);
        numArray->addObject(pNumber);
        pNumber->setNumber(0);
        pNumber->setPosition(ccp(m_point.x + (m_maxCol/2.0-i*1.0)*w, m_point.y));
        pNumber->setAnchorPoint(ccp(1, 0.5));
        this->addChild(pNumber,100);
    }
}

/*
 偶数: x+(m/2-i*1)*w
 奇数：x+(m/2-i*1)*w
 */

/*
 *  
 */
void UIRollNum::clearEffectSpriteFrame(const char *name ,float w,float h)
{
    for(int i=0; i <numArray->count(); i++) {
        UINumber* pNumber = (UINumber *)numArray->objectAtIndex(i);
        this->removeChild(pNumber,true);
    }
    numArray->removeAllObjects();
    
    for (int i = 0; i < m_maxCol; i++) {
        UINumber* pNumber = UINumber::create();
        pNumber->setTyle(style);
        pNumber->setTextureFromSpriteFrame(name,w,h);
        numArray->addObject(pNumber);
        pNumber->setNumber(0);
        pNumber->setPosition(ccp(m_point.x + (m_maxCol/2.0-i*1.0)*w, m_point.y));
        pNumber->setAnchorPoint(ccp(1, 0.5));
        this->addChild(pNumber,100);
    }
}

