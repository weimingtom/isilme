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
#include "Speaker.h"
#include "Phrase.h"
#include "Core/Entity.h"
#include "ScriptAPI.h"

namespace story
{
	Phrase::Phrase()
	{
	}

	Phrase::Phrase( PhrasePtr refPhrase )
	{
		mReference = refPhrase;
	}

	Phrase::~Phrase()
	{
	}

	bool Phrase::IsReference()
	{
		return mReference != 0;
	}

	int Phrase::GetAnswersCount()
	{
		if (mReference)
			return mReference->mChildren.size();

		return mChildren.size();
	}

	PhrasePtr Phrase::GetAnswer(int index)
	{
		if (mReference)
			return mReference->mChildren.at(index);

		return mChildren.at(index);
	}

	void Phrase::RunAction(SpeakerPtr speaker)
	{
		if (mReference)
		{
			mReference->RunAction(speaker);
			return;
		}

		if (mAction)
		{
			mAction(speaker);
		}
	}

	bool Phrase::CheckCondition(SpeakerPtr speaker)
	{
		if (mReference)
			return mReference->CheckCondition(speaker);

		// Проверяем скрипт-условие
		if (mCondition)
		{
			return luabind::call_function<bool>(mCondition, speaker);
		}

		if (mChance != 100 && mChance > 0)
		{
			int val = rand() % 100;
			return val <= mChance;
		}

		return true;
	}

	std::string Phrase::GetText()
	{
		if (mReference)
			return mReference->GetText();

		return mText;
	}

	void Phrase::SetText(std::string text)
	{
		mText = text;
	}

	void Phrase::AddAnswer(PhrasePtr phrase)
	{
		mChildren.push_back(phrase);
	}

	PhrasePtr Phrase::AutoChooseAnswer(SpeakerPtr speaker)
	{
		if (mReference)
		{
			return mReference->AutoChooseAnswer(speaker);
		}

		for (int i = 0; i < GetAnswersCount(); ++i)
		{
			PhrasePtr p = GetAnswer(i);
			if (p->CheckCondition(speaker))
				return p;
		}

		return PhrasePtr();
	}

	void Phrase::SetCondition( std::string attrCondition )
	{
		mConditionSource = attrCondition;
		if (mConditionSource != "")
			mCondition = ScriptAPI::MakeFunction("", attrCondition);
		else
			mCondition = luabind::object();
	}

	void Phrase::SetAction( std::string atttrAction )
	{
		mActionSource = atttrAction;
		mAction = ScriptAPI::MakeFunction("", atttrAction);
	}

	void Phrase::SetChance( int attrChance )
	{
		mChance = attrChance;
	}

	std::string Phrase::GetConditionSource()
	{
		if (mReference)
			return mReference->mConditionSource;

		return mConditionSource;
	}

	std::string Phrase::GetActionSource()
	{
		if (mReference)
			return mReference->mActionSource;

		return mActionSource;
	}

	int Phrase::GetChance()
	{
		if (mReference)
			return mChance;
		return mChance;
	}

	void Phrase::RemoveAnswer( PhrasePtr phrase )
	{
		PhraseVector::iterator it = std::find(mChildren.begin(), mChildren.end(), phrase);
		if (it != mChildren.end())
			mChildren.erase(it);
	}

	void Phrase::SetReference( PhrasePtr phrase )
	{
		mReference = phrase;
	}

	story::PhrasePtr Phrase::GetReference() const
	{
		return mReference;
	}

};