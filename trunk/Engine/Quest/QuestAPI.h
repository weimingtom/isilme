#ifndef QUEST_API_H
#define QUEST_API_H

#include <LuaCPP.h>
#include "Quests.h"

namespace QuestAPI
{
	void	ISILME_API RegisterAPI();

	bool	ISILME_API StartQuest(std::string questName);
};

#endif