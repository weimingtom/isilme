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
#include "Conversation.h"
#include "Phrase.h"
#include "Core/MasterFile.h"
#include "Core/FactoryManager.h"
#include "Speaker.h"

namespace story
{
	Conversation::Conversation(std::string id)
	{
		mID = id;
	}

	Conversation::~Conversation()
	{
	}

	void Conversation::AddPhrase(PhrasePtr phrase)
	{
		mPhrases.push_back(phrase);
	}

	int Conversation::GetPhrasesCount()
	{
		return mPhrases.size();
	}

	PhrasePtr Conversation::GetPhrase(int index)
	{
		return mPhrases.at(index);
	}

	std::string Conversation::GetID()
	{
		return mID;
	}

	PhrasePtr Conversation::AutoChoosePhrase(SpeakerPtr speaker)
	{
		for (int i = 0; i < GetPhrasesCount(); ++i)
		{
			PhrasePtr p = GetPhrase(i);
			if (p->CheckCondition(speaker))
				return p;
		}

		return PhrasePtr();
	}

	story::ConversationPtr Conversation::Get( std::string id ) 
	{
		CategoryPtr ctg = FactoryManager::GetSingleton()->GetMasterFile()->GetCategory("Conversations");
		if (ctg)
		{
			for (int i = 0; i < ctg->GetSize(); ++i)
			{
				EntryPtr entry = ctg->GetEntry(i);
				boost::shared_ptr<ConversationEntry> ce = boost::shared_dynamic_cast<ConversationEntry>(entry);
				if (ce)
				{
					if (ce->data->GetID() == id)
						return ce->data;
				}
			}
		}
		return ConversationPtr();
	}

	void Conversation::SetID( std::string id )
	{
		mID = id;
	}

}