#ifndef CAMERA_H
#define CAMERA_H

#include "Definitions.h"

class IsilmeExport Camera
{
public:
	float x;
	float y;
	float width;
	float height;
	float angle;

	Camera();
	Camera(CameraDefinition* def);

	virtual ~Camera();

	virtual void Update(float elapsedTime);
	
	void	Apply();
};

class IsilmeExport CameraDefinition
{
public:
	CameraDefinition();
	virtual ~CameraDefinition();

	virtual	CameraPtr Create();
	virtual void	Parse(TiXmlElement* def);
};

class IsilmeExport ICameraFactory
{
public:
	virtual ~ICameraFactory() {}
	virtual CameraDefPtr LoadDefinition(TiXmlElement* element) = 0;
};

// Шаблон для регистрации новых типов поведения
template <typename CameraType>
class CameraFactory : public ICameraFactory
{
public:
	CameraFactory()
	{
	}
	virtual ~CameraFactory()
	{
	}

	virtual CameraDefPtr LoadDefinition(TiXmlElement* element)
	{
		boost::shared_ptr<CameraType> def(new CameraType());
		def->Parse(element);
		return def;
	}
};

#endif