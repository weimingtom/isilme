#ifndef ISILME_INVENTORY_ITEMDEF_H
#define ISILME_INVENTORY_ITEMDEF_H

#include "Definitions.h"
#include <guichan.hpp>

namespace inventory
{
	class IsilmeExport ItemDef
	{
	public:
		ItemDef();
		virtual ~ItemDef();

		virtual ItemPtr Create();
		virtual void Parse(TiXmlElement* def);

		std::string Tag;
		std::string GND;
		int MaxAmmo;
		int Ammo;
		float UsingTime;
		float ReloadingTime;
		HEFFECT UseSound;
		gcn::Image* Icon;
		bool Infinity;
		bool UseMerging;

	};
};
#endif