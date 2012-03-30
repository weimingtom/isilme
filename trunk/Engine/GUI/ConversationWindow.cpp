#include "IsilmePCH.h"
#include "ConversationWindow.h"
#include "Engine/Story/Conversation.h"
#include "Engine/Story/Phrase.h"
#include "Core/Entity.h"

namespace gcn
{
	ConversationWindow::ConversationWindow()
	{
	}

	ConversationWindow::~ConversationWindow()
	{
	}

	void ConversationWindow::mouseClicked(MouseEvent& evt)
	{
		ButtonPtr b = boost::shared_dynamic_cast<gcn::Button>( evt.GetSource());
		if (b)
		{
			story::PhrasePtr answer = mAnswers[b];
			answer->RunAction(mSpeaker);
			SetCurrentPhrase(answer->AutoChooseAnswer(mSpeaker));
		}
	}

	void ConversationWindow::SetConversation(story::ConversationPtr conversation, EntityPtr speaker)
	{
		mSpeaker = speaker;
		mConversation = conversation;

		SetCurrentPhrase(mConversation->AutoChoosePhrase(mSpeaker));
	}

	void ConversationWindow::SetCurrentPhrase(story::PhrasePtr phrase)
	{
		for (std::map<ButtonPtr, story::PhrasePtr>::iterator it = mAnswers.begin(); it != mAnswers.end(); ++it)
		{
			Remove(it->first);
		}

		if (phrase == 0)
		{
			Close();
			return;
		}
		
		phrase->RunAction(mSpeaker);
		mCurrentPhrase = phrase;
		mText->setText(phrase->GetText());
		//mText->adjustSize();

		mAnswers.clear();
		int max = mText->GetWidth();
		int pos = mText->GetHeight() + 5;
		for (int i = 0; i < phrase->GetAnswersCount(); ++i)
			if (phrase->GetAnswer(i)->CheckCondition(mSpeaker))
			{
				ButtonPtr button(new Button());
				button->SetCaption(phrase->GetAnswer(i)->GetText());
				button->AdjustSize();
				Add(button, 5, pos);
				mAnswers[button] = phrase->GetAnswer(i);
				pos += button->GetHeight() + 5;
				if (button->GetWidth() > max)
					max = button->GetWidth();
			}
		SetSize(max + 15, pos + 20);
		SetPosition((GetParent()->GetWidth() - GetWidth()) / 2, GetParent()->GetHeight() - GetHeight() - 5 );
	}

	void ConversationWindow::Init()
	{
		mText = TextBoxPtr(new TextBox());
		mText->SetSize(500, 100);

		Add(mText, 0, 0);
		SetSize(800, 600);
		mText->setBackgroundColor(Color(0, 0, 0, 0));

		setCaption("Quests");
	}

};