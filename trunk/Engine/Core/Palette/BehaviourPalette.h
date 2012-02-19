#ifndef ISILME_CORE_PALETTE_BEHAVIOURPALETTE_H
#define ISILME_CORE_PALETTE_BEHAVIOURPALETTE_H

#include "Definitions.h"

class ISILME_API BehaviourPalette
{
public:
	BehaviourPalette();
	virtual ~BehaviourPalette();

	/// Gets factory of behaviour type
	BehaviourFactoryPtr GetFactory( std::string type );

	/// Gets default behaviour factory
	BehaviourFactoryPtr GetDefaultFactory();

	/// Registers behaviour type
	void	RegisterBehaviour(std::string type, BehaviourFactoryPtr factory);

	/// Register behavior type
	//template <class TBehaviour>
	//void RegisterBehaviour(std::string type);
private:
	typedef std::map<std::string, BehaviourFactoryPtr> BehaviourFactoryMap;

	/// Behaviour factories
	BehaviourFactoryMap			mBehaviourFactories;
};

//template <class TBehaviour>
//void BehaviourPalette<TBehaviour>::RegisterBehaviour( std::string type )
//{
//
//}

#endif