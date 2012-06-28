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
#ifndef ISILME_SERIALISATION_SAVEMANAGER_H
#define ISILME_SERIALISATION_SAVEMANAGER_H

#include "Definitions.h"

namespace serialisation
{
	class ISILME_API SaveManager
	{
	public:
		SaveManager();
		virtual ~SaveManager();

		static SaveManagerPtr GetSingleton();

		/// Создает пустое сохранение
		///
		/// @return	.
		SaveDataPtr CreateSaveData();

		/// Загружает информацию о доступных сохранениях
		void LoadSaveData();

		/// Возвращает количество сохранений
		///
		/// @return	количество сохранений
		int GetSaveCount();

		/// Возвращает сохранение
		///
		/// @param	index	индекс сохранения
		///
		/// @return	The save data.
		SaveDataPtr GetSaveData(int index);

		/// Возвращает автоматическое сохранение
		///
		/// @return	The automatic save.
		SaveDataPtr GetAutoSave();

		/// Gets the quick save.
		///
		/// @return	The quick save.
		SaveDataPtr GetQuickSave();
		std::string GetSaveFolder();
	private:
		/// Путь к файлам сохранений
		std::string mSaveFolder;

		/// Экземпляр менеджера сохранений
		static SaveManagerPtr mInstance;

		/// Массив сохранений
		std::vector<SaveDataPtr> mSaves;

		/// Файл автосохранения
		SaveDataPtr mAutoSave;

		/// Файл быстрого сохранения
		SaveDataPtr mQuickSave;
	};
};

#endif