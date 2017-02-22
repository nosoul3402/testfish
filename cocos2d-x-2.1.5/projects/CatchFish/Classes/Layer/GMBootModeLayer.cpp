//
//  GMBootModeLayer.cpp
//  FishX
//
//  Created by peng on 13-2-28.
//
//

#include "GMBootModeLayer.h"
#include "GMGameLayer.h"

const char* GMBootModeLayer::prompt[27] = {
    "是时候表演真正的技术了！你就好好\n看着吧！",                                 //剧情 _storyStatus = 1
    "点击屏幕发射子弹",                                                                 //剧情 _storyStatus = 2
    "点击切换爆弹威力",                                                                 //剧情 _storyStatus = 3
    "这，这是！？",                                                                    //剧情 _storyStatus = 4
    "传说中的美人鱼么！？",
    "人家明明是雅典娜女神！！都是波塞冬那臭鱼把我变成这\n幅模样的！",
    "这个样子也蛮可爱的嘛。",
    "算你识相！先别说这些，赶紧给本小姐把这些追杀我的\n臭鱼解决掉！打得人家好痛痛！",
    "被子弹打中会受到\n伤害",                                                             //剧情 _storyStatus = 5
    "你好厉害呀，几招就把他们收拾掉了！你手上那个武器是\n什么？",                               //剧情 _storyStatus = 6
    "这是我老爹留给我的宝物，启动它需要这些鱼的能量。\n咳..（吐出一口血）",
    "你个大笨蛋，受伤了还在笑，快把这个带着，这也是我\n老爹给我的宝物，使用它可以恢复伤势！",
    "点击恢复生命",                                                                   //剧情 _storyStatus = 7
    "太给力了，伤势全部恢复啦！",                                                       //剧情 _storyStatus = 8
    "算你识相，这可是本小姐的御用宝囊哦！快看，那是传说\n中的彩蛋鱼，里面有股特殊的能量！",
    "打爆彩蛋鱼有几率触发神秘技能！",                                                    //剧情 _storyStatus = 9
    "点击按钮释放技能，20秒不点击就会消失哦！",                                           //剧情 _storyStatus = 10
    "糟了，波塞冬那臭鱼派了好多追兵过来了！怎么办？",                                       //剧情 _storyStatus = 11
    "别担心，我还有秘密绝招呢！",
    "点击触发全屏秒怪",                                                                //剧情 _storyStatus = 12
    "雅典娜，你这贱人就是矫情，看你还往哪里跑，本宫亲自\n来收拾你！",                          //剧情 _storyStatus = 13
    "别担心，我会保护你！",
    "小心点，美杜莎有4个蛇头，每个都有不俗的攻击力！",
    "BOSS出现，使用炮弹等级越高，伤害越高",                                                //剧情 _storyStatus = 14
    "啊啊！你小子居然伤了我，本宫要回去禀告波塞冬大王！\n给本宫记住，下次见面就是你们的死期！！",      //剧情 _storyStatus = 15
    "尽管放马过来吧，我正要去亚特兰蒂斯寻找宝藏，让他把\n雅典娜的解药交出来，否则我去揍飞他！",
    "谢谢你，伊泽！"                                                  
};

bool GMBootModeLayer::init()
{
    //////////////////////////////
    if ( !CCLayerColor::init() ) {
        return false;
    }

    CCAddSpriteFramesWithFile(guide_plist);
    guideBatchNode = CCSpriteBatchNode::create(guide_png);
    this->addChild(guideBatchNode);
    
    CCAddSpriteFramesWithFile(guide1_plist);
    CCSpriteBatchNode *guide1BatchNode = CCSpriteBatchNode::create(guide1_png);
    this->addChild(guide1BatchNode);
    
    CCAddSpriteFramesAndTextureFile(guide2_plist,guide2_png);
    
    
    specialMenu = NULL;
    minusItem = NULL;
    minusItem = NULL;
    roundSprite = NULL;
    
    _storyStatus = 1;
    promptIndex = -1;
    isHitFishId15 = false;
    isShowDialogue = false;
    isShowDialogue2 = false;
    isClickSkill = false;
    isShow = false;
    return true;
}

