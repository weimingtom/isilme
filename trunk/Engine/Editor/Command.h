#ifndef EDITOR_COMMAND_H
#define EDITOR_COMMAND_H

#include "EditorDefinitions.h"

namespace editor
{
	/// Интерфейс команды
	class IsilmeExport Command
	{
	public:
		/// Отменяет выполнение команды
		virtual void Unexecute() = 0;

		/// Выполняет комманду
		virtual void Execute() = 0;
	};
};

#endif