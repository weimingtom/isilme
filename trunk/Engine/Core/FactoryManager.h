#ifndef FACTORYMANAGER_H
#define FACTORYMANAGER_H

#include "Definitions.h"
#include "Engine/Story/Quests.h"
#include "Graphics.h"
#include "Entity.h"
#include "Behaviour.h"
#include "Bodies.h"
#include "Joints.h"
#include "Camera.h"
#include "GraphicsFactory.h"
#include "EntityDefinition.h"
#include "GraphicsFactory.h"
#include "Engine/Inventory/ItemFactory.h"
#include "../Palette/Types.h"
#include "../Serialisation/Types.h"

/// class FactoryManager
/// Управляет созданием всех объектов игры, графических моделей, поведений
/// Helper class for embedded game components and factories
class ISILME_API FactoryManager
{
	friend class serialisation::DynamicLevelSerialiser;
public:
	virtual ~FactoryManager();

	/// Уничтожает сущность с указанным идентификатором
	void			DestroyEntity(std::string name);

	/// Уничтожает указанную сущность
	void			DestroyEntity(EntityPtr entity);

	/// Зарегистрировать новый тип графического представления
	void			RegisterGraphics(std::string type_info, GraphicsFactoryPtr factory);

	/// Зарегистрировать новый тип поведения
	void			RegisterBehaviour(std::string type, BehaviourFactoryPtr factory);

	/// Зарегистрировать тип предмета
	void			RegisterItem(std::string type, inventory::ItemFactoryPtr factory);

	/// Создать предмет
	inventory::ItemPtr	CreateItem(std::string tag);

	/// Создать сущность
	EntityPtr			CreateEntity(std::string type, std::string name);

	/// Возвращает сущность по имени
	EntityPtr			GetEntity(std::string name);

	/// Создает связь между объектами
	void			CreateJoint(JointDefPtr def);

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

	///// Загружает файл данных - палитры, объекты, уровни, квесты, предметы, лут, все в одном файле
	//void			LoadDataFile(std::string fileName);

	/// Loads master file
	void			LoadMasterFile(std::string fileName);

	/// Загружает описание фракций
	//void			LoadFractions(TiXmlElement* element);

	/// Загружает диалоги из файла
	//void			LoadConversations(std::string fileName);

	///// Loads a level.
	/////
	///// @param	fileName	Filename of the file.
	//LevelPtr			LoadLevel(std::string fileName);

	/// Возвращает диалог по имени
	story::ConversationPtr GetConversation(std::string id);

	/// Возвращает уровень по иднтификатору
	LevelPtr		GetLevel(std::string id);

	/// Сохраняет все данные в файл сохранения
	///
	/// @param		The serialisation::SaveDataPtr to save.
	void			SaveGame(serialisation::SaveDataPtr save);

	/// Загружает все данные из файла сохранения
	///
	/// @param	save	The save.
	void			LoadGame(serialisation::SaveDataPtr save);

	/// Gets the entity palette.
	///
	/// @return	The entity palette.
	EntityPalettePtr	GetEntityPalette();

	/// Gets graphics palette
	GraphicsPalettePtr	GetGraphicsPalette();

	/// Gets behaviour palette
	BehaviourPaletettePtr	GetBehaviourPalette();

	/// Gets ai palette
	AIPalettePtr GetAIPalette();

	/// Gets fractions palette
	FractionsPalettePtr GetFractionsPalette();
	
	/// Gets items palette
	ItemsPalettePtr GetItemsPalette();

	/// Добавить диалог
	//void AddConversation(story::ConversationPtr conversation);

	/// Gets master-file
	MasterFilePtr		GetMasterFile();

	/// Gets loader
	serialisation::MasterFileLoader*		GetLoader();
protected:	

	/// Создает сущность из определения
	EntityPtr			CreateEntity(EntityDefPtr definition, std::string name);

	/// Создает физическую модель объекта и определения
	Body*			CreateBody(BodyDef* def);
private:
	std::map<std::string, ICameraFactory*>	mCameraFactories;

	/// Диалоги
	std::map<std::string, story::ConversationPtr> mConversations;

	/// Items palette
	ItemsPalettePtr mItemsPalette;

	/// Fractions palette
	FractionsPalettePtr mFractionsPalette;

	/// AI Palette
	AIPalettePtr	mAIPalette;

	/// Entities palette
	EntityPalettePtr mEntitiesPalette;

	/// Graphics palette
	GraphicsPalettePtr mGraphicsPalette;

	/// Behaviour palette
	BehaviourPaletettePtr mBehaviourPalette;

	FactoryManager();

	/// All game data
	MasterFilePtr	mMasterFile;

	/// Master-file loader
	serialisation::MasterFileLoader* mLoader;

	static FactoryPtr mInstance;
};

#endif