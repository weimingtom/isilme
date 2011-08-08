#include "Isilme.h"
#include "QuestBook.h"
#include "Engine/Quest/Quest.h"
#include "Engine/Quest/Story.h"
#include "Engine/Quest/Stage.h"
#include "Engine/Quest/Quest.h"

namespace gcn
{
	QuestBook::QuestBook()
	{
		TabbedArea* tArea = new TabbedArea();
		mActiveTab = new ScrollArea();
		mFinishedTab = new ScrollArea();
		mActiveList = new Container();
		mFinishedList = new Container();

		mText = new TextBox();

		mActiveTab->setSize(300, 400);
		mActiveTab->setContent(mActiveList);

		mFinishedTab->setSize(300, 400);
		mFinishedTab->setContent(mFinishedList);

		mText->setSize(300, 400);

		tArea->setSize(300, 400);
		tArea->addTab("Active", mActiveTab);
		tArea->addTab("Finished", mFinishedTab);

		add(tArea, 0, 0);
		add(mText, 300, 0);

		setSize(600, 400);

		setCaption("Quests");
	}

	QuestBook::~QuestBook()
	{
	}

	void	QuestBook::UpdateQuests(story::StoryPtr s)
	{
		mQuests.clear();
		int y = 0;
		for (story::QuestList::iterator it = s->GetActiveQuests()->begin(); it != s->GetActiveQuests()->end(); ++it)
		{
			gcn::Button* btn = new gcn::Button();
			btn->setCaption((*it)->GetTitle());
			btn->adjustSize();

			mActiveList->add(btn, 0, y);
			y+=btn->getHeight();

			mQuests[btn] = (*it);
		}
		mActiveList->setSize(300, y);
	}

	void	QuestBook::mouseClicked(MouseEvent& evt)
	{
		Window::mouseClicked(evt);

		Widget* w = evt.getSource();
		if (mQuests.find(w) != mQuests.end())
		{
			story::QuestPtr q = mQuests[w];
			mText->setText(q->GetText());
		}
	}
};