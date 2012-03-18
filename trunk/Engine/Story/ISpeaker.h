#ifndef ISILME_STORY_ISPEAKER_H
#define ISILME_STORY_ISPEAKER_H

#include "Quests.h"

namespace story
{
	/// @interface ISpeaker
	/// Interface for speakers
	class ISILME_API ISpeaker
	{
	public:
		virtual ~ISpeaker() {};

		/// Sets conversation for speaker
		virtual void SetConversation(ConversationPtr conversation) = 0;

		/// Gets conversation for speaker
		virtual ConversationPtr GetConversation() const = 0;
	};
}
#endif