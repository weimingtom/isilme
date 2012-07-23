//
//  AIPackagesManager.cpp
//  Isilme
//
//  Created by Alexander Alimov on 7/20/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "AIPackagesExecuter.h"
#include "AIPackage.h"
#include "AIBehaviour.h"
#include "TargetSelector.h"

AIPackagesExecuter::AIPackagesExecuter()
{
    
}

AIPackagesExecuter::~AIPackagesExecuter()
{
    
}

void AIPackagesExecuter::AddPackage(AIPackagePtr package)
{
    mPackages.insert(package);
}

void AIPackagesExecuter::RemovePackage(AIPackagePtr package)
{
    mPackages.erase(package);
}

void AIPackagesExecuter::ChooseAction(AIBehaviourPtr actor, EntityPtr defaultTarget)
{
    float maxUtility = 0.0f;
    AIPackagePtr choosenPackage;
    EntityPtr choosenTarget;
    
    for (PackagesContainer::iterator it = mPackages.begin(); it != mPackages.end(); ++it)
    {
        AIPackagePtr package = *it;
        if (package->IsApplicable(actor))
        {
            EntityPtr target = package->GetTargetSelector()->SelectTargetFor(actor);
            
            float utility = package->CalcUtility(actor, target);
            if (utility > maxUtility)
            {
                maxUtility = utility;
                choosenPackage = package;
                choosenTarget = target;
            }
        }
    }
    
    if (choosenPackage)
    {
        ActionPtr action = choosenPackage->CreateAction();
        action->SetTarget(choosenTarget);
        actor->StartAction(action);
    }
}