#ifndef FACTORYMANAGER_H
#define FACTORYMANAGER_H

#include <map>
#include <string>
#include <list>
#include <set>
#include "Graphics.h"
#include "Entity.h"
#include "Behaviour.h"
#include "Bodies.h"
#include "Joints.h"
#include "Camera.h"
#include "GraphicsFactory.h"
#include "Definitions.h"
#include "EntityDefinition.h"
#include "GraphicsFactory.h"

/// class FactoryManager
/// Управляет созданием всех объектов игры, графических моделей, поведений
class IsilmeExport FactoryManager
{
public:
	/// Уничтожает сущность с указанным идентификатором
	void			DestroyEntity(std::string name);

	/// Уничтожает указанную сущность
	void			DestroyEntity(EntityPtr entity);

	/// Зарегистрировать новый тип графического представления
	void			RegisterGraphics(std::string type_info, GraphicsFactoryPtr factory);

	/// Зарегистрировать новый тип поведения
	void			RegisterBehaviour(std::string type, IBehaviourFactory* factory);

	/// Создать сущность
	EntityPtr			CreateEntity(std::string type, std::string name, LevelPtr level);

	/// Возвращает сущность по имени
	EntityPtr			GetEntity(std::string name);

	/// Создает связь между объектами
	void			CreateJoint(JointDefPtr def);

	/// Загружает палитру графики из XML-файла
	void			LoadGraphics(std::string fileName);

	/// Загружает отдельное описание графики
	GraphicsDefPtr	LoadGraphics(TiXmlElement* element);

	/// Загружает палитру объектов из XML-файла
	void			LoadEntities(std::string fileName);

	/// Фозвращает единственный экзэмпляр фабрики
	static FactoryManager* GetSingleton();

	/// Возвращает фабрику камеры
	ICameraFactory*			GetCameraFactory(std::string type);

	/// Регистрирует новый тип камеры
	void			RegisterCamera(std::string type, ICameraFactory* factory);

protected:	
	/// Создает сущность из определения
	EntityPtr			CreateEntity(EntityDefPtr definition, std::string name, LevelPtr level);

	/// Создает физическую модель объекта и определения
	Body*			CreateBody(BodyDef* def);
private:
	/// Фабрики поведений
	BehaviourMap			mBehaviourFactories;

	/// Фабрики графических моделей
	GraphicsFactoryMap		mGraphicsFactories;

	std::map<std::string, ICameraFactory*>	mCameraFactories;

	/// Графическая палитра
	GraphicsPalette			mGraphicsDefinitions;

	/// Палитра объектов
	EntityPalette			mEntityDefinitions;
	
	// Созданные объекты
	EntityMap		mCreatedEntities;


	//////////////////////////////////////////////////////

	FactoryManager();

	virtual ~FactoryManager();

	static FactoryManager* mInstance;
};

#endif