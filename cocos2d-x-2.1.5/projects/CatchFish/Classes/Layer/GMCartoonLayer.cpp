//
//  GMCartoonLayer.cpp
//  FishX
//
//  Created by peng on 13-3-6.
//
//

#include "GMCartoonLayer.h"
#include "../Config/GMHeaderConfig.h"
#include "GMMainLayer.h"


const char* GMCartoonLayer::cartoonPrompt[5] = {
    "冒险王罗杰曾经在最危险的海域-亚特兰蒂斯，捕获了传说中的暗黑金鲨，自己却受到神秘的诅咒英年早逝。",
    "于是，越来越多的人奔向大海，朝着冒险王的目标前进。",
    "然后，罗杰的儿子伊泽，从小却饱受欺凌，是阳光海域公认的废柴。",
    "直到有一天，伊泽打开了父亲在亚特兰蒂斯寻找到的宝藏，里面竟然是一只奇异的手套，伊泽的人生发生了改变。",
};

GMCartoonLayer::GMCartoonLayer()
{
	countTime1 = 0;
	countTime3 = 0;
	countTime4 = 0;
}

CCScene* GMCartoonLayer::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    GMCartoonLayer *layer = GMCartoonLayer::create();
    scene->addChild(layer);
    return scene;
}

// on "init" you need to initialize your instance
bool GMCartoonLayer::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    CCRemoveUnusedSpriteFrames();
    
    initElement1();
    _labelt = NULL;
    isScroll1 = true;
    isScroll2 = 0;
    isScroll3 = 0;
    
    GMAudioPlay::sharedAudioPlay()->playBGMusic(Audio_Home);
    
    this->schedule(schedule_selector(GMCartoonLayer::update), 0.01);
    
    
    CCMenuItem *item = CCMenuItemImage::create("cartoon/tiaoguo1.png", "cartoon/tiaoguo2.png", this, menu_selector(GMCartoonLayer::tiaoguoAction));
    SetScale2(item, Scale_X);
    item->setPosition(ccp(WINSIZE_W-114*Scale_X,Scale_X*20));
    
    CCMenu *m_pMenu = CCMenu::create(item,NULL);
    m_pMenu->setPosition(CCPointZero);
    this->addChild(m_pMenu,200);
    
    return true;
}

void GMCartoonLayer::tiaoguoAction(CCObject *object){
    
    this->cleanup();
    
    CCScene *pScene = CCTransitionFade::create(2.0, GMMainLayer::scene(), ccWHITE);
    CCDirector::sharedDirector()->replaceScene(pScene);
}

void GMCartoonLayer::setLabel(const char *string)
{
    CCLabelTTF *tempLabelt2 = (CCLabelTTF*)this->getChildByTag(20000);
    this->removeChild(tempLabelt2, true);

    CCLabelTTF *tempLabelt = CCLabelTTF::create(string,"Marker Felt",20,CCSize(S_WINSIZE_W-30, 120), kCCTextAlignmentCenter);
    tempLabelt->setVerticalAlignment(kCCVerticalTextAlignmentCenter);
    tempLabelt->setAnchorPoint(ccp(0, 0));
    tempLabelt->setPosition( ccp( 15*Scale_X , 0 ));
    tempLabelt->setColor(ccWHITE);//ccWHITE  //ccc3(211,105,58)
    SetScale2(tempLabelt,Scale_X);
    this->addChild(tempLabelt,200,20000);

}

void GMCartoonLayer::update(float time)
{
    /*
     *  第1幅漫画
     */
    cartoon1Move();
    /*
     *  第2幅漫画
     */
    countTime1++;
    initElement2();
    /*
     *  第3幅漫画
     */
    if (countTime1 == 255) {
//        initElement3();
    }
    
    if (countTime1>=256) {
        countTime1 = 256;
    }
    
    cartoon3Move();
    showCartoon3Word();
    
    cartoon4Move();
}
/*
 *  第1幅漫画
 */
