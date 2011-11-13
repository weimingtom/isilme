#include "Isilme.h"
#include "Phrase.h"

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

	void Phrase::RunAction()
	{
	}

	bool Phrase::CheckCondition()
	{
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

	PhrasePtr Phrase::AutoChooseAnswer()
	{
		for (int i = 0; i < GetAnswersCount(); ++i)
		{
			PhrasePtr p = GetAnswer(i);
			if (p->CheckCondition())
				return p;
		}

		return PhrasePtr();
	}
};