#include "Stdafx.h"
#include "FolderProxy.h"

namespace LevelEditor
{
	namespace Proxy
	{
	
		FolderProxy::FolderProxy()
		{
			mChildren = gcnew ObservableCollection<IHierarchicalProxy^>();
		}

		FolderProxy::FolderProxy( String^ name )
		{
			mName = name;
			mChildren = gcnew ObservableCollection<IHierarchicalProxy^>();
		}

		FolderProxy::~FolderProxy()
		{

		}

		String^ FolderProxy::Name::get()
		{
			return mName;
		}

		void FolderProxy::Name::set(String^ value)
		{
			mName = value;
		}

		String^ FolderProxy::FullName::get()
		{
			if (Parent == nullptr)
				return Name;
			else if (Parent->FullName == "")
				return Name;
			else
				return Parent->FullName + "/" + Name;
		}

		IHierarchicalProxy^ FolderProxy::Parent::get()
		{
			return mParent;
		}

		void FolderProxy::Parent::set(IHierarchicalProxy^ value)
		{
			mParent = (FolderProxy^)value;
		}

		IHierarchicalProxy^ FolderProxy::GetChild(String^ name)
		{
			for each (IHierarchicalProxy^ child in mChildren)
				if (child->Name == name)
					return child;

			return nullptr;
		}

		ObservableCollection<IHierarchicalProxy^>^ FolderProxy::Items::get()
		{
			return mChildren;
		}

		void FolderProxy::AddItem(IHierarchicalProxy^ item)
		{
			mChildren->Add(item);
			item->Parent = this;
		}

		PaletteItemProxy::PaletteItemProxy( String^ name )
		{
			mName = name;
		}

		String^ PaletteItemProxy::Name::get()
		{
			return mName;
		}

		void PaletteItemProxy::Name::set(String^ value)
		{
			mName = value;
		}

		String^ PaletteItemProxy::FullName::get()
		{
			if (Parent == nullptr)
				return Name;
			else if (Parent->FullName == "")
				return Name;
			else
				return Parent->FullName + "/" + Name;
		}

		IHierarchicalProxy^ PaletteItemProxy::Parent::get()
		{
			return mParent;
		}

		void PaletteItemProxy::Parent::set(IHierarchicalProxy^ value)
		{
			mParent = value;
		}
	}
}