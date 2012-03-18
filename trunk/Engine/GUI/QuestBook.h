#ifndef ISILME_GCN_QUESTBOOK_H
#define ISILME_GCN_QUESTBOOK_H

#include <guichan.hpp>
#include <map>
#include "Engine/Story/Quests.h"

namespace gcn
{
	class ISILME_API QuestBook : public Window
	{
	public:
		QuestBook();
		virtual ~QuestBook();

		void	UpdateQuests(story::StoryPtr story);

		virtual void Initialise();
	protected:
		virtual void mouseClicked(gcn::MouseEvent& evt);
	private:
		ContainerPtr mActiveList;
		ContainerPtr mFinishedList;
		ScrollAreaPtr mActiveTab;
		ScrollAreaPtr mFinishedTab;
		TextBoxPtr mText;
		std::map<WidgetPtr, story::QuestPtr> mQuests;
	};

	typedef boost::shared_ptr<QuestBook> QuestBookPtr;
};

#endif