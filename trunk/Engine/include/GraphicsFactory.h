﻿#ifndef GRAPHICS_FACTORY_H
#define GRAPHICS_FACTORY_H

#include <string>
#include <map>
#include <tinyxml.h>
#include "Definitions.h"
#include "Graphics.h"

/// class IGraphicsFactory
/// Интерфейс загрузчика графических моделей из XML файлов
class ISILME_API IGraphicsFactory
{
public:
	virtual GraphicsDefPtr	LoadDefinition(TiXmlElement* graphicsElement) = 0;
};

template <class T>
class GraphicsFactory : public IGraphicsFactory
{
public:
	static GraphicsFactoryPtr New()
	{
		return GraphicsFactoryPtr(new GraphicsFactory<T>());
	}

	virtual GraphicsDefPtr	LoadDefinition(TiXmlElement* graphicsElement)
	{
		T* def = new T();
		def->Parse(graphicsElement);
		return GraphicsDefPtr(def);
	}
//protected:
	GraphicsFactory()
	{
	}
};

#endif