#ifndef ISILME_QUESTS_CONVERSATION_H
#define ISILME_QUESTS_CONVERSATION_H

#include "Quests.h"
#include "Definitions.h"

namespace story
{
	/// Класс описывает диалог
	class IsilmeExport Conversation
	{
	public:
		Conversation();
		virtual ~Conversation();

		/// Загружает диалог ил XML-элемента
		static ConversationPtr Load(TiXmlElement* convElement);

		/// Возвращает идентификатор диалога
		std::string GetID();

		/// Добавляет фразу в диалог
		void AddPhrase(PhrasePtr phrase);

		/// Возвращает количество фраз
		int GetPhrasesCount();

		/// Возвращает фразц по индексу
		PhrasePtr GetPhrase(int index);

		/// Возвращает фразу, первую в диалоге
		PhrasePtr AutoChoosePhrase(EntityPtr speaker);
	private:
		std::string mID;
		std::vector<PhrasePtr> mPhrases;
	};
};

#endif