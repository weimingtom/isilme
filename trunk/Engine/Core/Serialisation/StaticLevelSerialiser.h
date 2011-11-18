#ifndef ISILME_SERIALISATION_STATICLEVELSERIALISER_H
#define ISILME_SERIALISATION_STATICLEVELSERIALISER_H

#include "Definitions.h"

namespace serialisation
{
	/// Serialiser for static level data.
	class IsilmeExport StaticLevelSerialiser
	{
	public:
		/// Serialises and writes to file
		///
		/// @param	level   	The level.
		/// @param	fileName	Filename of the file.
		virtual void Serialise(LevelPtr level, std::string fileName) = 0;
	};

	/// Serialiser for static level data.
	class IsilmeExport XMLStaticLevelSerialiser : public StaticLevelSerialiser
	{
	public:
		XMLStaticLevelSerialiser();
		virtual ~XMLStaticLevelSerialiser();

		/// Serialise layer.
		///
		/// @param	layer	The layer.
		///
		/// @return	null if it fails, else.
		TiXmlElement* SerialiseLayer(LayerPtr layer);

		/// Serialise entity.
		///
		/// @param	entity	The entity.
		///
		/// @return	null if it fails, else.
		TiXmlElement* SerialiseEntity(EntityPtr entity);

		/// Serialise.
		///
		/// @param	level	The level.
		///
		/// @return	null if it fails, else.
		TiXmlElement* Serialise(LevelPtr level);

		/// Serialise and write to file
		///
		/// @param	level   	The level.
		/// @param	fileName	Filename of the file.
		virtual void Serialise(LevelPtr level, std::string fileName);
	};
};

#endif