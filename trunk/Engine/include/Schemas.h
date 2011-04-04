#ifndef ISILME_SCHEMAS_H
#define ISILME_SCHEMAS_H

#include "Definitions.h"

namespace LevelSchema
{
	extern const IsilmeExport char *  Level;
	extern const IsilmeExport char*  Layer;
	extern const IsilmeExport char* Group;
	extern const IsilmeExport char* Entity;
};

namespace EntitySchema
{
	extern const IsilmeExport char* Entity;		
	extern const IsilmeExport char* Body;
	extern const IsilmeExport char* Graphics;
	extern const IsilmeExport char* Behaviour;
	extern const IsilmeExport char* BehaviourType;
	extern const IsilmeExport char* Actions;
	extern const IsilmeExport char* Action;
};
#endif