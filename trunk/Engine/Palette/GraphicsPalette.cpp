//  Copyright (C) 2010-2012 VSTU
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
//
//	���� ���� � ����� Isilme SDK.
//
//		Isilme SDK - ��������� ���������: �� ������ ������������������ �� �/���
//		�������� �� �� �������� ������� ����������� ������������ �������� GNU � ��� ����,
//		� ����� ��� ���� ������������ ������ ���������� ������������ �����������;
//		���� ������ 3 ��������, ���� (�� ������ ������) ����� ����� �������
//		������.
//
//		Isilme SDK ���������������� � �������, ��� ��� ����� ��������,
//		�� ���� ������ ��������; ���� ��� ������� �������� ��������� ����
//		��� ����������� ��� ������������ �����. ��������� ��. � ������� �����������
//		������������ �������� GNU.
//
//		�� ������ ���� �������� ����� ������� ����������� ������������ �������� GNU
//		������ � ���� ����������. ���� ��� �� ���, ��.
//		<http://www.gnu.org/licenses/>.
#include "IsilmePCH.h"
#include "GraphicsPalette.h"
#include "Core/GraphicsFactory.h"
//#include "Graphics.h"
#include "Graphics/StateGraphics.h"
#include "../Core/Engine.h"
#include "../Core/ResourceManager.h"

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
    
    char* path = Engine::GetSingleton()->GetResourceManager()->ResourcePath(fileName.c_str());
	document.LoadFile(path);

	TiXmlElement* root = document.RootElement();
	TiXmlElement* defElement = root->FirstChildElement();

	// ��������� ���������� ��� �������� � ���������� �������
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
