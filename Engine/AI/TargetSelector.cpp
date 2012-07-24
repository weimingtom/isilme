//  Copyright (C) 2012 VSTU
//
//	This file is part of Isilme SDK.
//
//		Isilme SDK is free software: you can redistribute it and/or modify
//		it under the terms of the GNU Lesser General Public License as published by
//		the Free Software Foundation, either version 3 of the License, or
//		(at your option) any later version.
//
//		Isilme SDK is distributed in the hope that it will be useful,
//		but WITHOUT ANY WARRANTY; without even the implied warranty of
//		MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//		GNU Lesser General Public License for more details.
//
//		You should have received a copy of the GNU Lesser General Public License
//		along with Isilme SDK.  If not, see <http://www.gnu.org/licenses/>.


#include "TargetSelector.h"
#include "AIBehaviour.h"
#include "../Core/FactoryManager.h"
#include "../Core/Entity.h"
#include "../Core/Level.h"

TargetSelector::~TargetSelector()
{
    
}

EntityPtr IDTargetSelector::SelectTargetFor(AIBehaviourPtr)
{
    EntityPtr target = FactoryManager::GetSingleton()->GetEntity(ID);
    return target;
}

EntityPtr RayCastTargetSelector::SelectTargetFor(AIBehaviourPtr behaviour)
{
    float x1 = actor->GetPosition().x;
    float y1 = actor->GetPosition().y;
    float x2 = x1 + maxDistance * cos(angle + actor->GetAngle());
    float y2 = y1 + maxDistance * sin(angle + actor->GetAngle());
    
    EntityPtr target = actor->GetLevel()->RayCastQueryNearest(x1, y1, x2, y2);
    return target;
}

EntityPtr PieTargetSelector::SelectTargetFor(AIBehaviourPtr behaviour)
{
    EntityPtr target;
    // @TODO: implement PieTargetSelector
    return target;
}

EntityPtr ParentTargetSelector::SelectTargetFor(AIBehaviourPtr behaviour)
{
	EntityPtr target;
	return target;
}