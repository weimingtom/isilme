#ifndef ISILME_QUESTS_CONVERSATION_H
#define ISILME_QUESTS_CONVERSATION_H

#include "Quests.h"

namespace story
{
	/// ����� ��������� ������
	class ISILME_API Conversation
	{
	public:
		Conversation(std::string id);
		virtual ~Conversation();
		
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