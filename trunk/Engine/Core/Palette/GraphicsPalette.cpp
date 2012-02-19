#include "IsilmePCH.h"
#include "GraphicsPalette.h"
#include "GraphicsFactory.h"
//#include "Graphics.h"
#include "Graphics/StateGraphics.h"

GraphicsPalette::GraphicsPalette()
{

}

GraphicsPalette::~GraphicsPalette()
{

}

void GraphicsPalette::RegisterGraphicsType( std::string type, GraphicsFactoryPtr factory )
{
	mFactories[type] = factory;
}

GraphicsPtr GraphicsPalette::CreateGraphics( std::string id )
{
	GraphicsDefMap::iterator it = mDefinitions.find(id);
	if (it != mDefinitions.end())
		return it->second->Create();

	return GraphicsPtr();
}

void GraphicsPalette::ClearPalette()
{
	mDefinitions.clear();
}

void GraphicsPalette::Load( std::string fileName )
{
	TiXmlDocument document;
	document.LoadFile(fileName.data());

	TiXmlElement* root = document.RootElement();
	TiXmlElement* defElement = root->FirstChildElement();

	// Загружаем поочередно все элементы с описаниями графики
	while(defElement)
	{
		GraphicsDefPtr def = LoadDefinition(defElement);

		defElement = defElement->NextSiblingElement();
	};
}

GraphicsDefPtr GraphicsPalette::LoadDefinition( TiXmlElement* element )
{
	GraphicsDefPtr def;
	std::string name = element->Attribute("Name");
	std::string type = element->Value();

	GraphicsFactoryMap::iterator it = mFactories.find(type);
	if (it != mFactories.end())
	{
		def = it->second->LoadDefinition(element);
		mDefinitions[name] = def;
	}
	else
	{
		RegisterGraphicsType(type, GraphicsFactory<graphics::StateGraphicsDef<Behaviour> >::New());
		it = mFactories.find(type);
		def = it->second->LoadDefinition(element);
		mDefinitions[name] = def;
		// Unregistered type
		LOG_W("Graphics type %s is not registered", type.c_str());
	}

	return def;
}

void GraphicsPalette::ClearTypes()
{
	mFactories.clear();
}

GraphicsDefPtr GraphicsPalette::GetDefinition( std::string id )
{
	GraphicsDefMap::iterator it = mDefinitions.find(id);
	if (it != mDefinitions.end())
		return it->second;
	return GraphicsDefPtr();
}

GraphicsFactoryPtr GraphicsPalette::GetFactory( std::string type )
{
	return mFactories[type];
}
