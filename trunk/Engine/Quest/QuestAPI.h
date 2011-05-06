#ifndef QUEST_API_H
#define QUEST_API_H

#include <LuaCPP.h>
#include "Quests.h"

namespace QuestAPI
{
	void	IsilmeExport RegisterAPI();

	bool	IsilmeExport StartQuest(std::string questName);
};

#endif