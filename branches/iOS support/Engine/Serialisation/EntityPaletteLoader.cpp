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
#include "EntityPaletteLoader.h"
#include "Core/FactoryManager.h"
#include "Palette/BehaviourPalette.h"
#include "Palette/GraphicsPalette.h"
#include "Palette/EntityPalette.h"
#include "Core/MasterFile.h"
#include "../Core/Engine.h"
#include "../Core/ResourceManager.h"

namespace serialisation
{

	EntityPaletteLoader::EntityPaletteLoader()
	{

	}

	EntityPaletteLoader::~EntityPaletteLoader()
	{

	}

	EntryPtr EntityPaletteLoader::LoadEntry( std::string filename )
	{
		ContainerEntry<EntityPalette>* entry = new ContainerEntry<EntityPalette>(filename);

        char* path = Engine::GetSingleton()->GetResourceManager()->ResourcePath(filename.c_str());
		TiXmlDocument document(path);
		document.LoadFile();

		entry->data = Load(document.RootElement());
		return EntryPtr(entry);
	}

	EntityPalettePtr EntityPaletteLoader::Load( TiXmlElement* element )
	{
		EntityPalettePtr palette = FactoryManager::GetSingleton()->GetEntityPalette();

		TiXmlElement* defElement = element->FirstChildElement("Entity");

		EntityDefPtr def;
		while (defElement)
		{
			std::string type = defElement->Attribute("Type");

			char* attr;
			/// ������ �������
			attr = (char*)(defElement->Attribute("Graphics"));
			GraphicsDefPtr graphics = FactoryManager::GetSingleton()->GetGraphicsPalette()->GetDefinition(attr);

			/// ������ ���������
			TiXmlElement* bElement = defElement->FirstChildElement("Behaviour");
			attr = (char*)(defElement->Attribute("Behaviour"));
			if (!attr)
				attr = "Default";
			BehaviourFactoryPtr bf = FactoryManager::GetSingleton()->GetBehaviourPalette()->GetFactory(attr);
			if (!bf)
				bf = FactoryManager::GetSingleton()->GetBehaviourPalette()->GetDefaultFactory();
			BehaviourDefPtr behaviour = bf->LoadDefinition(bElement);

			/// ������ ������
			BodyDef* body = new BodyDef();
			TiXmlElement* bodyElement = defElement->FirstChildElement("Body");
			body->Parse(bodyElement);

			/// ������� �����������
			def = EntityDefPtr(new EntityDefinition(body, graphics, behaviour));
			def->mType = type;

			palette->AddDefinition(def);

			defElement = defElement->NextSiblingElement("Entity");
		}
		return palette;
	}

}