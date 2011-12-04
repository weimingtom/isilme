#include "IsilmePCH.h"
#include "Attribute.h"

namespace ai
{
	Attribute::Attribute(std::string id, float value)
	{
		mID = id;
		mValue = value;
	}

	Attribute::~Attribute()
	{
	
	}

	float Attribute::GetValue()
	{
		return mValue;
	}

	void Attribute::SetValue(float value)
	{
		mValue = value;
	}

	std::string Attribute::GetID()
	{
		return mID;
	}
};