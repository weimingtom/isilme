#ifndef EDITOR_COMMAND_H
#define EDITOR_COMMAND_H

#include "EditorDefinitions.h"

namespace editor
{
	/// ��������� �������
	class Command
	{
	public:
		/// �������� ���������� �������
		virtual void Unexecute() = 0;

		/// ��������� ��������
		virtual void Execute() = 0;
	};
};

#endif