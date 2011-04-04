#include "Isilme.h"

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
