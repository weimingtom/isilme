#include "IsilmePCH.h"
#include "Behaviour.h"
#include "Action.h"
#include "AIPackage.h"
#include "AIPackageFactory.h"
#include "FactoryManager.h"
#include "AI/Attribute.h"
#include "AI/AttributeDef.h"

BehaviourPtr Behaviour::New()
{
	return BehaviourPtr(new Behaviour(0));
}

Behaviour::Behaviour(BehaviourDefinition* def)
{
	isActive = true;

	if (def)
	{
		// Читаем атрибуты
		for (int i = 0; i < def->GetAttributesCount(); ++i)
		{
			ai::AttributePtr a = def->GetAttribute(i)->Create();
			mAttributes[a->GetID()] = a;
		}

		// Читаем пакеты ИИ
		for (StringList::iterator it = def->AIPackages.begin(); it != def->AIPackages.end(); ++it)
		{
			AddAIPackage(*it);
		}
	}
}

Behaviour::~Behaviour()
{
}

void		Behaviour::SetActor(EntityPtr actor)
{
	mActor = actor;
}

EntityPtr		Behaviour::GetActor()
{
	return mActor.lock();
}

LevelPtr		Behaviour::GetLevel()
{
	return GetActor()->GetLevel();
}

void		Behaviour::Update(float elapsedTime)
{
	if (!isActive)
	{
		return;
	}

	Think(elapsedTime);
	UpdateActions(elapsedTime);

	/// Если агент бездействует активизируем пакет ИИ
	if (mActiveActions.size() == 0)
	{
		for (AIPackageList::iterator it = mActivePackages.begin(); it != mActivePackages.end(); ++it)
		{
			AIPackagePtr package = *it;
			if (package->GetBehaviour() == nullptr)
				package->mBehaviour = shared_from_this();
			if (package->CheckCondition())
			{
				StartAction(package->CreateAction());
				break;
			}
		}
	}
}

void		Behaviour::UpdateActions(float elapsedTime)
{
	ActionList::iterator it = mActiveActions.begin(); 
	while (it != mActiveActions.end())
	{
		(*it)->Update(elapsedTime);
		if ((*it)->GetState() == action::Done)
		{
			// Удаляем действие
			it = mActiveActions.erase(it);
		}
		else
		{
			// Продолжаем
			//mActionMask |= (*it)->GetMask();
			++it;
		}
	}
}

void		Behaviour::StartAction(ActionPtr action)
{
	mActiveActions.push_back(action);
	action->OnStart(shared_from_this());
}

void		Behaviour::SetActive(bool value)
{
	isActive = value;
}

bool		Behaviour::IsActive()
{
	return isActive;
}

void	BehaviourDefinition::Parse(TiXmlElement* element)
{
	if (!element)
		return;
	/// Считываем аттрибуты объекта
	TiXmlElement* attributesElement = element->FirstChildElement("Attributes");
	if (attributesElement)
		ParseAttributes(attributesElement);

	/// Считываем пакеты ИИ
	TiXmlElement* aiElement = element->FirstChildElement("AI");
	if (aiElement)
		ParseAIPackages(aiElement);
}

void	BehaviourDefinition::ParseAttributes(TiXmlElement* attributesElement)
{
	TiXmlElement* attributeElement = attributesElement->FirstChildElement("Attribute");
	while (attributeElement)
	{
		ai::AttributeDefPtr attrDef(new ai::AttributeDef());
		attrDef->Parse(attributeElement);
		mAttributes.push_back(attrDef);
		attributeElement = attributeElement->NextSiblingElement("Attribute");
	}
}

int BehaviourDefinition::GetAttributesCount()
{
	return mAttributes.size();
}

ai::AttributeDefPtr BehaviourDefinition::GetAttribute(int index)
{
	return mAttributes.at(index);
}

void	BehaviourDefinition::ParseAIPackages(TiXmlElement* aiElement)
{
	TiXmlElement* packageElement = aiElement->FirstChildElement("Package");
	while (packageElement)
	{
		const char* idAttr = packageElement->Attribute("ID");
		
		if (idAttr)
		{
			AIPackages.push_back(idAttr);
		}
		else
		{
			LOG_W("Incorrect package element");
		}

		packageElement = packageElement->NextSiblingElement("Package");
	}
}

void	Behaviour::AddAIPackage(AIPackagePtr package, int priority)
{
	mActivePackages.push_back(package);
}

void	Behaviour::AddAIPackage(std::string packageID, int priority)
{
	AIPackagePtr package = FactoryManager::GetSingleton()->GetAIPackage(packageID);
	if (package)
	{
		AddAIPackage(package, priority);
	}
	else
	{
		LOG_W("AI package %s not found", packageID.c_str());
	}
}

float Behaviour::GetAttributeValue(std::string ID)
{
	ai::AttributePtr attr = mAttributes[ID];
	if (!attr)
	{
		SetAttributeValue(ID, 0);
		return GetAttributeValue(ID);
	}
	else
	{
		return attr->GetValue();
	}
}

void Behaviour::SetAttributeValue(std::string ID, float value)
{
	ai::AttributePtr attr = GetAttribute(ID);
	if (!attr)
	{
		attr.reset(new ai::Attribute(ID, value));
		mAttributes[ID] = attr;
	}
	else
		attr->SetValue(value);
}

void Behaviour::Customize(TiXmlElement* element)
{

}

ai::AttributePtr Behaviour::GetAttribute(std::string id)
{
	return mAttributes[id];
}