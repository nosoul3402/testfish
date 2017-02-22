//
//  GMBillingLayer.cpp
//  FishX
//
//  Created by peng on 13-5-9.
//
//

#include "GMBillingLayer.h"
#include "../Config/GMHeaderConfig.h"
#include "../Layer/GMGameLayer.h"
#include "../Layer/GMCardLayer.h"
#include "../Layer/GMWinLayer.h"
#include "../Layer/GMIntroLayer.h"
#include "ZPJNIHelper.h"

GMBillingLayer::GMBillingLayer(){

}

GMBillingLayer::~GMBillingLayer(){
    setStartBliling(false);
    _delegate = NULL;
}

bool GMBillingLayer::init(){
    bool bRet = false;
    
    do {
        CC_BREAK_IF(!CCLayerColor::initWithColor(ccc4(0, 0, 0, 200)));
//        this->initDialog();
        bRet = true;
        m_pTaskTime2 = NULL;
        validtionbg2 = NULL;
        _isClickClose = true;

		purchaseBg		= NULL;
		_delegate		= NULL;
		m_pTaskTime1	= NULL;
		m_pTaskTime2	= NULL;
		validtionbg2	= NULL;
		charging005e	= NULL;
		textfield		= NULL;

        showKeyboard = false;
    } while (0);
    
    return bRet;
}

//#pragma mark - 
CCSprite* GMBillingLayer::setSprite(const char *name,CCPoint pos,CCPoint aPos,CCNode *node,int zOrder,float scale)
{
    CCSprite *tempSprite = CCSprite::create(name);
    tempSprite->setPosition(pos);
    tempSprite->setAnchorPoint(aPos);
    node->addChild(tempSprite,zOrder);
    SetScale2(tempSprite,scale);
    return tempSprite;
}

void GMBillingLayer::showLabelTTF(const char *string,CCSize size,const ccColor3B& color3){
    int font = 0;
    if (GMPublicMethod::getChangeTime(s_year,s_mon,s_day))
        font = 15;
    else
        font = 25;
    CCLabelTTF *labelTTF = CCLabelTTF::create(string,"Marker Felt",font,size, kCCTextAlignmentCenter);
    labelTTF->setVerticalAlignment(kCCVerticalTextAlignmentCenter);
    labelTTF->setAnchorPoint(ccp(0, 0));
    labelTTF->setPosition( ccp( (WINSIZE_W-size.width)/2, 1*Scale_X ));
    labelTTF->setColor(color3);
    this->addChild(labelTTF,0);
}

void GMBillingLayer::showLabelTTF1(CCNode*node,const char *string,CCPoint point,CCSize size,const ccColor3B& color3){
    CCLabelTTF *labelTTF = CCLabelTTF::create(string,"Marker Felt",20,size, kCCTextAlignmentCenter);
    labelTTF->setVerticalAlignment(kCCVerticalTextAlignmentCenter);
    labelTTF->setAnchorPoint(ccp(0, 0));
    labelTTF->setPosition( point);
    labelTTF->setColor(color3);
    node->addChild(labelTTF,0);
}

//#pragma mark - 正版验证提示
void GMBillingLayer::showGenuineValidationTips(){
    ZPLog("测试111111");
    CCSprite *validtionbg = setSprite("billingPic/charging022.png",ccp(WINSIZE_W/2,WINSIZE_H/2),ccp(0.5,0.5),this,0,Scale_Y);
    
    validtionbg2 = NULL;
    if (GMPublicMethod::getChangeTime(s_year,s_mon,s_day)){
        validtionbg2 = setSprite("billingPic/charging025.png",ccp(WINSIZE_W/2,WINSIZE_H/2),ccp(0.5,0.5),this,1,Scale_Y);    
        ZPLog("测试1112222");
        CCRotateBy *rotate = CCRotateBy::create(0.5, 30);
        CCRepeatForever *repeateF = CCRepeatForever::create(rotate);
        validtionbg2->runAction(repeateF);
    }
    ZPLog("测试133312222");
    float validtionbgW = GetSize(validtionbg).width;
    float validtionbgH = GetSize(validtionbg).height;

    CCSprite *tips1 = setSprite("billingPic/charging024.png",ccp(validtionbgW/2,validtionbgH),ccp(0.5,1),validtionbg,1,1);

    CCPoint point = ccp(validtionbgW/2,validtionbgH-GetSize(tips1).height+10);
    setSprite("billingPic/charging026.png",point,ccp(0.5,1),validtionbg,1,1);
    
    CCMenuItem *closeItem = CCMenuItemImage::create("billingPic/charging001.png", "billingPic/charging002.png", this, menu_selector(GMBillingLayer::closeAction));
    closeItem->setAnchorPoint(ccp(0,0));
    closeItem->setPosition(ccp(validtionbgW-100,validtionbgH-100));
    
    CCMenuItem *sureItem = CCMenuItemImage::create("billingPic/charging028.png", "billingPic/charging029.png", this, menu_selector(GMBillingLayer::sureAction));
    sureItem->setPosition(ccp(validtionbgW/2,validtionbgH/2+10));
    m_pMenu = CCMenu::create(closeItem,sureItem,NULL);
    m_pMenu->setPosition(CCPointZero);
    validtionbg->addChild(m_pMenu,1,1);

    point = ccp(validtionbgW/2,validtionbgH/2-48/2-5);
    CCSprite*temp1 = setSprite("billingPic/charging027.png",point,ccp(0.5,1),validtionbg,1,1);

    point = ccp(validtionbgW/2,-28);
    CCSprite*temp2 = setSprite("billingPic/charging023.png",point,ccp(0.5,0),validtionbg,1,1);
    
    
    ZPLog("测试2");
    CCSprite *junengEffect = CCSprite::createWithSpriteFrameName("changeboom6001.png");
    char junnengName[30] = {0};
    sprintf(junnengName,"changeboom%d",6);
    junengEffect->stopAllActions();
    GMPublicMethod::setRepeatAnimation(junengEffect, 1, 9, junnengName,"png",0.1,true);
    validtionbg->addChild(junengEffect,3);
    junengEffect->setPosition(ccp(validtionbgW/2,80));
    ZPLog("测试3333");
    
    if (GMPublicMethod::getChangeTime(s_year,s_mon,s_day)){}
    else {
        sureItem->setPosition(ccp(validtionbgW/2,40));
        temp1->setPosition(ccp(validtionbgW/2,validtionbgH/2+40));
        temp2->setPosition(ccp(validtionbgW/2,40));
        junengEffect->setPosition(ccp(validtionbgW/2,145));
    }
    ZPLog("测试233333");
#if (JNIHELPER_INDEX == JNIHELPER_TengXun)
    int operatorsIndex = ZPJNIHelper::getOperators();
    CCString *string = NULL;
    if(operatorsIndex == 1){
        string = CCString::create("需信息费4元，发送1条短信，4元/条（不含通信费）");
    }
    else if(operatorsIndex == 2){
        string = CCString::create("需信息费4元，发送2条短信，2元/条（不含通信费）");
    }
    else if(operatorsIndex == 3){
        string = CCString::create("需信息费4元，发送4条短信，1元/条（不含通信费）");
    }
    else{
        string = CCString::create("无卡模式");
    }
    if(string)
        showLabelTTF(string->getCString(),CCSize(WINSIZE_W, 69),ccWHITE);
#endif
}

