#include "Isilme.h"
#include "ItemDef.h"
#include "Item.h"

namespace inventory
{
	ItemDef::ItemDef()
	{
		ReloadingTime = 0.0f;
		UsingTime = 0.0f;
		Icon = 0;
		UseSound = 0;
		Ammo = 0;
		MaxAmmo = 0;
		Infinity = false;
	}

	ItemDef::~ItemDef()
	{
	}

	void	ItemDef::Parse(TiXmlElement* def)
	{
		def->QueryFloatAttribute("UsingTime", &UsingTime);
		def->QueryFloatAttribute("ReloadingTime", &ReloadingTime);
		def->QueryIntAttribute("Ammo", &Ammo);
		def->QueryIntAttribute("MaxAmmo", &MaxAmmo);
		int isInfinity = 0;
		def->QueryIntAttribute("Infinity", &isInfinity);
		Infinity = isInfinity != 0;

		if (def->Attribute("Icon"))
		{
			Icon = gcn::Image::load(def->Attribute("Icon"));
		}

		if (def->Attribute("UseSound"))
		{
			UseSound = Engine::GetSingleton()->GetResourceManager()->GetEffect(def->Attribute("UseSound"));
		}
	}

	ItemPtr	ItemDef::Create()
	{
		return ItemPtr(new Item(this));
	}
};