GMBootModeLayer::~GMBootModeLayer(void){
    _delegate = NULL;
    this->removeChild(guideBatchNode, true);
    CCRemoveSpriteFrameByName(guide_plist);
    CCRemoveTextureForKey(guide_png);
    CCRemoveSpriteFrameByName(guide1_plist);
    CCRemoveTextureForKey(guide1_png);
    CCRemoveSpriteFramesAndTextureForKey(guide2_plist,guide2_png);
}

void GMBootModeLayer::setInterceptionOfEvents()
{
    ((GMGameLayer*)_delegate)->setAndroidBack(true);
    isShow = true;
    ((GMGameLayer*)_delegate)->pauseAllAction(true);
    this->setOpacity(178.5);
    this->setTouchEnabled(true);
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,kCCMenuHandlerPriority, true);
}

void GMBootModeLayer::removeInterceptionOfEvents()
{
    ((GMGameLayer*)_delegate)->setAndroidBack(false);
    isShow = false;
    ((GMGameLayer*)_delegate)->pauseAllAction(false);
    this->setOpacity(0);
    this->setTouchEnabled(false);
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
}

void GMBootModeLayer::setSynopsisBg()
{
    setInterceptionOfEvents();
    
    guide001 = CCSprite::createWithSpriteFrameName("guide001.png");
    SetScale2(guide001,Scale_X);
    guide001->setAnchorPoint(ccp(0, 0));
    guide001->setPosition(ccp(0,0));
    this->addChild(guide001,1,1);
    
    CCSprite *normalSprite = CCSprite::createWithSpriteFrameName("guide007.png");
    CCSprite* selectedSprite = CCSprite::createWithSpriteFrameName("guide008.png");
    CCMenuItem *item = CCMenuItemSprite::create(normalSprite, selectedSprite, this, menu_selector(GMBootModeLayer::nextAction));
    CCRect rect = Get_Box(normalSprite);
    CCMenu *menu = CCMenu::create(item,NULL);
    menu->setPosition(ccp(S_WINSIZE_W-Get_W(rect)/2-10, Get_H(rect)/2+10));
    guide001->addChild(menu);
    //    Arial 、Thonburi 、Marker Felt、    
    labelt = CCLabelTTF::create("page \n 1", "Verdana-Bold", 30);
    labelt->setHorizontalAlignment(kCCTextAlignmentLeft);
    labelt->setVerticalAlignment(kCCVerticalTextAlignmentTop);
    labelt->setAnchorPoint(ccp(0, 1));
    labelt->setPosition( ccp( 16 , 90 ));
    labelt->setColor(ccc3(211,105,58));
    guide001->addChild(labelt);
    
    role1 = NULL;//左边
    role2 = NULL;//右边
    switch (_storyStatus) {
        case 1:{
            role1 = CCSprite::createWithSpriteFrameName("guide028.png");
        }   break;
        case 4:{
            role1 = CCSprite::createWithSpriteFrameName("guide030.png");
            role2 = CCSprite::createWithSpriteFrameName("guide024.png");
            role2->setOpacity(0);
        }   break;
        case 6:{
            role1 = CCSprite::createWithSpriteFrameName("guide027.png");
            role1->setOpacity(0);
            role2 = CCSprite::createWithSpriteFrameName("guide025.png");
        }   break;
        case 8:{
            role1 = CCSprite::createWithSpriteFrameName("guide029.png");
            role2 = CCSprite::createWithSpriteFrameName("guide023.png");
            role2->setOpacity(0);
        }   break;
        case 11:{
            role1 = CCSprite::createWithSpriteFrameName("guide026.png");
            role1->setOpacity(0);
            role2 = CCSprite::createWithSpriteFrameName("guide023.png");
        }   break;
        case 13:{
            role1 = CCSprite::createWithSpriteFrameName("guide031.png");
            role2 = CCSprite::createWithSpriteFrameName("guide023.png");
            role2->setOpacity(0);
        }   break;
        case 15:{
            role1 = CCSprite::createWithSpriteFrameName("guide031.png");
            role2 = CCSprite::createWithSpriteFrameName("guide022.png");
            role2->setOpacity(0);
        }   break;
        default:
            break;
    }
    
    if (role1) {
        role1->setAnchorPoint(ccp(0, 0));
        role1->setPosition(ccp(0,100));
        guide001->addChild(role1);
    }
    
    if (role2) {
        role2->setAnchorPoint(ccp(1, 0));
        role2->setPosition(ccp(Get_W(Get_Rect(guide001)),100));
        guide001->addChild(role2);
    }
}