//index = 0 正常， index = 1 进无尽模式 index
void GMBillingLayer::showSecondaryConfirmationTips(int index){
    CCPoint point = ccp(WINSIZE_W/2+(375*0.3*Scale_X)/2,WINSIZE_H/2);
    purchaseBg = setSprite("billingPic/charging003.png",point,ccp(0.5,0.5), this, 0, Scale_X);
    
    float purchaseBgW = 480;
    float purchaseBgH = GetSize(purchaseBg).height;
    point = ccp(0,0);
    if(index == 0){
        setSprite("billingPic/charging004.png",point,ccp(0.4,0.1),purchaseBg,0,1);
        point = ccp(purchaseBgW/2,purchaseBgH-20);//超级礼包
        setSprite("billingPic/charging056.png",point,ccp(0.5,0),purchaseBg,0,1);
        
        point = ccp(purchaseBgW/2-35,purchaseBgH+20);
        CCSprite*temp1 = setSprite("billingPic/charging023.png",point,ccp(0.5,1),purchaseBg,0,1);
    
        point = ccp(purchaseBgW/2+50,purchaseBgH-60);
        CCSprite*temp2 = setSprite("billingPic/charging057.png",point,ccp(0,1),purchaseBg,0,1);
        
        point = ccp(purchaseBgW/2+20,25);
        CCSprite*temp3 = setSprite("billingPic/charging058.png",point,ccp(0.5,0),purchaseBg,0,1);
        if (GMPublicMethod::getChangeTime(s_year,s_mon,s_day)){
            
        }
        else {
            temp1->setPosition(ccp(purchaseBgW/2-85,purchaseBgH-20));
            temp2->setPosition(ccp(purchaseBgW/2+30,purchaseBgH-60));
            temp3->setPosition(ccp(purchaseBgW/2+10,purchaseBgH-55));
            temp3->setScale(0.8);
        }
    }
    else if(index == 1) {
        setSprite("billingPic/charging004.png",point,ccp(0.4,0.1),purchaseBg,0,1);
        
        point = ccp(purchaseBgW/2,purchaseBgH-20);
        setSprite("billingPic/charging061.png",point,ccp(0.5,1),purchaseBg,0,1);
        
        if (GMPublicMethod::getChangeTime(s_year,s_mon,s_day))
            point = ccp(purchaseBgW/2+20,25);
        else
            point = ccp(purchaseBgW/2+20,purchaseBgH/2-40);
        setSprite("billingPic/charging062.png",point,ccp(0.5,0),purchaseBg,0,1);
    }
    
    CCMenuItem *closeItem = CCMenuItemImage::create("billingPic/charging001.png", "billingPic/charging002.png", this, menu_selector(GMBillingLayer::closeAction));
    closeItem->setAnchorPoint(ccp(1,1));
    closeItem->setPosition(ccp(purchaseBgW,purchaseBgH));
    
    CCMenuItem *sureItem= CCMenuItemImage::create("billingPic/charging028.png", "billingPic/charging029.png", this, menu_selector(GMBillingLayer::sureAction));
    
    if (GMPublicMethod::getChangeTime(s_year,s_mon,s_day))
        point = ccp(purchaseBgW/2-40,purchaseBgH/2-30);
    else
        point = ccp(purchaseBgW/2+100,55);
    sureItem->setPosition( point );
    
    m_pMenu = CCMenu::create(sureItem,closeItem,NULL);
    m_pMenu->setPosition(CCPointZero);
    purchaseBg->addChild(m_pMenu,1,1);
    
#if (JNIHELPER_INDEX == JNIHELPER_TengXun)
    int operatorsIndex = ZPJNIHelper::getOperators();
    ZPLog("operatorsIndex  operatorsIndex   %d",operatorsIndex);
    CCString *string = NULL;
    if(operatorsIndex == 1){
        string = CCString::create("需信息费4元，发送1条短信，4元/条（不含通信费）");
    }
    else if(operatorsIndex == 2){
        string = CCString::create("需信息费4元，发送2条短信，2元/条（不含通信费）");
    }
    else if(operatorsIndex == 3){
        string = CCString::create("需信息费4元，发送4条短信，1元/条（不含通信费）");
    }
    else{
        string = CCString::create("无卡模式");
    }
    if(string)
        showLabelTTF(string->getCString(),CCSize(WINSIZE_W, 69),ccWHITE);
#endif
    
}

