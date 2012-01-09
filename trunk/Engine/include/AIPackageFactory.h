#ifndef ISILME_AI_AIPACKAGE_FACTORY_H
#define ISILME_AI_AIPACKAGE_FACTORY_H

#include "Definitions.h"

class IAIPackageFactory
{
public:
	virtual AIPackageDefPtr CreateDef() = 0;
};

template <class T>
class AIPackageFactory : public IAIPackageFactory
{
public:
	AIPackageFactory()
	{
	};
	virtual ~AIPackageFactory()
	{
	}

	virtual AIPackageDefPtr CreateDef()
	{
		T* package = new T();
		return AIPackageDefPtr(package);
	}

	static AIPackageFactoryPtr New()
	{
		return AIPackageFactoryPtr(new AIPackageFactory<T>());
	}
};

#endif