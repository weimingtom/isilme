#ifndef ENTITY_H
#define ENTITY_H

#include <string>
#include <map>
#include <list>
#include <tinyxml.h>
#include "Definitions.h"
#include "Graphics.h"
#include "Collisions.h"
#include "Action.h"
#include "Behaviour.h"
#include "Bodies.h"


/// @class Entity
/// Описывает любую сущность в игре.
/// Сущность включает в себя графическую, физическую и "когнитивную" модели объекта
/// Сущность использует универсальные интерфейсы моделей и не зависит от их реализации.
class ISILME_API Entity
{
	friend class FactoryManager;
	friend class Layer;
	friend class Level;
	friend class EntityPalette;
public:
	
	
	/// News.
	///
	/// @param	level			The level.
	/// @param	behaviour   	The behaviour.
	/// @param [in,out]	body	If non-null, the body.
	/// @param	graphics		The graphics.
	///
	/// @return	.
	static EntityPtr New(LevelPtr level, BehaviourPtr behaviour, Body* body, GraphicsPtr graphics);
	
	/// Destructor.
	virtual ~Entity();
	
	/// Gets the name.
	///
	/// @return	The name.
	std::string		GetName();
	
	/// Query if this object is removed.
	///
	/// @return	true if removed, false if not.
	bool			IsRemoved();
	
	/// Removes this object.
	void			Remove();

	/// Gets the angle.
	///
	/// @return	The angle.
	float			GetAngle();

	/// Gets the position.
	///
	/// @return	The position.
	Vector2&		GetPosition();

	/// Gets the graphics.
	///
	/// @return	The graphics.
	GraphicsPtr		GetGraphics();
	
	/// Gets the behaviour.
	///
	/// @return	The behaviour.
	BehaviourPtr		GetBehaviour();

	/// Updates the given ElapsedTime.
	///
	/// @param	ElapsedTime	Time of the elapsed.
	virtual void	Update(float ElapsedTime);
	
	/// Sets a position.
	///
	/// @param	x	The x coordinate.
	/// @param	y	The y coordinate.
	void			SetPosition(float x, float y);

	/// Sets a position.
	///
	/// @param	pos	The position.
	void			SetPosition(Vector2 pos);

	/// Sets an angle.
	///
	/// @param	angle	The angle.
	void			SetAngle(float angle);
	
	/// Removes the body.
	void			RemoveBody();

	/// Gets the body.
	///
	/// @return	null if it fails, else the body.
	Body*			GetBody();
	
	/// Gets the level.
	///
	/// @return	The level.
	LevelPtr		GetLevel();

	/// Gets the layer.
	///
	/// @return	The layer.
	LayerPtr		GetLayer();
	
	/// Removes the joints.
	void			RemoveJoints();
	
	/// Gets the scale.
	///
	/// @return	The scale.
	float			GetScale();

	/// Sets a scale.
	///
	/// @param	value	The value.
	void			SetScale(float value);
	
	/// Gets an angle to.
	///
	/// @param	entity	The entity.
	///
	/// @return	The angle to.
	float		GetAngleTo(EntityPtr entity);
	
	/// Gets an angle to.
	///
	/// @param	point	The point.
	///
	/// @return	The angle to.
	float		GetAngleTo(Vector2 point);

	/// Gets a distance to.
	///
	/// @param	entity	The entity.
	///
	/// @return	The distance to.
	float		GetDistanceTo(EntityPtr entity);
	
	/// Gets a distance to.
	///
	/// @param	point	The point.
	///
	/// @return	The distance to.
	float		GetDistanceTo(Vector2 point);
	
	/// Is this object.
	///
	/// @return	true if it succeeds, false if it fails.
	template<class T>
	bool Is();

	/// Gets as.
	///
	/// @return	.
	template <class T>
	boost::shared_ptr<T> As();
	
	/// Gets the type.
	///
	/// @return	The type.
	std::string GetType();

	/// Scales.
	///
	/// @param	def	The def.
	void Scale(float def);

	/// Query if this object is serialisable.
	///
	/// @return	true if serialisable, false if not.
	bool IsSerialisable();
protected:	
	/// Default constructor.
	Entity();
	
	/// Executes the added to layer action.
	///
	/// @param	layer	The layer.
	void	OnAddedToLayer(LayerPtr layer);
private:
	/// Флаг удаления связей
	bool			removeJoints;

	/// Уровень, на котором размещена сущность
	LevelWPtr			mLevel;

	/// Слой, на котором размещена сущность
	LayerWPtr			mLayer;

	/// Имя сущности
	std::string		mName;

	/// Флаг равен true, если сущность удалена
	bool			isRemoved;

	/// Флаг удалено ли тело сущности
	bool			isBodyRemoved;

	/// Графика сущности
	GraphicsPtr		mGraphics;

	/// Поведение сущности
	BehaviourPtr		mBehaviour;

	/// 
	Body*			mBody;

	/// Масштаб сущности
	float			mScale;

	std::string	mType;
};

template<class T>
bool Entity::Is()
{
	return !(boost::shared_dynamic_cast<T>(GetBehaviour()) == 0);
}

template<class T>
boost::shared_ptr<T> Entity::As()
{
	return boost::shared_dynamic_cast<T>(GetBehaviour());
}
#endif