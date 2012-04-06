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
#include "ConversationSerialiser.h"

namespace serialisation
{
	XMLConversationSerialiser::XMLConversationSerialiser()
	{

	}

	XMLConversationSerialiser::~XMLConversationSerialiser()
	{

	}

	void XMLConversationSerialiser::Serilise( story::ConversationPtr conversation, std::string fileName )
	{
		TiXmlDocument document(fileName.c_str());
		TiXmlElement convElement("Conversation");

		SerialiseConversation(conversation, &convElement);
		document.InsertEndChild(convElement);

		document.SaveFile();
	}

	void XMLConversationSerialiser::SerialiseConversation( story::ConversationPtr conversation, TiXmlElement* element )
	{
		element->SetAttribute("ID", conversation->GetID().c_str());

		for (int i = 0; i < conversation->GetPhrasesCount(); ++i)
		{
			story::PhrasePtr phrase = conversation->GetPhrase(i);
			TiXmlElement phraseElement("Phrase");

			SerialisePhrase(phrase, &phraseElement);
			element->InsertEndChild(phraseElement);
		}
	}

	void XMLConversationSerialiser::SerialisePhrase( story::PhrasePtr phrase, TiXmlElement* element )
	{
		if (phrase->IsReference())
		{
			element->SetAttribute("Ref", (int)(phrase->GetReference().get()));
			return;
		}

		element->SetAttribute("ID", (int)(phrase.get()));

		element->SetAttribute("Text", phrase->GetText().c_str());
		element->SetAttribute("Action", phrase->GetActionSource().c_str());
		element->SetAttribute("Condition", phrase->GetConditionSource().c_str());
		element->SetAttribute("Chance", phrase->GetChance());
		for (int i = 0; i < phrase->GetAnswersCount(); ++i)
		{
			story::PhrasePtr answer = phrase->GetAnswer(i);
			TiXmlElement phraseElement("Phrase");

			SerialisePhrase(answer, &phraseElement);
			element->InsertEndChild(phraseElement);
		}
	}

}