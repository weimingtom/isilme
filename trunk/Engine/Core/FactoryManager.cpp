#include "IsilmePCH.h"
#include "FactoryManager.h"
#include "GraphicsFactory.h"
#include "Engine/Inventory/Item.h"
#include "Engine/Inventory/ItemDef.h"
#include "Engine/Inventory/ItemFactory.h"
#include "Engine/Story/Conversation.h"
#include "Engine/include/Trigger.h"
#include "Behaviour.h"
#include "Graphics/Animation.h"
#include "Graphics/Sprite.h"
#include "Graphics/Particles.h"
#include "Graphics/TriggerGraphics.h"
#include "Graphics/StateGraphics.h"
#include "Serialisation/SaveData.h"
#include "Serialisation/DynamicLevelSerialiser.h"
#include "Palette/EntityPalette.h"
#include "Serialisation/ConversationLoader.h"
#include "Game.h"
#include "Story/Story.h"
#include "Palette/AIPalette.h"
#include "AI/ScriptAIPackageDef.h"
#include "Serialisation/MasterLoader.h"
#include "Palette/BehaviourPalette.h"
#include "Palette/GraphicsPalette.h"
#include "Core/MasterFile.h"
#include "Palette/FractionsPalette.h"
#include "Palette/ItemsPalette.h"

FactoryPtr FactoryManager::mInstance;

FactoryManager::FactoryManager() : 
	mEntitiesPalette(new EntityPalette()),
	mAIPalette(new AIPalette()),
	mGraphicsPalette(new GraphicsPalette()),
	mBehaviourPalette(new BehaviourPalette()),
	mFractionsPalette(new FractionsPalette()),
	mItemsPalette(new ItemsPalette()),
	mLoader(new serialisation::MasterFileLoader()),
	mMasterFile(new MasterFile())
{
	RegisterBehaviour("Default", BehaviourFactory<BehaviourDefinition>::New());
	RegisterBehaviour("Trigger", BehaviourFactory<TriggerDefinition>::New());

	RegisterGraphics("Sprite", GraphicsFactory<graphics::SpriteDefinition>::New());
	RegisterGraphics("Animation", GraphicsFactory<graphics::AnimationDefinition>::New());
	RegisterGraphics("Particles", GraphicsFactory<graphics::ParticlesDefinition>::New());
	RegisterGraphics("Trigger", GraphicsFactory<graphics::TriggerDef>::New());

	//RegisterAIPackage("Script", AIPackageFactory<ScriptAIPackageDef>::New());
	RegisterCamera("Default", new CameraFactory<CameraDefinition>());
}

FactoryManager::~FactoryManager()
{
}

FactoryPtr FactoryManager::GetSingleton()
{
	if (mInstance == 0)
		mInstance = FactoryPtr(new FactoryManager());
	return mInstance;
}

inventory::ItemPtr	FactoryManager::CreateItem(std::string tag)
{
	return mItemsPalette->CreateItem(tag);
}

void	FactoryManager::RegisterItem(std::string type, inventory::ItemFactoryPtr factory)
{
	mItemsPalette->RegisterFactory(type, factory);
}

Body*	FactoryManager::CreateBody(BodyDef* def)
{
	if (def->Type == BodyDef::SimpleBody)
	{
		SimpleBody* body = new SimpleBody();
		return body;
	}
	else if (def->Type == BodyDef::Box2DBody)
	{
		Box2DBody* body = new Box2DBody(def);
		return body;
	}
	return 0;
}

void			FactoryManager::RegisterBehaviour(std::string type, BehaviourFactoryPtr factory)
{
	mBehaviourPalette->RegisterBehaviour(type, factory);
}

void			FactoryManager::DestroyEntity(std::string name)
{
	mEntitiesPalette->Destroy(name);
}

GraphicsPtr		FactoryManager::CreateGraphics(std::string tag)
{
	return mGraphicsPalette->CreateGraphics(tag);
}

void			FactoryManager::DestroyEntity(EntityPtr entity)
{
	mEntitiesPalette->Destroy(entity);
}

void			FactoryManager::RegisterGraphics(std::string type, GraphicsFactoryPtr factory)
{
	mGraphicsPalette->RegisterGraphicsType(type, factory);
}

EntityPtr		FactoryManager::CreateEntity(std::string type, std::string name)
{
	return mEntitiesPalette->Create(type, name);
}

EntityPtr		FactoryManager::GetEntity(std::string name)
{
	return mEntitiesPalette->GetEntity(name);
}

ICameraFactory*	FactoryManager::GetCameraFactory(std::string type)
{
	return mCameraFactories[type];
}

void		FactoryManager::RegisterCamera(std::string type, ICameraFactory* factory)
{
	mCameraFactories[type] = factory;
}

void	FactoryManager::CreateJoint(JointDefPtr def)
{
	//return new Joint(def);
}

FractionPtr		FactoryManager::GetFraction(std::string fractionID)
{
	return mFractionsPalette->GetFraction(fractionID);//mFractions[fractionID];
}

