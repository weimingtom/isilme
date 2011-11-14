#ifndef ISILME_STORY_PHRASE_H
#define ISILME_STORY_PHRASE_H

#include "Quests.h"
#include "Definitions.h"

namespace story
{
	class IsilmeExport Phrase
	{
	public:
		Phrase();
		virtual ~Phrase();

		/// Проверяет, выполняется ли условие фразы
		bool CheckCondition(EntityPtr speaker);

		/// Возвращает текст фразы
		std::string GetText();

		/// Возвращает количество ответов
		int	GetAnswersCount();

		/// Возвращает ответ по идексу
		PhrasePtr GetAnswer(int index);

		/// Запускае сценарий действия
		void RunAction(EntityPtr speaker);

		/// Добавить ответ
		void AddAnswer(PhrasePtr phrase);

		/// Установить текст
		void SetText(std::string text);

		/// Загружает фразу из XML
		static PhrasePtr Load(TiXmlElement* phraseElement);

		/// Выбрать ответ
		PhrasePtr AutoChooseAnswer(EntityPtr speaker);
	private:
		std::string mText;

		/// Условие фразы
		luabind::object mCondition;

		/// Действие фразы
		luabind::object mAction;

		/// Дочерние фразы
		std::vector<PhrasePtr> mChildren;

		/// Вероятность появления фразы от 0 до 100
		int mChance;
	};
};

#endif 