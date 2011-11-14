#ifndef ISILME_QUESTS_CONVERSATION_H
#define ISILME_QUESTS_CONVERSATION_H

#include "Quests.h"
#include "Definitions.h"

namespace story
{
	/// ����� ��������� ������
	class IsilmeExport Conversation
	{
	public:
		Conversation();
		virtual ~Conversation();

		/// ��������� ������ �� XML-��������
		static ConversationPtr Load(TiXmlElement* convElement);

		/// ���������� ������������� �������
		std::string GetID();

		/// ��������� ����� � ������
		void AddPhrase(PhrasePtr phrase);

		/// ���������� ���������� ����
		int GetPhrasesCount();

		/// ���������� ����� �� �������
		PhrasePtr GetPhrase(int index);

		/// ���������� �����, ������ � �������
		PhrasePtr AutoChoosePhrase(EntityPtr speaker);
	private:
		std::string mID;
		std::vector<PhrasePtr> mPhrases;
	};
};

#endif