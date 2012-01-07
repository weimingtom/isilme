#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include "Definitions.h"
#include <hgeresource.h>

/// @class ResourceManager
/// Менеджер ресурсов, интерфейс
class ISILME_API ResourceManager
{
public:
	virtual ~ResourceManager();
	virtual void				ChangeScript(std::string scriptname="") = 0;
	virtual bool				Precache(int groupid=0) = 0;
	virtual void				Purge(int groupid=0) = 0;

	virtual void*				GetResource(std::string name, int resgroup=0) = 0;
	virtual HTEXTURE			GetTexture(std::string name, int resgroup=0) = 0;
	virtual HEFFECT				GetEffect(std::string name, int resgroup=0) = 0;
	virtual HMUSIC				GetMusic(std::string name, int resgroup=0) = 0;
	virtual HSTREAM				GetStream(std::string name, int resgroup=0) = 0;
	virtual HTARGET				GetTarget(std::string name) = 0;

protected:
};

/// @class HGEResourceManager
/// Реализация менеджера ресурсов, использующая HGE
class ISILME_API HGEResourceManager : public ResourceManager
{
public:
	HGEResourceManager(HGE* hge);
	virtual ~HGEResourceManager();

	virtual void				ChangeScript(std::string scriptname="");
	virtual bool				Precache(int groupid=0);
	virtual void				Purge(int groupid=0);

	virtual void*				GetResource(std::string name, int resgroup=0);
	virtual HTEXTURE			GetTexture(std::string name, int resgroup=0);
	virtual HEFFECT				GetEffect(std::string name, int resgroup=0);
	virtual HMUSIC				GetMusic(std::string name, int resgroup=0);
	virtual HSTREAM				GetStream(std::string name, int resgroup=0);
	virtual HTARGET				GetTarget(std::string name);
protected:
	HGE*				mHGE;
	hgeResourceManager* mResourceManager;
};
#endif