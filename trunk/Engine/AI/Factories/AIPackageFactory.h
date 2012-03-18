#ifndef ISILME_AI_AIPACKAGEFACTORY_H
#define ISILME_AI_AIPACKAGEFACTORY_H

#include "../AITypes.h"

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