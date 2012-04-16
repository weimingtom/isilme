//  Copyright (C) 2010-2012 VSTU
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