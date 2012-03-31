#ifndef GCN_CONVERSATION_WINDOW_H
#define GCN_CONVERSATION_WINDOW_H

#include "Definitions.h"
#include "Engine/Story/Quests.h"
#include "ModalDialog.h"

namespace gcn
{
	class ISILME_API ConversationWindow : public ModalDialog
	{
	public:
		ConversationWindow();
		virtual ~ConversationWindow();

		virtual void mouseClicked(gcn::MouseEvent& evt);

		/// Setup conversation
		///
		/// @param conversation
		/// @param player - Human player
		/// @param speaker - NPC
		void SetConversation(story::ConversationPtr conversation, story::SpeakerPtr player, story::SpeakerPtr speaker);

		void SetCurrentPhrase(story::PhrasePtr phrase);
		virtual void Init();
	private:
		story::SpeakerPtr mPlayer;
		story::SpeakerPtr mSpeaker;
		TextBoxPtr mText;
		story::ConversationPtr mConversation;
		story::PhrasePtr mCurrentPhrase;
		std::map<gcn::ButtonPtr, story::PhrasePtr> mAnswers;
	};
	typedef boost::shared_ptr<ConversationWindow> ConversationWindowPtr;
};

#endif