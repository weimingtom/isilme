#include "IsilmePCH.h"
#include "MasterFile.h"

MasterFile::MasterFile()
{

}

MasterFile::~MasterFile()
{

}

void MasterFile::AddCategory( CategoryPtr ctg )
{
	mCategoriesMap[ctg->GetName()] = ctg;
	mCategories.push_back(ctg);
}

CategoryPtr MasterFile::GetCategory( std::string id )
{
	CategoryMap::iterator it = mCategoriesMap.find(id);
	if (it != mCategoriesMap.end())
		return it->second;
	return CategoryPtr();
}

int MasterFile::GetSize()
{
	return mCategoriesMap.size();
}

CategoryPtr MasterFile::GetCategoryAt( int index ) const
{
	CategoryList::const_iterator it = mCategories.cbegin() + index;

	return *it;
}

std::string Category::GetName()
{
	return mName;
}

Category::Category( std::string name )
{
	mName = name;
}

void Category::Clear()
{
	mEntries.clear();
}

void Category::Remove( EntryPtr entry )
{
	EntryVector::iterator it = std::find(mEntries.begin(), mEntries.end(), entry);
	if (it != mEntries.end())
		mEntries.erase(it);
}

void Category::Add( EntryPtr entry )
{
	mEntries.push_back(entry);
}

EntryPtr Category::GetEntry( int index )
{
	return mEntries.at(index);
}

int Category::GetSize()
{
	return mEntries.size();
}

Entry::Entry(std::string fileName)
{
	mFilename = fileName;
}

Entry::~Entry()
{

}

std::string Entry::GetFileName()
{
	return mFilename;
}

void Entry::SetFileName( std::string value )
{
	mFilename = value;
}