void GMCartoonLayer::initElement1()
{
    CCAddSpriteFramesWithFile(manhuagx_plist);
    CCSpriteBatchNode *manhuaBatchNode1 = CCSpriteBatchNode::create(maxhuagx_png);
    this->addChild(manhuaBatchNode1);
    
    CCAddSpriteFramesWithFile(cartoon_plist);
    CCSpriteBatchNode *cartoonBatchNode1 = CCSpriteBatchNode::create(cartoon_png);
    this->addChild(cartoonBatchNode1);

    sprite1 = CCSprite::create("cartoon/cartoon1001.jpg");
    rect1 = Get_Rect(sprite1);
    SetScale2(sprite1, Scale_X);
    float tempH = Get_H(rect1);
    sprite1->setAnchorPoint(ccp(0, 0));
    sprite1->setPosition(ccp(0, 0));

    //    this->addChild(layer);
    
    scrollView1 = CCScrollView::create();// 位置不是居中的
    scrollView1->setPosition(CCPointZero);
    scrollView1->setContentOffset(CCPointZero);
    scrollView1->setViewSize(CCSizeMake(WINSIZE_W, WINSIZE_H));
    scrollView1->setContentSize(CCSizeMake(WINSIZE_W, tempH*Scale_X));		//设置显示区域的大小
    scrollView1->setContainer(sprite1);                            //设置需要滚动的内容
    scrollView1->setTouchEnabled(false);                         //因为要自己实现触摸消息，所以这里设为false
    //    scrollView1->setDelegate(this);
    scrollView1->setDirection(kCCScrollViewDirectionVertical);  //设置滚动的方向，有三种可以选择
    scrollView1->setPosition(ccp(0, 0));
    
    
    adjustPos = ccp(0,-480);
    scrollView1->setContentOffset(adjustPos, false);
    //    scrollView1->setContentOffsetInDuration(adjustPos, 0);
    this->addChild(scrollView1,1);
    
    
    CCSprite *manhuagx001 = CCSprite::createWithSpriteFrameName("manhuagx001.png");
    manhuagx001->setPosition(ccp(550, 785));
    GMPublicMethod::setRepeatAnimation(manhuagx001, 1, 6, "manhuagx", "png", 0.1,true);
    sprite1->addChild(manhuagx001);
    
    ZPLog("%f",scrollView1->getViewSize().width);
    
    setLabel(cartoonPrompt[0]);
}

void GMCartoonLayer::cartoon1Move()
{
    if (isScroll1) {
        CCPoint oldP = adjustPos;
        adjustPos = ccp(0,oldP.y+2);
        if (adjustPos.y>=0) {
            adjustPos = ccp(0,0);
            isScroll1 = false;
        }
        else if(adjustPos.y == -200){
            rainParticle = CCParticleSystemQuad::create(Particles_Rain);
            rainParticle->setPosition(ccp(WINSIZE_W/2, WINSIZE_H)); //setPosition(point);
            this->addChild(rainParticle, 5, 100);
            rainParticle->setScale(BG_SCALE2);
//            rainParticle->setScale(2);
        }
        else if (adjustPos.y == -150) {
            CCSprite *role1 = CCSprite::createWithSpriteFrameName("cartoon1002.png");
            role1->setAnchorPoint(ccp(0,0));
            role1->setPosition(ccp(30,120));
            sprite1->addChild(role1,2);
            role1->setOpacity(0);
            CCFadeIn *fadeIn = CCFadeIn::create(1);
            role1->runAction(fadeIn);
        }
        else if (adjustPos.y == -100) {
            CCSprite *role2 = CCSprite::createWithSpriteFrameName("cartoon1003.png");
            role2->setAnchorPoint(ccp(1,0));
            role2->setPosition(ccp(Get_W(rect1)-30,50));
            sprite1->addChild(role2,2);
            role2->setOpacity(0);
            CCFadeIn *fadeIn = CCFadeIn::create(1);
            role2->runAction(fadeIn);
        }
        
        scrollView1->setContentOffset(adjustPos, false);
        countTime1 = 0;
    }
}
/*
 *  第2幅漫画
 */
