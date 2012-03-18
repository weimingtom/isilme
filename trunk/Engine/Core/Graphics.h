#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "Definitions.h"
#include "GraphicsDefinition.h"

// Описание графической модели
class ISILME_API GraphicsDefinition 
{
public:
	virtual ~GraphicsDefinition() {}

	virtual void Parse(TiXmlElement* defElement);
	virtual GraphicsPtr Create() = 0;

	Vector2 Anchor;
protected:
	std::string mType;
};

// Класс описывает графику сущности
class ISILME_API Graphics
{
	friend class Entity;
	friend class FactoryManager;
	friend class EntityPalette;
public:
	Graphics(GraphicsDefinition* def = 0);
	virtual ~Graphics();

	/// Обновить графику
	virtual void Update(float elapsedTime);

	/// Визуализировать 
	virtual void Render(float x, float y, float angle);

	virtual void Reset() {};

	virtual void Attach(std::string tag, GraphicsPtr g);

	virtual void Remove(std::string tag);

	/// Сущность
	EntityPtr	GetEntity();

	/// Sets a scale.
	///
	/// @param	value	The value.
	void SetScale(float value);

	/// Gets the scale.
	///
	/// @return	The scale.
	float GetScale();

	/// Scales.
	///
	/// @param	scale	The scale.
	void Scale(float scale);

	/// Возвращает точку привязки графики к телу сущности
	Vector2	GetAnchor();

	/// Устанавливает точку привязки графики к телу
	void SetAnchor(Vector2 point);
protected:
	typedef std::map<std::string, GraphicsPtr> GraphicsMap;
	float mScale;
	EntityWPtr mEntity;
	GraphicsMap mAttached;
private:
	/// Точка привязки
	Vector2 mAnchor;
};

#endif