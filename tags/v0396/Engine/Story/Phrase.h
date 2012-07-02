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
#ifndef ISILME_STORY_PHRASE_H
#define ISILME_STORY_PHRASE_H

#include "Quests.h"

namespace story
{
	class ISILME_API Phrase
	{
	public:
		Phrase(PhrasePtr refPhrase);
		Phrase();
		virtual ~Phrase();

		/// Проверяет, выполняется ли условие фразы
		bool CheckCondition(SpeakerPtr speaker);

		/// Возвращает текст фразы
		std::string GetText();

		/// Возвращает количество ответов
		int	GetAnswersCount();

		/// Возвращает ответ по идексу
		PhrasePtr GetAnswer(int index);

		/// Запускае сценарий действия
		void RunAction(SpeakerPtr speaker);

		/// Добавить ответ
		void AddAnswer(PhrasePtr phrase);

		/// Removes answer phrase
		void RemoveAnswer(PhrasePtr phrase);

		/// Установить текст
		void SetText(std::string text);

		/// Выбрать ответ
		PhrasePtr AutoChooseAnswer(SpeakerPtr speaker);

		void SetCondition( std::string attrCondition );

		std::string GetConditionSource();
		
		std::string GetActionSource();

		void SetAction( std::string atttrAction );
		
		void SetChance( int attrChance );

		int GetChance();

		bool IsReference();

		/// Makes phrase as reference
		void SetReference(PhrasePtr phrase);

		/// Gets referenced phrase
		PhrasePtr GetReference() const;
	private:
		PhrasePtr mReference;

		/// Текст сценария-условия
		std::string mConditionSource;

		/// Текст сценария-действия
		std::string mActionSource;

		/// Текст фразы
		std::string mText;

		/// Условие фразы
		luabind::object mCondition;

		/// Действие фразы
		luabind::object mAction;

		/// Дочерние фразы
		typedef std::vector<PhrasePtr> PhraseVector;
		PhraseVector mChildren;

		/// Вероятность появления фразы от 0 до 100
		int mChance;
	};
};

#endif 