void GMCartoonLayer::initElement2()
{
    if (countTime1 == 100 && isScroll2 == 0) {
        cclayer2 = CCLayer::create();
        this->addChild(cclayer2,3);
        
        cartoon2001 = CCSprite::create("cartoon/cartoon2001.png");
        cartoon2001->setAnchorPoint(ccp(0,0));
        SetScale2(cartoon2001, Scale_Y);
        cartoon2001->setPosition(ccp(WINSIZE_W,0));
        cclayer2->addChild(cartoon2001,3);
        isScroll2 = 1;
        
        setLabel(cartoonPrompt[1]);
    }
    if (cartoon2001 && isScroll2 == 1) {
        
        CCPoint oldP1 = cartoon2001->getPosition();
        oldP1.x -= 5;
        if (oldP1.x <= (WINSIZE_W-Get_W(Get_Rect(cartoon2001))*Scale_Y)) {
            oldP1.x = (WINSIZE_W-Get_W(Get_Rect(cartoon2001))*Scale_Y);
            isScroll2 = 2;
            
            CCSprite *bg1 = CCSprite::create("cartoon/cartoon2002.jpg");
//            SetScale2(bg1, Scale_Y);
            SetScale(bg1);
            bg1->setAnchorPoint(ccp(0,0));
            bg1->setPosition(ccp(0,0));
            bg1->setOpacity(0);
            cclayer2->addChild(bg1,2);
            
            CCFadeIn *fadeIn = CCFadeIn::create(2);
            CCCallFunc *callFunc = CCCallFunc::create(this, callfunc_selector(GMCartoonLayer::removeScrollView1));
            CCFiniteTimeAction * action = CCSequence::create(fadeIn, callFunc,NULL);
            bg1->runAction(action);
        }
        cartoon2001->setPosition(ccp(oldP1.x,oldP1.y));
        
    }
    if (isScroll2== 3) {
        
        countTime1++;
        if (countTime1 == 50) {
            initElement3();
            isScroll2 = 4;
        }
    }
}

void GMCartoonLayer::removeScrollView1()
{
    rainParticle->setAutoRemoveOnFinish(true);
    this->removeChild(rainParticle, true);
    this->removeChild(scrollView1, true);
    scrollView1 = NULL;
    isScroll2 = 3;
    
    countTime1 = 0;
}

/*
 *  第3幅漫画
 */
void GMCartoonLayer::initElement3()
{
    sprite3 = CCSprite::create("cartoon/cartoon3001.jpg");
    CCRect rect = Get_Rect(sprite3);
    SetScale2(sprite3, Scale_Y);
    float tempW = Get_W(rect);
    sprite3->setAnchorPoint(ccp(0, 0));
    sprite3->setPosition(ccp(0, 0));
    //    this->addChild(layer);
    
    scrollView3 = CCScrollView::create();// 位置不是居中的
    scrollView3->setPosition(CCPointZero);
    scrollView3->setContentOffset(CCPointZero);
    scrollView3->setViewSize(CCSizeMake(WINSIZE_W, WINSIZE_H));
    scrollView3->setContentSize(CCSizeMake(tempW*Scale_Y, WINSIZE_H));		//设置显示区域的大小
    scrollView3->setContainer(sprite3);                            //设置需要滚动的内容
    scrollView3->setTouchEnabled(false);                         //因为要自己实现触摸消息，所以这里设为false
    scrollView3->setDirection(kCCScrollViewDirectionHorizontal);  //设置滚动的方向，有三种可以选择
    scrollView3->setPosition(ccp(0, 0));
    adjustPos = ccp(0,0);
    scrollView3->setContentOffset(adjustPos, false);
    this->addChild(scrollView3,3);
    
    this->removeChild(cclayer2, true);
    cclayer2 = NULL;
    
    sprite3->setOpacity(0);
    CCFadeIn *fadeIn = CCFadeIn::create(5);
    CCCallFunc *callFunc = CCCallFunc::create(this, callfunc_selector(GMCartoonLayer::startMove3));
    CCActionInterval * action = (CCActionInterval*)CCSequence::create(fadeIn, callFunc,NULL);
    sprite3->runAction(action);

    setLabel(cartoonPrompt[2]);
//    isScroll3 = 1;
}
void GMCartoonLayer::startMove3()
{
    isScroll3 = 1;
}

