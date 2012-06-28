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
#ifndef ISILME_SERIALISATION_MASTERFILELOADER_H
#define ISILME_SERIALISATION_MASTERFILELOADER_H

#include "../Definitions.h"
#include "Types.h"
#include "EntryLoader.h"

namespace serialisation
{
	/// @class MasterFileLoader
	/// Loader for masterfiles
	class ISILME_API MasterFileLoader
	{
	public:
		MasterFileLoader();
		virtual ~MasterFileLoader();

		/// Loads masterfile and all data in it
		MasterFilePtr Load(std::string fileName);

		/// Add loader for category
		void Add(std::string category, EntryLoaderPtr loader);

	protected:
		/// Loads masterfile from XML data
		MasterFilePtr Load(TiXmlElement* element);

		/// Loads category and all entries
		CategoryPtr LoadCategory( TiXmlElement* categoryElement );
	private:
		typedef std::map<std::string, EntryLoaderPtr> EntryLoadersMap;

		/// Loaders for each category
		EntryLoadersMap mLoaders;

	};

	class ISILME_API MasterFileSerialiser
	{
	public:
		MasterFileSerialiser();
		virtual ~MasterFileSerialiser();

		virtual void Serialise(MasterFilePtr data, std::string filename);
	};
}
#endif