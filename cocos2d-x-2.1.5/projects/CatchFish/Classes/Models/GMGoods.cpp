//
//  GMGoods.cpp
//  FishX
//
//  Created by peng on 13-3-1.
//
//

#include "GMGoods.h"


GMGoods::GMGoods()
{
    
}

GMGoods::~GMGoods()
{
    
}
void GMGoods::setValue(CCDictionary *dictionary)
{
    _id		= ((CCString*)dictionary->valueForKey("id"))->intValue();
    _name	= ((CCString*)dictionary->valueForKey("name"))->getCString();
    _rate	= ((CCString*)dictionary->valueForKey("rate"))->floatValue();
    _type	= ((CCString*)dictionary->valueForKey("type"))->intValue();
    _rate	= ((CCString*)dictionary->valueForKey("rate"))->floatValue();
    _angle	= ((CCString*)dictionary->valueForKey("angle"))->floatValue();
    _energe = ((CCString*)dictionary->valueForKey("energe"))->intValue();
}


