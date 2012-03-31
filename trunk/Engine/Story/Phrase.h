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