void GMBootModeLayer::setLabelInfo(int index)
{
    _page = index;
    promptIndex++;
    ZPLog("%s",prompt[promptIndex]);
    labelt->setString(prompt[promptIndex]);
}

void GMBootModeLayer::setOtherValue()
{
    _storyStatus++;
    promptIndex++;
}
/*
 *  
 */
void GMBootModeLayer::showPromptBox()
{
    setInterceptionOfEvents();
    
    CCSprite *guide015 = CCSprite::createWithSpriteFrameName("guide015.png");
    guide015->setPosition(ccp(WINSIZE_W/2,WINSIZE_H/2));
    this->addChild(guide015,1,2);
    SetScale2(guide015,Scale_Y);
    
    labelt = CCLabelTTF::create("page \n 1", "Verdana-Bold", 25,CCSize(270, 70), kCCTextAlignmentCenter);
//    labelt->setVerticalAlignment(kCCVerticalTextAlignmentCenter);
    labelt->setAnchorPoint(ccp(0, 0));
    labelt->setPosition( ccp( 15 , 26 ));
    labelt->setColor(ccc3(211,105,58));
    guide015->addChild(labelt);
    
    CCSprite *normalSprite = NULL;
    CCSprite* selectedSprite = NULL;
    switch (_storyStatus) {
        case 2:
        case 5:{
            normalSprite = CCSprite::createWithSpriteFrameName("guide009.png");
            selectedSprite = CCSprite::createWithSpriteFrameName("guide010.png");
            CCMenuItem *item = CCMenuItemSprite::create(normalSprite, selectedSprite, this, menu_selector(GMBootModeLayer::sureAction));
            item->setPosition(ccp(312/2,40/2-8));
            CCRect rect = Get_Box(normalSprite);
            CCMenu *menu = CCMenu::create(item,NULL);
            menu->setPosition(CCPointZero);
            guide015->addChild(menu);
        }   break;
        case 3:{ // 改变炮台
            guide015->setAnchorPoint(ccp(0.5, 0));
            guide015->setPosition(ccp(WINSIZE_W/2+30*Scale_Y,139*Scale_Y));

            CCSprite *guide005 = CCSprite::createWithSpriteFrameName("guide005.png");
            guide005->setAnchorPoint(ccp(0,1));
            guide005->setPosition(ccp(312/2,-15));
            guide015->addChild(guide005,1,2);
            
            normalSprite = CCSprite::createWithSpriteFrameName("mainmenu018.png");
            selectedSprite = CCSprite::createWithSpriteFrameName("mainmenu019.png");
            CCMenuItem *item = CCMenuItemSprite::create(normalSprite, selectedSprite, this, menu_selector(GMBootModeLayer::sureAction));
            
            SetScale2(item, Scale_X);
            item->setAnchorPoint(ccp(1,0));
            item->setPosition(ccp(WINSIZE_W/2+(111-20)*Scale_X,-2*Scale_X));
            specialMenu = CCMenu::create(item,NULL);
            specialMenu->setPosition(CCPointZero);
            this->addChild(specialMenu);
            
        }   break;
        case 7:{
            guide015->setAnchorPoint(ccp(1, 0));
            guide015->setPosition(ccp(620*Scale_X,95*Scale_X));
            
            CCSprite *guide005 = CCSprite::createWithSpriteFrameName("guide005.png");
            guide005->setAnchorPoint(ccp(0,1));
            guide005->setPosition(ccp(312+3,69));
            guide015->addChild(guide005,1,2);
            
            normalSprite = CCSprite::createWithSpriteFrameName("mainmenu014b.png");
            CCMenuItem *item = CCMenuItemSprite::create(normalSprite, selectedSprite, this, menu_selector(GMBootModeLayer::sureAction));
            item->setAnchorPoint(ccp(1,0));
            SetScale2(item, Scale_X);
            CCRect rect16 = item->boundingBox();
            item->setPosition(ccp(WINSIZE_W-(85+20)*Scale_X, 10*Scale_X));
            specialMenu = CCMenu::create(item,NULL);
            specialMenu->setPosition(CCPointZero);
            this->addChild(specialMenu);
            
            int num = GMAccessData::sharedAccessData()->getSkillBloodNum();
            UIRollNum *skillRollNum1 = UIRollNum::create();
            skillRollNum1->setEffect("game/number13.png",2,7.0,9.0,NumStyleNormal0);
            skillRollNum1->setNumber(num);
            skillRollNum1->setPosition(ccp(88-10,20));
            item->addChild(skillRollNum1,MENU_NUM_Layer);
            
        }   break;
        case 9:{
            guide015->setAnchorPoint(ccp(1, 0));
            guide015->setPosition(ccp(630*Scale_X,165*Scale_Y));
            
            roundSprite = CCSprite::createWithSpriteFrameName("guide017.png");
            roundSprite->setAnchorPoint(ccp(0.5,0.5));
            roundSprite->setScale(((GMGameLayer*)_delegate)->getScaleValue());
            roundSprite->setPosition(((GMGameLayer*)_delegate)->getFish15Point());
            this->addChild(roundSprite,1,2);
            
            normalSprite = CCSprite::createWithSpriteFrameName("guide009.png");
            selectedSprite = CCSprite::createWithSpriteFrameName("guide010.png");
            CCMenuItem *item = CCMenuItemSprite::create(normalSprite, selectedSprite, this, menu_selector(GMBootModeLayer::sureAction));
            item->setPosition(ccp(312/2,40/2-8));
            CCRect rect = Get_Box(normalSprite);
            CCMenu *menu = CCMenu::create(item,NULL);
            menu->setPosition(CCPointZero);
            guide015->addChild(menu);
        }   break;
        case 10:{
            guide015->setAnchorPoint(ccp(1, 0));
            guide015->setPosition(ccp(715*Scale_X,190*Scale_X));
            
            CCSprite *guide005 = CCSprite::createWithSpriteFrameName("guide005.png");
            guide005->setAnchorPoint(ccp(0,1));
            guide005->setPosition(ccp(312+3,69));
            guide015->addChild(guide005,1,2);
            
            normalSprite = CCSprite::createWithSpriteFrameName("luck005.png");
            selectedSprite = CCSprite::createWithSpriteFrameName("luck005.png");
            CCMenuItem *item = CCMenuItemSprite::create(normalSprite, selectedSprite, this, menu_selector(GMBootModeLayer::sureAction));
            SetScale2(item, Scale_X);
            item->setAnchorPoint(ccp(1,0));
            item->setPosition(ccp(WINSIZE_W - (10)*Scale_X, (10+92)*Scale_X));
            CCRect rect = Get_Box(normalSprite);
            specialMenu = CCMenu::create(item,NULL);
            specialMenu->setPosition(CCPointZero);
            this->addChild(specialMenu);
        }   break;
        case 12:{
            guide015->setAnchorPoint(ccp(1, 0));
            guide015->setPosition(ccp(720*Scale_X,95*Scale_X));
            
            CCSprite *guide005 = CCSprite::createWithSpriteFrameName("guide005.png");
            guide005->setAnchorPoint(ccp(0,1));
            guide005->setPosition(ccp(312+3,69));
            guide015->addChild(guide005,1,2);
            
            normalSprite = CCSprite::createWithSpriteFrameName("mainmenu014a.png");
            CCMenuItem *item = CCMenuItemSprite::create(normalSprite, selectedSprite, this, menu_selector(GMBootModeLayer::sureAction));
            SetScale2(item, Scale_X);
            item->setAnchorPoint(ccp(1,0));
            item->setPosition(ccp(WINSIZE_W - 10*Scale_X, 10*Scale_X));
 
            specialMenu = CCMenu::create(item,NULL);
            specialMenu->setPosition(CCPointZero);
            this->addChild(specialMenu);
            
            int num = GMAccessData::sharedAccessData()->getSkillPaysNum();
            UIRollNum *skillRollNum1 = UIRollNum::create();
            skillRollNum1->setEffect("game/number13.png",2,7.0,9.0,NumStyleNormal0);
            skillRollNum1->setNumber(num);
            skillRollNum1->setPosition(ccp(88-10,20));
            item->addChild(skillRollNum1,MENU_NUM_Layer);
        }   break;
        case 14:{
            guide015->setAnchorPoint(ccp(0.5, 0));
            guide015->setPosition(ccp(WINSIZE_W/2,100*Scale_Y));
            
//            SetScale2(minusItem, Scale_X);
//            minusItem->setAnchorPoint(ccp(0,0));
//            minusItem->setPosition(ccp(WINSIZE_W/2-(temp20W-20)*Scale_X,-2*Scale_X));
//            CCSprite *normalSprite18 = CCSprite::createWithSpriteFrameName("mainmenu018.png");
//            CCSprite* selectedSprite19 = CCSprite::createWithSpriteFrameName("mainmenu019.png");
//            plusItem = CCMenuItemSprite::create(normalSprite18, selectedSprite19, this, menu_selector(GMMenuLayer::largerAction));
//            SetScale2(plusItem, Scale_X);
//            plusItem->setAnchorPoint(ccp(1,0));
//            plusItem->setPosition(ccp(WINSIZE_W/2+(temp20W-20)*Scale_X,-2*Scale_X));
            
            minusItem = CCSprite::createWithSpriteFrameName("mainmenu016.png");
            SetScale2(minusItem, Scale_X);
            minusItem->setAnchorPoint(ccp(0,0));
            minusItem->setPosition(ccp(WINSIZE_W/2-(111-20)*Scale_X,-2*Scale_X));
            this->addChild(minusItem,1,2);
            
            plusItem = CCSprite::createWithSpriteFrameName("mainmenu018.png");
            SetScale2(plusItem, Scale_X);
            plusItem->setAnchorPoint(ccp(0.5,0));
            plusItem->setAnchorPoint(ccp(1,0));
            plusItem->setPosition(ccp(WINSIZE_W/2+(111-20)*Scale_X,-2*Scale_X));
            this->addChild(plusItem,1,2);
            
            normalSprite = CCSprite::createWithSpriteFrameName("guide009.png");
            selectedSprite = CCSprite::createWithSpriteFrameName("guide010.png");
            CCMenuItem *item = CCMenuItemSprite::create(normalSprite, selectedSprite, this, menu_selector(GMBootModeLayer::sureAction));
            item->setPosition(ccp(312/2,40/2-8));
            CCRect rect = Get_Box(normalSprite);
            CCMenu *menu = CCMenu::create(item,NULL);
            menu->setPosition(CCPointZero);
            guide015->addChild(menu);
        }   break;
        
        default:
            break;
    }
}

