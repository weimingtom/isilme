#ifndef ISILME_SERIALISATION_MASTERFILELOADER_H
#define ISILME_SERIALISATION_MASTERFILELOADER_H

#include "Definitions.h"
#include "Types.h"
#include "EntryLoader.h"

namespace serialisation
{
	/// @class MasterFileLoader
	/// Loader for masterfiles
	class ISILME_API MasterFileLoader
	{
	public:
		MasterFileLoader();
		virtual ~MasterFileLoader();

		/// Loads masterfile and all data in it
		MasterFilePtr Load(std::string fileName);

		/// Add loader for category
		void Add(std::string category, EntryLoaderPtr loader);

	protected:
		/// Loads masterfile from XML data
		MasterFilePtr Load(TiXmlElement* element);

		/// Loads category and all entries
		CategoryPtr LoadCategory( TiXmlElement* categoryElement );
	private:
		typedef std::map<std::string, EntryLoaderPtr> EntryLoadersMap;

		/// Loaders for each category
		EntryLoadersMap mLoaders;

	};
}
#endif