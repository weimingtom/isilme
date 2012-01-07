#ifndef ISILME_GCN_QUESTBOOK_H
#define ISILME_GCN_QUESTBOOK_H

#include <guichan.hpp>
#include <map>
#include "Engine/Quest/Quests.h"

namespace gcn
{
	class ISILME_API QuestBook : public Window
	{
	public:
		QuestBook();
		virtual ~QuestBook();

		void	UpdateQuests(story::StoryPtr story);
	protected:
		virtual void mouseClicked(gcn::MouseEvent& evt);
	private:
		Container* mActiveList;
		Container* mFinishedList;
		ScrollArea* mActiveTab;
		ScrollArea* mFinishedTab;
		TextBox* mText;
		std::map<Widget*, story::QuestPtr> mQuests;
	};
};

#endif