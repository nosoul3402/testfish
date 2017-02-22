//
//  Config.h
//  FISHING
//
//  Created by peng on 12-10-24.
//
//

#ifndef FISHING_Config_h
#define FISHING_Config_h

#define _PI 3.14159265359f
#define _DEG2RAD 180.0f/_PI
#define DADIANS_TO_DEGREES1(__ANGLE__) ((__ANGLE__)/180*M_PI)

#define Enemy_Max          10

#define Max_Score1           40 //达到这个值时显示 “你真牛”


#define Checkpoints_1         1
#define Checkpoints_2         2
#define Checkpoints_3         3

//#pragma mark - 层次

#define Enemy_Layer         8
#define Bullet_Layer        9
#define UI_Layer            10
#define MENU_Layer          10
#define Element_Layer       10
#define MENU_NUM_Layer      11
#define MENU_C_Layer        11
#define Wheel_Layer         12
#define Target_Layer        12
#define APrompt_Layer       11
#define Dialog_Layer        100
//#define Bullet_Layer        7
#define Index_Pause         20

#define EnergyTime          60


#define CountAttackTime       2

#define GoToEndless 11


#define BOSS_TAG1               1001
#define BOSS_TAG2               1002
#define BOSS_TAG3               1003
#define BOSS_TAG4               1004

#define Billing_tag             20000000
//#pragma mark - 音效

#define VIDEO_GUN                   "Bombette.wav"
#define VIDEO_COIN                  "bgm_coin_01.mp3"

#define mainmenuTask_plist          "game/mainmenuTask.plist"
#define mainmenuTask_png            "game/mainmenuTask.png"

#define cannon_plist                "game/cannon.plist"
#define cannon_png                  "game/cannon.png"

#define Loading_plist               "Loading/loading.plist"
#define Loading_png                 "Loading/loading.png"

#define pause_plist                 "pause/pause.plist"
#define pause_png                   "pause/pause.png"

#define Buttle_plist1               "game/bomb.plist"
#define Buttle_png1                 "game/bomb.png"

#define Jiguang_plist               "game/jiguang.plist"
#define Jiguang_png                 "game/jiguang.png"

#define Win_plist                   "win/win.plist"
#define Win_png                     "win/win.png"

#define Lose_plist                  "lose/lose.plist"
#define Lose_png                    "lose/lose.png"

#define hitfish_plist               "game/hitfish.plist"
#define hitfish_png                 "game/hitfish.png"

#define gamegoal_plist				"game/gamegoal.plist"
#define gamegoal_png				"game/gamegoal.png"

#define gamegoal1_plist				"game/gamegoal1.plist"
#define gamegoal1_png				"game/gamegoal1.png"

#define numbera_plist				"game/numbera.plist"
#define numbera_png					"game/numbera.png"

#define changeboom_plist			"game/changeboom.plist"
#define changeboom_png				"game/changeboom.png"

#define homepage_plist              "home/homepage.plist"
#define homepage_png                "home/homepage.png"

#define homepage_plist1             "home/homepage1.plist"
#define homepage_png1               "home/homepage1.png"

#define yuwang_plist                "game/net.plist"
#define yuwang_png                  "game/net.png"

#define card_plist                  "Card/card.plist"
#define card_png                    "Card/card.png"

#define blood_plist                 "game/blood.plist"
#define blood_png                   "game/blood.png"
#define payskill_plist              "game/payskill.plist"
#define payskill_png                "game/payskill.png"
#define iceage_plist                "game/iceage.plist"
#define iceage_png                  "game/iceage.png"

#define juneng_plist                "game/juneng.plist"
#define juneng_png                  "game/juneng.png"

#define mainmenu_plist				"game/mainmenu.plist"
#define mainmenu_png				"game/mainmenu.png"

#define mainmenu021_plist			"game/mainmenu021.plist"
#define mainmenu021_png				"game/mainmenu021.png"

#define water_plist                 "game/water.plist"
#define water_png                   "game/water.png"

#define liuguang_plist				"game/liuguang.plist"
#define liuguang_png				"game/liuguang.png"

