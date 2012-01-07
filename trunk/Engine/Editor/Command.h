#ifndef EDITOR_COMMAND_H
#define EDITOR_COMMAND_H

#include "EditorDefinitions.h"

namespace editor
{
	/// @class	Command
	///
	/// @brief	��������� �������
	///
	/// @author	Velorth
	/// @date	17.11.2011
	class ISILME_API Command
	{
	public:

		/// @fn	virtual void Command::Unexecute() = 0;
		///
		/// @brief	�������� ���������� �������
		///
		/// @author	Velorth
		/// @date	17.11.2011
		virtual void Unexecute() = 0;

		/// @fn	virtual void Command::Execute() = 0;
		///
		/// @brief	��������� ��������
		///
		/// @author	Velorth
		/// @date	17.11.2011
		virtual void Execute() = 0;
	};
};

#endif