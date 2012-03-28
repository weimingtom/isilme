#include "IsilmePCH.h"
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

	void Phrase::RunAction(EntityPtr speaker)
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

	bool Phrase::CheckCondition(EntityPtr speaker)
	{
		if (mReference)
			return mReference->CheckCondition(speaker);

		// Проверяем скрипт-условие
		if (mCondition)
		{
			return luabind::call_function<bool>(mCondition, speaker);
		}

		if (mChance != 100)
		{
			int val = rand() % 100;
			return val >= mChance;
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

	PhrasePtr Phrase::AutoChooseAnswer(EntityPtr speaker)
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

};