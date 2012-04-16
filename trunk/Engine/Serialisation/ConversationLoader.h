﻿//  Copyright (C) 2010-2012 VSTU
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
#ifndef ISILME_SERIALISATION_CONVERSATIONLOADER_H
#define ISILME_SERIALISATION_CONVERSATIONLOADER_H

#include "../Definitions.h"
#include "EntryLoader.h"
#include "Engine/Story/Conversation.h"
#include "Engine/Story/Phrase.h"

namespace serialisation
{
	class ISILME_API ConversationLoader : public EntryLoader
	{
	public:
		ConversationLoader();
		virtual ~ConversationLoader();

		virtual EntryPtr LoadEntry(std::string filename);
	protected:
		virtual story::ConversationPtr LoadConversation(std::string fileName);
		virtual story::ConversationPtr LoadConversation(TiXmlElement* element);
		virtual story::PhrasePtr LoadPhrase(TiXmlElement* element);

		story::PhrasePtr GetPhraseByRef(int refValue);
	private:
		typedef std::map<int, story::PhrasePtr> IDPhraseMap;
		typedef std::map<story::PhrasePtr, int> PhraseRefMap;
		IDPhraseMap mPhraseMap;
		PhraseRefMap mRefMap;
	};
}
#endif