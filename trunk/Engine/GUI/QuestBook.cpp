#include "IsilmePCH.h"
#include "QuestBook.h"
#include "Engine/Story/Quest.h"
#include "Engine/Story/Story.h"
#include "Engine/Story/Stage.h"
#include "Engine/Story/Quest.h"

namespace gcn
{
	QuestBook::QuestBook()
	{
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
			gcn::ButtonPtr btn(new gcn::Button());
			btn->SetCaption((*it)->GetTitle());
			btn->AdjustSize();

			mActiveList->Add(btn, 0, y);
			y+=btn->GetHeight();

			mQuests[btn] = (*it);
		}
		mActiveList->SetSize(300, y);
	}

	void	QuestBook::mouseClicked(MouseEvent& evt)
	{
		Window::mouseClicked(evt);

		WidgetPtr w = evt.GetSource();
		if (mQuests.find(w) != mQuests.end())
		{
			story::QuestPtr q = mQuests[w];
			mText->setText(q->GetText());
		}
	}

	void QuestBook::Initialise()
	{
		TabbedAreaPtr tArea = TabbedAreaPtr(new TabbedArea());
		tArea->Initialise();
		mActiveTab = ScrollAreaPtr(new ScrollArea());
		mFinishedTab = ScrollAreaPtr(new ScrollArea());
		mActiveList = ContainerPtr(new Container());
		mFinishedList = ContainerPtr(new Container());

		mText = TextBoxPtr(new TextBox());

		mActiveTab->SetSize(300, 400);
		mActiveTab->SetContent(mActiveList);

		mFinishedTab->SetSize(300, 400);
		mFinishedTab->SetContent(mFinishedList);

		mText->SetSize(300, 400);

		tArea->SetSize(300, 400);
		tArea->AddTab("Active", mActiveTab);
		tArea->AddTab("Finished", mFinishedTab);

		Add(tArea, 0, 0);
		Add(mText, 300, 0);

		SetSize(600, 400);

		setCaption("Quests");
	}

};