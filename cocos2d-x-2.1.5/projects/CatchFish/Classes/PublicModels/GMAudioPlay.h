//
//  GMAudioPlay.h
//  FishX
//
//  Created by peng on 13-2-27.
//
//

#ifndef __FishX__GMAudioPlay__
#define __FishX__GMAudioPlay__

#include <iostream>
#include "cocos2d.h"
USING_NS_CC;

#define Audio_anger                     "Audio/Audio_E_Anger.mp3"
#define Audio_energe                    "Audio/Audio_E_Energe.mp3"
#define Audio_attack1                   "Audio/Audio_E_Attack1.mp3"//攻击
#define Audio_attack2                   "Audio/Audio_E_Attack2.mp3"//受到攻击
#define Audio_Button                    "Audio/Audio_E_Button.mp3"
#define Audio_Achievement               "Audio/Audio_E_Ach.mp3"
#define Audio_Waves                     "Audio/Audio_E_Waves.mp3"
#define Audio_Boss1Death                "Audio/Audio_E_Boss1Death.mp3"
#define Audio_Rewarad                   "Audio/Audio_E_Rewarad.mp3"
#define Audio_Task                      "Audio/Audio_E_Task.mp3"
#define Audio_Win                       "Audio/Audio_E_Win.mp3"
#define Audio_Lose                      "Audio/Audio_E_Lose.mp3"
#define Audio_Over                      "Audio/Audio_E_Over.mp3"
#define Audio_Home                      "Audio/Audio_B_Home.mp3"
#define Audio_BG_Boss                   "Audio/Audio_B_Boss.mp3"
#define Audio_Gmae1                     "Audio/Audio_B_Gmae1.mp3"
#define Audio_Wheel                     "Audio/Audio_E_Wheel.mp3"
#define Audio_Rayover                   "Audio/Audio_E_rayover.mp3"			//没有能量
#define Audio_Blood                     "Audio/Audio_E_Blood.mp3"			//没有能量
#define Audio_Crow                      "Audio/Audio_E_Crow.mp3"			//没有能量
#define Audio_Pays                      "Audio/Audio_E_Pays.mp3"			//没有能量
#define Audio_Attack3                   "Audio/Audio_E_Attack3.mp3"			//没有能量



class GMAudioPlay // : public CCObject
{
public:
    GMAudioPlay();
    virtual ~GMAudioPlay(void);
    
    static GMAudioPlay* sharedAudioPlay();
    
    void setCloseStatus();
    
private:
    static GMAudioPlay* m_pAudioPlay;
    void initValue();
    
    int         closeStatus;
public:
    void playBGMusic(const char *name);
    void stopBGMusic();
//
    void playOtherEffect(const char *name, bool bLoop);
    void playButtonEffect();
    void playAngerEffect();
    void playEnergeEffect();
    void playAttackEffect(const char *name);
    void stopMyAllEffects();
//
    void purgeSharedAudioPlay();
};

#endif /* defined(__FishX__GMAudioPlay__) */
