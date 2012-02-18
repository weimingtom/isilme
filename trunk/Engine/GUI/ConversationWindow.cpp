#include "IsilmePCH.h"
#include "ConversationWindow.h"
#include "Engine/Quest/Conversation.h"
#include "Engine/Quest/Phrase.h"
#include "Entity.h"

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


		mAnswers.clear();

		int pos = 0;
		for (int i = 0; i < phrase->GetAnswersCount(); ++i)
			if (phrase->GetAnswer(i)->CheckCondition(mSpeaker))
			{
				pos++;
				ButtonPtr button(new Button());
				button->SetCaption(phrase->GetAnswer(i)->GetText());
				button->AdjustSize();
				Add(button, 0, 100 * pos);
				mAnswers[button] = phrase->GetAnswer(i);
			}
	}

	void ConversationWindow::Init()
	{
		mText = TextBoxPtr(new TextBox());
		mText->SetSize(500, 100);

		Add(mText, 0, 0);
		SetSize(600, 400);

		setCaption("Quests");
	}

};