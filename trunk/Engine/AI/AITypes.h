#ifndef ISILME_AI_TYPES_H
#define ISILME_AI_TYPES_H

#include "Definitions.h"

class Actuator;
typedef boost::shared_ptr<Actuator> ActuatorPtr;

class Attribute;
typedef boost::shared_ptr<Attribute> AttributePtr;

class AttributeDef;

class AIBehaviour;
typedef boost::shared_ptr<AIBehaviour> AIBehaviourPtr;

class AIBehaviourDef;

class AIPackage;
typedef boost::shared_ptr<AIPackage> AIPackagePtr;

class AIPackageDef;
typedef boost::shared_ptr<AIPackageDef> AIPackageDefPtr;

class IAIPackageFactory;
typedef boost::shared_ptr<IAIPackageFactory> AIPackageFactoryPtr;
typedef std::map<std::string, AIPackageFactoryPtr> AIFactoryMap;

class Message;
typedef boost::shared_ptr<Message> MessagePtr;

class MessageData;
typedef boost::shared_ptr<MessageData> MessageDataPtr;

class Perception;
typedef boost::shared_ptr<Perception> PerceptionPtr;

class PerceptionList;

class UtilityFunction;
typedef boost::shared_ptr<UtilityFunction> UtilityFunctionPtr;

#endif