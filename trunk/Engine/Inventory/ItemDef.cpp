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
#include "ItemDef.h"
#include "Item.h"
#include "Core/ResourceManager.h"

namespace inventory
{
	ItemDef::ItemDef()
	{
		ReloadingTime = 0.0f;
		UsingTime = 0.0f;
		Icon = 0;
		UseSound = 0;
		Ammo = 0;
		MaxAmmo = 0;
		Infinity = false;
	}

	ItemDef::~ItemDef()
	{
	}

	void	ItemDef::Parse(TiXmlElement* def)
	{
		Tag = def->Attribute("Tag");
		def->QueryFloatAttribute("UsingTime", &UsingTime);
		def->QueryFloatAttribute("ReloadingTime", &ReloadingTime);
		def->QueryIntAttribute("Ammo", &Ammo);
		def->QueryIntAttribute("MaxAmmo", &MaxAmmo);

		int isInfinity = 0;
		def->QueryIntAttribute("Infinity", &isInfinity);
		Infinity = isInfinity != 0;

		int isMerging = 0;
		def->QueryIntAttribute("UseMerging", &isMerging);
		UseMerging = isMerging != 0;

		if (def->Attribute("Icon"))
		{
			Icon = gcn::Image::load(def->Attribute("Icon"));
		}

		if (def->Attribute("UseSound"))
		{
			UseSound = Engine::GetSingleton()->GetResourceManager()->GetEffect(def->Attribute("UseSound"));
		}

		if (def->Attribute("GND"))
		{
			GND = def->Attribute("GND");
		}
	}

	ItemPtr	ItemDef::Create()
	{
		return ItemPtr(new Item(this));
	}
};