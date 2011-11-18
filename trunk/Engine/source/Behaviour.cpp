#include "IsilmePCH.h"
#include "Behaviour.h"
#include "Action.h"
#include "AIPackage.h"
#include "AIPackageFactory.h"
#include "FactoryManager.h"

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
		for (AttributeMap::iterator it = def->Attributes.begin(); it != def->Attributes.end(); ++it)
		{
			SetAttribute(it->first, it->second);
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
			if (package->CheckCondition(shared_from_this()))
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
		const char* idAttr = attributeElement->Attribute("ID");
		float value = 0.0f;
		attributeElement->QueryFloatAttribute("Value", &value);

		if (idAttr)
		{
			Attributes[idAttr] = value;
		}
		attributeElement = attributeElement->NextSiblingElement("Attribute");
	}
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

float Behaviour::GetAttribute(std::string ID)
{
	return mAttributes[ID];
}

void Behaviour::SetAttribute(std::string ID, float value)
{
	mAttributes[ID] = value;
}

void Behaviour::Customize(TiXmlElement* element)
{

}