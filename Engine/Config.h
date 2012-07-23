//  Copyright (C) 2010-2012 VSTU
//
//	This file is part of Isilme SDK.
//
//		Isilme SDK is free software: you can redistribute it and/or modify
//		it under the terms of the GNU Lesser General Public License as published by
//		the Free Software Foundation, either version 3 of the License, or
//		(at your option) any later version.
//
//		Isilme SDK is distributed in the hope that it will be useful,
//		but WITHOUT ANY WARRANTY; without even the implied warranty of
//		MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//		GNU Lesser General Public License for more details.
//
//		You should have received a copy of the GNU Lesser General Public License
//		along with Isilme SDK.  If not, see <http://www.gnu.org/licenses/>.
//
//	Этот файл — часть Isilme SDK.
//
//		Isilme SDK - свободная программа: вы можете перераспространять ее и/или
//		изменять ее на условиях Меньшей стандартной общественной лицензии GNU в том виде,
//		в каком она была опубликована Фондом свободного программного обеспечения;
//		либо версии 3 лицензии, либо (по вашему выбору) любой более поздней
//		версии.
//
//		Isilme SDK распространяется в надежде, что она будет полезной,
//		но БЕЗО ВСЯКИХ ГАРАНТИЙ; даже без неявной гарантии ТОВАРНОГО ВИДА
//		или ПРИГОДНОСТИ ДЛЯ ОПРЕДЕЛЕННЫХ ЦЕЛЕЙ. Подробнее см. в Меньшей стандартной
//		общественной лицензии GNU.
//
//		Вы должны были получить копию Меньшей стандартной общественной лицензии GNU
//		вместе с этой программой. Если это не так, см.
//		<http://www.gnu.org/licenses/>.

// Old versions of GCC don't support some C++11 keywords
#define GCC_VERSION (__GNUC__ * 10000 \
+ __GNUC_MINOR__ * 100 \
+ __GNUC_PATCHLEVEL__)

#if GCC_VERSION < 40600
#define nullptr NULL
#define override
#endif

// MSVS prelinked libraries
#if !defined( __libPerstStat_link_h__ )
#define __libPerstStat_link_h__

#if defined (_MSC_VER) 
#	if defined(_DEBUG)
#		pragma comment(lib, "xinput.lib")
#		pragma comment(lib, "luabind_d.lib")
#		pragma comment(lib, "hge_d.lib")
#		pragma comment(lib, "hgehelp_d.lib")
#		pragma comment(lib, "GUIChan_d.lib")
#		pragma comment(lib, "tinyxml_d.lib")
#		pragma comment(lib, "box2d_d.lib")
#		pragma comment(lib, "lua_d.lib")
#		if !defined(ISILME_DLL)
#		pragma comment(lib, "Engine_d.lib")
#		endif
#	else
#		pragma comment(lib, "xinput.lib")
#		pragma comment(lib, "luabind.lib")
#		pragma comment(lib, "hge.lib")
#		pragma comment(lib, "hgehelp.lib")
#		pragma comment(lib, "GUIChan.lib")
#		pragma comment(lib, "tinyxml.lib")
#		pragma comment(lib, "box2d.lib")
#		pragma comment(lib, "lua.lib")
#		if !defined(ISILME_DLL)
#		pragma comment(lib, "Engine.lib")
#		endif
#	endif
#endif

#endif  // __libPerstStat_link_h__