//
//  AIAction.cpp
//  Isilme
//
//  Created by Alexander Alimov on 7/20/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "AIAction.h"

void AIAction::OnStart()
{
    
}

void AIAction::OnDone()
{
    
}

void AIAction::OnUpdate(float elapsedTime)
{
    mExecuter.ChooseAction(GetActor(), GetTarget());
}