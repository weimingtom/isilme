//  Copyright (C) 2010-2012 Alexander Alimov
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
#ifndef ISILME_CORE_MASTERFILE_H
#define ISILME_CORE_MASTERFILE_H

#include "../Definitions.h"
#include "../Story/Quests.h"

class ISILME_API MasterFile
{
public:
	MasterFile();
	virtual ~MasterFile();

	/// Adds category to master-file
	void AddCategory( CategoryPtr ctg );

	/// Gets category by id
	CategoryPtr GetCategory(std::string id);

	/// Gets count of categories
	int GetSize();

	/// Gets category by index
	CategoryPtr	GetCategoryAt(int index) const;
private:
	typedef std::map<std::string, CategoryPtr> CategoryMap;
	typedef std::vector<CategoryPtr> CategoryList;

	/// Categories
	CategoryMap mCategoriesMap;
	CategoryList mCategories;
};

/// @class Category
/// Container for similar entries 
class ISILME_API Category
{
public:
	Category(std::string name);

	/// Gets category name
	std::string GetName();

	/// Gets count of entries
	int GetSize();

	/// Gets Entry by index
	EntryPtr GetEntry(int index);

	template <class T>
	boost::shared_ptr<T> GetEntry(int index);

	/// Adds entry to category
	void Add(EntryPtr entry);

	/// Delete all entries
	void Clear();

	/// Remove entry
	void Remove(EntryPtr entry);

private:
	typedef std::vector<EntryPtr> EntryVector;
	/// List of all entries
	EntryVector mEntries;

	/// Category name
	std::string mName;
};

template <class T>
boost::shared_ptr<T> Category::GetEntry( int index )
{
	return boost::shared_dynamic_cast<T>(GetEntry(index));
}

/// @class Entry
/// Base class for all masterfile entries
class ISILME_API Entry
{
public:
	Entry(std::string fileName);
	virtual ~Entry();

	/// Gets name of file with entry definition
	std::string GetFileName();

	/// Sets file name
	void SetFileName(std::string value);
private:
	/// Filename
	std::string mFilename;
};

/// @class ScriptEntry
/// 
class ScriptEntry : public Entry
{
public:
};

template <typename T>
class ContainerEntry : public Entry
{
public:
	typedef boost::shared_ptr<T> TPtr;

	ContainerEntry(std::string filename) : Entry(filename) {}

	TPtr data;
};

typedef ContainerEntry<Level> LevelEntry;
typedef ContainerEntry<story::Story> StoryEntry;
typedef ContainerEntry<story::Conversation> ConversationEntry;

#endif