#ifndef ISILME_QUESTS_STORY_H
#define ISILME_QUESTS_STORY_H

#include "Definitions.h"
#include "Quests.h"

namespace story
{
	class Story
	{
	public:
		Story();
		virtual ~Story();

		
		/// Обновить историю
		void			Update(float elapsedTime);

		/// Загрузить историю
		void			Load(std::string fileName);
	};
};

#endif