#define fishBullet_plist            "game/fishBullet.plist"
#define fishBullet_png              "game/fishBullet.png"

//鱼的子弹爆炸效果
#define explosionEffect_plist       "game/explosionEffect.plist"
#define explosionEffect_png         "game/explosionEffect.png"

//boss子弹爆炸效果
#define explosionEffect1_plist       "game/explosionEffect1.plist"
#define explosionEffect1_png         "game/explosionEffect1.png"

//赢的贝壳效果
#define wineffect_plist             "game/wineffect.plist"
#define wineffect_png               "game/wineffect.png"

//粒子特效
#define Particles1                  "particles/goldPortrait.plist"//"GoldenTroutParticles.plist"//"gemParticles.plist"
#define Particles3                  "particles/guangquan.plist"
#define Particles2                  "particles/lizhi_qipao.plist"
#define Particles4                  "particles/lizhi_qipao1.plist"
#define Particles_Energe            "particles/partucle_Energe.plist"
#define Particles_Rain				"particles/partucle_rain.plist"

//成就
#define achievement_plist           "game/achievement.plist"
#define achievement_png             "game/achievement.png"
#define achievement1_plist			"game/achievement1.plist"
#define achievement1_png			"game/achievement1.png"
#define achievement2_plist           "game/achievement2.plist"
#define achievement2_png             "game/achievement2.png"
#define achievement3_plist           "game/achievement3.plist"
#define achievement3_png             "game/achievement3.png"


//新手引导
#define guide_plist                 "game/guide.plist"
#define guide_png                   "game/guide.png"
#define guide1_plist                "cartoon/guide1.plist"
#define guide1_png                  "cartoon/guide1.png"

#define manhuagx_plist				"cartoon/manhuagx.plist"
#define maxhuagx_png				"cartoon/manhuagx.png"

#define cartoon_plist				"cartoon/cartoon.plist"
#define cartoon_png					"cartoon/cartoon.png"

//幸运转盘
#define luck_plist                  "game/luck.plist"
#define luck_png                    "game/luck.png"
#define luck_plist1                 "game/luck1.plist"
#define luck_png1                   "game/luck1.png"

//暴击
#define baoji1_plist                 "game/baoji1.plist"
#define baoji1_png                   "game/baoji1.png"
//boss 的血
#define bossblood1_plist             "game/bossblood1.plist"
#define bossblood1_png               "game/bossblood1.png"

#define APromptList_plist			 "File/APromptList.plist"

//boss 手
#define boss1hand1_plist             "fish/boss1hand1.plist"
#define boss1hand1_png               "fish/boss1hand1.png"

#define mermaid_plist				 "fish/mermaid.plist"
#define mermaid_png					 "fish/mermaid.png"

#define Fish_plist1                 "fish/fish.plist"
#define Fish_png1                   "fish/fish.png"

#define Fish_plist2                 "fish/attackfish1.plist"
#define Fish_png2                   "fish/attackfish1.png"

#define bossPoseidonEffect_plist	"fish/bossPoseidonEffect.plist"
#define bossPoseidonEffect_png		"fish/bossPoseidonEffect.png"

#define bossPoseidon1_plist			"fish/bossPoseidon1.plist"
#define bossPoseidon1_png			"fish/bossPoseidon1.png"

#define bossPoseidon2_plist			"fish/bossPoseidon2.plist"
#define bossPoseidon2_png			"fish/bossPoseidon2.png"

// boss 石化
#define petrifaction1_plist          "game/petrifaction1.plist"
#define petrifaction1_png            "game/petrifaction1.png"

#define guide2_plist				 "game/guide2.plist"
#define guide2_png					 "game/guide2.png"

#define guide1_plist				 "cartoon/guide1.plist"
#define guide1_png					 "cartoon/guide1.png"

#define ui_checkpointsfish_plist	 "Card/UI_Checkpointsfish.plist"
#define ui_checkpointsfish_png		 "Card/UI_Checkpointsfish.png"

#define s_year    2013
#define s_mon     8
#define s_day     20

//#pragma mark - plist




#endif
