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
#ifndef ISILME_STORY_QUEST_H
#define ISILME_STORY_QUEST_H

#include "Quests.h"
#include <string>
#include "../Core/Script.h"

namespace story
{
	class ISILME_API Quest : public boost::enable_shared_from_this<Quest>
	{
		friend class Story;
	public:
		static QuestPtr Load(TiXmlElement* element);
		Quest();
		virtual ~Quest();

		/// Возвращает имя квеста
		std::string		GetName();
		void			SetName(std::string name);

		/// Возвращает заголовок квеста
		std::string		GetTitle();
		void			SetTitle(std::string title);

		/// Возвращает стадию квеста
		int				GetStage();
		StagePtr		GetStage(int stage);
		void			SetStage(int stage);

		std::string		GetText();

		std::string		GetDescription();
		void			SetDescription(std::string description);

		void			OnUpdate(float elapsedTime);

		bool			IsActive();

		bool			IsFinished();

		/// Выполняется в начале квеста
		void			OnStart();
		void			OnFinished();

		int				GetStageCount() const;
		StagePtr		GetStageAtIndex(int index) const;

		void			AddStage(StagePtr stage);

		void			RemoveStage(StagePtr stage);

		/// Gets script for start event
		ScriptPtr		GetStartScript();

		/// Gets script for finish event
		ScriptPtr		GetFinishScript();
	protected:
		StoryWPtr	mStory;
		std::string mName;
		std::string mTitle;
		std::string mDescription;
		std::string mText;
		bool	isActive;
		bool	isFinished;

		Script		mStartScript;
		Script		mFinishScript;
		StageMap		mStages;
		StagePtr		mCurrentStage;
		
	};
};

#endif