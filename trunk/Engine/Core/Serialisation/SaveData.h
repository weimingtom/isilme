#ifndef ISILME_SERIALISATION_SAVEDATA_H
#define ISILME_SERIALISATION_SAVEDATA_H

#include "Definitions.h"
#include <time.h>

namespace serialisation
{
	class ISILME_API SaveData
	{
	public:
		SaveData();
		virtual ~SaveData();

		/// Возвращает время, когда было сделано сохранение
		///
		/// @return	The time.
		time_t GetTime();

		/// Gets the name.
		///
		/// @return	The name.
		std::string GetName();

		/// Устанавливает имя сохранения
		///
		/// @param	value	The value.
		void SetName(std::string value);

		/// Возвращает абсолютный путь к файлу сохранения
		///
		/// @return	The full path.
		std::string GetFullPath();
	private:
		///< Время сохранения
		time_t mTime;
		///< Имя сохранения
		std::string mName;
	};
};
#endif