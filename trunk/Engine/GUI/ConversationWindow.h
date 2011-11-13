#ifndef GCN_CONVERSATION_WINDOW_H
#define GCN_CONVERSATION_WINDOW_H

#include "Definitions.h"
#include "Engine/Quest/Quests.h"
#include "ModalDialog.h"

namespace gcn
{
	class IsilmeExport ConversationWindow : public ModalDialog
	{
	public:
		ConversationWindow();
		virtual ~ConversationWindow();

		virtual void mouseClicked(gcn::MouseEvent& evt);

		/// Устанвоить диалог
		void SetConversation(story::ConversationPtr conversation);

		void SetCurrentPhrase(story::PhrasePtr phrase);
	private:
		TextBox* mText;
		story::ConversationPtr mConversation;
		story::PhrasePtr mCurrentPhrase;
		std::map<gcn::Button*, story::PhrasePtr> mAnswers;
	};
};

#endif