void GMBillingLayer::removeGenuineValidationTips(){
    closeAction(NULL);
}

//#pragma mark - 显示购买能量
// type == 1 免费送  2  购买
void GMBillingLayer::showThePurchaseOfEnergy(int type,int index){
    _type = type;
	_type = 2;
    CCPoint point = ccp(WINSIZE_W/2+(375*0.3*Scale_X)/2,WINSIZE_H/2);
    purchaseBg = setSprite("billingPic/charging003.png",point,ccp(0.5,0.5), this, 0, Scale_X);
    
    float purchaseBgW = 480;
    float purchaseBgH = GetSize(purchaseBg).height;
    point = ccp(0,0);
    setSprite("billingPic/charging004.png",point,ccp(0.4,0.1),purchaseBg,0,1);
    point = ccp(purchaseBgW/2,purchaseBgH-20);
    if(type == 1)
        setSprite("billingPic/charging005a2.png",point,ccp(0.5,0),purchaseBg,0,1);
    else if(type == 2)
        setSprite("billingPic/charging005.png",point,ccp(0.5,0),purchaseBg,0,1);
    point = ccp(purchaseBgW/2,purchaseBgH-25);
    setSprite("billingPic/charging005b.png",point,ccp(0.5,1),purchaseBg,0,1);
    
    CCMenuItem *closeItem = CCMenuItemImage::create("billingPic/charging001.png", "billingPic/charging002.png", this, menu_selector(GMBillingLayer::closeAction));
    closeItem->setAnchorPoint(ccp(1,1));
    closeItem->setPosition(ccp(purchaseBgW,purchaseBgH));
    
    CCMenuItem *sureItem = CCMenuItemImage::create("billingPic/charging028.png", "billingPic/charging029.png", this, menu_selector(GMBillingLayer::sureAction));
    
    if (GMPublicMethod::getChangeTime(s_year,s_mon,s_day))
        point = ccp(purchaseBgW/2,purchaseBgH/2-20);
    else 
        point = ccp(purchaseBgW/2+110,55);
    sureItem->setPosition(point);
    
    m_pMenu = CCMenu::create(sureItem,closeItem,NULL);
    m_pMenu->setPosition(CCPointZero);
    purchaseBg->addChild(m_pMenu,1,1);
    
    if (GMPublicMethod::getChangeTime(s_year,s_mon,s_day))
        point = ccp(purchaseBgW/2+20,25);
    else
        point = ccp(purchaseBgW/2,purchaseBgH/2-30);
    
    
    if(type == 1){
        if(index == 1)
            setSprite("billingPic/charging005c3.png",point,ccp(0.5,0),purchaseBg,0,1);
        else if(index == 2)
            setSprite("billingPic/charging005c2.png",point,ccp(0.5,0),purchaseBg,0,1);
    }else if(type == 2){
        setSprite("billingPic/charging005c.png",point,ccp(0.5,0),purchaseBg,0,1);
    }
    
    if (GMPublicMethod::getChangeTime(s_year,s_mon,s_day))
        point = ccp(purchaseBgW/2+172/2+27/2+10,purchaseBgH/2-76/2);
    else
        point = ccp(purchaseBgW/2-120,purchaseBgH/2-76);

    showTime(purchaseBg,point);
    
#if (JNIHELPER_INDEX == JNIHELPER_TengXun)
    if(type == 1){
        if(index == 1)
            showLabelTTF("再等待30秒可以领取1000能量哦！",CCSize(WINSIZE_W, 69),ccWHITE);
        else if(index == 2)
            showLabelTTF("再等待45秒可以领取5000能量哦！",CCSize(WINSIZE_W, 69),ccWHITE);
    }else if(type == 2){
        int operatorsIndex = ZPJNIHelper::getOperators();
        CCString *string = NULL;
        if(operatorsIndex == 1 || operatorsIndex == 2){
            string = CCString::create("需信息费2元，发送1条短信，2元/条（不含通信费）");
        }
        else if(operatorsIndex == 3){
            string = CCString::create("需信息费2元，发送2条短信，1元/条（不含通信费）");
        }
        else{
            string = CCString::create("无卡模式");
        }
        if(string)
            showLabelTTF(string->getCString(),CCSize(WINSIZE_W, 69),ccWHITE);
    }
#endif
}

