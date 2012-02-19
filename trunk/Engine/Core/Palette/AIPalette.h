#ifndef ISILME_PALETTE_AIPALETTE_H
#define ISILME_PALETTE_AIPALETTE_H

#include "Definitions.h"

class ISILME_API AIPalette
{
public:
	AIPalette();
	virtual ~AIPalette();

	/// Registers AI type
	void RegisterAIType(std::string type, AIPackageFactoryPtr aiFactory);

	/// Registers AI type
	template<typename DefType>
	void RegisterAIType(std::string type);

	/// Creates ai package
	AIPackagePtr CreateAIPackage(std::string id);

	/// Clears palette
	void Clear();

	/// Loads palette from file
	void Load(std::string fileName);

protected:
	void Load(TiXmlElement* element);
private:
	typedef std::map<std::string, AIPackageFactoryPtr> AIFactoryMap;
	typedef std::map<std::string, AIPackageDefPtr> AIDefMap;

	/// Контейнер тип пакета ИИ - фабрика
	AIFactoryMap mFactories;

	/// Палитра Идентификатор - определение
	AIDefMap mDefinitions;
};

template<typename DefType>
void AIPalette::RegisterAIType( std::string type )
{
	AIPackageFactoryPtr factory = AIPackageFactory<DefType>::New();
	RegisterAIType(type, factory);
}

#endif