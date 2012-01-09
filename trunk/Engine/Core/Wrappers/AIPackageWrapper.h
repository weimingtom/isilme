#ifndef ISILME_CORE_AIPACKAGEWRAPPER_H
#define ISILME_CORE_AIPACKAGEWRAPPER_H

#include "Definitions.h"
#include "AIPackage.h"

class ISILME_API AIPackageWrapper : public AIPackage, public luabind::wrap_base
{
public:
	virtual bool CheckCondition();
	virtual ActionPtr CreateAction();

	static bool defaultCheckCondition(AIPackage* base);
	static ActionPtr defaultCreateAction(AIPackage* base);

};

#endif