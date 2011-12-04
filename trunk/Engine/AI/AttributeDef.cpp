#include "IsilmePCH.h"
#include "AttributeDef.h"
#include "Attribute.h"

namespace ai
{
	AttributeDef::AttributeDef()
	{
	
	}

	AttributeDef::~AttributeDef()
	{
	
	}

	AttributePtr AttributeDef::Create()
	{
		return AttributePtr(new Attribute(mID, mValue));
	}

	void AttributeDef::Parse(TiXmlElement* attrElement)
	{
		mID = "";
		mValue = 0.0f;

		const char* idAttr = attrElement->Attribute("ID");
		if (idAttr)
			mID = idAttr;

		attrElement->QueryFloatAttribute("Value", &mValue);
	}
}