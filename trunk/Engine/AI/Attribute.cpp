#include "IsilmePCH.h"
#include "Attribute.h"


Attribute::Attribute(std::string id, float value, float maxValue)
{
	mID = id;
	mValue = value;
	mMaxValue = mMaxValue;
}

Attribute::~Attribute()
{

}

float Attribute::GetValue() const
{
	return mValue;
}

void Attribute::SetValue(float value)
{
	if (mMaxValue != Infinity)
		mValue = std::min(value, mMaxValue);
	mValue = value;
}

std::string Attribute::GetID() const
{
	return mID;
}

float Attribute::GetMaxValue() const
{
	return mMaxValue;
}

void Attribute::SetMaxValue( float value )
{
	mMaxValue = value;
	if (mMaxValue != Infinity)
		mValue = std::min(mValue, mMaxValue);
}


const float Attribute::Infinity = std::numeric_limits<float>::infinity();