void GMBootModeLayer::sureAction(CCObject *pSender)
{
    removeInterceptionOfEvents();
    removePrompView();
    if (specialMenu) {
        this->removeChild(specialMenu, true);
        specialMenu = NULL;
    }
    if (minusItem) {
        this->removeChild(minusItem, true);
        this->removeChild(plusItem, true);
    }
    if (roundSprite) {
        this->removeChild(roundSprite, true);
        roundSprite = NULL;
    }
    if (isShowDialogue == true) {
        isShowDialogue = false;
        return;
    }
    switch (_storyStatus) {
        case 3:{
            ((GMGameLayer*)_delegate)->setMinusAndPlusEnabled(3);
            ((GMGameLayer*)_delegate)->plusAction();
        }   break;
        case 7:{
            ((GMGameLayer*)_delegate)->setMinusAndPlusEnabled(6);
            ((GMGameLayer*)_delegate)->usedSkill1(NULL);
        }   break;
        case 10:{
            isClickSkill = true;
            ((GMGameLayer*)_delegate)->setCastSkill(3);
        }   break;
        case 12:{
            ((GMGameLayer*)_delegate)->setMinusAndPlusEnabled(11);
            ((GMGameLayer*)_delegate)->usedSkill2(NULL);
        }   break;
        default:
            break;
    }
    _storyStatus++;
    ZPLog("剧情 id = %d",_storyStatus);
}


