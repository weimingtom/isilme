#ifndef ISILME_AI_AIPACKAGE_FACTORY_H
#define ISILME_AI_AIPACKAGE_FACTORY_H

#include "Definitions.h"

class IAIPackageFactory
{
public:
	virtual AIPackagePtr	CreatePackage() = 0;
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

	virtual AIPackagePtr CreatePackage()
	{
		T* package = new T();
		return AIPackagePtr(package);
	}

	static AIPackageFactoryPtr New()
	{
		return AIPackageFactoryPtr(new AIPackageFactory<T>());
	}
};

#endif