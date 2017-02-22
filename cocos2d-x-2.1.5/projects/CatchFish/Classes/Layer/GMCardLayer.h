//
//  GMCardLayer.h
//  FishX
//
//  Created by peng on 12-12-24.
//
//

#ifndef __FishX__GMCardLayer__
#define __FishX__GMCardLayer__

#include <iostream>
//#include "cocos2d.h"
#include "../Config/GMFashionConfig.h"
#include "../PublicModels/UIRollNum.h"
#include "cocos-ext.h"

typedef enum {
    Tag_TAG = 100000,
    Tag_Title,
    Tag_Fish,
    Tag_Star1,
    Tag_Star2,
    Tag_Star3,
    Tag_xBg,
    Tag_Cover,//遮盖
    Tag_Bg,//选中关卡后出现场景的小图标
    Tag_Waves,
    Tag_SocreTitle,
    Tag_MaxSocre,
} tag ;

class GMCardLayer : public cocos2d::CCLayer
{
public:

	CCLayerColor        *m_pLayer;
	cocos2d::extension::CCScrollView      *m_pScrollView;

private:
    void initElement();
    
    void backAction(CCObject *pSender);
    void goleAction(CCObject *pSender);
    void startAction(CCObject *pSender);

    void showStart(int num,CCNode* pChild);
    int   level;
    
    float tempW;
    float tempH;
    CCPoint sPoint;
    CCPoint ePoint;
    
    float           tempx1,tempx2;
    int   checkpoints_index; //大关卡索引
    int   checkpoints_tag;//小关的标签
    int   tempcheckpointsIndex; // 临时的一个 大关卡索引
    CCMenuItemSprite  *startMenu;
    CCMenu *otherMenu;
    CCMenuItemSprite *arrow1;
    CCMenuItemSprite *arrow2;
    CCSprite *checkpointTheme;
    
    UIRollNum *m_pTotalEnergy;
    
    bool     isSelectCheckpoints;
    bool     isSelectotherMenu;
    bool     isShowDialogLayer;
    bool     isLoadT;
    bool                _isShowYiDong;//是否已经显示移动的计费界面
//    CCRenderTexture    *renderTexture;//截屏
public:
    virtual bool init();
    virtual ~GMCardLayer(void);
    static cocos2d::CCScene* scene();
	int choosedCard;
	CCObject* tempObj;
    CREATE_FUNC(GMCardLayer);
    
     void removeBilling(int index,bool _isClickClose,int tag);
private:
    
    GMBillingModel      billingModel;
    
    CCSpriteBatchNode *cardBatchNode;
    
    void showMoney(float dt);
    void setMoney();
    int    moneyNum;
    //每一关
    void initEachLevel(int index);
    void chooseLevel(CCObject *object);
    void removeWaves();
    
    void intScorllView();
    
    void arrowAtion1(CCObject *pSender);
    void arrowAtion2(CCObject *pSender);
    
    void adjustScrollView(int arrow,bool isScroll);
    
    void setRepeatScale(CCNode *node);
    
    void setPage(bool plus,bool isScroll);
    
    void removeDialogLayer(CCNode *dialog);
    
    void addchangeboom();
    //1 为正版验证，2为购买能量，3为购买技能，4为购买武器
    void addBilling(int index,int index2);
    void checkBillingPoint(float dt);
    //91 移动 获取验证码和好友手机号
    void check91BillingCode(float dt);
    void check91BillingPoint(float dt);
    
    void showYidongSdkView(int index);
//#pragma mark - 电信计费相关的方法
    void showTelecomSMSView(int _index);
    
    void removeTipView(float dt);
    
    CCMenuItemSprite *addMenu(const char *normal,const char *selected,bool filpx,CCPoint point,SEL_MenuHandler selector,CCPoint anc);
    
    virtual bool ccTouchBegan (CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved (CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded (CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    
    virtual void keyBackClicked();//Android 返回键
	virtual void keyboardHook(int keyCode, int keyEvent);
};
#endif /* defined(__FishX__GMCardLayer__) */
