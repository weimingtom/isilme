#include "Stdafx.h"
#include "EntityPaletteProxy.h"
#include "FolderProxy.h"

namespace LevelEditor
{
	namespace Proxy
	{
		EntityPaletteProxy::EntityPaletteProxy( EntityPalettePtr palette )
		{
			mPalette = new SharedCLIPtr<EntityPalette>(palette);
			mChildrenRoot = gcnew FolderProxy("");

			for (EntityPalette::EntityDefMap::iterator it = palette->GetData()->begin(); it != palette->GetData()->end(); ++it)
			{
				String^ itemName = gcnew String(it->second->GetType().c_str());

				FolderProxy^ root = mChildrenRoot;
				while (itemName->IndexOf('/') != -1)
				{
					String^ folderName = itemName->Substring(0, itemName->IndexOf('/'));
					itemName = itemName->Substring(itemName->IndexOf('/') + 1);
					FolderProxy^ subFolder = (FolderProxy^)root->GetChild(folderName);
					if (subFolder == nullptr)
					{
						subFolder = gcnew FolderProxy(folderName);
						root->AddItem(subFolder);
					}

					root = subFolder;
				}

				PaletteItemProxy^ item = gcnew PaletteItemProxy(itemName);

				root->AddItem(item);
			}
		}

		EntityPaletteProxy::~EntityPaletteProxy()
		{
			delete mPalette;
		}

		ObservableCollection<IHierarchicalProxy^>^ EntityPaletteProxy::Items::get()
		{
			return mChildrenRoot->Items;
		}
	}
}