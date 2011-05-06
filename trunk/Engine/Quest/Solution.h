#ifndef ISILME_STORY_SOLUTION_H
#define ISILME_STORY_SOLUTION_H

#include "Quests.h"

namespace story
{
	/// @class Solution
	/// Решение квеста
	class IsilmeExport Solution
	{
	public:
		Solution();
		virtual ~Solution();

		/// Проверяет условие завершения квеста
		bool	OnCheckCondition();

		/// Вызывается при срабатывании квеста
		void	OnTriggered();

		/// Устанавливает сценарий проверки решения квеста
		void	SetConditionScript(std::string script);

		/// Устанавливает сценарий выполнения при спешной проверке решения
		void	SetTriggeredScript(std::string script);
	private:
		luabind::object mTriggeredScript;
		luabind::object mConditionScript;
	};
};

#endif