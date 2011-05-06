#ifndef ISILME_STORY_SOLUTION_H
#define ISILME_STORY_SOLUTION_H

#include "Quests.h"

namespace story
{
	/// @class Solution
	/// ������� ������
	class IsilmeExport Solution
	{
	public:
		Solution();
		virtual ~Solution();

		/// ��������� ������� ���������� ������
		bool	OnCheckCondition();

		/// ���������� ��� ������������ ������
		void	OnTriggered();

		/// ������������� �������� �������� ������� ������
		void	SetConditionScript(std::string script);

		/// ������������� �������� ���������� ��� ������� �������� �������
		void	SetTriggeredScript(std::string script);
	private:
		luabind::object mTriggeredScript;
		luabind::object mConditionScript;
	};
};

#endif