//void			FactoryManager::LoadFractions(TiXmlElement* element)
//{
//	std::map<std::pair<std::string, std::string>, int> relations;
//	// Загружаем фракции
//	TiXmlElement* fractionElement = element->FirstChildElement("Fraction");
//
//	while (fractionElement)
//	{
//		// Читаем аттрибуты
//		const char* idAttr = fractionElement->Attribute("ID");
//		const char* nameAttr = fractionElement->Attribute("Name");
//
//		if (idAttr)
//		{
//			FractionPtr fraction(new Fraction());
//
//			// Идентификатор фракции
//			fraction->mID = idAttr;
//
//			// Название фракции
//			fraction->mName = nameAttr ? nameAttr : "";
//
//			// Агрессивность
//			fraction->mAgression = 0;
//			fractionElement->QueryIntAttribute("Agression", &(fraction->mAgression));
//
//			// Ранги
//			TiXmlElement* rankElement = fractionElement->FirstChildElement("Rank");
//			while (rankElement)
//			{
//				int rankID = 0;
//				rankElement->QueryIntAttribute("ID", &rankID);
//
//				if (rankID)
//				{
//					RankPtr rank(new Rank());
//					rank->mID = rankID;
//
//					fraction->mRanks[rankID] = rank;
//				}
//				else
//				{
//					LOG_W("Rank of %s fraction has no ID", idAttr);
//				}
//				rankElement = rankElement->NextSiblingElement("Rank");
//			}
//
//			// Отношения
//			TiXmlElement* attitudeElement = fractionElement->FirstChildElement("Attitude");
//			while (attitudeElement)
//			{
//				const char* otherFraction = attitudeElement->Attribute("Fraction");
//				int attitude = 0;
//				attitudeElement->QueryIntAttribute("Value", &attitude);
//
//				if (otherFraction)
//				{
//					relations[std::pair<std::string, std::string>(fraction->GetID(), otherFraction)] = attitude;
//				}
//
//				attitudeElement = attitudeElement->NextSiblingElement("Attitude");
//			}
//
//			// Запоминаем фракцию
//			mFractions[fraction->mID] = fraction;
//		}
//		else
//		{
//			LOG_W("Fraction has no ID");
//		}
//
//		fractionElement = fractionElement->NextSiblingElement("Fraction");
//	}
//
//	// Загружаем отношения между фракциями
//	for (std::map<std::pair<std::string, std::string>, int>::iterator it = relations.begin(); it != relations.end(); ++it)
//	{
//		FractionPtr f1 = GetFraction(it->first.first);
//		FractionPtr f2 = GetFraction(it->first.second);
//
//		if (!f2)
//		{
//			LOG_W("Cannot set attitude to %s. Fraction doesn\'t exist", it->first.second.c_str());
//		}
//		else
//		{
//			f1->SetAttitudeTo(f2, it->second);
//		}
//	}
//}

story::ConversationPtr	FactoryManager::GetConversation(std::string id)
{
	return mConversations[id];
}

LevelPtr FactoryManager::GetLevel(std::string id)
{
	CategoryPtr category = mMasterFile->GetCategory("Levels");

	for (int i = 0; i < category->GetSize(); ++i)
	{
		boost::shared_ptr<LevelEntry> entry = category->GetEntry<LevelEntry>(i);
		if (entry)
		{
			if (entry->data->GetID() == id)
				return entry->data;
		}
	}

	return LevelPtr();
}

void FactoryManager::SaveGame( serialisation::SaveDataPtr save )
{
	serialisation::DynamicLevelSerialiser* serialiser = new serialisation::DynamicLevelSerialiser();

	
	TiXmlElement* saveElement = serialiser->SerialiseWorld();

	TiXmlDocument* document = new TiXmlDocument(save->GetFullPath().c_str());
	document->InsertEndChild(*saveElement);
	document->SaveFile();
	delete document;
	delete serialiser;
}

void FactoryManager::LoadGame( serialisation::SaveDataPtr save )
{

}

EntityPalettePtr FactoryManager::GetEntityPalette()
{
	return mEntitiesPalette;
}

void FactoryManager::LoadMasterFile( std::string fileName )
{
	LOG_M("LoadMasterFile: %s", fileName.c_str());

	mMasterFile = mLoader->Load(fileName);

	LOG_M("Success");
}

GraphicsPalettePtr FactoryManager::GetGraphicsPalette()
{
	return mGraphicsPalette;
}

BehaviourPaletettePtr FactoryManager::GetBehaviourPalette()
{
	return mBehaviourPalette;
}

MasterFilePtr FactoryManager::GetMasterFile()
{
	return mMasterFile;
}

AIPalettePtr FactoryManager::GetAIPalette()
{
	return mAIPalette;
}

FractionsPalettePtr FactoryManager::GetFractionsPalette()
{
	return mFractionsPalette;
}

ItemsPalettePtr FactoryManager::GetItemsPalette()
{
	return mItemsPalette;
}

serialisation::MasterFileLoader* FactoryManager::GetLoader()
{
	return mLoader;
}

//void FactoryManager::AddConversation( story::ConversationPtr conversation )
//{
//	mConversations[conversation->GetID()] = conversation;
//}