void GMCartoonLayer::showCartoon3Word()
{
   
    if (scrollView3 && isScroll3==1) {
        countTime3 ++;
        if (countTime3 == 30) {
            CCSprite *cartoon3002 = CCSprite::createWithSpriteFrameName("cartoon3002.png");
            cartoon3002->setAnchorPoint(ccp(0,0));
            cartoon3002->setPosition(ccp(32,354));
            sprite3->addChild(cartoon3002 , 1);
            cartoon3002->setOpacity(0);
            CCFadeIn *fadeTo = CCFadeIn::create(2);
            cartoon3002->runAction(fadeTo);
        }
        else if(countTime3 == 100)
        {
            CCSprite *cartoon3003 = CCSprite::createWithSpriteFrameName("cartoon3003.png");
            cartoon3003->setAnchorPoint(ccp(0,0));
            cartoon3003->setPosition(ccp(187,244));
            scrollView3->addChild(cartoon3003 , 1);
            cartoon3003->setOpacity(0);
            CCFadeIn *fadeTo = CCFadeIn::create(2);
            cartoon3003->runAction(fadeTo);
        }
        else if (countTime3 == 150) {
            CCSprite *cartoon3004 = CCSprite::createWithSpriteFrameName("cartoon3004.png");
            cartoon3004->setAnchorPoint(ccp(0,0));
            cartoon3004->setPosition(ccp(44,125));
            cartoon3004->setOpacity(0);
            scrollView3->addChild(cartoon3004 , 1);
            cartoon3004->setOpacity(0);
            CCFadeIn *fadeTo = CCFadeIn::create(2);
            cartoon3004->runAction(fadeTo);
        }
        else if(countTime3 == 180) {
            isScroll3 = 2;
            countTime3 = 0;
        }
    }
}

void GMCartoonLayer::cartoon3Move()
{
    if (scrollView3 && isScroll3 == 2) {
        CCPoint oldP = scrollView3->getContentOffset();
        adjustPos = ccp(oldP.x-2,0);
        if (adjustPos.x <= -(Scale_Y*1100-WINSIZE_W)) {
            adjustPos = ccp(-(Scale_Y*1100-WINSIZE_W),0);
            countTime3 = 0;
            isScroll3 = 3;
        }
        
        if (adjustPos.x == -50) {
            CCSprite *cartoon3005 = CCSprite::createWithSpriteFrameName("cartoon3005.png");
            cartoon3005->setAnchorPoint(ccp(0,0));
            cartoon3005->setPosition(ccp(480,25));
            scrollView3->addChild(cartoon3005 , 1);
            cartoon3005->setOpacity(0);
            CCFadeIn *fadeTo = CCFadeIn::create(1.5);
            cartoon3005->runAction(fadeTo);
        }
        else if(adjustPos.x == -80){
            CCSprite *cartoon3006 = CCSprite::createWithSpriteFrameName("cartoon3006.png");
            cartoon3006->setAnchorPoint(ccp(0,0));
            cartoon3006->setPosition(ccp(560,340));
            scrollView3->addChild(cartoon3006 , 1);
            cartoon3006->setOpacity(0);
            CCFadeIn *fadeTo = CCFadeIn::create(1.5);
            cartoon3006->runAction(fadeTo);
        }
        scrollView3->setContentOffset(adjustPos, false);
    }
    
    if ( scrollView3 && isScroll3 == 3) {
        countTime3 ++;
        if (countTime3 == 20) {
            CCFadeOut *fadeTo = CCFadeOut::create(2);
            CCCallFunc *callFunc = CCCallFunc::create(this, callfunc_selector(GMCartoonLayer::removeScrollView3));
            CCActionInterval * action = (CCActionInterval*)CCSequence::create(fadeTo,callFunc,NULL);
            sprite3->runAction(action);
        }
    }
    
    if (isScroll3 == 4) {
        countTime3 ++;
        if (countTime3 == 180) {
            this->removeChild(cartoon3007, true);
            cartoon3007 = NULL;
            initElement4();
        }
    }
    
}

