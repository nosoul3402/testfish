//
//  GMAchievement.cpp
//  FishX
//
//  Created by peng on 13-3-12.
//
//

#include "GMAchievement.h"
#include "../Config/GMFashion_Config.h"

GMAchievement::GMAchievement()
{
    
}

GMAchievement::~GMAchievement()
{
    sprintf(_name, "%s","");
}

void GMAchievement::setValue(CCDictionary *dictionary)
{
    _id = ((CCString*)dictionary->valueForKey("id"))->intValue();
    const char *name = ((CCString*)dictionary->valueForKey("name"))->getCString();
    sprintf(_name, "%s",name);
    _energe = ((CCString*)dictionary->valueForKey("energe"))->intValue();
    const char *note = ((CCString*)dictionary->valueForKey("Note"))->getCString();
    sprintf(_note, "%s",note);
    
    _status = 0;
}


