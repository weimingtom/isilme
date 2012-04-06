//  Copyright (C) 2010-2012 Alexander Alimov
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
//	Этот файл — часть Isilme SDK.
//
//		Isilme SDK - свободная программа: вы можете перераспространять ее и/или
//		изменять ее на условиях Меньшей стандартной общественной лицензии GNU в том виде,
//		в каком она была опубликована Фондом свободного программного обеспечения;
//		либо версии 3 лицензии, либо (по вашему выбору) любой более поздней
//		версии.
//
//		Isilme SDK распространяется в надежде, что она будет полезной,
//		но БЕЗО ВСЯКИХ ГАРАНТИЙ; даже без неявной гарантии ТОВАРНОГО ВИДА
//		или ПРИГОДНОСТИ ДЛЯ ОПРЕДЕЛЕННЫХ ЦЕЛЕЙ. Подробнее см. в Меньшей стандартной
//		общественной лицензии GNU.
//
//		Вы должны были получить копию Меньшей стандартной общественной лицензии GNU
//		вместе с этой программой. Если это не так, см.
//		<http://www.gnu.org/licenses/>.
#include "IsilmePCH.h"
#include "DynamicLevelSerialiser.h"
#include "LevelSerialiser.h"
#include "Core/Layer.h"
#include "Core/Level.h"
#include "Core/Entity.h"
#include "Core/Behaviour.h"
#include "Core/FactoryManager.h"
#include "Core/MasterFile.h"

namespace serialisation
{
	DynamicLevelSerialiser::DynamicLevelSerialiser()
	{
	
	}

	DynamicLevelSerialiser::~DynamicLevelSerialiser()
	{
	
	}

	void DynamicLevelSerialiser::Serialise(LevelPtr level, std::string fileName)
	{

	}

	TiXmlElement* DynamicLevelSerialiser::Serialise( LevelPtr level )
	{
		TiXmlElement* levelElement = new TiXmlElement("Level");

		for (int i = 0; i < level->GetLayersCount(); ++i)
		{
			levelElement->InsertEndChild(*SerialiseLayer(level->GetLayer(i)));
		}
		return levelElement;
	}

	TiXmlElement* DynamicLevelSerialiser::SerialiseEntity( EntityPtr entity )
	{
		TiXmlElement* element = new TiXmlElement("Entity");

		// Сохраняем общие данные
		element->SetAttribute("ID", entity->GetName().c_str());
		element->SetAttribute("Type", entity->GetType().c_str());

		// Сохраняем координты, угол, масштаб
		char position[256];
		sprintf(position, "%d, %d", entity->GetPosition().x, entity->GetPosition().y);
		element->SetAttribute("Position", position);
		element->SetAttribute("Angle", entity->GetAngle());
		element->SetAttribute("Scale", entity->GetScale());

		return element;
	}

	TiXmlElement* DynamicLevelSerialiser::SerialiseWorld()
	{
		TiXmlElement* elemet = new TiXmlElement("Data");

		FactoryPtr factory = FactoryManager::GetSingleton();

		CategoryPtr levels = FactoryManager::GetSingleton()->GetMasterFile()->GetCategory("Levels");
		for (int i = 0; i < levels->GetSize(); ++i)
		{
			LevelPtr level = levels->GetEntry<LevelEntry>(i)->data;
			elemet->InsertEndChild(*Serialise(level));
		}

		return elemet;
	}

	TiXmlElement* DynamicLevelSerialiser::SerialiseLayer( LayerPtr layer )
	{
		TiXmlElement* layerElement = new TiXmlElement("Layer");

		for (int i = 0; i < layer->Size(); ++i)
		{
			layerElement->InsertEndChild(*SerialiseEntity(layer->GetEntity(i)));
		}

		return layerElement;
	}

};