void GMCartoonLayer::removeScrollView3()
{
    this->removeChild(scrollView3, true);
    scrollView3 = NULL;
    
    cartoon3007 = CCSprite::createWithSpriteFrameName("cartoon3007.png");
    cartoon3007->setPosition(ccp(WINSIZE_W/2,WINSIZE_H/2));
    this->addChild(cartoon3007);
    cartoon3007->setOpacity(0);
    CCFadeIn *fadeTo = CCFadeIn::create(5);
    cartoon3007->runAction(fadeTo);
    SetScale2(cartoon3007, Scale_X);
    isScroll3 = 4;
    countTime3 = 0;
    
    CCLabelTTF *tempLabelt2 = (CCLabelTTF*)this->getChildByTag(20000);
    this->removeChild(tempLabelt2, true);
}

/*
 *  第4幅漫画
 */
void GMCartoonLayer::initElement4()
{

    sprite4 = CCSprite::create("cartoon/cartoon4001.jpg");
    CCRect rect = Get_Rect(sprite4);
    SetScale2(sprite4, Scale_Y);
    float tempW = Get_W(rect);
    sprite4->setAnchorPoint(ccp(0, 0));
    sprite4->setPosition(ccp(0, 0));
//    layer->addChild(sprite);
//    layer->setContentSize(CCSizeMake(tempW*Scale_Y, WINSIZE_H));
    
    scrollView4 = CCScrollView::create();// 位置不是居中的
    scrollView4->setPosition(CCPointZero);
    scrollView4->setContentOffset(CCPointZero);
    scrollView4->setViewSize(CCSizeMake(WINSIZE_W, WINSIZE_H));
    scrollView4->setContentSize(CCSizeMake(tempW*Scale_Y, WINSIZE_H));		//设置显示区域的大小
    scrollView4->setContainer(sprite4);                            //设置需要滚动的内容
    scrollView4->setTouchEnabled(false);                         //因为要自己实现触摸消息，所以这里设为false
    scrollView4->setDirection(kCCScrollViewDirectionHorizontal);  //设置滚动的方向，有三种可以选择
    scrollView4->setPosition(ccp(0, 0));
    adjustPos = ccp(0,0);
    scrollView4->setContentOffset(adjustPos, false);
    this->addChild(scrollView4,3);
    sprite4->setOpacity(0);
    CCFadeIn *fadeIn = CCFadeIn::create(5);
    sprite4->runAction(fadeIn);
//
    
    CCSprite *cartoon4002 = CCSprite::createWithSpriteFrameName("cartoon4002.png");
//    SetScale2(cartoon4002, Scale_Y);
    cartoon4002->setAnchorPoint(ccp(0,0));
    cartoon4002->setPosition(ccp(20,300));
    scrollView4->addChild(cartoon4002 , 1);
    cartoon4002->setOpacity(0);
    
    CCFadeIn *fadeTo = CCFadeIn::create(5);
    CCCallFunc *callFunc = CCCallFunc::create(this, callfunc_selector(GMCartoonLayer::startMove4));
    CCActionInterval * action = (CCActionInterval*)CCSequence::create(fadeTo, callFunc,NULL);
    cartoon4002->runAction(action);
    
     setLabel(cartoonPrompt[3]);
}

