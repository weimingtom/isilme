#ifndef SENSOR_H
#define SENSOR_H

class ISensor
{
public:
	virtual ~ISensor();
	virtual Entity* GetEntity() = 0;
	virtual void OnUpdate(float elapsedTime) = 0;
	virtual void OnInstall(Entity* entity) = 0;
	virtual void OnUninstall(Entity* entity) = 0;
};

/// @class Sensor
/// Сенсор объекта
/// Объект может обращаться к своим сенсорам вместо того, 
/// чтобы работать с данными внешней среды напрямую
template <class T>
class Sensor : public ISensor
{
public:
	Sensor()
	{
	}

	virtual ~Sensor()
	{
	}

	T	GetValue() 
	{
		return mValue;
	}

	Entity*	GetEntity()
	{
		return mEntity;
	}

	virtual void	OnUpdate() = 0;

	virtual void	OnInstall(Entity* entity)
	{
		mEntity = Entity;
	}

	virtual void	OnUninstall()
	{
		mEntity = 0;
	}
protected:
	void	SetValue(T value)
	{
		mValue = T;
	}
private:
	T mValue;
	Entity* mEntity;
};

typedef Sensor<bool> BoolSensor;
typedef Sensor<int> IntSensor;
typedef Sensor<float> FloatSensor;

#endif