//#pragma mark - 显示武器升级
void GMBillingLayer::showWeaponUpgrades(int index){
    CCPoint point = ccp(WINSIZE_W/2,WINSIZE_H/2);
    purchaseBg = setSprite("billingPic/charging003.png",point,ccp(0.5,0.5), this, 0, Scale_X);
    
    float purchaseBgW = 480;
    float purchaseBgH = GetSize(purchaseBg).height;
    if(index != 6){
        point = ccp(purchaseBgW/2,purchaseBgH);
        setSprite("billingPic/charging010.png",point,ccp(0.5,0.1),purchaseBg,0,1);
        point = ccp(purchaseBgW/2-12,purchaseBgH);
        if(index == 3)
            setSprite("billingPic/charging011.png",point,ccp(0.5,0),purchaseBg,0,1);
        else if(index == 4)
            setSprite("billingPic/charging012.png",point,ccp(0.5,0),purchaseBg,0,1);
        else if(index == 5)
            setSprite("billingPic/charging013.png",point,ccp(0.5,0),purchaseBg,0,1);
    }
    point = ccp(purchaseBgW/2,purchaseBgH-25);
    CCSprite *temp2 = setSprite("billingPic/charging009a.png",point,ccp(0.5,1),purchaseBg,0,1);
    CCMenuItem *closeItem = CCMenuItemImage::create("billingPic/charging001.png", "billingPic/charging002.png", this, menu_selector(GMBillingLayer::closeAction));
    closeItem->setAnchorPoint(ccp(1,1));
    closeItem->setPosition(ccp(purchaseBgW,purchaseBgH));
    
    CCMenuItem *sureItem = CCMenuItemImage::create("billingPic/charging009c.png", "billingPic/charging009c2.png", this, menu_selector(GMBillingLayer::sureAction));
    
    if (GMPublicMethod::getChangeTime(s_year,s_mon,s_day))
        point = ccp(purchaseBgW/2,purchaseBgH/2+10);
    else
        point =  ccp(purchaseBgW/2+140,50);
    sureItem->setPosition(point);
    m_pMenu = CCMenu::create(sureItem,closeItem,NULL);
    m_pMenu->setPosition(CCPointZero);
    purchaseBg->addChild(m_pMenu,1,1);
    
    if (GMPublicMethod::getChangeTime(s_year,s_mon,s_day))
        point = ccp(50,purchaseBgH/2+10);
    else
        point = ccp(50,purchaseBgH/2+10);
    showTime(purchaseBg,point);
    
    point = ccp(15,8);
    setSprite("billingPic/charging009.png",point,ccp(0,0),purchaseBg,0,1);
    
    point = ccp(purchaseBgW-18,8);
    CCSprite *temp5 = setSprite("billingPic/charging009b.png",point,ccp(1,0),purchaseBg,0,1);
    
    if (GMPublicMethod::getChangeTime(s_year,s_mon,s_day)){
    }
    else {
        temp2->setPosition(ccp(purchaseBgW/2-30,purchaseBgH-18));
        temp5->setPosition(ccp(purchaseBgW+5,purchaseBgH/2-70));
    }
    
#if (JNIHELPER_INDEX == JNIHELPER_TengXun)  
    int operatorsIndex = ZPJNIHelper::getOperators();
    CCString *string = NULL;
    if(operatorsIndex == 1 || operatorsIndex == 2){
        string = CCString::create("需信息费2元，发送1条短信，2元/条（不含通信费）");
    }
    else if(operatorsIndex == 3){
        string = CCString::create("需信息费2元，发送2条短信，1元/条（不含通信费）");
    }
    else{
        string = CCString::create("无卡模式");
    }
    if(string)
        showLabelTTF(string->getCString(),CCSize(WINSIZE_W, 69),ccWHITE);
#endif
}

//#pragma mark - 显示购买技能
void GMBillingLayer::showPurchasingSkills(){
    CCPoint point = ccp(WINSIZE_W/2+(255*0.4*Scale_X)/2,WINSIZE_H/2);
    purchaseBg = setSprite("billingPic/charging003.png",point,ccp(0.5,0.5), this, 0, Scale_X);
    
    float purchaseBgW = 480;
    float purchaseBgH = GetSize(purchaseBg).height;
    point = ccp(purchaseBgW/2-5,purchaseBgH+5);
    setSprite("billingPic/charging031.png",point,ccp(0.5,0.3),purchaseBg,0,1);
    point = ccp(0,-5);
    setSprite("billingPic/charging007.png",point,ccp(0.5,0),purchaseBg,0,1);
    point = ccp(purchaseBgW/2,purchaseBgH-20);
    setSprite("billingPic/charging030.png",point,ccp(0.5,1),purchaseBg,0,1);
    point = ccp(purchaseBgW/2,purchaseBgH-70);
    setSprite("billingPic/charging032.png",point,ccp(0.5,1),purchaseBg,0,1);
    
    CCMenuItem *closeItem = CCMenuItemImage::create("billingPic/charging001.png", "billingPic/charging002.png", this, menu_selector(GMBillingLayer::closeAction));
    closeItem->setAnchorPoint(ccp(1,1));
    closeItem->setPosition(ccp(purchaseBgW,purchaseBgH));
    
    CCMenuItem *sureItem = CCMenuItemImage::create("billingPic/charging034.png", "billingPic/charging035.png", this, menu_selector(GMBillingLayer::sureAction));
    
    if (GMPublicMethod::getChangeTime(s_year,s_mon,s_day))
        point = ccp(purchaseBgW/2,purchaseBgH/2-40);
    else
        point = ccp(purchaseBgW/2+90,60);
    sureItem->setPosition( point );
    m_pMenu = CCMenu::create(sureItem,closeItem,NULL);
    m_pMenu->setPosition(CCPointZero);
    purchaseBg->addChild(m_pMenu,1,1);
    
    if (GMPublicMethod::getChangeTime(s_year,s_mon,s_day))
        point = ccp(purchaseBgW/2+172/2+27/2+10,purchaseBgH/2-76/2-20);
    else
        point = ccp(purchaseBgW/2-100,60);
    showTime(purchaseBg,point);
    
    if (GMPublicMethod::getChangeTime(s_year,s_mon,s_day))
        point = ccp(purchaseBgW-20,18);
    else
        point = ccp(purchaseBgW-30,100);
    setSprite("billingPic/charging008.png",point,ccp(1,0),purchaseBg,0,1);
#if (JNIHELPER_INDEX == JNIHELPER_TengXun)
    int operatorsIndex = ZPJNIHelper::getOperators();
    CCString *string = NULL;
    if(operatorsIndex == 1 || operatorsIndex == 2){
        string = CCString::create("需信息费2元，发送1条短信，2元/条（不含通信费）");
    }
    else if(operatorsIndex == 3){
        string = CCString::create("需信息费2元，发送2条短信，1元/条（不含通信费）");
    }
    if(string)
        showLabelTTF(string->getCString(),CCSize(WINSIZE_W, 69),ccWHITE);
#endif
}

