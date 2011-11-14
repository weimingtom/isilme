#include "Isilme.h"
#include "ConversationWindow.h"
#include "Engine/Quest/Conversation.h"
#include "Engine/Quest/Phrase.h"
#include "Entity.h"

namespace gcn
{
	ConversationWindow::ConversationWindow()
	{
		mText = new TextBox();
		mText->setSize(500, 100);

		add(mText, 0, 0);
		setSize(600, 400);

		setCaption("Quests");
	}

	ConversationWindow::~ConversationWindow()
	{
	}

	void ConversationWindow::mouseClicked(MouseEvent& evt)
	{
		Button* b = dynamic_cast<gcn::Button*>( evt.getSource());
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
		for (std::map<Button*, story::PhrasePtr>::iterator it = mAnswers.begin(); it != mAnswers.end(); ++it)
		{
			remove(it->first);
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
				Button* button = new Button();
				button->setCaption(phrase->GetAnswer(i)->GetText());
				button->adjustSize();
				add(button, 0, 100 * pos);
				mAnswers[button] = phrase->GetAnswer(i);
			}
	}
};