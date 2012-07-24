//
//  AIAction.cpp
//  Isilme
//
//  Created by Alexander Alimov on 7/20/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "AIAction.h"

AIAction::~AIAction()
{

}

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

AIBehaviourPtr AIAction::GetActor()
{
	AIBehaviourPtr a;
	return a;
}