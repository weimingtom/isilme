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
#include "StaticLevelSerialiser.h"
#include "Core/FactoryManager.h"
#include "Core/Level.h"
#include "Core/Layer.h"
#include "Core/Entity.h"

namespace serialisation
{
	StaticLevelSerialiser::StaticLevelSerialiser()
	{

	}

	StaticLevelSerialiser::~StaticLevelSerialiser()
	{
	
	}

	TiXmlElement* StaticLevelSerialiser::SerialiseEntity(EntityPtr entity)
	{
		TiXmlElement* entityElement = new TiXmlElement("Entity");

		entityElement->SetAttribute("Name", entity->GetName().c_str());
		entityElement->SetAttribute("Type", entity->GetType().c_str());

		char dummy[256];
		sprintf(dummy, "%f, %f, %f", entity->GetPosition().x, entity->GetPosition().y, entity->GetAngle());
		entityElement->SetAttribute("Position", dummy);
		entityElement->SetAttribute("Scale", entity->GetScale());
		return entityElement;
	}

	TiXmlElement* StaticLevelSerialiser::SerialiseLayer(LayerPtr layer)
	{
		TiXmlElement* layerElement = new TiXmlElement("Layer");
		layerElement->SetAttribute("Name", layer->GetName().c_str());

		for (int i = 0; i < layer->Size(); ++i)
		{
			EntityPtr e = layer->GetEntity(i);
			layerElement->InsertEndChild(*SerialiseEntity(e));
		}

		return layerElement;
	}

	TiXmlElement* StaticLevelSerialiser::Serialise(LevelPtr level)
	{
		TiXmlElement* levelElement = new TiXmlElement("Level");
		TiXmlElement* worldElement = new TiXmlElement("World");
		char buf[256];
		sprintf(buf, "%f, %f", level->GetWorld()->GetGravity().x, level->GetWorld()->GetGravity().y);

		worldElement->SetAttribute("Gravity", buf);
		levelElement->InsertEndChild(*worldElement);

		// Записываем имя уровня
		levelElement->SetAttribute("Name", level->GetID().c_str());


		// Записываем камеру
		// Записываем физику
		// Записываем слои
		for (int i = 0; i < level->GetLayersCount(); ++i)
		{
			LayerPtr layer = level->GetLayer(i);
			TiXmlElement* layerElement = SerialiseLayer(layer);
			levelElement->InsertEndChild(*layerElement);
		}

		return levelElement;
	}

	void StaticLevelSerialiser::Serialise(LevelPtr level, std::string fileName)
	{
		TiXmlElement* root = Serialise(level);
		TiXmlDocument* document = new TiXmlDocument(fileName.c_str());
		document->InsertEndChild(*root);
		document->SaveFile();
		delete document;
	}
};