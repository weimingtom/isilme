#ifndef ISILME_CONVERSATIONSERIALISER_H
#define ISILME_CONVERSATIONSERIALISER_H

#include "Definitions.h"
#include "Engine/Quest/Conversation.h"
#include "Engine/Quest/Phrase.h"

namespace serialisation
{
	class ISILME_API IConversationSerialiser
	{
	public:
		virtual void Serilise(story::ConversationPtr conversation, std::string fileName) = 0;
	};

	class ISILME_API XMLConversationSerialiser : public IConversationSerialiser
	{
	public:
		XMLConversationSerialiser();
		virtual ~XMLConversationSerialiser();

		virtual void Serilise(story::ConversationPtr conversation, std::string fileName);

		virtual void SerialiseConversation(story::ConversationPtr conversation, TiXmlElement* element);
		virtual void SerialisePhrase(story::PhrasePtr phrase, TiXmlElement* element);
	private:
		std::set<int> mRefs;
	};
}

#endif