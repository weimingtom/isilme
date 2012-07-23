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
#ifndef ISILME_STORY_QUESTS_H
#define ISILME_STORY_QUESTS_H

#include "../Definitions.h"

namespace story
{
	class ISpeaker;
	typedef boost::shared_ptr<ISpeaker>		SpeakerPtr;
	typedef boost::weak_ptr<ISpeaker> SpeakerWPtr;

	class Quest;
	typedef boost::shared_ptr<Quest>		QuestPtr;
	typedef	boost::weak_ptr<Quest>			QuestWPtr;
	typedef std::map<std::string, QuestPtr>	QuestMap;
	typedef std::set<QuestPtr>				QuestSet;
	typedef std::list<QuestPtr>				QuestList;

	class Stage;
	typedef boost::shared_ptr<Stage>		StagePtr;
	typedef boost::weak_ptr<Stage>			StageWPtr;
	typedef std::map<int, StagePtr>			StageMap;

	class Story;
	typedef boost::shared_ptr<Story> StoryPtr;
	typedef boost::weak_ptr<Story> StoryWPtr;


	class Conversation;
	typedef boost::shared_ptr<Conversation> ConversationPtr;
	typedef boost::weak_ptr<Conversation> ConversationWPtr;

	class Phrase;
	typedef boost::shared_ptr<Phrase> PhrasePtr;
	typedef boost::weak_ptr<Phrase> PhraseWPtr;
}

#endif