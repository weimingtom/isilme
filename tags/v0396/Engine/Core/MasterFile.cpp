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
