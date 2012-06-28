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
#ifndef ISILME_STORY_STAGE_H
#define ISILME_STORY_STAGE_H

#include "Quests.h"
#include "../Core/Script.h"

namespace story
{
	class ISILME_API Stage
	{
		friend class Quest;
		friend class Story;
	public:
		/// Загружает стадию квеста из XML-файла
		static StagePtr	Load(TiXmlElement* element);
		Stage();
		virtual ~Stage();

		/// Возвращает ID стадии
		int	GetID();

		/// Возвращает текст стадии
		std::string GetText() const;

		void	SetText(std::string text);

		/// Gets if stage will finish the quest
		bool IsFinishQuest() const;

		/// Sets if stage will finish the quest
		void SetFinishQuest(bool value);

		void	OnStart();
		void	OnUpdate(float elapsedTime);

		QuestPtr	GetQuest();

		// Gets script for OnStart event
		ScriptPtr	GetStartScript();

		/// Gets script for OnUpdate event
		ScriptPtr	GetUpdateScript();

		void SetID( int value );
	private:
		int mID;
		std::string mText;
		::Script mStartScript;
		::Script mUpdateScript;
		QuestWPtr	mQuest;
		bool	isFinish;
	};
};
#endif