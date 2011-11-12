/// ****************************** Module Header ******************************
/// @file  Layer.h
///	Project:      Isilme
/// Copyright (c) Ofiel.
///
/// Модуль содержит описание слоя сцены
/// ***************************************************************************

#ifndef LAYER_H
#define LAYER_H

#include "Definitions.h"
#include "Entity.h"
#include "Camera.h"

/// @class Layer
/// Обычный слой на котором распологаются различные сущности.
/// Слой фактически является контейнером
class IsilmeExport Layer : public boost::enable_shared_from_this<Layer>
{
	friend class Level;
public:

	Layer();
	virtual ~Layer();

	/// Добавляет на слой сущность.
	/// Добавляемая сущность рисуется поверх всех остальных
	/// @param entity Entity*
	void		Add(EntityPtr entity);

	void		Remove(EntityPtr entity);

	/// Возвращает количество сущностей на слое
	/// @return int
	int			Size();

	/// Возвращает список сушностей
	/// @depricated
	EntityList* GetObjects();

	/// Уничтожает все объект на слое
	void	Clear();

	/// Возвращает, уровень, на котором расоложен слой
	LevelPtr	GetLevel();
protected:
	/// Вызывается во время удаления сущности
	void	OnRemoveEntity(EntityPtr entity);

private:
	/// Объекты слоя
	EntityList mObjects;

	/// Камера слоя
	Camera mCamera;

	/// Ссылка на уровень
	LevelWPtr mLevel;
};

typedef std::list<LayerPtr>	LayerList;
typedef std::map<std::string, LayerPtr> LayerMap;

#endif