void GMBootModeLayer::removePrompView()
{
    CCSprite *guide015 = (CCSprite*)this->getChildByTag(2);
    if (guide015) {
        this->removeChild(guide015, true);
        guide015 = NULL;
    }
}

void GMBootModeLayer::showBootModeStory(int countTime,int enemyCount)
{
    int tempStatus = GMAccessData::sharedAccessData()->getRoleDeathStatus();
    if (tempStatus == 1 && _storyStatus == 1) {
        _storyStatus = 13;
        promptIndex = 19;
    }
    
    ZPLog("引导测试: storyStatus = %d, enemyCount = %d",_storyStatus,enemyCount);
    ZPLog("引导测试: curTimes = %d  countTime = %d",curTimes ,countTime);
    
    switch (_storyStatus) {
        case 1:{ //是时候表演真正的技术了！老爹，你就在天上好好\n看着吧
            if (countTime == 0) {
                setSynopsisBg();
                setLabelInfo(0);
            }
        }   break;
        case 2:{ //点击屏幕发射子弹
            if (countTime == 3) {
                showPromptBox();
                setLabelInfo(0);
            }
        }   break;
        case 3:{//点击切换爆弹威力
            if (countTime == 12) {
                showPromptBox();
                setLabelInfo(0);
            }
        }   break;
        case 4:{//
            if (countTime == 25) {                
                ((GMGameLayer*)_delegate)->showBootModeFIshID16();
            }
            else if(countTime == 28){
                setSynopsisBg();
                setLabelInfo(5);
            }
        }   break;
        case 5:{//被子弹打中会受到\n伤害
            if(countTime == 35){
                showPromptBox();
                setLabelInfo(0);
            }
        }   break;
        case 6:{//你好厉害呀
            if(enemyCount == 0) {
                setSynopsisBg();
                setLabelInfo(3);
            }
        }   break;
        case 7:{//点击恢复生命
            curTimes = countTime;
            showPromptBox();
            setLabelInfo(0);
        }   break;
        case 8:{//太给力了，伤势全部恢复啦！
            if (countTime == curTimes+2){
                setSynopsisBg();
                setLabelInfo(2);
                curTimes = countTime;
            }
        }   break;
        case 9:{//打爆彩蛋鱼有几率触发神秘技能
            if(curTimes + 2 == countTime){
                showPromptBox();
                setLabelInfo(0);
                curTimes = countTime;
            }
        }   break;
        case 10:{ //冰河世纪
            if (isHitFishId15 == false) {
                curTimes = countTime;
            }
            if(curTimes + 3 == countTime && isHitFishId15 == true){
                showPromptBox();
                setLabelInfo(0);
            }
        }   break;
        case 11:{//糟了，波塞冬那臭鱼派了好多追兵过来了！怎么办
            if (enemyCount == 0) {
                setSynopsisBg();
                setLabelInfo(2);
                curTimes = countTime;
            }
        }   break;
        case 12:{//点击触
            if(curTimes + 5 == countTime){
                showPromptBox();
                setLabelInfo(0);
                curTimes = countTime;
            }
        }   break;
        case 13:{
            if((curTimes + 3 == countTime) || tempStatus == 1){
                setSynopsisBg();
                setLabelInfo(3);
                curTimes = countTime;
            }
        }   break;
        case 14:{
            if(curTimes + 3 == countTime){
                curTimes = 0;
                showPromptBox();
                setLabelInfo(0);
            }
        }   break;
        case 15:{
            
        }   break;
        default:
            break;
    }
}

