#ifndef ISILME_CORE_AIPACKAGEWRAPPER_H
#define ISILME_CORE_AIPACKAGEWRAPPER_H

#include "Definitions.h"
#include "AIPackage.h"

class ISILME_API AIPackageWrapper : public AIPackage, luabind::wrap_base
{
public:
	AIPackageWrapper();
	virtual ~AIPackageWrapper();
	virtual bool CheckCondition(BehaviourPtr behaviour);
	virtual ActionPtr CreateAction();

	static bool defaultCheckCondition(AIPackage* base, BehaviourPtr behaviour);
	static ActionPtr defaultCreateAction(AIPackage* base);

};

#endif