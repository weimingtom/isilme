//  Copyright (C) 2010-2012 Alexander Alimov
//
//	This file is part of Isilme SDK.
//
//		Isilme SDK is free software: you can redistribute it and/or modify
//		it under the terms of the GNU Lesser General Public License as published by
//		the Free Software Foundation, either version 3 of the License, or
//		(at your option) any later version.
//
//		Isilme SDK is distributed in the hope that it will be useful,
//		but WITHOUT ANY WARRANTY; without even the implied warranty of
//		MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//		GNU Lesser General Public License for more details.
//
//		You should have received a copy of the GNU Lesser General Public License
//		along with Isilme SDK.  If not, see <http://www.gnu.org/licenses/>.
//
//	Этот файл — часть Isilme SDK.
//
//		Isilme SDK - свободная программа: вы можете перераспространять ее и/или
//		изменять ее на условиях Меньшей стандартной общественной лицензии GNU в том виде,
//		в каком она была опубликована Фондом свободного программного обеспечения;
//		либо версии 3 лицензии, либо (по вашему выбору) любой более поздней
//		версии.
//
//		Isilme SDK распространяется в надежде, что она будет полезной,
//		но БЕЗО ВСЯКИХ ГАРАНТИЙ; даже без неявной гарантии ТОВАРНОГО ВИДА
//		или ПРИГОДНОСТИ ДЛЯ ОПРЕДЕЛЕННЫХ ЦЕЛЕЙ. Подробнее см. в Меньшей стандартной
//		общественной лицензии GNU.
//
//		Вы должны были получить копию Меньшей стандартной общественной лицензии GNU
//		вместе с этой программой. Если это не так, см.
//		<http://www.gnu.org/licenses/>.
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

	void ConversationWindow::SetConversation(story::ConversationPtr conversation, story::SpeakerPtr player, story::SpeakerPtr speaker)
	{
		mPlayer = player;
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