void GMBootModeLayer::nextAction(CCObject *pSender)
{
    GMAudioPlay::sharedAudioPlay()->playButtonEffect();
    
    if (_page>0) {
        _page--;
        if (_page>0) {
            setLabelInfo(_page);
        }
        CCSpriteFrame *spriteFrame = NULL;
        switch (_storyStatus) {
            case 4:{
                if (_page == 4) {
                    spriteFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("guide029.png");
                    role1->setDisplayFrame(spriteFrame);
                }
                else if (_page == 3) {
                    role2->setOpacity(255);
                    role1->setOpacity(0);
                }
                else if(_page == 2){
                    spriteFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("guide027.png");
                    role1->setDisplayFrame(spriteFrame);
                    role1->setOpacity(255);
                    role2->setOpacity(0);
                }
                else if(_page == 1){
                    spriteFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("guide025.png");
                    role2->setDisplayFrame(spriteFrame);
                    role2->setOpacity(255);
                    role1->setOpacity(0);
                }
            }   break;
            case 6:{
                if (_page == 2) {
                    role2->setOpacity(0);
                    role1->setOpacity(255);
                }
                else if(_page == 1){
                    spriteFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("guide023.png");
                    role2->setDisplayFrame(spriteFrame);
                    role2->setOpacity(255);
                    role1->setOpacity(0);
                }
            }   break;
            case 8:{
                if(_page == 1){
                    role2->setOpacity(255);
                    role1->setOpacity(0);
                }
            }   break;
            case 11:{
                if(_page == 1){
                    role2->setOpacity(0);
                    role1->setOpacity(255);
                }
            }   break;
            case 13:{
                if (_page == 2) {
                    spriteFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("guide028.png");
                    role1->setDisplayFrame(spriteFrame);
                }
                else if(_page == 1){
                    role2->setOpacity(255);
                    role1->setOpacity(0);
                }
            }   break;
            case 15:{
                if (_page == 2) {
                    spriteFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("guide026.png");
                    role1->setDisplayFrame(spriteFrame);
                }
                else if(_page == 1){
                    role2->setOpacity(255);
                    role1->setOpacity(0);
                }
            }   break;
            default:
                break;
        }
    }
    
    if (_page == 0) {
        
        guide001->removeChild(role1, true);
        role1 = NULL;
        this->removeChild(guide001, true);
        
        guide001 = NULL;
        
        removeInterceptionOfEvents();
       
        ((GMGameLayer*)_delegate)->nextAction(_storyStatus);
        _storyStatus++;
        ZPLog("剧情 id = %d",_storyStatus);
    }
}

