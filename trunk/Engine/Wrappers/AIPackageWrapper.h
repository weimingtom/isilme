#ifndef ISILME_CORE_AIPACKAGEWRAPPER_H
#define ISILME_CORE_AIPACKAGEWRAPPER_H

#include "Definitions.h"
#include "AI/AIPackage.h"

class ISILME_API AIPackageWrapper : public AIPackage, public luabind::wrap_base
{
public:
	AIPackageWrapper();
	virtual ~AIPackageWrapper();

	virtual bool IsApplicable(BehaviourPtr behaviour) const override;

	virtual ActionPtr CreateAction() const override;

	static bool defaultIsApplciable(AIPackage* base, BehaviourPtr behaviour);
	static ActionPtr defaultCreateAction(AIPackage* base);
	luabind::wrapped_self_t  self1;
};

#endif