//#pragma mark - 91购买能量界面
void GMBillingLayer::show91Shop(){
    CCPoint point = ccp(WINSIZE_W/2+(105*0.4*Scale_X)/2,WINSIZE_H/2);
    purchaseBg = setSprite("billingPic/charging003.png",point,ccp(0.5,0.5), this, 0, Scale_X);
    
    float purchaseBgW = 480;
    float purchaseBgH = GetSize(purchaseBg).height;
    
    point = ccp(purchaseBgW/2,purchaseBgH);
    setSprite("billingPic/charging065.png",point,ccp(0.5,0.5),purchaseBg,0,1);
    
    CCMenuItem *closeItem = CCMenuItemImage::create("billingPic/charging001.png", "billingPic/charging002.png", this, menu_selector(GMBillingLayer::closeAction));
    closeItem->setAnchorPoint(ccp(1,1));
    closeItem->setPosition(ccp(purchaseBgW,purchaseBgH));
    
  
    CCMenuItem *item1 = CCMenuItemImage::create("billingPic/charging066.png", NULL, this, menu_selector(GMBillingLayer::sureAction));
    item1->setPosition(ccp((GetSize(item1).width/2)+20,purchaseBgH/2));
    item1->setTag(1);
    point = ccp(GetSize(item1).width,GetSize(item1).height);
    setSprite("billingPic/charging067.png",point,ccp(1,1),item1,0,1);
    
    point = ccp(GetSize(item1).width/2,GetSize(item1).height/2);
    setSprite("billingPic/charging073.png",point,ccp(0.5,0.5),item1,0,1);
    
    CCMenuItem *item2 = CCMenuItemImage::create("billingPic/charging066.png", NULL, this, menu_selector(GMBillingLayer::sureAction));
    item2->setPosition(ccp(purchaseBgW/2,purchaseBgH/2));
    item2->setTag(2);
    
    point = ccp(GetSize(item2).width,GetSize(item2).height);
    setSprite("billingPic/charging068.png",point,ccp(1,1),item2,0,1);
    
    point = ccp(GetSize(item2).width/2,GetSize(item2).height/2);
    setSprite("billingPic/charging074.png",point,ccp(0.5,0.5),item2,0,1);
    
    CCMenuItem *item3 = CCMenuItemImage::create("billingPic/charging066.png", NULL, this, menu_selector(GMBillingLayer::sureAction));
    item3->setPosition(ccp(purchaseBgW/2+GetSize(item1).width+20,purchaseBgH/2));
    item3->setTag(3);
    
    point = ccp(GetSize(item3).width,GetSize(item3).height);
    setSprite("billingPic/charging069.png",point,ccp(1,1),item3,0,1);
    
    point = ccp(GetSize(item3).width/2,GetSize(item3).height/2);
    setSprite("billingPic/charging075.png",point,ccp(0.5,0.5),item3,0,1);
    
    m_pMenu = CCMenu::create(item1,item2,item3,closeItem,NULL);
    m_pMenu->setPosition(CCPointZero);
    purchaseBg->addChild(m_pMenu,1,1);
 
    for (int i = 0; i < 3; i++) {
        point = ccp(80+i*(160),50);
        char picName[30] = {0};
        sprintf(picName, "billingPic/charging07%d.png",i);
        setSprite(picName,point,ccp(0.5,0.5),purchaseBg,0,1);
    }
}

//#pragma mark - 91移动联网付费
void GMBillingLayer::show91MobileView(){
#if (JNIHELPER_INDEX == JNIHELPER_91_IOS)
    float purchaseBgW = 480;
    CCPoint point = ccp((WINSIZE_W-purchaseBgW*Scale_X)/2,WINSIZE_H/2);
    purchaseBg = setSprite("billingPic/charging003.png",point,ccp(0,0.5), this, 0, Scale_X);
    
    float purchaseBgH = GetSize(purchaseBg).height;
    
    point = ccp(purchaseBgW/2,purchaseBgH);
    setSprite("91jifei/jifei006.png",point,ccp(0.5,0.2),purchaseBg,1,1);
    
    CCMenuItem *closeItem = CCMenuItemImage::create("billingPic/charging001.png", "billingPic/charging002.png", this, menu_selector(GMBillingLayer::closeAction));
    closeItem->setAnchorPoint(ccp(1,1));
    closeItem->setPosition(ccp(purchaseBgW,purchaseBgH));
    
    CCMenuItem *textFieldItem = CCMenuItemImage::create("91jifei/jifei008.png","91jifei/jifei008.png", this, menu_selector(GMBillingLayer::textFieldAction));
    textFieldItem->setAnchorPoint(ccp(0,0.5));
    textFieldItem->setPosition(ccp(30, purchaseBgH*0.5-20));
    //找好友代付
    CCMenuItem *friendItem = CCMenuItemImage::create("91jifei/jifei011.png","91jifei/jifei012.png", this, menu_selector(GMBillingLayer::getFriendAction));
    friendItem->setAnchorPoint(ccp(0,0.5));
    friendItem->setPosition(ccp(purchaseBgW/2+50, purchaseBgH*0.5-20));
    
    //获取验证码
    CCMenuItem *getCode = CCMenuItemImage::create("91jifei/jifei009.png","91jifei/jifei010.png", this, menu_selector(GMBillingLayer::getCodeAction));
    getCode->setAnchorPoint(ccp(0.5,0.5));
    getCode->setPosition(ccp(purchaseBgW/2,0));
    
    m_pMenu = CCMenu::create(closeItem,textFieldItem,friendItem,getCode,NULL);
    m_pMenu->setPosition(CCPointZero);
    purchaseBg->addChild(m_pMenu,1,1);
    
    point = ccp(purchaseBgW/2,purchaseBgH-10);
    setSprite("91jifei/jifei007.png",point,ccp(0.5,1),purchaseBg,1,1);//尊敬的用户……
    //购买技能名称
    char skillName[30] = {0};
    int index = GMPublicMethod::sharedPublicMethod()->getBillingIndex();
    int tempIndex = 0;
   
    if(index == 1)     {    tempIndex = 2;  }
    else if(index == 2){    tempIndex = 2;  }
    else if(index == 3){    tempIndex = 4;  }
    else if(index == 4){    tempIndex = 9;  }
    else if(index == 5){    tempIndex = 2;  }
    else if(index == 6){    tempIndex = 4;  }
    if(index>0){
        int picIndex = index;
        if(index == 6){picIndex = 16;}
        sprintf(skillName, "91jifei/jifei%03d.png",picIndex);
        point = ccp(purchaseBgW/2,purchaseBgH-40);
        setSprite(skillName,point,ccp(0.5,1),purchaseBg,1,1);
    }
//    CCString * string = CCString::create("共需支付话费 2 元(折合200点)\n请输入您的手机号码以获取验证码");
    CCString * string = CCString::createWithFormat("共需支付话费 %d 元(折合%d点)\n请输入您的手机号码以获取验证码",tempIndex,tempIndex*100);
    showLabelTTF1(purchaseBg,string->getCString(),ccp(0,purchaseBgH-150),CCSize(purchaseBgW, 69),ccc3(211,105,58));


    textfield = CCTextFieldTTF::textFieldWithPlaceHolder("输入手机号", "Thonburi",25);
    textfield->setPosition(ccp((textFieldItem->boundingBox().size.width)/2,(textFieldItem->boundingBox().size.height)/2));
    textfield->setDimensions(CCSize(textFieldItem->boundingBox().size.width,textFieldItem->boundingBox().size.height-20));
    //textfield->setKeyboardType(KEY_BOARD_TYPE_NORMAL);
    //textfield->setString(PublicCPP::getPhoneNum());
    textfield->setColor(ccBLACK);
    textFieldItem->addChild(textfield);
//    绑定接口
    textfield->setDelegate(this);
//开启输入
//    关闭输入
//    textfield->detachWithIME();
    
    CCString *string2 = CCString::create("游戏名称:捕鱼大冒险\n客服电话:027-87778199");
    showLabelTTF1(purchaseBg,string2->getCString(),ccp(0,35),CCSize(purchaseBgW, 69),ccc3(211,105,58));
#endif
}

