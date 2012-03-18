#include "IsilmePCH.h"
#include "AIPalette.h"
#include "AI/AIPackage.h"
#include "Engine/AI/AIPackageDef.h"
#include "AI/Factories/AIPackageFactory.h"

AIPalette::AIPalette()
{

}

AIPalette::~AIPalette()
{

}

void AIPalette::RegisterAIType( std::string type, AIPackageFactoryPtr aiFactory )
{
	mFactories[type] = aiFactory;
}

AIPackagePtr AIPalette::CreateAIPackage( std::string id )
{
	AIDefMap::iterator it = mDefinitions.find(id);
	if (it != mDefinitions.end())
		return it->second->CreatePackage();

	return AIPackagePtr();
}

void AIPalette::Clear()
{
	mDefinitions.clear();
}

void AIPalette::Load( std::string fileName )
{
	TiXmlDocument document(fileName.c_str());
	document.LoadFile();
	
	Load(document.RootElement());
}

void AIPalette::Load( TiXmlElement* element )
{
	TiXmlElement* packageElement = element->FirstChildElement();
	while (packageElement)
	{
		std::string packageType = packageElement->Value();

		AIPackageFactoryPtr factory = mFactories[packageType];
		if (factory)
		{
			const char* idAttr = packageElement->Attribute("ID");
			if (idAttr)
			{
				std::string id = idAttr;
				AIPackageDefPtr definition = factory->CreateDef();
				definition->Parse(packageElement);
				mDefinitions[id] = definition;
			}
			else
			{
				LOG_D("ID was not specified for AI package");
			}
		}
		else
		{
			LOG_D("AI Package type %s not found", packageType.c_str());
		}

		packageElement = packageElement->NextSiblingElement();
	}
}