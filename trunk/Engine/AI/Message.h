#ifndef ISILME_AI_MESSAGE_H
#define ISILME_AI_MESSAGE_H

#include "AITypes.h"

/// @class Message
/// Сообщение пересылаемое агентом агенту
class ISILME_API Message
{
	friend class Behaviour;
public:
	Message(std::string type, MessageDataPtr data);
	virtual ~Message();

	// 	/// Возвращает идентификатор сообщения
	// 	std::string GetID();

	/// Возвращает тип сообщения
	std::string GetType();

	/// Возвращает данные сообщения
	MessageDataPtr	GetData();

	/// Возвращает отправителя сообщения
	BehaviourPtr	GetSender();
protected:

private:
	std::string mType;
	MessageDataPtr mData;
	BehaviourWPtr mSender;
};

#endif