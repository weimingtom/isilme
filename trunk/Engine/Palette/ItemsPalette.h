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
#ifndef ISILME_PALETTE_ITEMSPALETTE_H
#define ISILME_PALETTE_ITEMSPALETTE_H

#include "Definitions.h"
#include "Types.h"

class ISILME_API ItemsPalette
{
public:
	ItemsPalette();
	virtual ~ItemsPalette();

	/// Clears the palette
	void Clear();

	/// Creates items by tag
	inventory::ItemPtr CreateItem( std::string tag );

	/// Gets factory of special type
	inventory::ItemFactoryPtr GetFactory( std::string type );

	/// Adds definition to palette
	void AddDefinition( inventory::ItemDefPtr def );

	/// Registers factory for type
	void RegisterFactory( std::string type, inventory::ItemFactoryPtr factory );
private:
	typedef std::map<std::string, inventory::ItemFactoryPtr> FactoriesMap;
	typedef std::map<std::string, inventory::ItemDefPtr> DefMap;

	FactoriesMap mFactories;
	DefMap mDefinitions;
};
#endif