#ifndef ISILME_PALETTE_AIPALETTE_H
#define ISILME_PALETTE_AIPALETTE_H

#include "Definitions.h"

class ISILME_API AIPalette
{
public:
	AIPalette();
	virtual ~AIPalette();

	/// Заригестрировать тип пакета ИИ
	void RegisterAIType(std::string type, AIPackageFactoryPtr aiFactory);

	/// Зарегистрировать тип пакета ИИ
	template<typename DefType>
	void RegisterAIType(std::string type);

	/// Создать пакет ИИ
	AIPackagePtr CreateAIPackage(std::string id);

	/// Очистить палитру
	void Clear();

	/// Загрузить палитру из файла
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