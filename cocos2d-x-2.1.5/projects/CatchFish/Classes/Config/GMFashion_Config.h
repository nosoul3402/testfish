//
//  IOSFashion_Config.h
//  peng
//
//  Created by peng on 12-12-5.
//  Copyright (c) 2012年 peng. All rights reserved.
//

/*
 **************************
 *      一些方法定义成宏     *
 **************************
 */

#ifndef Test_Fashion_Config_h
#define Test_Fashion_Config_h

/*
 **************************
 *          NSLog         *
 **************************
 */
#define ZPLog(s,...)               \
   CCLog("测试:: %s ==>(Note:function %s line %d)\n", CCString::createWithFormat(s, ##__VA_ARGS__)->getCString() , __FUNCTION__, __LINE__);

#define ZPFileLog(s,...) \
    CCLog("%s ==>\nCocos2d:(Note:in %s %s %d)\n", CCString::createWithFormat(s, ##__VA_ARGS__)->getCString() , __FILE__, __FUNCTION__, __LINE__);

//    CCLog("::%s -> %s  ",__FUNCTION__ ,CCString::createWithFormat(s, ##__VA_ARGS__)->getCString())
/*
 **************************
 *        String          *
 **************************
 */
#define IOSString(s,...)               \
    ([NSString stringWithFormat:(s), ##__VA_ARGS__]);

/*
 **************************
 *        Release         *
 **************************
 */
//#pragma mark - Release

#define Release(__v)        ([__v release]);
#define SafeRelease(__v)    ([__v release], __v = nil);


#define RADIANS_TO_DEGREES(__ANGLE__) ((__ANGLE__)/M_PI*180)

#define WINSIZE         CCDirector::sharedDirector()->getWinSize()//([[CCDirector sharedDirector] winSize])

#define WINSIZE_W       (WINSIZE.width)
#define WINSIZE_H       (WINSIZE.height)

#define DELEGATE        ((AppDelegate*)CCApplication::sharedApplication())

#define Get_W(rect)         (rect.size.width)
#define Get_H(rect)         (rect.size.height)

#define Get_Rect(object)       (object->getTextureRect())
#define Get_Box(object)        (object->boundingBox())
#define GetSize(object)        (object->getContentSize())

#define SCALE           CCDirector::sharedDirector()->getContentScaleFactor()

#define Screen_Scale    (([UIScreen mainScreen].scale)/2.0)

#define Scale1   0.65
#define Scale2   0.6
#define Scale3   0.7
#define Scale4   0.5

#define S_WINSIZE_W        800
#define S_WINSIZE_H        480


#define FISH_W        480
#define FISH_H        320

#define FISH_SCALE    (WINSIZE_H/FISH_H)

#define BG_SCALE2    (WINSIZE_W/FISH_W)

#define Scale_X         ((WINSIZE_W)/S_WINSIZE_W)
#define Scale_Y         ((WINSIZE_H)/S_WINSIZE_H)

#define SetScale(object) \
    object->setScaleX(Scale_X);\
    object->setScaleY(Scale_Y);

#define SetScale1(object) \
    object->setScale(Scale1);

#define SetScale2(object,scale) \
    object->setScale(scale);



#define JNIHELPER_NUKNOW        0
#define JNIHELPER_TengXun       1
#define JNIHELPER_91            2
#define JNIHELPER_91_IOS        3
#define JNIHELPER_YiDong        4
#define JNIHELPER_Telecom       5//电信计费
#define JNIHELPER_91_Android    6
#define JNIHELPER_Unicom_Android 7

#define JNIHELPER_INDEX         JNIHELPER_91_IOS


#endif






