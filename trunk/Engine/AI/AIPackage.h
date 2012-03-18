#ifndef ISILME_AI_AIPACKAGE_H
#define ISILME_AI_AIPACKAGE_H

#include "Definitions.h"
#include "AITypes.h"

class ISILME_API AIPackage
{
public:
	/// Creates action
	virtual ActionPtr CreateAction() const;

	/// Checks if AIPackage is applicable 
	virtual bool IsApplicable(BehaviourPtr behaviour) const;
private:
};


#endif