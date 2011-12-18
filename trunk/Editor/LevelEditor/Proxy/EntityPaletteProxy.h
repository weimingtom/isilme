#include "../Stdafx.h"
#include "../SharedCLIPtr.h"

using namespace System::Collections::ObjectModel;
using namespace System;

namespace LevelEditor
{
	namespace Proxy
	{
		public ref class EntityPaletteProxy : public Common::ProxyObject
		{
		public:
			EntityPaletteProxy(EntityPalettePtr palette);
			virtual ~EntityPaletteProxy();

			property ObservableCollection<IHierarchicalProxy^>^ Items
			{
				ObservableCollection<IHierarchicalProxy^>^ get();
			}
		private:
			FolderProxy^ mChildrenRoot;
			SharedCLIPtr<EntityPalette>* mPalette;
		};
	}
}