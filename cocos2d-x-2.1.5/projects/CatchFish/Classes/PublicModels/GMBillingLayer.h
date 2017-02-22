//
//  GMBillingLayer.h
//  FishX
//
//  Created by peng on 13-5-9.
//
//

#ifndef __FishX__GMBillingLayer__
#define __FishX__GMBillingLayer__

#include <iostream>
#include "cocos2d.h"
#include "UIRollNum.h"

USING_NS_CC;

class GMBillingLayer: public CCLayerColor,public CCTextFieldDelegate
{
    // 模态对话框菜单
    CCMenu *m_pMenu;
    // 记录菜单点击
    bool m_bTouchedMenu;
    
public:
    GMBillingLayer();
    ~GMBillingLayer();
    
    virtual bool init();
    // 初始化对话框内容
    void initDialog();
    
    CREATE_FUNC(GMBillingLayer);
    
private:
    CCSprite    *purchaseBg;
    UIRollNum   *m_pTaskTime1;
    UIRollNum   *m_pTaskTime2;
    CCObject    *_delegate;
    CCSprite    *validtionbg2;
    CCSprite    *charging005e;//冒号

    int         _index;
    int         classType;// classType == 1(GMGameLayer) classType == 2(GMCarDLayer)
    bool        _isClickClose;
    int         _type;
    int         _itemTag;
    
    CCTextFieldTTF *textfield;
    bool            showKeyboard;
    
    int             billingIndex;
private:
    CCSprite* setSprite(const char *name,CCPoint pos,CCPoint aPos,CCNode *node,int zOrder,float scale);
    void showLabelTTF(const char *string,CCSize size,const ccColor3B& color3);
    void showLabelTTF1(CCNode*node,const char *string,CCPoint point,CCSize size,const ccColor3B& color3);
//#pragma mark - time
    
    int       countTime;
    void showTime(CCNode *node,CCPoint point);
    void updata(float dt);
    
    void sureAction(CCObject *pSender);
//#pragma mark - 正版验证提示
    void removeGenuineValidationTips();
    
    void check91MobileStatus(float dt);
    void check91BillingCode(float dt);
    
public:
    void setDelegate(CCObject *target) { _delegate = target;}
    void setIndex(int index) {_index = index; }
    void setClassType(int index) { classType = index; }
    
    CC_SYNTHESIZE(bool, _startBliling, StartBliling);
    
//#pragma mark - 正版验证提示
    void showGenuineValidationTips();
    void showSecondaryConfirmationTips(int index);
//#pragma mark - 显示购买能量
    void showThePurchaseOfEnergy(int type,int index);
//#pragma mark - 显示武器升级
    void showWeaponUpgrades(int index);
    
//#pragma mark - 显示购买技能
    void showPurchasingSkills();
//#pragma mark - 91购买能量界面
    void show91Shop();
    
//#pragma mark - 91移动联网付费
    void show91MobileView();
    void show91MobileView2();
    
    void textFieldAction(CCObject *object);
    void getFriendAction(CCObject *object);
    void getCodeAction(CCObject *object);
    void sendCodeAction(CCObject *object);
    
    
    void closeAction(CCObject *pSender);
public:
//#pragma mark -
    void onEnter();
    void onExit();
    
    
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);
    
    void okMenuItemCallback(CCObject *pSender);
    void cancelMenuItemCallback(CCObject *pSender);
    
//    重写CCTextFieldDelegate的回调函数
//    当用户启动虚拟键盘的时候回调函数

//    要有输出口
    virtual bool onTextFieldAttachWithIME(CCTextFieldTTF * sender);
//    当用户关闭虚拟键盘的时候回调函数
    virtual bool onTextFieldDetachWithIME(CCTextFieldTTF * sender);
//    当用户进行输入 虚拟键盘的时候回调函数
    virtual bool onTextFieldInsertText(CCTextFieldTTF * sender, const char * text, int nLen);
//    当用户进行删除文字 虚拟键盘的时候回调函数
    virtual bool onTextFieldDeleteBackward(CCTextFieldTTF * sender, const char * delText, int nLen);
};

#endif /* defined(__FishX__GMBillingLayer__) */
