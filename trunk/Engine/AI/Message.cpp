#include "IsilmePCH.h"
#include "Message.h"
#include "MessageData.h"

Message::~Message()
{

}

std::string Message::GetType()
{
	return mType;
}

MessageDataPtr Message::GetData()
{
	return mData;
}

BehaviourPtr	Message::GetSender()
{
	return mSender.lock();
}

Message::Message( std::string type, MessageDataPtr data )
{
	mType = type;
	mData = data;
}