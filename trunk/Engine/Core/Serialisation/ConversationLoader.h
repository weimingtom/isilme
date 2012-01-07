#ifndef ISILME_SERIALISATION_CONVERSATIONLOADER_H
#define ISILME_SERIALISATION_CONVERSATIONLOADER_H

#include "Definitions.h"
#include "Engine/Quest/Conversation.h"
#include "Engine/Quest/Phrase.h"

namespace serialisation
{
	class ISILME_API IConversationLoader
	{
	public:
		virtual story::ConversationPtr LoadConversation(std::string fileName) = 0;
	};

	class ISILME_API XMLConversationLoader : public IConversationLoader
	{
	public:
		XMLConversationLoader();
		virtual ~XMLConversationLoader();

		virtual story::ConversationPtr LoadConversation(std::string fileName);
		virtual story::ConversationPtr LoadConversation(TiXmlElement* element);
		virtual story::PhrasePtr LoadPhrase(TiXmlElement* element);

		story::PhrasePtr GetPhraseByRef(int refValue);
	private:
		std::map<int, story::PhrasePtr> mPhraseMap;
	};
}
#endif