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
class ISILME_API Layer : public boost::enable_shared_from_this<Layer>
{
	friend class Level;
public:

	Layer();
	virtual ~Layer();

	/// Добавляет на слой сущность.
	/// Добавляемая сущность рисуется поверх всех остальных
	/// @param entity Entity*
	void		Add(EntityPtr entity);

	/// Удаляет сущность со слоя
	void		Remove(EntityPtr entity);

	/// Возвращает количество сущностей на слое
	/// @return int
	int			Size();

	/// Уничтожает все объект на слое
	void	Clear();

	/// Возвращает, уровень, на котором расоложен слой
	LevelPtr	GetLevel();

	/// Возвращает сущность по индексу
	EntityPtr	GetEntity(int index);

	/// Возвращает имя слоя
	std::string	GetName();

	/// Переименовывает слой, если возможно
	void SetName(std::string name);

	/// Возвращает видимость слоя
	bool IsVisible();

	/// Устанавливает видимость слоя
	void SetVisible(bool value);
private:
	/// Имя слоя
	std::string mName;

	/// Объекты слоя
	std::vector<EntityPtr> mObjects;

	/// Камера слоя
	/// @depricated
	Camera mCamera;

	/// Ссылка на уровень
	LevelWPtr mLevel;

	/// Видимость слоя
	bool isVisible;
};

typedef std::list<LayerPtr>	LayerList;
typedef std::map<std::string, LayerPtr> LayerMap;

#endif