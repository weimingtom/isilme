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
	friend class Layer;
	friend class FactoryManager;
public:
	Level();
	virtual ~Level();

	/// Загружает уровень из XML
	static LevelPtr Load(TiXmlElement* levelElement);

	static LevelPtr Load(std::string fileName);

	/// Возвращает имя уровня
	std::string		GetName();

	/// Возвращает используемую в уровне камеру
	Camera*			GetCamera();

	/// Устанавливает камеру
	void			SetCamera(Camera* camera);

	/// Возвращает физическую модель уровня
	b2World*		GetWorld();

	/// Возвращает слой по индексу
	LayerPtr		GetLayer(int index);

	/// Возвращает количество слоев
	int				GetLayersCount();

	/// Обновляет уровень
	virtual void	Update(float elapsedTime);

	/// Очищает уровень
	void			Clear();

	/// Возвращает слой по имени
	/// Если слой не найден, создается новый слой
	LayerPtr		GetLayer(std::string name);

	/// Создает новый слой
	LayerPtr		AddLayer(std::string name);

	/// Добавляет слой на уровень
	void			AddLayer(LayerPtr layer);

	/// Удалить слой из уровня
	void			RemoveLayer(LayerPtr layer);

	/// Создает сущность на уровне
	EntityPtr		CreateEntity(std::string type, float x, float y, float angle, std::string name = "");

	/// Запрос по трассировке луча
	bool		RayCastQueryAll(EntityList* entitiesDest, float x1, float y1, float x2, float y2, int count = 0);


	EntityPtr	RayCastQueryNearest(float x1, float y1, float x2, float y2);

	bool		RayCastQueryAny(float x1, float y1, float x2, float y2);

	/// AABB-запрос
	bool			AABBQuery(EntityList* entitiesDest, float x1, float y1, float x2, float y2);
private:
	/// Таймер итераций физического мира
	float		mPhisicsTimer;

	/// Список слоев сцены
	std::vector<LayerPtr>	mLayers;

	/// Поименованные слои
	LayerMap	mLayerNames;

	EntitySet	mEntities;

	/// Текущая камера
	Camera*		mCamera;

	/// Физическая модель игрового мира
	b2World*	mWorld;

	/// Имя уровня
	std::string mName;
};

#endif