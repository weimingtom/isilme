#include "Isilme.h"
#include "Phrase.h"
#include "Entity.h"

namespace story
{
	Phrase::Phrase()
	{
	}

	Phrase::~Phrase()
	{
	}

	int Phrase::GetAnswersCount()
	{
		return mChildren.size();
	}

	PhrasePtr Phrase::GetAnswer(int index)
	{
		return mChildren.at(index);
	}

	void Phrase::RunAction(EntityPtr speaker)
	{
		if (mAction)
		{
			mAction(speaker);
		}
	}

	bool Phrase::CheckCondition(EntityPtr speaker)
	{
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

	PhrasePtr Phrase::Load(TiXmlElement* phraseElement)
	{
		PhrasePtr phrase(new Phrase());

		// Читаем текст
		TiXmlElement* textElement = phraseElement->FirstChildElement("Text");
		if (textElement)
		{
			const char* text = textElement->GetText();
			phrase->SetText(text ? text : "");
		}

		// Читаем вероятность фразы
		phrase->mChance = 100;
		phraseElement->QueryIntAttribute("Chance", &(phrase->mChance));

		// Читаем скрипты
		const char* conditionAttr = phraseElement->Attribute("Condition");
		if (conditionAttr)
		{
			phrase->mCondition = ScriptAPI::MakeFunction("speaker", conditionAttr);
		}

		const char* actionAttr = phraseElement->Attribute("Action");
		if (actionAttr)
		{
			phrase->mAction = ScriptAPI::MakeFunction("Speaker", actionAttr);
		}

		// Читаем ответы
		TiXmlElement* answersElement = phraseElement->FirstChildElement("Answers");
		if (answersElement)
		{
			TiXmlElement* childElement = answersElement->FirstChildElement("Phrase");
			while (childElement)
			{
				PhrasePtr child = Phrase::Load(childElement);
				phrase->AddAnswer(child);
				childElement = childElement->NextSiblingElement("Phrase");
			}
		}
		return phrase;
	}

	PhrasePtr Phrase::AutoChooseAnswer(EntityPtr speaker)
	{
		for (int i = 0; i < GetAnswersCount(); ++i)
		{
			PhrasePtr p = GetAnswer(i);
			if (p->CheckCondition(speaker))
				return p;
		}

		return PhrasePtr();
	}
};