void GMBillingLayer::show91MobileView2(){
#if (JNIHELPER_INDEX == JNIHELPER_91_IOS)
    float purchaseBgW = 480;
    CCPoint point = ccp((WINSIZE_W-purchaseBgW*Scale_X)/2,WINSIZE_H/2);
    purchaseBg = setSprite("billingPic/charging003.png",point,ccp(0,0.5), this, 0, Scale_X);
    
    float purchaseBgH = GetSize(purchaseBg).height;
    
    point = ccp(purchaseBgW/2,purchaseBgH);
    setSprite("91jifei/jifei006.png",point,ccp(0.5,0.2),purchaseBg,1,1);
    
    CCMenuItem *closeItem = CCMenuItemImage::create("billingPic/charging001.png", "billingPic/charging002.png", this, menu_selector(GMBillingLayer::closeAction));
    closeItem->setAnchorPoint(ccp(1,1));
    closeItem->setPosition(ccp(purchaseBgW,purchaseBgH));
    
    CCMenuItem *textFieldItem = CCMenuItemImage::create("91jifei/jifei008.png","91jifei/jifei008.png", this, menu_selector(GMBillingLayer::textFieldAction));
    textFieldItem->setAnchorPoint(ccp(0.5,0.5));
    textFieldItem->setPosition(ccp(purchaseBgW/2, purchaseBgH*0.5-20));
    //确认
    CCMenuItem *getCode = CCMenuItemImage::create("91jifei/jifei014.png","91jifei/jifei015.png", this, menu_selector(GMBillingLayer::sendCodeAction));
    getCode->setAnchorPoint(ccp(0.5,0.5));
    getCode->setPosition(ccp(purchaseBgW/2,0));
    
    m_pMenu = CCMenu::create(closeItem,textFieldItem,getCode,NULL);
    m_pMenu->setPosition(CCPointZero);
    purchaseBg->addChild(m_pMenu,1,1);
    
    point = ccp(purchaseBgW/2,purchaseBgH-10);
    setSprite("91jifei/jifei007.png",point,ccp(0.5,1),purchaseBg,1,1);//尊敬的用户……
    
    //购买技能名称
    char skillName[30] = {0};
    int index = GMPublicMethod::sharedPublicMethod()->getBillingIndex();
    int tempIndex = 0;
    if(index == 1){         tempIndex = 2;  }
    else if(index == 2){    tempIndex = 2;  }
    else if(index == 3){    tempIndex = 4;  }
    else if(index == 4){    tempIndex = 9;  }
    else if(index == 5){    tempIndex = 2;  }
    else if(index == 6){    tempIndex = 4;  }
    if(index>0){
        int picIndex = index;
        if(index == 6){picIndex = 16;}
        sprintf(skillName, "91jifei/jifei%03d.png",picIndex);
        point = ccp(purchaseBgW/2,purchaseBgH-40);
        setSprite(skillName,point,ccp(0.5,1),purchaseBg,1,1);
    }
    
    CCString * string = CCString::createWithFormat("共需支付话费 %d 元(折合%d点)",tempIndex,tempIndex*100);
    showLabelTTF1(purchaseBg,string->getCString(),ccp(0,purchaseBgH-135),CCSize(purchaseBgW, 69),ccc3(211,105,58));
   
    point = ccp(purchaseBgW/2,purchaseBgH/2+30);
    setSprite("91jifei/jifei013.png",point,ccp(0.5,1),purchaseBg,1,1);
    
    textfield = CCTextFieldTTF::textFieldWithPlaceHolder("输入验证码", "Thonburi",25);
    textfield->setPosition(ccp((textFieldItem->boundingBox().size.width)/2,(textFieldItem->boundingBox().size.height)/2));
    textfield->setDimensions(CCSize(textFieldItem->boundingBox().size.width,textFieldItem->boundingBox().size.height-20));
    //textfield->setKeyboardType(KEY_BOARD_TYPE_NORMAL);
    textfield->setColor(ccBLACK);
    textFieldItem->addChild(textfield);
    //绑定接口
    textfield->setDelegate(this);
    
    CCString *string2 = CCString::create("提示短信验证码在五分钟内有效，超过时间仍未收到验证码，请您稍后再试");
    showLabelTTF1(purchaseBg,string2->getCString(),ccp(10,35),CCSize(purchaseBgW-20, 69),ccc3(211,105,58));
#endif
}

