#ifndef ISILME_CORE_SERIALISATION_DYNAMICLEVELSERIALISER_H
#define ISILME_CORE_SERIALISATION_DYNAMICLEVELSERIALISER_H

#include "Definitions.h"
#include "LevelSerialiser.h"

namespace serialisation
{
	/// Dynamic level serialiser.
	/// Writes dynamic data into file
	class IsilmeExport DynamicLevelSerialiser : public LevelSerialiser
	{
	public:
		DynamicLevelSerialiser();
		virtual ~DynamicLevelSerialiser();

		void Serialise(LevelPtr level, std::string fileName);

		TiXmlElement* SerialiseWorld();

		TiXmlElement* Serialise(LevelPtr level);

		/// Serialise body.
		///
		/// @param	body	The body.
		///
		/// @return	null if it fails, else.
		TiXmlElement* SerialiseBody(BodyPtr body);

		/// Сохраняет сущность
		///
		/// @param	entity	The entity.
		///
		/// @return	null if it fails, else.
		TiXmlElement* SerialiseEntity(EntityPtr entity);

		/// Сохраняет слой
		///
		/// @param	layer	The layer.
		///
		/// @return	null if it fails, else.
		TiXmlElement* SerialiseLayer(LayerPtr layer);
	private:
	};
};

#endif