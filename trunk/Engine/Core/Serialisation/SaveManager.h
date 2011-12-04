#ifndef ISILME_SERIALISATION_SAVEMANAGER_H
#define ISILME_SERIALISATION_SAVEMANAGER_H

#include "Definitions.h"

namespace serialisation
{
	class IsilmeExport SaveManager
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
		///< Путь к файлам сохранений
		std::string mSaveFolder;

		///< Экземпляр менеджера сохранений
		static SaveManagerPtr mInstance;

		///< Массив сохранений
		std::vector<SaveDataPtr> mSaves;

		///< Файл автосохранения
		SaveDataPtr mAutoSave;

		///< Файл быстрого сохранения
		SaveDataPtr mQuickSave;
	};
};

#endif