void GMBillingLayer::textFieldAction(CCObject *object){
    
    CCMoveTo *moveTo = NULL;
    if(showKeyboard ==false){
        textfield->attachWithIME();
        moveTo = CCMoveTo::create(0.1, ccp(purchaseBg->getPosition().x,WINSIZE_H/2+WINSIZE_H/4));
        showKeyboard = true;
    }
    else {
        textfield->detachWithIME();
        moveTo = CCMoveTo::create(0.1, ccp(purchaseBg->getPosition().x,WINSIZE_H/2));
        showKeyboard = false;
    }
    purchaseBg->runAction(moveTo);
}

void GMBillingLayer::getFriendAction(CCObject *object){
#if (JNIHELPER_INDEX == JNIHELPER_91_IOS)
    //PublicCPP::addPicker();
    this->schedule(schedule_selector(GMBillingLayer::check91MobileStatus));
#endif
}

void GMBillingLayer::getCodeAction(CCObject *object){
    if(textfield && strlen ( textfield->getString() ) > 0){
        _isClickClose = false;
#if (JNIHELPER_INDEX == JNIHELPER_91_IOS)
        billingIndex = GMPublicMethod::sharedPublicMethod()->getBillingIndex();
        
        GMPublicMethod::sharedPublicMethod()->setPhoneNumber(textfield->getString());
       
//        CCString *temp = CCString::createWithFormat("%s",textfield->getString());
//        GMPublicMethod::sharedPublicMethod()->setNumber(temp);
        
        //PublicCPP::payment91MobileNet(billingIndex,textfield->getString() ,NULL);
        //PublicCPP::setPaymentSuccess(0);
        this->schedule(schedule_selector(GMBillingLayer::check91BillingCode));
#endif
    }
}

void GMBillingLayer::sendCodeAction(CCObject *object){
#if (JNIHELPER_INDEX == JNIHELPER_91_IOS)
    if(textfield && strlen ( textfield->getString() ) > 0){
        billingIndex = GMPublicMethod::sharedPublicMethod()->getBillingIndex();
        
        const char*temp = GMPublicMethod::sharedPublicMethod()->getPhoneNumber();
        //PublicCPP::payment91MobileNet(billingIndex,temp,textfield->getString());
        //PublicCPP::setPaymentSuccess(0);
        this->schedule(schedule_selector(GMBillingLayer::check91BillingCode));
    }
#endif
}

//91 移动 获取好友手机号
void GMBillingLayer::check91MobileStatus(float dt){
#if (JNIHELPER_INDEX == JNIHELPER_91_IOS)
    /*int phontStatus = PublicCPP::getMobileStatus();
    if(phontStatus!=0){
        if(phontStatus == 1){
            textfield->setString(PublicCPP::getPhoneNum());
        }
        this->unschedule(schedule_selector(GMBillingLayer::check91MobileStatus));
    }*/
#endif
}

//91 移动 获取验证码
void GMBillingLayer::check91BillingCode(float dt){
#if (JNIHELPER_INDEX == JNIHELPER_91_IOS)
    /*int phontStatus = PublicCPP::getPaymentSuccess();
    if(phontStatus!=0){
        this->unschedule(schedule_selector(GMBillingLayer::check91BillingCode));
        if(phontStatus == 1){
           _isClickClose = false;
        }
        else {
            _isClickClose = true;
        }
        closeAction();
    }*/
#endif
}


//#pragma mark - sure  close
void GMBillingLayer::sureAction(CCObject *pSender){
	CCMenuItem *item = (CCMenuItem *)pSender;

    ZPLog("sureAction");
    _isClickClose = true;
    _itemTag = item->getTag();
    if((_index == 1 || _index == 6) && _startBliling == true){
        if(validtionbg2){
            GMAudioPlay::sharedAudioPlay()->playOtherEffect(Audio_Button,false);
            validtionbg2->stopAllActions();
            CCScaleTo *scale1 = CCScaleTo::create(0.5, 0);
            CCMoveTo *moveTo = CCMoveTo::create(0.5,ccp(validtionbg2->getPosition().x,65));
            CCFiniteTimeAction *spawn = CCSpawn::create(scale1,moveTo,NULL);
            CCCallFunc *callFun = CCCallFunc::create(this, callfunc_selector(GMBillingLayer::removeGenuineValidationTips));
            CCFiniteTimeAction *sequence = CCSequence::create(spawn,callFun,NULL);
            validtionbg2->runAction(sequence);
        }
        else {
            closeAction(NULL);
        }
    }
    else {
        closeAction(NULL);
    }
}

void GMBillingLayer::closeAction(CCObject *pSender){
//    this->unschedule(schedule_selector(GMBillingLayer::updata));
    this->cleanup();
    GMAudioPlay::sharedAudioPlay()->playOtherEffect(Audio_Button,false);
    switch (classType) {
        case 1:{
#if (JNIHELPER_INDEX == JNIHELPER_91_IOS || JNIHELPER_INDEX == JNIHELPER_91_Android)
            _type = _itemTag;
#endif
			if (_delegate) {
				((GMGameLayer*)_delegate)->checkBillingPoint(0);
                ((GMGameLayer*)_delegate)->removeBilling(_index,_isClickClose,_type);
			}
        }   break;
        case 2:{
            if (_delegate)
                ((GMCardLayer*)_delegate)->removeBilling(_index,_isClickClose,_itemTag);
        }   break;
        case 3:{
            if (_delegate)
                ((GMWinLayer*)_delegate)->removeBilling(_index,_isClickClose);
        }   break;
        case 4:{
            if (_delegate)
                ((GMIntroLayer*)_delegate)->removeBilling(_index,_isClickClose);
        }   break;
        default:
            break;
    }
 
}

