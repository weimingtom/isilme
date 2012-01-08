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
class ISILME_API Level : public boost::enable_shared_from_this<Level>
{
	/// The layer
	friend class Layer;
	/// Manager for factory
	friend class FactoryManager;
public:
	/// Default constructor.
	Level();
	/// Destructor.
	virtual ~Level();

	/// Loads.
	///
	/// @param [in,out]	levelElement	If non-null, the TiXmlElement* to load.
	///
	/// @return	.
	static LevelPtr Load(TiXmlElement* levelElement);

	/// Loads the given file.
	///
	/// @param	fileName	The std::string to load.
	///
	/// @return	.
	static LevelPtr Load(std::string fileName);

	/// Gets the name.
	///
	/// @return	The name.
	std::string		GetID();

	/// Gets the active camera.
	///
	/// @return	The active camera.
	CameraPtr	GetActiveCamera();

	/// Sets an active camera.
	///
	/// @param	camera	The camera.
	void	SetActiveCamera(CameraPtr camera);

	/// Gets the world.
	///
	/// @return	null if it fails, else the world.
	b2World*		GetWorld();

	/// Gets a layer.
	///
	/// @param	index	Zero-based index of the.
	///
	/// @return	The layer.
	LayerPtr		GetLayer(int index);

	/// Gets the layers count.
	///
	/// @return	The layers count.
	int				GetLayersCount();

	/// Updates the given elapsedTime.
	///
	/// @param	elapsedTime	Time of the elapsed.
	virtual void	Update(float elapsedTime);

	/// Clears this object to its blank/initial state.
	void			Clear();

	/// Gets a layer.
	///
	/// @param	name	The name.
	///
	/// @return	The layer.
	LayerPtr		GetLayer(std::string name);

	/// Adds a layer.
	///
	/// @param	name	The name.
	///
	/// @return	.
	LayerPtr		AddLayer(std::string name);

	/// Adds a layer.
	///
	/// @param	layer	The layer.
	void			AddLayer(LayerPtr layer);

	/// Removes the layer described by layer.
	///
	/// @param	layer	The layer.
	void			RemoveLayer(LayerPtr layer);

	/// Creates an entity.
	///
	/// @param	type 	The type.
	/// @param	x	 	The x coordinate.
	/// @param	y	 	The y coordinate.
	/// @param	angle	The angle.
	/// @param	name 	(optional) the name.
	///
	/// @return	.
	EntityPtr		CreateEntity(std::string type, float x, float y, float angle, std::string name = "");

	/// Ray cast query all.
	///
	/// @param	x1   	The first x value.
	/// @param	y1   	The first y value.
	/// @param	x2   	The second x value.
	/// @param	y2   	The second y value.
	/// @param	count	(optional) number of.
	///
	/// @return	.
	QueryPtr RayCastQueryAll(float x1, float y1, float x2, float y2, int count = 0);

	/// Ray cast query nearest.
	///
	/// @param	x1	The first x value.
	/// @param	y1	The first y value.
	/// @param	x2	The second x value.
	/// @param	y2	The second y value.
	///
	/// @return	.
	EntityPtr	RayCastQueryNearest(float x1, float y1, float x2, float y2);

	/// Ray cast query any.
	///
	/// @param	x1	The first x value.
	/// @param	y1	The first y value.
	/// @param	x2	The second x value.
	/// @param	y2	The second y value.
	///
	/// @return	true if it succeeds, false if it fails.
	bool		RayCastQueryAny(float x1, float y1, float x2, float y2);

	/// Aabb query.
	///
	/// @param	x1	The first x value.
	/// @param	y1	The first y value.
	/// @param	x2	The second x value.
	/// @param	y2	The second y value.
	///
	/// @return	.
	QueryPtr	AABBQuery(float x1, float y1, float x2, float y2);
void RenameLayer( std::string oldName, std::string name );
private:
	/// Таймер итераций физического мира
	float		mPhisicsTimer;

	/// Список слоев сцены
	std::vector<LayerPtr>	mLayers;

	/// Поименованные слои
	LayerMap	mLayerNames;

	/// The entities
	EntitySet	mEntities;

	/// Текущая камера
	CameraPtr		mCamera;

	/// Физическая модель игрового мира
	b2World*	mWorld;

	/// Имя уровня
	std::string mName;
};

#endif