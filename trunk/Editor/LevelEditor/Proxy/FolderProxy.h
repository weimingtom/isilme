#pragma once
#include "../Stdafx.h"

using namespace System;
using namespace System::Windows;
using namespace System::Windows::Controls;
using namespace System::Windows::Data;
using namespace System::Collections::ObjectModel;
using namespace Common;

namespace LevelEditor
{
namespace Proxy
{
	public interface class IHierarchicalProxy
	{
	public:
		property String^ Name
		{
			String^ get();
		}

		property String^ FullName
		{
			String^ get();
		}

		property IHierarchicalProxy^ Parent
		{
			IHierarchicalProxy^ get();
			void set(IHierarchicalProxy^ value);
		}
		//property ObservableCollection<IHierarchicalProxy^>^ Children
		//{
		//	ObservableCollection<IHierarchicalProxy^>^ get();
		//}

		//void AddChild(IHierarchicalProxy^ child);

		//IHierarchicalProxy^ GetChild(String^ name);
	};

	/// Каталог, содержащий вложенные объекты, используется для отображения объектов палитры
	public ref class FolderProxy : public Common::ProxyObject, public IHierarchicalProxy
	{
	public:
		FolderProxy(String^ name);
		FolderProxy();
		virtual ~FolderProxy();

		property String^ Name
		{
			virtual String^ get();
			virtual void set(String^ value);
		}

		property IHierarchicalProxy^ Parent
		{
			virtual IHierarchicalProxy^ get();
			virtual void set(IHierarchicalProxy^ value);
		}

		property String^ FullName
		{
			virtual String^ get();
		}
	
		property ObservableCollection<IHierarchicalProxy^>^ Items
		{
			virtual ObservableCollection<IHierarchicalProxy^>^ get();
		}

		void AddItem(IHierarchicalProxy^ item);

		IHierarchicalProxy^ GetChild(String^ name);
	private:
		String^ mName;
		FolderProxy^ mParent;
		ObservableCollection<IHierarchicalProxy^>^ mChildren;
	};

	public ref class PaletteItemProxy : public Common::ProxyObject, public IHierarchicalProxy
	{
	public:
		PaletteItemProxy(String^ name);

		property String^ Name
		{
			virtual String^ get();
			virtual void set(String^ value);
		}

		property IHierarchicalProxy^ Parent
		{
			virtual IHierarchicalProxy^ get();
			virtual void set(IHierarchicalProxy^ value);
		}

		property String^ FullName
		{
			virtual String^ get();
		}

	private:
		String^ mName;
		IHierarchicalProxy^ mParent;
	};
}
}