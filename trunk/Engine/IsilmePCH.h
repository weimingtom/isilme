#ifndef ISILME_PCH_H
#define ISILME_PCH_H

#define NOMINMAX

#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
//#define new DEBUG_NEW
#endif

#include <luabind/lua_include.hpp>
#include <luabind/luabind.hpp>
#include <luabind/function.hpp>
#include <LuaBind/class.hpp>

#include <vector>
#include <list>
#include <set>
#include <map>

#include "Definitions.h"
#endif