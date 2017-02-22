//
//  GMAudioPlay.cpp
//  FishX
//
//  Created by peng on 13-2-27.
//
//

#include "GMAudioPlay.h"
#include "SimpleAudioEngine.h"
#include "GMAccessData.h"
#include "GMPublicMethod.h"

using namespace CocosDenshion;

GMAudioPlay* GMAudioPlay::m_pAudioPlay = 0;

GMAudioPlay* GMAudioPlay::sharedAudioPlay()
{
    if (! m_pAudioPlay)
    {
        m_pAudioPlay = new GMAudioPlay();
        m_pAudioPlay->initValue();
        m_pAudioPlay->setCloseStatus();
    }
    
    return m_pAudioPlay;
}

GMAudioPlay::GMAudioPlay()
{
    
}

GMAudioPlay::~GMAudioPlay()
{
    SimpleAudioEngine::sharedEngine()->end();
}

void GMAudioPlay::setCloseStatus()
{
    closeStatus = GMPublicMethod::sharedPublicMethod()->getAudioStatus();//GMAccessData::getAudioStatus();
}

void GMAudioPlay::initValue(){
    SimpleAudioEngine::sharedEngine()->preloadEffect(Audio_anger);
    SimpleAudioEngine::sharedEngine()->preloadEffect(Audio_energe);
    SimpleAudioEngine::sharedEngine()->preloadEffect(Audio_attack1);
    SimpleAudioEngine::sharedEngine()->preloadEffect(Audio_attack2);
    
    SimpleAudioEngine::sharedEngine()->preloadEffect(Audio_Button);
    SimpleAudioEngine::sharedEngine()->preloadEffect(Audio_Achievement);
    SimpleAudioEngine::sharedEngine()->preloadEffect(Audio_Waves);
    SimpleAudioEngine::sharedEngine()->preloadEffect(Audio_Rewarad);
    SimpleAudioEngine::sharedEngine()->preloadEffect(Audio_Task);
    SimpleAudioEngine::sharedEngine()->preloadEffect(Audio_Win);
    SimpleAudioEngine::sharedEngine()->preloadEffect(Audio_Lose);
    SimpleAudioEngine::sharedEngine()->preloadEffect(Audio_Over);
    SimpleAudioEngine::sharedEngine()->preloadEffect(Audio_Wheel);
    SimpleAudioEngine::sharedEngine()->preloadEffect(Audio_Blood); 
    
    SimpleAudioEngine::sharedEngine()->preloadEffect(Audio_Crow);
    SimpleAudioEngine::sharedEngine()->preloadEffect(Audio_Pays);
    SimpleAudioEngine::sharedEngine()->preloadEffect(Audio_Attack3); 

	SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic(Audio_Home);
	SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic(Audio_BG_Boss);
	SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic(Audio_Home);
}

void GMAudioPlay::playBGMusic(const char *name){
    if (closeStatus == 1) {
        stopBGMusic();
    }
    else {
        stopBGMusic();
        SimpleAudioEngine::sharedEngine()->playBackgroundMusic(name,true);
    }
}
//
void GMAudioPlay::stopBGMusic()
{
    bool play = SimpleAudioEngine::sharedEngine()->isBackgroundMusicPlaying();
    if (play) {
        SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
    }
}
//
void GMAudioPlay::playButtonEffect()
{
    if (closeStatus==1) {
        return;
    }
    SimpleAudioEngine::sharedEngine()->playEffect(Audio_Button);
}

void GMAudioPlay::playOtherEffect(const char *name, bool bLoop)
{
    if (closeStatus==1) {
        return;
    }
    SimpleAudioEngine::sharedEngine()->playEffect(name,bLoop);
}

void GMAudioPlay::stopMyAllEffects()
{
    if (closeStatus==1) {
        return;
    }
    SimpleAudioEngine::sharedEngine()->stopAllEffects();
}

//
void GMAudioPlay::playAngerEffect()
{
    if (closeStatus==1) {
        return;
    }
    SimpleAudioEngine::sharedEngine()->playEffect(Audio_anger);
}

void GMAudioPlay::playEnergeEffect()
{
    if (closeStatus==1) {
        return;
    }
    SimpleAudioEngine::sharedEngine()->playEffect(Audio_energe);
}
//
void GMAudioPlay::playAttackEffect(const char *name)
{
    if (closeStatus==1) {
        return;
    }
    SimpleAudioEngine::sharedEngine()->playEffect(name);
}

void GMAudioPlay::purgeSharedAudioPlay()
{
    CC_SAFE_DELETE(m_pAudioPlay);
    m_pAudioPlay = NULL;
}
