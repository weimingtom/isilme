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

		
		/// �������� �������
		void			Update(float elapsedTime);

		/// ��������� �������
		void			Load(std::string fileName);
	};
};

#endif