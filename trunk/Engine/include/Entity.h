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
class IsilmeExport Entity
{
	friend class FactoryManager;
	friend class Layer;
	friend class Level;
public:
	static EntityPtr New(LevelPtr level, BehaviourPtr behaviour, Body* body, GraphicsPtr graphics);

	/// Деструктор сущности
	virtual ~Entity();

	/// Возвращает имя сущности
	std::string		GetName();

	/// Удалена ли сущность
	bool			IsRemoved();

	/// Удаляет сущность
	void			Remove();

	/// Возвращает поворот сущности
	float			GetAngle();

	/// Возвращает координаты сущности
	Vector2&		GetPosition();

	/// Возвращает графику сущности
	GraphicsPtr		GetGraphics();
	
	/// Возвоащает поведение сущности
	BehaviourPtr		GetBehaviour();

	/// Обновляет сущность
	virtual void	Update(float ElapsedTime);

	/// Задает координаты сущности
	void			SetPosition(float x, float y);

	/// Задает угол поворота сущности
	void			SetAngle(float angle);

	/// Удаляет тело сущности
	void			RemoveBody();

	/// Возвращает тело сущности
	Body*			GetBody();
	
	/// Возвращает уровень
	LevelPtr		GetLevel();

	/// Возвращает слой, на котором расположена сущность
	LayerPtr		GetLayer();
	
	/// Удалить все физические связи
	void			RemoveJoints();

protected:
	/// Создает сущность
	Entity();

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
};

#endif