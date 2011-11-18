#include "IsilmePCH.h"
#include "EntityDefinition.h"

EntityDefinition::EntityDefinition(BodyDef* body, GraphicsDefPtr graphics, BehaviourDefPtr behaviour)
{
	mBody = body;
	mGraphics = graphics;
	mBehaviour = behaviour;
}

EntityDefinition::~EntityDefinition()
{
}

BodyDef* EntityDefinition::GetBodyDefinition()
{
	return mBody;
}

GraphicsDefPtr EntityDefinition::GetGraphicsDefinition()
{
	return mGraphics;
}

BehaviourDefPtr EntityDefinition::GetBehaviourDefinition()
{
	return mBehaviour;
}
