#ifndef ISILME_STORY_SPEAKER_H
#define ISILME_STORY_SPEAKER_H

#include "ISpeaker.h"

namespace story
{
	/// @class Speaker
	/// Simple speaker implementation
	/// You can use multiple inheritance (Behaviour + Speaker)
	class ISILME_API Speaker : public ISpeaker
	{
	public:
		Speaker();
		virtual ~Speaker();

		/// Sets conversation for speaker
		virtual void SetConversation(ConversationPtr conversation);

		/// Gets conversation for speaker
		virtual ConversationPtr GetConversation() const;
	private:
		ConversationPtr mConversation;
	};
}

#endif