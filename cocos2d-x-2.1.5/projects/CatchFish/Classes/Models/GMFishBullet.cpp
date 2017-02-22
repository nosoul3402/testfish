//
//  GMFishBullet.cpp
//  FishX
//
//  Created by peng on 13-3-1.
//
//

#include "GMFishBullet.h"


GMFishBullet::GMFishBullet()
{
    
}

GMFishBullet::~GMFishBullet()
{
    
}

void GMFishBullet::setValue(CCDictionary *dictionary)
{
    _id = ((CCString*)dictionary->valueForKey("id"))->intValue();
    _speed = ((CCString*)dictionary->valueForKey("speed"))->floatValue();
    _hurt_Value = ((CCString*)dictionary->valueForKey("hurt_Value"))->floatValue();
    _angle_Value = ((CCString*)dictionary->valueForKey("angle_Value"))->intValue();
    _life_Value = ((CCString*)dictionary->valueForKey("life_Value"))->floatValue();
    _rates_Value = ((CCString*)dictionary->valueForKey("rates_Value"))->floatValue();
    
}
