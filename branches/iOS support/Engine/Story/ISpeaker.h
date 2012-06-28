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
#ifndef ISILME_STORY_ISPEAKER_H
#define ISILME_STORY_ISPEAKER_H

#include "Quests.h"

namespace story
{
	/// @interface ISpeaker
	/// Interface for speakers
	class ISILME_API ISpeaker
	{
	public:
		virtual ~ISpeaker() {};

		/// Sets conversation for speaker
		virtual void SetConversation(ConversationPtr conversation) = 0;

		/// Gets conversation for speaker
		virtual ConversationPtr GetConversation() const = 0;

		/// Callback for starting conversation
		virtual void OnConversationStart(SpeakerPtr other) = 0;

		/// Callback for ending conversation
		virtual void OnConversationEnd(SpeakerPtr other) = 0;

		/// Initiate conversation with other speaker
		virtual void StartConversationWith(SpeakerPtr other) = 0;

		/// Say phrase
		//virtual void OnSay(PhrasePtr phrase) = 0;
	};
}
#endif