void GMCartoonLayer::startMove4()
{
    CCSprite *cartoon4006 = CCSprite::createWithSpriteFrameName("cartoon4006.png");
    CCArray *temp = CCArray::create();
    char strName[40] = {0};
    for (int j = 6; j <= 7; j++) {
        sprintf(strName,"cartoon4%03d.png",j);
        CCSpriteFrame *spriteFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(strName);
        temp->addObject(spriteFrame);
    }
    CCAnimation *m_pAnimation = CCAnimation::createWithSpriteFrames(temp,0.1);
    CCAnimate *animate = CCAnimate::create(m_pAnimation);
    CCFiniteTimeAction *sequence = CCSequence::create(animate,NULL);
    cartoon4006->setAnchorPoint(ccp(0,1));
    cartoon4006->setPosition(ccp(6.2,480-6.5));
    sprite4->addChild(cartoon4006);
    cartoon4006->runAction(sequence);
    
    isScroll4 = 1;
}

void GMCartoonLayer::cartoon4Move()
{
    if (scrollView4 && isScroll4 == 1) {
        countTime4 ++;
        if (countTime4 >= 100) {
            CCPoint oldP = scrollView4->getContentOffset();
            adjustPos = ccp(oldP.x-1,0);
            if (adjustPos.x <= -(Scale_Y*1000-WINSIZE_W)) {
                adjustPos = ccp(-(Scale_Y*1000-WINSIZE_W),0);
                countTime4 = 0;
                isScroll4 = 2;
            }
            if (adjustPos.x == -10) {
                CCSprite *cartoon4003 = CCSprite::createWithSpriteFrameName("cartoon4003.png");
//                SetScale2(cartoon4003, Scale_Y);
                cartoon4003->setAnchorPoint(ccp(0,0));
                cartoon4003->setPosition(ccp(260,30));
                scrollView4->addChild(cartoon4003 , 1);
                cartoon4003->setOpacity(0);
                CCFadeIn *fadeTo = CCFadeIn::create(2);
                cartoon4003->runAction(fadeTo);
            }
            else if(adjustPos.x == -50)
            {
                CCSprite *cartoon4004 = CCSprite::createWithSpriteFrameName("cartoon4004.png");
//                SetScale2(cartoon4004, Scale_Y);
                cartoon4004->setAnchorPoint(ccp(0,0));
                cartoon4004->setPosition(ccp(550,355));
                scrollView4->addChild(cartoon4004 , 1);
                cartoon4004->setOpacity(0);
                CCFadeIn *fadeTo = CCFadeIn::create(1);
                cartoon4004->runAction(fadeTo);
            }
            scrollView4->setContentOffset(adjustPos, false);
        }
        
    }
    
    if ( scrollView4 && isScroll4 == 2) {
        countTime4++;
        if (countTime4 == 20) {
//            CCFadeOut *fadeTo = CCFadeOut::create(2);
//            CCCallFunc *callFunc = CCCallFunc::create(this, callfunc_selector(GMCartoonLayer::removeScrollView3));
//            CCActionInterval * action = (CCActionInterval*)CCSpawn::create(fadeTo, callFunc,NULL);
//            scrollView3->runAction(action);
            
            CCScene *pScene = CCTransitionFade::create(2.0, GMMainLayer::scene(), ccWHITE);
            CCDirector::sharedDirector()->replaceScene(pScene);
        }
    }
}


GMCartoonLayer::~GMCartoonLayer()
{
    CCRemoveSpriteFrameByName(manhuagx_plist);
    CCRemoveTextureForKey(maxhuagx_png);
    
    CCRemoveSpriteFrameByName(cartoon_plist);
    CCRemoveTextureForKey(cartoon_png);

}





