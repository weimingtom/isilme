/// ****************************** Module Header ******************************
/// @file  Level.h
///	Project:      Isilme
/// Copyright (c) Ofiel.
///
/// Модуль содержит описание сцены уровня. Для каждого уровня создается свой 
/// физический мир, 
/// ***************************************************************************

#ifndef LEVEL_H
#define LEVEL_H

#include <list>
#include "Layer.h"
#include "Camera.h"
#include "Collisions.h"

/// @class Level
/// Сцена уровня.
/// Сцена уровня содержит несколько слоев, на которых располагаются объекты и камеру.
/// Уровень поддерживает различные реализации камеры.
/// Каждый уровень пользуется своей моделью физического мира.
class IsilmeExport Level : public boost::enable_shared_from_this<Level>
{
	friend class FactoryManager;
public:
	Level();
	virtual ~Level();

	/// Возвращает используемую в уровне камеру
	Camera*			GetCamera();

	/// Устанавливает камеру
	void			SetCamera(Camera* camera);

	/// Возвращает физическую модель уровня
	b2World*		GetWorld();

	/// Возвращает слои сцены уровня
	LayerList*		GetLayers();

	/// Обновляет уровень
	virtual void	Update(float elapsedTime);

	/// Загружает уровень
	void			Load(std::string fileName);

	/// Очищает уровень
	void			Clear();

	/// Возвращает слой по имени
	/// Если слой не найден, создается новый слой
	LayerPtr		GetLayer(std::string name);

	/// Создает новый слой
	LayerPtr		AddLayer(std::string name);
private:
	/// Таймер итераций физического мира
	float		mPhisicsTimer;

	/// Список слоев сцены
	LayerList	mLayers;

	/// Поименованные слои
	LayerMap	mLayerNames;

	EntitySet	mEntities;

	/// Текущая камера
	Camera*		mCamera;

	/// Физическая модель игрового мира
	b2World*	mWorld;
};

#endif