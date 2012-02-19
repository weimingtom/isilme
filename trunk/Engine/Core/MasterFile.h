#ifndef ISILME_CORE_MASTERFILE_H
#define ISILME_CORE_MASTERFILE_H

#include "Definitions.h"
#include "Engine/Quest/Quests.h"

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
	CategoryPtr	GetCategoryAt(int index);
private:
	typedef std::map<std::string, CategoryPtr> CategoryMap;

	/// Categories
	CategoryMap mCategories;
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