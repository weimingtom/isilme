//  Copyright (C) 2010-2012 Alexander Alimov
//
//	This file is part of Isilme SDK.
//
//		Isilme SDK is free software: you can redistribute it and/or modify
//		it under the terms of the GNU Lesser General Public License as published by
//		the Free Software Foundation, either version 3 of the License, or
//		(at your option) any later version.
//
//		Isilme SDK is distributed in the hope that it will be useful,
//		but WITHOUT ANY WARRANTY; without even the implied warranty of
//		MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//		GNU Lesser General Public License for more details.
//
//		You should have received a copy of the GNU Lesser General Public License
//		along with Isilme SDK.  If not, see <http://www.gnu.org/licenses/>.
//
//	Этот файл — часть Isilme SDK.
//
//		Isilme SDK - свободная программа: вы можете перераспространять ее и/или
//		изменять ее на условиях Меньшей стандартной общественной лицензии GNU в том виде,
//		в каком она была опубликована Фондом свободного программного обеспечения;
//		либо версии 3 лицензии, либо (по вашему выбору) любой более поздней
//		версии.
//
//		Isilme SDK распространяется в надежде, что она будет полезной,
//		но БЕЗО ВСЯКИХ ГАРАНТИЙ; даже без неявной гарантии ТОВАРНОГО ВИДА
//		или ПРИГОДНОСТИ ДЛЯ ОПРЕДЕЛЕННЫХ ЦЕЛЕЙ. Подробнее см. в Меньшей стандартной
//		общественной лицензии GNU.
//
//		Вы должны были получить копию Меньшей стандартной общественной лицензии GNU
//		вместе с этой программой. Если это не так, см.
//		<http://www.gnu.org/licenses/>.
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