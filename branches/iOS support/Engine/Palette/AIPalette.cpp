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