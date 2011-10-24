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
#include "Engine/Inventory/ItemFactory.h"

/// class FactoryManager
/// Управляет созданием всех объектов игры, графических моделей, поведений
class IsilmeExport FactoryManager
{
public:
	virtual ~FactoryManager();

	/// Уничтожает сущность с указанным идентификатором
	void			DestroyEntity(std::string name);

	/// Уничтожает указанную сущность
	void			DestroyEntity(EntityPtr entity);

	/// Зарегистрировать новый тип графического представления
	void			RegisterGraphics(std::string type_info, GraphicsFactoryPtr factory);

	/// Зарегистрировать новый тип поведения
	void			RegisterBehaviour(std::string type, IBehaviourFactory* factory);

	/// Зарегистрировать тип предмета
	void			RegisterItem(std::string type, inventory::ItemFactoryPtr factory);

	void			RegisterAIPackage(std::string type, AIPackageFactoryPtr factory);

	/// Возвращает ИИ-пакет
	AIPackagePtr	GetAIPackage(std::string type);

	/// Создать предмет
	inventory::ItemPtr	CreateItem(std::string tag);

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

	void			ClearItems();

	/// Загружает палитру предметов
	void			LoadItems(std::string fileName);

	/// Фозвращает единственный экзэмпляр фабрики
	static FactoryPtr GetSingleton();

	/// Возвращает фабрику камеры
	ICameraFactory*			GetCameraFactory(std::string type);

	/// Регистрирует новый тип камеры
	void			RegisterCamera(std::string type, ICameraFactory* factory);

	/// Созадет графику
	GraphicsPtr		CreateGraphics(std::string tag);

	/// Возвращает фракцию по идентификатору
	FractionPtr		GetFraction(std::string fractionID);

	/// Загружает файл данных - палитры, объекты, уровни, квесты, предметы, лут, все в одном файле
	void			LoadDataFile(std::string fileName);

	/// Загружает описание фракций
	void			LoadFractions(TiXmlElement* element);

	/// Загружает пакеты AI
	void			LoadAIPackages(TiXmlElement* element);
protected:	
	/// Создает сущность из определения
	EntityPtr			CreateEntity(EntityDefPtr definition, std::string name, LevelPtr level);

	inventory::ItemDefPtr LoadItem(TiXmlElement* def);

	/// Создает физическую модель объекта и определения
	Body*			CreateBody(BodyDef* def);
private:
	/// Фабрики поведений
	BehaviourMap			mBehaviourFactories;

	/// Фабрики графических моделей
	GraphicsFactoryMap		mGraphicsFactories;

	/// Фабрики предметов
	inventory::ItemFactoryMap mItemFactories;
	std::map<std::string, ICameraFactory*>	mCameraFactories;

	/// Графическая палитра
	GraphicsPalette			mGraphicsDefinitions;

	/// Палитра объектов
	EntityPalette			mEntityDefinitions;

	/// Палитра предметов
	inventory::ItemsPalette mItemsPalette;
	
	// Созданные объекты
	EntityMap		mCreatedEntities;

	// Фракции
	FractionMap		mFractions;

	/// Пакеты ИИ
	AIPackageMap	mAIPackages;

	/// Фабрики пакетов ИИ отображение тип-фабрика
	AIFactoryMap	mAIFactories;
	//////////////////////////////////////////////////////

	FactoryManager();

	static FactoryPtr mInstance;
};

#endif