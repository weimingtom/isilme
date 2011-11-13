#include "Isilme.h"
#include "ConversationWindow.h"
#include "Engine/Quest/Conversation.h"
#include "Engine/Quest/Phrase.h"

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
			SetCurrentPhrase(answer->AutoChooseAnswer());
		}
	}

	void ConversationWindow::SetConversation(story::ConversationPtr conversation)
	{
		mConversation = conversation;

		SetCurrentPhrase(mConversation->AutoChoosePhrase());
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

		mCurrentPhrase = phrase;
		mText->setText(phrase->GetText());


		mAnswers.clear();

		for (int i = 0; i < phrase->GetAnswersCount(); ++i)
		{
			Button* button = new Button();
			button->setCaption(phrase->GetAnswer(i)->GetText());
			button->adjustSize();
			add(button, 0, 100 * (i+1));
			mAnswers[button] = phrase->GetAnswer(i);
		}
	}
};