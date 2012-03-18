#include "IsilmePCH.h"
#include "Core/Behaviour.h"

#include "Perception.h"
#include "Attribute.h"
#include "AIBehaviour.h"

Perception::Perception()
{

}

Perception::~Perception()
{

}

void Perception::SetID( std::string id )
{
	mID = id;
}

std::string Perception::GetID() const
{
	return mID;
}

std::string AttributePerception::GetAttributeID() const
{
	return mAttribute;
}

float AttributePerception::GetValue( BehaviourPtr behaviour ) const 
{
	
	AttributePtr attr = boost::shared_dynamic_cast<AIBehaviour>(behaviour)->GetAttribute(mAttribute);
	return attr->GetValue();
}

AttributePerception::AttributePerception( std::string attribute )
{
	mAttribute = attribute;
}

void AttributePerception::SetAttributeID( std::string attr )
{
	mAttribute = attr;
}

luabind::object ScriptedPerception::GetLuaFunction() const
{
	return mLuaFunction;
}

void ScriptedPerception::SetLuaFunction( luabind::object f )
{
	mLuaFunction = f;
}

float ScriptedPerception::GetValue( BehaviourPtr behaviour ) const 
{
	return 0.0f;
}
