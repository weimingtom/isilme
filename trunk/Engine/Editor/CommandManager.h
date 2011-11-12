#ifndef EDITOR_COMMAND_MANAGER_H
#define EDITOR_COMMAND_MANAGER_H

#include "EditorDefinitions.h"

namespace editor
{
	/// �������� ������
	class IsilmeExport CommandManager
	{
	public:
		CommandManager();
		virtual ~CommandManager();

		/// �������� ��������� �������
		void Undo();

		/// ������� ��������� �������
		void Redo();

		/// ���������, ����� �� �������� �������
		bool IsUndoPossible();

		/// ��������� ����� �� ������� �������
		bool IsRedoPossible();

		/// ��������� �������
		void Execute(CommandPtr command);
	protected:
	private:
		CommandStack mCommands;
		CommandStack mUndoneCommands;
	};
};

#endif