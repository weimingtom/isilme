#include "Stdafx.h"
#include "ScriptFileProxy.h"
#include <fstream>

namespace LevelEditor
{
	namespace Proxy
	{
		Common::IProxyObject^ ScriptDataToProxyConverter::Convert( SharedCLIPtr<Entry>* entry )
		{
			boost::shared_ptr<EditableScriptEntry> e = boost::shared_dynamic_cast<EditableScriptEntry>(entry->Value);

			if (e)
			{
				Common::ProxyObject^ proxy = gcnew ScriptFileProxy(e->Source.c_str());
				return proxy;
			}

			return nullptr;
		}


		ScriptFileProxy::ScriptFileProxy( const char* text )
		{
			mText = gcnew String(text);
		}

		String^ ScriptFileProxy::Text::get()
		{
			return mText;
		}

		void ScriptFileProxy::Text::set(String^ value)
		{
			mText = value;
		}
	}
}

EntryPtr serialisation::EditableScirptLoader::LoadEntry( std::string filename )
{
	EditableScriptEntry* entry = new EditableScriptEntry(filename);

	std::ifstream ifs(filename);

	std::string str((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());

	entry->Source = str;

	//FILE* file = fopen(filename.c_str(), "r");

	//unsigned int length = ftell(file);
	//char* buf = new char[length + 2];
	//fread(buf, 1, length, file);
	//entry->Source = buf;
	//delete[]buf;
	//fclose(file);
	return EntryPtr(entry);
}

EditableScriptEntry::EditableScriptEntry( std::string filename ) :
	Entry(filename)
{

}
