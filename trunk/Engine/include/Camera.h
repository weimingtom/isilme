#ifndef CAMERA_H
#define CAMERA_H

#include <tinyxml.h>

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

	virtual	Camera* Create();
	virtual void	Parse(TiXmlElement* def);
};

class IsilmeExport ICameraFactory
{
public:
	virtual ~ICameraFactory() {}
	virtual CameraDefinition* LoadDefinition(TiXmlElement* element) = 0;
};

// Шаблон для регистрации новых типов поведения
template <class CameraType>
class CameraFactory : public ICameraFactory
{
public:
	CameraFactory()
	{
	}
	virtual ~CameraFactory()
	{
	}

	virtual CameraDefinition* LoadDefinition(TiXmlElement* element)
	{
		CameraType* def = new CameraType();
		def->Parse(element);
		return def;
	}
};

#endif