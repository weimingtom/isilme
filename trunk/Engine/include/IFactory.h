#ifndef IFACTORY_H
#define IFACTORY_H

#include "tinyxml.h"
#include "Object.h"

class IsilmeExport IFactory
{
public:
	virtual Object* CreateInstance(TiXmlElement* element) = 0;
};
#endif