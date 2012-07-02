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
#include "IsilmePCH.h"
#include "ResourceManager.h"
// ResourceManager

ResourceManager::~ResourceManager()
{
}

// HGEResourceManager

HGEResourceManager::HGEResourceManager(HGE* hge) :
	mHGE(hge),
	mResourceManager(0)
{
	mResourceManager = new hgeResourceManager();
}

HGEResourceManager::~HGEResourceManager()
{
	if (mResourceManager)
		delete mResourceManager;
}

void		HGEResourceManager::ChangeScript(std::string scriptname)
{
	mResourceManager->ChangeScript(scriptname.c_str());
}

bool		HGEResourceManager::Precache(int groupid)
{
	return mResourceManager->Precache(groupid);
}

void		HGEResourceManager::Purge(int groupid)
{
	mResourceManager->Purge(groupid);
}

void*		HGEResourceManager::GetResource(std::string name, int resgroup)
{
	return mResourceManager->GetResource(name.c_str(), resgroup);
}

HTEXTURE	HGEResourceManager::GetTexture(std::string name, int resgroup)
{
	return mResourceManager->GetTexture(name.c_str(), resgroup);
}

HEFFECT		HGEResourceManager::GetEffect(std::string name, int resgroup)
{
	return mResourceManager->GetEffect(name.c_str(), resgroup);
}

HMUSIC		HGEResourceManager::GetMusic(std::string name, int resgroup)
{
	return mResourceManager->GetMusic(name.c_str(), resgroup);
}

HSTREAM		HGEResourceManager::GetStream(std::string name, int resgroup)
{
	return mResourceManager->GetStream(name.c_str(), resgroup);
}

HTARGET		HGEResourceManager::GetTarget(std::string name)
{
	return mResourceManager->GetTarget(name.c_str());
}
