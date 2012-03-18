#ifndef ISILME_CORE_AIPACKAGEDEF_H
#define ISILME_CORE_AIPACKAGEDEF_H

#include "AITypes.h"

/// Определение пакета ИИ
class ISILME_API AIPackageDef
{
public:
	AIPackageDef();
	virtual ~AIPackageDef();

	/// Читает параметры пакета ИИ
	virtual void Parse(TiXmlElement* element);

	/// Создает пакет ИИ с соответствующими настройками цели, флагов
	virtual AIPackagePtr CreatePackage();
};

#endif