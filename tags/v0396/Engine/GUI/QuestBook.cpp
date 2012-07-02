//  Copyright (C) 2010-2012 VSTU
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