//#pragma mark - time
void GMBillingLayer::showTime(CCNode *node,CCPoint point){
    m_pTaskTime1 = UIRollNum::create();
    m_pTaskTime1->setEffect1("billingPic/charging005d.png",1,27.0,34.0,NumStyleNormal0);
    m_pTaskTime1->setNumber(0);
    m_pTaskTime1->setPosition( point );
    node->addChild(m_pTaskTime1,1);
    
    CCScaleTo *scaleTo3 = CCScaleTo::create(0.5, 1);
    CCScaleTo *scaleTo4 = CCScaleTo::create(0.5, 1.5);
    CCActionInterval *sequence1 = (CCActionInterval*)CCSequence::create(scaleTo3,scaleTo4,NULL);
    CCRepeatForever *repeatForever1 = CCRepeatForever::create(sequence1);
    m_pTaskTime1->runAction(repeatForever1);
    
    point = ccp(point.x+15+13/2,point.y);
    charging005e = setSprite("billingPic/charging005e.png",point,ccp(0,0.5),node,0,1);
    
    point = ccp(point.x+27+13/2+15,point.y);
    m_pTaskTime2 = UIRollNum::create();
    m_pTaskTime2->setEffect1("billingPic/charging005d.png",2,26.95,34,NumStyleNormal0);
    m_pTaskTime2->setNumber(10);
    m_pTaskTime2->setPosition( point );
    node->addChild(m_pTaskTime2,1);
    CCScaleTo *scaleTo1 = CCScaleTo::create(0.5, 1);
    CCScaleTo *scaleTo2 = CCScaleTo::create(0.5, 1.5);
    CCActionInterval *sequence = (CCActionInterval*)CCSequence::create(scaleTo1,scaleTo2,NULL);
    CCRepeatForever *repeatForever= CCRepeatForever::create(sequence);
    m_pTaskTime2->runAction(repeatForever);

    countTime = 10;
    this->schedule(schedule_selector(GMBillingLayer::updata),1);
}

void GMBillingLayer::updata(float dt){
    if(m_pTaskTime2){
        if(countTime==0){
            m_pTaskTime1->stopAllActions();
            m_pTaskTime2->stopAllActions();
            if(purchaseBg){
                purchaseBg->removeChild(m_pTaskTime1, true);
                purchaseBg->removeChild(m_pTaskTime2, true);
                purchaseBg->removeChild(charging005e, true);
            }
            this->unschedule(schedule_selector(GMBillingLayer::updata));
//            closeAction();
        }
        else {
            countTime--;
            m_pTaskTime2->setNumber(countTime);
        }
    }
}

//#pragma mark - CCTextFieldTTF
bool GMBillingLayer::onTextFieldAttachWithIME(CCTextFieldTTF * sender)
{
    CCLOG("启动输入");
    return false;
    //    return true;(不启动)
}
//    当用户关闭虚拟键盘的时候回调函数
bool GMBillingLayer::onTextFieldDetachWithIME(CCTextFieldTTF * sender)
{
    CCLOG("关闭输入");
    CCMoveTo *moveTo = CCMoveTo::create(0.1, ccp(purchaseBg->getPosition().x,WINSIZE_H/2));
    showKeyboard = false;
    purchaseBg->runAction(moveTo);
    return false;
    //    return true;(不关闭)
}
//    当用户进行输入 虚拟键盘的时候回调函数
bool  GMBillingLayer::onTextFieldInsertText(CCTextFieldTTF * sender, const char * text, int nLen)
{
    CCLOG("输入字符");
    return false;
    //    return true;(不输入)
}
//    当用户进行删除文字 虚拟键盘的时候回调函数
bool GMBillingLayer::onTextFieldDeleteBackward(CCTextFieldTTF * sender, const char * delText, int nLen)
{
    CCLOG("删除字符");
    return false;
    //    return true;(不删除)
}

//#pragma mark - 重构

void GMBillingLayer::onEnter(){
    CCLayerColor::onEnter();
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,kCCMenuHandlerPriority-1, true);
}

void GMBillingLayer::onExit(){
    CCLayerColor::onExit();
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
}

bool GMBillingLayer::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent){
    if (m_pMenu) {
        m_bTouchedMenu = m_pMenu->ccTouchBegan(pTouch, pEvent);
    }
    return true;
}

void GMBillingLayer::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent){
    if (m_bTouchedMenu && m_pMenu) {
        m_pMenu->ccTouchMoved(pTouch, pEvent);
    }
}

void GMBillingLayer::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent){
 
    if (m_bTouchedMenu && m_pMenu) {
        m_pMenu->ccTouchEnded(pTouch, pEvent);
        m_bTouchedMenu = false;
    }
}

void GMBillingLayer::ccTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent){
    if (m_bTouchedMenu && m_pMenu) {
        m_pMenu->ccTouchCancelled(pTouch, pEvent);
        m_bTouchedMenu = false;
    }
}

void GMBillingLayer::okMenuItemCallback(cocos2d::CCObject *pSender){
    // 点击确定就退出（拷贝的原有方法）
    CCDirector::sharedDirector()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}

void GMBillingLayer::cancelMenuItemCallback(cocos2d::CCObject *pSender){
    this->removeFromParentAndCleanup(false);
}







