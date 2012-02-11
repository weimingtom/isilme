#ifndef GCN_CONVERSATION_WINDOW_H
#define GCN_CONVERSATION_WINDOW_H

#include "Definitions.h"
#include "Engine/Quest/Quests.h"
#include "ModalDialog.h"

namespace gcn
{
	class ISILME_API ConversationWindow : public ModalDialog
	{
	public:
		ConversationWindow();
		virtual ~ConversationWindow();

		virtual void mouseClicked(gcn::MouseEvent& evt);

		/// Устанвоить диалог
		void SetConversation(story::ConversationPtr conversation, EntityPtr speaker);

		void SetCurrentPhrase(story::PhrasePtr phrase);
	private:
		EntityPtr mSpeaker;
		TextBoxPtr mText;
		story::ConversationPtr mConversation;
		story::PhrasePtr mCurrentPhrase;
		std::map<gcn::ButtonPtr, story::PhrasePtr> mAnswers;
	};
	typedef boost::shared_ptr<ConversationWindow> ConversationWindowPtr;
};

#endif