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

		/// ���������, ����������� �� ������� �����
		bool CheckCondition();

		/// ���������� ����� �����
		std::string GetText();

		/// ���������� ���������� �������
		int	GetAnswersCount();

		/// ���������� ����� �� ������
		PhrasePtr GetAnswer(int index);

		/// �������� �������� ��������
		void RunAction();

		/// �������� �����
		void AddAnswer(PhrasePtr phrase);

		/// ���������� �����
		void SetText(std::string text);

		/// ��������� ����� �� XML
		static PhrasePtr Load(TiXmlElement* phraseElement);

		/// ������� �����
		PhrasePtr AutoChooseAnswer();
	private:
		std::string mText;

		/// ������� �����
		luabind::object mCondition;

		/// �������� �����
		luabind::object mAction;

		/// �������� �����
		std::vector<PhrasePtr> mChildren;
	};
};

#endif 