void GMBootModeLayer::showBossDeath()
{
    setSynopsisBg();
    setLabelInfo(3);
}

void GMBootModeLayer::showDialogueNum()
{
    if (isShow == false && isShowDialogue2 == false) {
        isShowDialogue = true;
        isShowDialogue2 = true;
        setInterceptionOfEvents();
        
        CCSprite *guide015 = CCSprite::createWithSpriteFrameName("guide015.png");
        guide015->setAnchorPoint(ccp(0,0.5));
        guide015->setPosition(ccp(10*Scale_Y,WINSIZE_H/2));
        this->addChild(guide015,1,2);
        SetScale2(guide015,Scale_Y);
        
        labelt = CCLabelTTF::create("发射消耗能量，打中的鱼会转换成能量", "Verdana-Bold", 25,CCSize(270, 69), kCCTextAlignmentCenter);
        labelt->setVerticalAlignment(kCCVerticalTextAlignmentCenter);
        labelt->setAnchorPoint(ccp(0, 0));
        labelt->setPosition( ccp( 10 , 26 ));
        labelt->setColor(ccc3(211,105,58));
        guide015->addChild(labelt);
        
        CCSprite *guide005 = CCSprite::createWithSpriteFrameName("guide005.png");
        guide005->setAnchorPoint(ccp(0,1));
        guide005->setPosition(ccp(80,-5));
        guide015->addChild(guide005,1,2);
        
        CCSprite *normalSprite = CCSprite::createWithSpriteFrameName("guide009.png");
        CCSprite *selectedSprite = CCSprite::createWithSpriteFrameName("guide010.png");
        CCMenuItem *item = CCMenuItemSprite::create(normalSprite, selectedSprite, this, menu_selector(GMBootModeLayer::sureAction));
        item->setPosition(ccp(312/2,40/2-8));
        CCRect rect = Get_Box(normalSprite);
        CCMenu *menu = CCMenu::create(item,NULL);
        menu->setPosition(CCPointZero);
        guide015->addChild(menu);
    }
}

bool GMBootModeLayer::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{

    return true;
}

void GMBootModeLayer::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
}

void GMBootModeLayer::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
}


