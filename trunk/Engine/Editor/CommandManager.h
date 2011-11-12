#ifndef EDITOR_COMMAND_MANAGER_H
#define EDITOR_COMMAND_MANAGER_H

#include "EditorDefinitions.h"

namespace editor
{
	/// Менеджер команд
	class IsilmeExport CommandManager
	{
	public:
		CommandManager();
		virtual ~CommandManager();

		/// Отменить последнюю команду
		void Undo();

		/// Вернуть последнюю команду
		void Redo();

		/// Проверяет, можно ли отменить команду
		bool IsUndoPossible();

		/// Проверяет можно ли вернуть команду
		bool IsRedoPossible();

		/// Выполнить команду
		void Execute(CommandPtr command);
	protected:
	private:
		CommandStack mCommands;
		CommandStack mUndoneCommands;
	};
};

#endif